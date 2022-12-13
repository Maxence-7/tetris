#pragma once
#include "BlockContainer.hpp"
#include "../utils/Vector.hpp"
#include "../utils/Color.hpp"

#include <random>
#include <array>
#include <map>
//#template<unsigned n>
class Shape {
    private:
        using Value_t = BlockContainer::Value_t;
        using Container_t = BlockContainer::Container_t;
        Container_t m_data;
        Vector m_pos;
        
    public:
        enum ROTATION_DIRECTION {L=1,R=-1};
        enum ROTATION_AXIS {X,Y,Z};

        // Constructors
        Shape() : m_pos(Vector(0,0,0)) {}
        Shape(Vector pos) : m_pos(pos) {}
        Shape (Vector pos, Container_t data) : m_pos(pos), m_data(data) {};
        ~Shape() {}
        

        /**
         * @brief Convert a Shape Object to BlockContainer
         * @return The BlockContainer object
         */
        BlockContainer toBlockContainer() const {
            Container_t map;
            for (auto const& [key,value] : m_data) {
                map.insert(std::make_pair(getAbsolutePosition(key),value));
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

        bool canTranslate(const Vector& translation, BlockContainer blocks) {
            for (auto const& [key,value] : m_data) {
                const Vector translated = getAbsolutePosition(key)+translation;
                if (blocks.isOccupied(translated) || !blocks.isValidPosition(translated)) return false;
            }
            return true;
        }

        void translate(const Vector& translation) {
            m_pos = m_pos + translation;
        }

        bool isInContainer(const BlockContainer& cont) {
            for (auto const& [key,value] : m_data) {
                if(!cont.isInContainer(getAbsolutePosition(key))) return false;
            }
            return true;
        }

        

        void rotate(ROTATION_AXIS ax, ROTATION_DIRECTION r,bool (*func) (const Vector&)) {
            BlockContainer::Container_t copy;
            for (const auto& [key, value] : m_data) {
                Vector newKey;
                switch (ax) {
                    case ROTATION_AXIS::X:
                        newKey.x = key.x;
                        newKey.y = -((Vector::Coordinate_t) r)*key.z;
                        newKey.z = ((Vector::Coordinate_t) r)*key.y;
                        break;
                    case ROTATION_AXIS::Y:
                        newKey.x = ((Vector::Coordinate_t) r)*key.z;
                        newKey.y = key.y;
                        newKey.z = -((Vector::Coordinate_t) r)*key.x;
                        break;
                    case ROTATION_AXIS::Z:
                        newKey.x = -((Vector::Coordinate_t) r)*key.y;
                        newKey.y = ((Vector::Coordinate_t) r)*key.x;
                        newKey.z = key.z;
                        break;
                }
                if(!func(getAbsolutePosition(newKey))) return;
                copy.insert(std::make_pair(newKey,value));
            }

            m_data = copy;
        }

        void rotate(ROTATION_AXIS ax, ROTATION_DIRECTION r) {
            rotate(ax,r,[](const Vector&) {return true;});
        }

        void dropUntilHit(const BlockContainer& container) {
            //Vector t (0,0,-1);
            while (!container.isCollidingWith(this->toBlockContainer())) {
                translate(Vector(0,0,-1));
            }

        }

        bool isOccupied(const Vector& pos) const {
            Vector relative = pos-m_pos;
            return m_data.contains(relative);   
        }

        static Shape getRandomShape(std::mt19937 gen, Vector gridSize) {
            Container_t map;
            map.insert(std::make_pair(Vector(0,0,0),Color(1,0,0)));
            return Shape(Vector(0,2,10),map); 
            std::uniform_int_distribution<char> typeDistrib(0,6);
            switch (typeDistrib(gen)) {
                case 0: // Bar
                    map.insert(std::make_pair(Vector(2,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(1,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(0,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(-1,0,0),Color(1,0,0)));
                    break;
                case 1: // T
                    map.insert(std::make_pair(Vector(0,0,1),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(1,0,0),Color(1,0,0)));             
                    map.insert(std::make_pair(Vector(0,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(-1,0,0),Color(1,0,0)));
                    break;
                case 2: // -_
                    map.insert(std::make_pair(Vector(1,0,1),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(0,0,1),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(0,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(-1,0,0),Color(1,0,0)));
                    break;
                case 3: // TODO -_
                    map.insert(std::make_pair(Vector(1,0,1),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(0,0,1),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(0,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(1,0,0),Color(1,0,0)));
                    break;
                case 4: // L
                    map.insert(std::make_pair(Vector(2,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(1,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(0,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(0,0,1),Color(1,0,0)));
                    break;
                case 5: // L inv 
                    map.insert(std::make_pair(Vector(2,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(1,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(0,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(0,0,-1),Color(1,0,0)));
                    break;
                case 6: // Cube
                    map.insert(std::make_pair(Vector(1,0,1),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(1,0,0),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(0,0,1),Color(1,0,0)));
                    map.insert(std::make_pair(Vector(0,0,0),Color(1,0,0)));
                    break;

    
                default:
                    break;
            }
        }

        
};
