#pragma once
#include "BlockContainer.hpp"
#include "../utils/Color.hpp"
#include "../utils/Vector3D.hpp"
#include <SFML/Network.hpp>

#include <random>
#include <map>



/**
 * @brief Shape is a container with a define position and blocks placed relative to this main position. 
 */
class Shape {
    public:
        using Value_t = BlockContainer::Value_t;
        using Relative_t = BlockContainer::Relative_t;
        using Absolute_t = BlockContainer::Absolute_t;

        using Container_t = std::map<Vector3D<Relative_t>,Value_t>;
    
    private:   
        Container_t m_data;
        Vector3D<Absolute_t> m_pos;
        
    public:
        // Enums

        /**
         * @brief Rotation direction. L for Left, R for Right
         */
        enum ROTATION_DIRECTION {L=1,R=-1};

        enum ROTATION_AXIS {X,Y,Z};

        /**
         * @brief Constructor for an empty shape at a define position
         * @param  position : Shape Position
         */
        explicit Shape(Vector3D<Absolute_t>); 

        /**
         * @brief Constructor for shape with relative position of blocks and define position
         * @param position : Shape Position
         * @param cont : Relative position of each Blocks from the Shape Position
         */
        Shape (Vector3D<Absolute_t> , Container_t);


        Shape(const Shape&) = default;
        ~Shape();
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

        /**
         * @brief Translate the shape by the specified vector.
         * @param vec : Vector representing the translation
         * @attention Doesn't check if the shape can be translated as requested.
         */
        void translate(const Vector3D<Relative_t>&);
        
        /**
         * @brief Check if the translation of the shape by a given vector is feasible.
         * @param  vec : Vector representing the translation
         * @param  cont : BlockContainer representing all blocks in the shape environement
         * @param  size : Size of the BlockContainer 
         * @return boolean, true if the translation can be performed.
         */
        bool canTranslate(const Vector3D<Relative_t>&,const BlockContainer& , const Vector3D<Relative_t>&);

        /**
         * @brief Rotate the shape around a specified axis of 90° in the specified direction
         * @param ax : Rotation axis 
         * @param dir : Direction (Left or Right)
         * @attention Doesn't check if the shape can be rotated as requested.
         */
        void rotate(ROTATION_AXIS,ROTATION_DIRECTION);

        
        /**
         * @brief Check if the rotation  of the shape around a specified axis of 90° in the specified direction is feasible.
         * @param ax : Rotation axis 
         * @param dir : Direction (Left or Right) 
         * @param  cont : BlockContainer representing all blocks in the shape environement
         * @param  size : Size of the BlockContainer 
         * @return boolean, true if the rotation can be performed.
         */
        bool canRotate(ROTATION_AXIS&, ROTATION_DIRECTION&, const BlockContainer&, const Vector3D<Relative_t>&) ;

        /**
         * @brief Check if a position is already occupied by a Tetris Block
         * @param pos : Absolute Position in the grid
         * @return boolean, true if it is already occupied
         */
        bool isOccupied(const Vector3D<Absolute_t>&) const;

        /**
         * @brief Generate a random Shape
         * @param size : Main Grid size
         * @return Random shape with random position positioned at the top of the grid.
         * @attention A grid size is considered as 2D (with only 2D shapes generated) if the Y coordinate of size is equal to one.
         */
        static Shape getRandomShape(Vector3D<BlockContainer::Absolute_t>);

        /**
         * @brief Getter for Shape Position
         * @return Shape Position 
         */
        inline Vector3D<Absolute_t> getPosition() const {
            return m_pos;
        }

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
         * @param shape : Shape to be added to the packet.
         * @return Updated SFML Packet with data of the Shape append to it.
         */
        friend sf::Packet& operator<< (sf::Packet&, const Shape&);

        /**
         * @brief Compatibility with SFML Networking. 
         * @param pack : An SFML packet with a Shape to be extracted. 
         * @param shape : extacted Shape from the Packet
         * @return Updated SFML Packet without the data of the Shape.
         */
        friend sf::Packet& operator >>(sf::Packet&, Shape&);
        
};

