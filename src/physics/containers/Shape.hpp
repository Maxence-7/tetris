#pragma once
#include "BlockContainer.hpp"
#include "../utils/Color.hpp"
#include "../utils/Vector3D.hpp"
#include <SFML/Network.hpp>

#include <random>
#include <map>
//#template<unsigned n>
class Shape {
    public:
        using Value_t = BlockContainer::Value_t;
        using Relative_t = BlockContainer::Relative_t;
        using Absolute_t = BlockContainer::Absolute_t;

        using Container_t = std::map<Vector3D<Relative_t>,Value_t>;
        friend class sf::Packet;
    
    private:   
        Container_t m_data;
        Vector3D<Absolute_t> m_pos;
        
    public:
        // Enums
        enum ROTATION_DIRECTION {L=1,R=-1};
        enum ROTATION_AXIS {X,Y,Z};

        // Constructors
        explicit Shape(Vector3D<Absolute_t> ); 
        Shape (Vector3D<Absolute_t> , Container_t);
        Shape(const Shape&) = default;
        ~Shape();

        //Shape operator =(const Shape&);
        operator BlockContainer() const;


        //Methods
        /**
         * @brief Convert a Shape Object to BlockContainer
         * @return The BlockContainer object
         */
        BlockContainer toBlockContainer() const {
            return (BlockContainer) *this;
        }

        /**
         * @brief Convert a Shape Object to BlockContainer
         * @return The BlockContainer object
         */
        BlockContainer toBlockContainer(const Vector3D<Relative_t>& translation) const {
           BlockContainer::Container_t map;
            for (auto const& [key,value] : m_data) {
                map.insert(std::make_pair(getAbsolutePosition(Vector3D<Relative_t>(key)+translation),value));
            }
            return BlockContainer(map);
        }

        /**
         * @brief All coordinates stored inside Shape are relative to the main position of the shape. 
         * This function convert the relative position of a Block composing the shape to his absolute position. 
         * @param relPos The relative position stored inside the Shape Object
         * @return Absolute position of the Block
         */
        inline Vector3D<Absolute_t> getAbsolutePosition(const Vector3D<Relative_t>& relPos) const  {
            return Vector3D<Shape::Absolute_t>(relPos + Vector3D<Shape::Relative_t>(this->m_pos));
        }

        void translate(const Vector3D<Relative_t>&);
        
        bool canTranslate(const Vector3D<Relative_t>&,const BlockContainer& , const Vector3D<Relative_t>&);

        void rotate(ROTATION_AXIS,ROTATION_DIRECTION);

        bool canRotate(ROTATION_AXIS&, ROTATION_DIRECTION&, const BlockContainer&, const Vector3D<Relative_t>&) ;

        bool isOccupied(const Vector3D<Absolute_t>&) const;

        static Shape getRandomShape(Vector3D<BlockContainer::Absolute_t>);

        inline Vector3D<Absolute_t> getPosition() const {
            return m_pos;
        }

        inline size_t size() const {
            return m_data.size();
        }
    
        
};

inline sf::Packet& operator<< (sf::Packet& packet, const Shape& shape)
{
    Vector3D<Shape::Absolute_t> pos = shape.getPosition();
    packet << pos;
    packet << (unsigned) shape.size();
    for (auto const &[key, value] : (BlockContainer) shape) {
        packet << Vector3D<Shape::Relative_t>(pos)-Vector3D<Shape::Relative_t>(key) << value;
    }
    
    return packet;
}


inline sf::Packet& operator >>(sf::Packet& packet, Shape& shape)
{
    Vector3D<Shape::Absolute_t> pos = shape.getPosition();
    packet >> pos;
    unsigned tmp;
    packet >> tmp;
    size_t size = (size_t) tmp;
    Shape::Container_t container;
    Vector3D<Shape::Relative_t> key;
    Color value;
    for (size_t i = 0; i < size; i++) {
        packet >> key >> value;
        container.insert(std::make_pair(key,value));
    }
    shape = Shape(pos,container);
    return packet;
}
