#include "GameCore.hpp"

GameCore::GameCore(const Vector& size) : m_isPaused(false), m_tick(0), m_score(0),m_size(size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    m_gen = gen;
    m_curShape = Shape::getRandomShape(m_gen,size);
    m_nextShape = Shape::getRandomShape(m_gen,size);
    m_grid = BlockContainer();

}

GameCore::GameCore(const GameCore&) = default;
GameCore::~GameCore() {}


bool GameCore::isGameLose() const {
    for (auto const& [vec,col] : (BlockContainer) m_curShape) {
        if (vec.z >=  m_size.z) {
            return true;
        }   
    }
    return false;
}


// Getters
GameCore::State GameCore::getState() const {
    return m_state;
}

GameCore::Score_t GameCore::getScore() const {
    return m_score;
}

Vector GameCore::getSize() const {
    return m_size;
}