#pragma once
#include "./containers/Shape.hpp"
#include "./containers/BlockContainer.hpp"
#include "./utils/Vector.hpp"
#include "GL/glut.h"
#include "GL/gl.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <map>
#include <memory>

class GameCore {
    enum State {MOVING_BLOCK,PAUSE,COLLISION,GENERATING_NEW_BLOCK,CHECKING_COMPLETE_LINES,LOSE_CHECK};
    public:
        friend class BlockContainer;
        friend class Shape;
        using Score_t = unsigned;
        using Tick_t = long long;

    private:
        State m_state; 
        Score_t m_score;
        Tick_t m_tick;
        Shape m_curShape; 
        Shape m_nextShape;
        BlockContainer m_grid;
        std::mt19937 m_gen;
        
    public:

        GameCore() {}
        GameCore(Vector size) {
            /*std::random_device rd();
            std::mt19937 gen(19);*/
            
            //m_gen = gen;
            m_curShape = Shape::getRandomShape(m_gen,size);
            m_nextShape = Shape::getRandomShape(m_gen,size);
            m_grid = BlockContainer(size);
            m_tick = 0;
            m_score = 0;

        }
        ~GameCore() {}
        

        std::map<Vector,BlockContainer::Value_t> render(double offset) const {
            std::map<Vector,BlockContainer::Value_t> out;
            Vector size = m_grid.getSize();
            for (auto const& [vec, col] : m_grid) {
                out.insert(std::make_pair(Vector((vec.x-std::floor(size.x/2))*offset,(vec.y-std::floor(size.y/2))*offset,(vec.z)*offset),col));
            }

            for (auto const& [vec, col] : m_curShape.toBlockContainer()) {
                out.insert(std::make_pair(Vector((vec.x-std::floor(size.x/2))*offset,(vec.y-std::floor(size.y/2))*offset,(vec.z)*offset),col));
            }
            return out;
        }

        void start() {
            m_state = State::GENERATING_NEW_BLOCK;
            turn();
        }

    // Getters
        State getState() const {
            return m_state;
        }

        
        Score_t getScore() const {
            return m_score;
        }

        Vector getSize() const {
            return m_grid.getSize();
        }


    static void startThread(std::shared_ptr<GameCore> corePtr) {
        return corePtr->start();
    }

    private:
        void turn() {
            switch (m_state) {
                case PAUSE:
                    return turn();
                case GENERATING_NEW_BLOCK:
                    m_curShape = m_nextShape;
                    m_curShape = Shape::getRandomShape(m_gen,m_grid.getSize());
                    m_state = State::MOVING_BLOCK;
                    break;
                case COLLISION:
                    m_grid.append(m_curShape.toBlockContainer());
                    m_state = State::LOSE_CHECK;
                    break;
                case MOVING_BLOCK:
                    if (m_curShape.canTranslate(Vector(0,0,-1),m_grid)) {
                        m_curShape.translate(Vector(0,0,-1));    
                    } else {
                        m_state = State::COLLISION;
                    }
                    break;
                    
                
                case LOSE_CHECK:
                    if (!m_curShape.isInContainer(m_grid))
                    {
                        return;
                    }
                    
                    m_state = State::CHECKING_COMPLETE_LINES;
                    break;

                case CHECKING_COMPLETE_LINES:
                    int numberOfComplete = 0 ;
                    
                    m_state = State::GENERATING_NEW_BLOCK;
                    break;
            }
            disp();
            m_tick++;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            turn();
        }
        
    public:
        void translate(const Vector& v) {
            if(m_state == State::MOVING_BLOCK && m_curShape.canTranslate(v,m_grid)) m_curShape.translate(v);
        }

        void rotate(Shape::ROTATION_AXIS ax, Shape::ROTATION_DIRECTION dir) {
            if(m_state == State::MOVING_BLOCK) m_curShape.rotate(ax,dir);
        }

        void dropUntilHit() {
            if(m_state == State::MOVING_BLOCK) {
                // TODO DROP UNTIL HIT;
                m_state = State::COLLISION;  
            }
        }


        void disp() {
            std::cout << "TEST" << std::endl;
            Vector shPos = m_curShape.getAbsolutePosition(Vector(0,0,0));
            Vector size = m_grid.getSize();
            std::cout << "CurScore " << m_score << " | Tick " << m_tick << " | State :" << m_state << " | Position " << shPos.x << "," << shPos.y<<","<<shPos.z<<std::endl; 
            /*//for (size_t i = 0; i < size.x; i++) {
            for (size_t i = 0; i < 1; i++) {
                std::cout << "----------------- P "<< i << "-----------------" << std::endl;
                for (Vector::Coordinate_t k = size.z-1; k >= 0; k--) {
                    for (size_t j = 0; j < size.y; j++) {
                        if (m_grid.isOccupied(Vector(i,j,k))) {
                            std::cout << 1;
                        } else if (m_curShape.isOccupied(Vector(i,j,k))) {
                            std::cout << 2;
                        } else {
                            std::cout << 0;
                        }
                        std::cout << ' ';
                        //std::cout << k << ' ' <<j << std::endl;
                    }
                    std::cout << std::endl;
                }
            }
            std::cout << std::endl << std::endl<< std::endl;*/
        }

};
