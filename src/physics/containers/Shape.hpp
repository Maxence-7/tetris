#pragma once
#include "BlockContainer.hpp"
#include "../utils/Vector.hpp"
#include <array>

//#template<unsigned n>
class Shape : public BlockContainer {
    private:
        Vector m_pos;
        
    public:
        enum ROTATION_DIRECTION {L=1,R=-1};
        enum ROTATION_AXIS {X,Y,Z};

        Shape(/* args */);
        ~Shape();

        BlockContainer getAbsolutePosition() {
            BlockContainer::Container_t map;
            for (auto const& [key,value] : m_data) {
                map.insert(std::make_pair(getAbsolutePosition(key),value));
            }
            return BlockContainer(map);
        }

        Vector getAbsolutePosition(const Vector& relPos) const {
            return relPos + m_pos;
        }

        void translate(const Vector& translation, bool (*func)(const Vector&)) {
            //BlockContainer::Container_t copy;
            for (auto const& [key,value] : m_data) {
                const Vector translated = getAbsolutePosition(key)+translation;
                if (!func(translated)) return;
            }
            translate(translation);
        }

        void translate(const Vector& translation) {
            m_pos = m_pos + translation;
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
            while (!container.isCollidingWith(*this)) {
                translate(Vector(0,0,-1));
            }

        }

        

        
};
