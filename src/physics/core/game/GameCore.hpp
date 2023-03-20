#pragma once
#include "../../containers/Shape.hpp"
#include "../../containers/BlockContainer.hpp"
#include "../../utils/Vector3D.hpp"
#include <iostream>
#include <thread>
#include <random>
#include <map>
#include <vector>
#include <memory>
#include <cmath>

class GameCore {
    enum State {MOVING_BLOCK,GENERATING_NEW_BLOCK,CHECKING_COMPLETE_LINES,LOSE_CHECK};
    public:
        friend class BlockContainer;
        friend class Shape;
        using Score_t = unsigned;
        using Size_t = Vector3D<unsigned>;

        template<typename T>
        using Container_t = std::map<Vector3D<T>,Color>;

    private:
        bool m_isPaused;
        Size_t m_size;
        State m_state; 
        Score_t m_score;

        Shape m_curShape; 
        Shape m_nextShape;
        BlockContainer m_grid;
        //SoundCore m_soundCore ;//= SoundCore(30);


        std::mt19937 m_gen;
        std::vector<unsigned> m_indexesComplete;
    public:
        GameCore(const Size_t&); 
        GameCore(const GameCore&);
        ~GameCore();
        
        template<typename T,typename U>
        Vector3D<T> getDisplayVectorFromGridVector(const Vector3D<U>& vec, T offset) const {
            Vector3D<T> castVect(vec);
            Vector3D<T> castSize(m_size);
            return Vector3D<T>((castVect.x-std::floor(castSize.x/2))*offset,(castVect.y-std::floor(castSize.y/2))*offset,(castVect.z)*offset);
        }

        template<typename T>
        Container_t<T> render(T offset) const {
            Container_t<T> out;
            for (auto const& [vec, col] : m_grid) {
                out.insert(std::make_pair(getDisplayVectorFromGridVector(vec,offset),col));
            }

            for (auto const& [vec, col] : m_curShape.toBlockContainer()) {
                out.insert(std::make_pair(getDisplayVectorFromGridVector(vec,offset),col));
            }
            
            return out;
        }

        template<typename T>
        Container_t<T> renderNextShape(T offset) const {
            Container_t<T> out;
            Vector3D<Shape::Absolute_t> shapePos = m_nextShape.getAbsolutePosition(Vector3D<Shape::Relative_t>(0,0,0));
            for (auto const& [vec, col] : (BlockContainer) m_nextShape) {
                out.insert(std::make_pair(getDisplayVectorFromGridVector(Vector3D<Shape::Relative_t>(vec)-Vector3D<Shape::Relative_t>(shapePos),offset),col));
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
        Size_t getSize() const;


        static void startThread(std::shared_ptr<GameCore> corePtr) {
            return corePtr->start();
        }

    protected:
        void switchShape() {
            m_curShape = m_nextShape;
            m_nextShape = Shape::getRandomShape(m_gen,m_size);
        }

    private:
        void turn() {
            while(m_isPaused);
            switch (m_state) {
                case GENERATING_NEW_BLOCK:
                    switchShape();
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
            turn();
        }
        
    public:
        void translate(const Vector3D<Shape::Relative_t>& v) {
            if(m_state == State::MOVING_BLOCK && m_curShape.canTranslate(v,m_grid,m_size)) m_curShape.translate(v);
        }

        void rotate(Shape::ROTATION_AXIS ax, Shape::ROTATION_DIRECTION dir) {
            if(m_state == State::MOVING_BLOCK && m_curShape.canRotate(ax,dir,m_grid,m_size)) m_curShape.rotate(ax,dir);
        }

        void dropUntilHit() {
            if(m_state == State::MOVING_BLOCK) {
                Vector3D<Shape::Relative_t> down(0,0,-1);
                while (m_curShape.canTranslate(down,m_grid,m_size)) {
                    m_curShape.translate(down);
                }
                m_state = State::LOSE_CHECK;  
            }
        }

        bool isGameLose() const;
};
