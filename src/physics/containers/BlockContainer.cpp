#include "BlockContainer.hpp"

// Constructeurs
BlockContainer::BlockContainer() : m_data(BlockContainer::Container_t()){}
BlockContainer::BlockContainer(BlockContainer::Container_t map) : m_data(map) {}
BlockContainer::~BlockContainer() {}

// Iterators
BlockContainer::iterator BlockContainer::begin() {
    return m_data.begin();
}

BlockContainer::iterator BlockContainer::end() {
    return m_data.end();
}

// Const iterators
BlockContainer::const_iterator BlockContainer::begin() const { 
    return m_data.begin();
}

BlockContainer::const_iterator BlockContainer::end() const { 
    return m_data.end();
}

BlockContainer::const_iterator BlockContainer::cbegin() const {
    return m_data.cbegin();
}

BlockContainer::const_iterator BlockContainer::cend() const {
    return m_data.cend();
}

void BlockContainer::append(const BlockContainer& cont) {
    for (auto const& [vec, col] : cont) {
        m_data.insert(std::make_pair(vec,col));
    }
}


bool BlockContainer::isOccupied(const Vector& pos) const {
    for (auto const& [vec,col] : *this) {
        if (pos == vec) {
            return true;
        }
    }
    return false;
}

bool BlockContainer::isCollidingWith(const BlockContainer& cont) const {
    for (auto const& [vec, col] : *this) {
        if(cont.isOccupied(vec)) {
            return true;
        } 
    }
    return false;
    
}