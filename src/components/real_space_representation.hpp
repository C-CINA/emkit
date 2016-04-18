/* 
 * This file is a part of emkit.
 * 
 * emkit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or any 
 * later version.
 * 
 * emkit is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public 
 * License for more details <http://www.gnu.org/licenses/>
 * 
 * Author:
 * Nikhil Biyani: nikhil(dot)biyani(at)gmail(dot)com
 * 
 */

#ifndef REAL_SPACE_REPRESENTATION_HPP
#define REAL_SPACE_REPRESENTATION_HPP

#include <memory>

#include "../helper/tripet.hpp"

#include "type_recognizer.hpp"
#include "representation.hpp"


namespace em {

    class ReciprocalSpaceRepresentation;

    class RealSpaceRepresentation : public Representation {
    public:

        virtual value_t density_at(Triplet<int> v) const = 0;

        virtual void set_density_at(Triplet<int> v, value_t value) = 0;

        virtual size_t number_of_voxels() const = 0;

        virtual std::unique_ptr<ReciprocalSpaceRepresentation> get_fourier() const = 0;

    };
}

#endif /* REAL_SPACE_REPRESENTATION_HPP */

