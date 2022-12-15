#pragma once
#include "BlockContainer.hpp"
#include "../utils/Vector.hpp"
#include "../utils/Color.hpp"

#include <random>
#include <array>
#include <map>
//#template<unsigned n>
class Shape {
    using Value_t = BlockContainer::Value_t;
    using Container_t = BlockContainer::Container_t;
    
    private:   
        Container_t m_data;
        Vector m_pos;
        
    public:
        // Enums
        enum ROTATION_DIRECTION {L=1,R=-1};
        enum ROTATION_AXIS {X,Y,Z};

        // Constructors
        Shape();
        Shape(Vector); 
        Shape (Vector, Container_t);
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
        BlockContainer toBlockContainer(const Vector& translation) const {
            Container_t map;
            for (auto const& [key,value] : m_data) {
                map.insert(std::make_pair(getAbsolutePosition(key+translation),value));
            }
            return BlockContainer(map);
        }

        /**
         * @brief All coordinates stored inside Shape are relative to the main position of the shape. 
         * This function convert the relative position of a Block composing the shape to his absolute position. 
         * @param relPos The relative position stored inside the Shape Object
         * @return Absolute position of the Block
         */
        Vector getAbsolutePosition(const Vector& relPos) const {
            return relPos + m_pos;
        }

        void translate(const Vector&);

        bool canTranslate(const Vector& translation,const BlockContainer& blocks, const Vector& gridSize) {
            //bool b = true;
            for (auto const& [key, value] : (BlockContainer) *this) {
                Vector translated = key + translation;
                if (!((translated.x >= 0 && translated.x < gridSize.x) && (translated.y >= 0 && translated.y < gridSize.y) && (translated.z >= 0))) {
                    return false;
                }
            }
            return ! (this->toBlockContainer(translation).isCollidingWith(blocks));
        }

        void rotate(ROTATION_AXIS,ROTATION_DIRECTION);

        bool canRotate(ROTATION_AXIS& ax, ROTATION_DIRECTION& dir, const BlockContainer& blocks, const Vector& gridSize) {
            Shape cpy = *this;
            cpy.rotate(ax,dir);
            BlockContainer cont = (BlockContainer) cpy;
            for (auto const& [key, value] : cont) {
                //Vector translated = key + translation;
                if (!((key.x >= 0 && key.x < gridSize.x) && (key.y >= 0 && key.y < gridSize.y) && (key.z >= 0))) {
                    return false;
                }
            }
            return !blocks.isCollidingWith(cont);
        }

        bool isOccupied(const Vector& pos) const {
            return ((BlockContainer) *this).isOccupied(pos);   
        }

        static Shape getRandomShape(std::mt19937 yo, Vector gridSize) {

            std::random_device rd;
            std::mt19937 gen(rd());
            Container_t map;
            /*map.insert(std::make_pair(Vector(0,0,0),Color(1,0,0)));
            return Shape(Vector(0,2,10),map);*/ 
            
            std::uniform_int_distribution<char> typeDistrib(0,6);
            std::uniform_int_distribution<char> nbRotDistrib(0,3);

            Color c;
            switch (typeDistrib(gen)) {
                case 0: // Bar
                    c = Color(0.1,0.91,0.95);
                    map.insert(std::make_pair(Vector(2,0,0),c));
                    map.insert(std::make_pair(Vector(1,0,0),c));
                    map.insert(std::make_pair(Vector(0,0,0),c));
                    map.insert(std::make_pair(Vector(-1,0,0),c));
                    break;
                case 1: // T
                    c = Color(0.66,0.1,0.95);
                    map.insert(std::make_pair(Vector(0,0,1),c));
                    map.insert(std::make_pair(Vector(1,0,0),c));             
                    map.insert(std::make_pair(Vector(0,0,0),c));
                    map.insert(std::make_pair(Vector(-1,0,0),c));
                    break;
                case 2: // -_
                    map.insert(std::make_pair(Vector(1,0,1),Color(0,0,1)));
                    map.insert(std::make_pair(Vector(0,0,1),Color(0,0,1)));
                    map.insert(std::make_pair(Vector(0,0,0),Color(0,0,1)));
                    map.insert(std::make_pair(Vector(-1,0,0),Color(0,0,1)));
                    break;
                case 3: // TODO -_
                    map.insert(std::make_pair(Vector(1,0,1),Color(0,0,1)));
                    map.insert(std::make_pair(Vector(0,0,1),Color(0,0,1)));
                    map.insert(std::make_pair(Vector(0,0,0),Color(0,0,1)));
                    map.insert(std::make_pair(Vector(1,0,0),Color(0,0,1)));
                    break;
                case 4: // L
                    c = Color(0.95,0.55,0.10);
                    map.insert(std::make_pair(Vector(2,0,0),c));
                    map.insert(std::make_pair(Vector(1,0,0),c));
                    map.insert(std::make_pair(Vector(0,0,0),c));
                    map.insert(std::make_pair(Vector(0,0,1),c));
                    break;
                case 5: // L inv 
                    c = Color(1,0,0);
                    map.insert(std::make_pair(Vector(2,0,0),c));
                    map.insert(std::make_pair(Vector(1,0,0),c));
                    map.insert(std::make_pair(Vector(0,0,0),c));
                    map.insert(std::make_pair(Vector(0,0,-1),c));
                    break;
                case 6: // Cube
                    c = Color(0.95,0.83,0.1);
                    map.insert(std::make_pair(Vector(1,0,1),c));
                    map.insert(std::make_pair(Vector(1,0,0),c));
                    map.insert(std::make_pair(Vector(0,0,1),c));
                    map.insert(std::make_pair(Vector(0,0,0),c));
                    break;

    
                default:
                    break;
            }
            
            Shape s(Vector(floor(gridSize.x/2),floor(gridSize.y/2),gridSize.z+4), map);
            
            for (ROTATION_AXIS ax :  {ROTATION_AXIS::X,ROTATION_AXIS::Y,ROTATION_AXIS::Z}) {
                char nbRot = nbRotDistrib(gen);
                for (char i = 0; i < nbRot; i++) {
                    s.rotate(ax,ROTATION_DIRECTION::L);
                }
                
            }

            return s;
        }

        
};
