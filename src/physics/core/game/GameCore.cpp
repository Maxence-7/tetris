#include "GameCore.hpp"

// Constructors
GameCore::GameCore() : GameCore(GameCore::DEFAULT_SIZE) {}
GameCore::GameCore(const Size_t& size) : m_isPaused(false), m_score(0),m_size(size), m_curShape(Shape::getRandomShape(size)), m_nextShape(Shape::getRandomShape(size)) {
    m_grid = BlockContainer();

};

GameCore::GameCore(const GameCore&) = default;
GameCore::~GameCore() {}

// Constants 

const GameCore::Size_t GameCore::DEFAULT_SIZE(5,5,24);

// Methods

bool GameCore::isGameLose() const {
    for (auto const& [vec,col] : (BlockContainer) m_curShape) {
        if (vec.z >=  m_size.z) {
            return true;
        }   
    }
    return false;
}

void GameCore::togglePause()  {
    m_isPaused = !m_isPaused;
}


void GameCore::start() {
    if (!m_isLose && !m_alreadyStarted) {
        m_alreadyStarted = true;
        m_state = State::GENERATING_NEW_BLOCK;
        while (!m_isLose) {
            if (!m_isPaused) {
                switch (m_state) {
                    case GENERATING_NEW_BLOCK:
                        
                        onAwait();
                        m_state = State::MOVING_BLOCK;
                        break;
                    case MOVING_BLOCK:
                        if (m_curShape.canTranslate(Vector3D<Shape::Relative_t>(0,0,-1),m_grid,m_size)) {
                            m_curShape.translate(Vector3D<Shape::Relative_t>(0,0,-1));    
                        } else {
                            m_state = State::LOSE_CHECK;
                        }
                        break;
                    case LOSE_CHECK:
                        m_isLose = isGameLose();
                        if (m_isLose) {
                            std::cout << "LOSE" << std::endl;
                            return;
                        }
                        m_grid.append((BlockContainer) m_curShape);
                        m_state = State::CHECKING_COMPLETE_LINES;
                        break;

                    case CHECKING_COMPLETE_LINES:                    
                        m_indexesComplete.clear();

                        
                        for (size_t k = 0; k < m_size.z; k++) {
                            for (size_t i = 0; i < m_size.x; i++) {
                                for (size_t j = 0; j < m_size.y; j++) {
                                    if (!m_grid.isOccupied(Vector3D<BlockContainer::Absolute_t>(i,j,k)) && k < m_size.z) {
                                        i = 0;
                                        j = 0;
                                        k++;
                                    }
                                }
                                
                            }
                            if (k < m_size.z) m_indexesComplete.push_back(k);
                        }
                        
                        // Construit la grille après suppression 
                        BlockContainer::Container_t map;
                        if (m_indexesComplete.size() != 0) {
                            for (auto const& [vec, col] : m_grid) {
                                if (std::find(m_indexesComplete.begin(),m_indexesComplete.end(),vec.z) == m_indexesComplete.end()) {
                                    size_t diff = count_if(m_indexesComplete.begin(),m_indexesComplete.end(),[vec](unsigned val) {return val < vec.z;});
                                    map.insert(std::make_pair(Vector3D<BlockContainer::Absolute_t>(Vector3D<BlockContainer::Relative_t>(vec)-Vector3D<BlockContainer::Relative_t>(0,0,diff)),col));
                                }   
                            }

                            m_score = m_score + std::pow((Score_t) 2, m_indexesComplete.size());
                            m_grid = BlockContainer(map);
                        }
                        m_state = State::GENERATING_NEW_BLOCK;
                        break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(750));
            }
        }
    }
}


// Getters 
GameCore::Score_t GameCore::getScore() const {
    return m_score;
}

GameCore::Size_t GameCore::getSize() const {
    return m_size;
}


// Move methods
void GameCore::dropUntilHit()  {
    if(m_state == State::MOVING_BLOCK) {
        Vector3D<Shape::Relative_t> down(0,0,-1);
        while (m_curShape.canTranslate(down,m_grid,m_size)) {
            m_curShape.translate(down);
        }
        m_state = State::LOSE_CHECK;  
    }
}

void GameCore::rotate(Shape::ROTATION_AXIS ax, Shape::ROTATION_DIRECTION dir) {
    if(m_state == State::MOVING_BLOCK && m_curShape.canRotate(ax,dir,m_grid,m_size)) m_curShape.rotate(ax,dir);
}

void GameCore::translate(const Vector3D<Shape::Relative_t>& v) {
    if(m_state == State::MOVING_BLOCK && m_curShape.canTranslate(v,m_grid,m_size)) m_curShape.translate(v);
}



//SFML Compatibility

sf::Packet& operator<< (sf::Packet& packet, const GameCore& gc) {
    return packet << gc.m_isPaused << gc.m_size << gc.m_score << ((unsigned) gc.m_state) << gc.m_curShape << gc.m_nextShape << gc.m_grid;
}


sf::Packet& operator >>(sf::Packet& packet, GameCore& gc){
    unsigned tmpState;
    packet >> gc.m_isPaused >> gc.m_size >> gc.m_score >> tmpState >> gc.m_curShape >> gc.m_nextShape >> gc.m_grid;
    gc.m_state = (GameCore::State) tmpState; 
    return packet;
}
