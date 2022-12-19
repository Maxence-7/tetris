#pragma once
#include "../../containers/Shape.hpp"
#include "../../containers/BlockContainer.hpp"
#include "../../utils/Vector.hpp"

#include <iostream>
#include <thread>
#include <random>
#include <map>
#include <vector>
#include <memory>
#include <cmath>

class GameCore {
    enum State {MOVING_BLOCK,COLLISION,GENERATING_NEW_BLOCK,CHECKING_COMPLETE_LINES,LOSE_CHECK};
    public:
        friend class BlockContainer;
        friend class Shape;
        using Score_t = unsigned;
        using Tick_t = long long;

    private:
        bool m_isPaused;
        Vector m_size;
        State m_state; 
        Score_t m_score;
        Tick_t m_tick; 

        Shape m_curShape; 
        Shape m_nextShape;
        BlockContainer m_grid;


        std::mt19937 m_gen;
        std::vector<unsigned> m_indexesComplete;
        //std::thread coreThread;
    public:
        //GameCore() : m_isPaused(false), m_tick(0), m_score(0)  {}
        GameCore(const Vector&); 
        GameCore(const GameCore&);
        ~GameCore();
        
        Vector getDisplayVectorFromGridVector(const Vector& vec, double offset) const {
            return Vector((vec.x-std::floor(m_size.x/2))*offset,(vec.y-std::floor(m_size.y/2))*offset,(vec.z)*offset);
        }

        BlockContainer::Container_t render(double offset) const {
            BlockContainer::Container_t out;
            for (auto const& [vec, col] : m_grid) {
                out.insert(std::make_pair(getDisplayVectorFromGridVector(vec,offset),col));
            }

            for (auto const& [vec, col] : m_curShape.toBlockContainer()) {
                out.insert(std::make_pair(getDisplayVectorFromGridVector(vec,offset),col));
            }
            
            return out;
        }

        BlockContainer::Container_t renderNextShape(double offset) const {
            BlockContainer::Container_t out;
            Vector shapePos = m_nextShape.getAbsolutePosition(Vector(0,0,0));
            for (auto const& [vec, col] : (BlockContainer) m_nextShape) {
                out.insert(std::make_pair(getDisplayVectorFromGridVector(vec-shapePos,offset),col));
            }
            
            return out;
        }

        void start() {
            m_state = State::GENERATING_NEW_BLOCK;
            turn();
        }


        void togglePause() {
            m_isPaused = !m_isPaused;
        }

    // Getters
        State getState() const;        
        Score_t getScore() const;
        Vector getSize() const;


        static void startThread(std::shared_ptr<GameCore> corePtr) {
            return corePtr->start();
        }

    protected:
        void switchShape() {
            m_curShape = m_nextShape;
            m_curShape = Shape::getRandomShape(m_gen,m_size);
        }

    private:
        void turn() {
            while(m_isPaused);
            switch (m_state) {
                case GENERATING_NEW_BLOCK:
                    switchShape();
                    m_state = State::MOVING_BLOCK;
                    break;
                case COLLISION:
                    m_state = State::LOSE_CHECK;
                    break;
                case MOVING_BLOCK:
                    if (m_curShape.canTranslate(Vector(0,0,-1),m_grid,m_size)) {
                        m_curShape.translate(Vector(0,0,-1));    
                    } else {
                        m_state = State::COLLISION;
                    }
                    break;
                    
                
                case LOSE_CHECK:
                    if (isGameLose())
                    {
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
                                if (!m_grid.isOccupied(Vector(i,j,k)) && k < m_size.z) {
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
                                map.insert(std::make_pair(vec-Vector(0,0,diff),col));
                            }   
                        }

                        m_score = m_score + std::pow((Score_t) 2, m_indexesComplete.size());
                        m_grid = BlockContainer(map);
                    }
                    m_state = State::GENERATING_NEW_BLOCK;
                    break;
            }
            disp();
            m_tick++;
            std::this_thread::sleep_for(std::chrono::milliseconds(750));
            turn();
        }
        
    public:
        void translate(const Vector& v) {
            if(m_state == State::MOVING_BLOCK && m_curShape.canTranslate(v,m_grid,m_size)) m_curShape.translate(v);
        }

        void rotate(Shape::ROTATION_AXIS ax, Shape::ROTATION_DIRECTION dir) {
            if(m_state == State::MOVING_BLOCK && m_curShape.canRotate(ax,dir,m_grid,m_size)) m_curShape.rotate(ax,dir);
        }

        void dropUntilHit() {
            if(m_state == State::MOVING_BLOCK) {
                Vector down(0,0,-1);
                while (m_curShape.canTranslate(down,m_grid,m_size)) {
                    m_curShape.translate(down);
                }
                m_state = State::COLLISION;  
            }
        }

        bool isValidPosition(const Vector& pos) const;
        bool isGameLose() const;

        void disp() {
            //std::cout << "TEST" << std::endl;
            Vector shPos = m_curShape.getAbsolutePosition(Vector(0,0,0));
            std::cout << "CurScore " << m_score << " | Tick " << m_tick << " | State :" << m_state << " | Position " << shPos.x << "," << shPos.y<<","<<shPos.z<<std::endl; 
        }


};
