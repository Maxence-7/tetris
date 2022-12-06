#pragma once
#include "../utils/Vector.hpp"
#include "../utils/Color.hpp"

#include <map>

class BlockContainer {
    
    public:
        using Value_t = Color;  
        using Container_t = std::map<Vector,Value_t>;
    protected:
        Vector m_size;
        Container_t m_data;
    public:
        BlockContainer(Vector size) : m_size(size) {}
        explicit BlockContainer(Container_t data) : m_data(data) {};
        
        BlockContainer(const BlockContainer&) = default;

        ~BlockContainer() {}

        void append(const BlockContainer& cont) {
            m_data.insert(cont.m_data.begin(),cont.m_data.end());
        }

        bool isValidPosition(const Vector& pos) const {
            return (pos.x >= 0 && pos.x < m_size.x) && (pos.y >= 0 && pos.y < m_size.y) && (pos.z >= 0);
        }

        bool isInContainer(const Vector& pos) const {
            
            return isValidPosition(pos) && pos.z < m_size.z;
        }

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

class PositionOccupiedException : public std::exception {
    public:
        char* what() {
            return "B";
        }
};

class PositionUnOccupiedException : public std::exception {
    public:
        char* what() {
            return "A";
        }
};