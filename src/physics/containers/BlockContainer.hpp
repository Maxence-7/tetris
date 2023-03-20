#pragma once
#include "../utils/Vector3D.hpp"
#include "../utils/Color.hpp"

#include <map>
#include <iostream>

class BlockContainer {
    
    public:
        using Relative_t = int;
        using Absolute_t = unsigned;
        using Value_t = Color;  
        using Container_t = std::map<Vector3D<Absolute_t>,Value_t>;
        

        using iterator  = Container_t::iterator;
        using const_iterator = Container_t::const_iterator;

    protected:
        Container_t m_data;
    public:
        // Constructors
        BlockContainer();
        BlockContainer(Container_t);
        BlockContainer(const BlockContainer&) = default;
        ~BlockContainer(); 
        
        
        // Iterators
        iterator begin();
        iterator end();
        
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;


        // Methods
        void append(const BlockContainer&);
        
        bool isOccupied(const Vector3D<Absolute_t>&) const;
        bool isCollidingWith(const BlockContainer& other) const;

        

        

        
};
