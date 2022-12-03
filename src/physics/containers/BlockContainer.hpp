#pragma once
#include "../utils/Vector.hpp"
#include "../utils/Color.hpp"

#include <map>

class BlockContainer {
    
    public:
        using Key_t = Vector;
        using Value_t = Color;  
        using Container_t = std::map<Vector,Value_t>;
    protected:
        Container_t m_data;
    public:
        BlockContainer(/* args */);
        BlockContainer(Container_t data) : m_data(data) {};
        
        BlockContainer(const BlockContainer&) = default;

        ~BlockContainer();

        void move(const Vector& posBef, const Vector& posAft) {
            if (isOccupied(posBef)) m_data.try_emplace(posAft,m_data.at(posBef));
        }
        
        void erase(const Vector& pos) {
            m_data.erase(pos);
        }

        bool isOccupied(const Vector& pos) const {
            return m_data.contains(pos);
        }

        bool isCollidingWith(const BlockContainer& other) const {
            if (m_data.size() > other.m_data.size()) {
                return other.isCollidingWith(*this);    
            }
            
            for (auto const& [key,val] : m_data) {
                if(other.isOccupied(key)) return false;
            }
            return true;
        }
};