#pragma once
#include "../utils/Vector3D.hpp"
#include "../utils/Color.hpp"
#include <SFML/Network.hpp>

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
        friend class sf::Packet;

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

        /**
         * @brief Concatenate two BlockContainers. In case of overlapping between the two containers, the call
         * @param  container 
         * @return boolean, true if there is a block at this position
         */
        void append(const BlockContainer&);
        
        /**
         * @brief Check if there is a block at position
         * @param  position to be checked
         * @return boolean, true if there is a block at this position
         */
        bool isOccupied(const Vector3D<Absolute_t>&) const;

        /**
         * @brief Check if there some overlapping between two Blockcontainers
         * @param  container : An other BlockContainer
         * @return boolean, true if there is some overlapping, false if not.
         */
        bool isCollidingWith(const BlockContainer& other) const;

        /**
         * @brief Return the number of blocks
         * @return Number of blocks using std::map::size_t type 
         */
        inline size_t size() const {
            return m_data.size();
        }

        
        /**
         * @brief Compatibility with SFML Networking. 
         * @param pack : An SFML packet 
         * @param container : BlockContainer to be added to the packet.
         * @return Updated SFML Packet with data of the BlockContainer append to it.
         */
        friend sf::Packet& operator << (sf::Packet&, const BlockContainer&);

        /**
         * @brief Compatibility with SFML Networking. 
         * @param pack : An SFML packet with a BlockContainer to be extracted. 
         * @param container : extacted BlockContainer from the Packet
         * @return Updated SFML Packet without the data of the BlockContainer.
         */
        friend sf::Packet& operator >> (sf::Packet&, BlockContainer&);
        
};
