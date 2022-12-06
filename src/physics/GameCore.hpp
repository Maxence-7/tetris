#pragma once
#include "./containers/Shape.hpp"
#include "./containers/BlockContainer.hpp"
#include "./utils/Vector.hpp"
#include "GL/glut.h"
#include "GL/gl.h"

#include <iostream>
#include <thread>
#include <chrono>

class GameCore {
    enum State {MOVING_BLOCK,PAUSE,COLLISION,GENERATING_NEW_BLOCK,CHECKING_COMPLETE_LINES,LOSE_CHECK};
    public:
        using Score_t = unsigned;
        using Tick_t = long long;

    private:
        State m_state; 
        Vector m_size;
        Score_t m_score;
        Tick_t m_tick;
        Shape m_curShape; 
        Shape m_nextShape;
        BlockContainer m_grid;
        
    public:
        GameCore(Vector size) : m_score(0), m_tick(0), m_curShape(Shape::getRandomShape()), m_nextShape(Shape::getRandomShape()), m_grid(BlockContainer(size)), m_size(size) {}
        ~GameCore() {}

        void start() {
            m_state = State::GENERATING_NEW_BLOCK;
            turn();
        }

        
    private:
        void turn() {
            switch (m_state) {
                case PAUSE:
                    return turn();
                case GENERATING_NEW_BLOCK:
                    m_curShape = m_nextShape;
                    m_curShape = Shape::getRandomShape();
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
        bool isValidPosition(const Vector& pos) const {
            return (pos.x >= 0 && pos.x < m_size.x) && (pos.y >= 0 && pos.y < m_size.y) && (pos.z >= 0);
        }

        bool isOccupied(const Vector& pos) const {
            return m_grid.isOccupied(pos) && m_curShape.isOccupied(pos); 
        }

        bool isValidMove(const Vector& pos) {
            return m_grid.isOccupied(pos) && isValidPosition(pos);
        
        }


        void disp() {
            std::cout << "TEST" << std::endl;
            Vector shPos = m_curShape.getAbsolutePosition(Vector(0,0,0));
            std::cout << "CurScore " << m_score << " | Tick " << m_tick << " | State :" << m_state << " | Position " << shPos.x << "," << shPos.y<<","<<shPos.z<<std::endl; 
            //for (size_t i = 0; i < m_size.x; i++) {
            for (size_t i = 0; i < 1; i++) {
                std::cout << "----------------- P "<< i << "-----------------" << std::endl;
                for (Vector::Coordinate_t k = m_size.z-1; k >= 0; k--) {
                    for (size_t j = 0; j < m_size.y; j++) {
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
            std::cout << std::endl << std::endl<< std::endl;
        }

};
