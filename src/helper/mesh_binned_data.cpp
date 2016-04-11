/* 
 * Author: Nikhil Biyani - nikhil(dot)biyani(at)gmail(dot)com
 *
 * This file is a part of 2dx.
 * 
 * 2dx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or any 
 * later version.
 * 
 * 2dx is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public 
 * License for more details <http://www.gnu.org/licenses/>.
 */


#include "file.hpp"

#include "mesh_binned_data.hpp"


using namespace em;

MeshBinnedData::MeshBinnedData(double min_x, double max_x, double min_y, double max_y, int bins_x, int bins_y)
{
    _min_x = min_x;
    _max_x = max_x;
    _min_y = min_y;
    _max_y = max_y;
    _bins_x = bins_x;
    _bins_y = bins_y;
    _data = (double*) calloc(_bins_x*_bins_y, sizeof(double));
    _counts = (int*) calloc(_bins_x*_bins_y, sizeof(int));
}

void MeshBinnedData::add_data_at(double x, double y, double value)
{
    //Find the appropriate bin
    if ( x <= max_x() && x >= min_x() && y <= max_y() && y >= min_y()) 
    {
        int bin_x = get_bin_x(x);
        int bin_y = get_bin_y(y);
        if(bin_x != -1 && bin_y !=-1)
        {   
            int bin = get_linear_bin(bin_x, bin_y);
            //std::cout << "x: " << x << " y: " << y << " falls in: " << bin_x << ", " << bin_y << " -> " << bin << " with value: " << value << "\n"; 
            _data[bin] += value;
            _counts[bin]++;
        }
    }
}

void MeshBinnedData::set_bin_sum(int bin_x, int bin_y, double sum)
{
    if(bin_x >=0 && bin_x < bins_x() && bin_y >=0 && bin_y < bins_y()) _data[get_linear_bin(bin_x, bin_y)] = sum;
    else std::cerr << "Warning: The bin provided exceeds limits.";
}

void MeshBinnedData::set_bin_count(int bin_x, int bin_y, int count)
{
    if(bin_x >=0 && bin_x < bins_x() && bin_y >=0 && bin_y < bins_y()) _counts[get_linear_bin(bin_x, bin_y)] = count;
    else std::cerr << "Warning: The bin provided exceeds limits.";
}

void MeshBinnedData::write_sum(std::string file) const
{
    write(file, false);
}

void MeshBinnedData::write_average(std::string file) const
{
    write(file, true);
}

void MeshBinnedData::write(std::string file, bool average) const
{
    em::File writeFile(file, em::File::OUTPUT);
    
    //Check for the existence of the file
    if(writeFile.exists())
    {
        std::cout << "WARNING: File.. " << file << " already exists. Overwriting!\n";
    }
    
    std::string output = "";
    output += "\n";
    if(average) output += "#Averaged ";
    else output += "#Summed ";
    output += "data in range: X direction (" + 
                std::to_string(min_x()) +
                ", " + std::to_string(max_x()) +
                ") and in Y direction (" + 
                std::to_string(min_y()) +
                ", " + std::to_string(max_y()) +
                ") spaced in X by " + std::to_string(spacing_x())+
                " and in Y by " + std::to_string(spacing_y()) + "\n\n";
    
    for(int bin_x=0; bin_x<bins_x(); bin_x++)
    {
        for(int bin_y=0; bin_y<bins_y(); bin_y++)
        {
            double x = min_x() + (bin_x)*spacing_x();
            double y = min_y() + (bin_y)*spacing_y();
            double data;
            if(average) data = average_in(bin_x, bin_y);
            else data = sum_in(bin_x, bin_y);
            output += std::to_string(x) + "\t" + std::to_string(y) + "\t" + std::to_string(data) + "\n";
        }
    }
    
    writeFile << output;
    writeFile.close();
}

double MeshBinnedData::sum_at(double x, double y) const
{   
    return sum_in(get_bin_x(x), get_bin_y(y));      
}

double MeshBinnedData::average_at(double x, double y) const
{   
    return average_in(get_bin_x(x), get_bin_y(y));       
}

double MeshBinnedData::sum_in(int bin_x, int bin_y) const
{
    if(bin_x >=0 && bin_x < bins_x() && bin_y >=0 && bin_y < bins_y())
        return _data[get_linear_bin(bin_x, bin_y)];
    else
        return -1.0;
}

double MeshBinnedData::average_in(int bin_x, int bin_y) const
{
    if(bin_x >=0 && bin_x < bins_x() && bin_y >=0 && bin_y < bins_y())
        if(_counts[get_linear_bin(bin_x, bin_y)] == 0) return 0.0;
        else return _data[get_linear_bin(bin_x, bin_y)]/_counts[get_linear_bin(bin_x, bin_y)];
    else
        return -1.0;
}

double MeshBinnedData::min_x() const
{
    return _min_x;
}

double MeshBinnedData::max_x() const
{
    return _max_x;
}

double MeshBinnedData::min_y() const
{
    return _min_y;
}

double MeshBinnedData::max_y() const
{
    return _max_y;
}

int MeshBinnedData::bins_x() const
{
    return _bins_x;
}

int MeshBinnedData::bins_y() const
{
    return _bins_y;
}

double MeshBinnedData::spacing_x() const
{
    return (max_x() - min_x())/(bins_x());
}

double MeshBinnedData::spacing_y() const
{
    return (max_y() - min_y())/(bins_y());
}

int MeshBinnedData::get_bin_x(double x) const
{
    int bin = floor((x-min_x())/spacing_x());
    if( bin>=0 && bin<bins_x() )
        return bin;
    else
        return -1;
}

int MeshBinnedData::get_bin_y(double y) const
{
    int bin = floor((y-min_y())/spacing_y());
    if( bin>=0 && bin<bins_y() )
        return bin;
    else
        return -1;
}

int MeshBinnedData::get_linear_bin(int bin_x, int bin_y) const
{
    return bin_y + bins_y() * bin_x;
}