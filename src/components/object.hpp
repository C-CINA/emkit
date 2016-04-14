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
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <iostream>
#include <memory>

#include "container.hpp"
#include "object_properties.hpp"
#include "representation.hpp"


namespace em
{
    template<class value_t>
    class Object
    {
    public:
        
        const ObjectProperties& properties() const
        {
            return _properties;
        };
        
        ObjectProperties& properties()
        {
            return _properties;
        };
        
    protected:
        ObjectProperties _properties;
    };
}

#endif /* OBJECT_HPP */
