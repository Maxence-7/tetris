#pragma once
#include "../../containers/Shape.hpp"
#include "../../containers/BlockContainer.hpp"
#include "../../utils/Vector3D.hpp"
#include "../sound/SoundCore.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <random>
#include <map>
#include <vector>
#include <memory>
#include <cmath>

/**
 * @brief GameCore compile Game Logic and Data.
 */
class GameCore {
    
    public:
        using Score_t = unsigned;
        using Size_t = Vector3D<unsigned>;

        enum State {MOVING_BLOCK,GENERATING_NEW_BLOCK,CHECKING_COMPLETE_LINES,LOSE_CHECK};
        
        /**
         * @brief Default Grid Size for a Game
         */
        static const Size_t DEFAULT_SIZE;


        template<typename T>
        using Container_t = std::map<Vector3D<T>,Color>;


        
    private:
        bool m_isPaused;
        bool m_isLose = false;
        bool m_alreadyStarted = false;
        State m_state; 
        Score_t m_score;
        BlockContainer m_grid;
        std::vector<unsigned> m_indexesComplete;
        SoundCore m_soundCore();
    protected:
        Size_t m_size;
        Shape m_curShape; 
        Shape m_nextShape;
    private:

    public:
        /**
         * @brief Default constructor, using Default 3D size.
         */
        GameCore();


        /**
         * @brief Constructor with a custom size
         * @param  size : Size of the game
         * @attention In case of a 2D game, a 3D vector must be specified and the y coordinate of size must be equal to one.
         */
        explicit GameCore(const Size_t&); 

        GameCore(const GameCore&);
        ~GameCore();
        
        // OpenGL Interface
        /**
         * @brief Convert absolute coordinates to OpenGL ones, independantly of typing
         * @tparam T : type for output vector
         * @tparam U : Type of the input vector (that will be casted to T)
         * @param vec : Input a vector
         * @param offset : Offset between two blocks
         * @return Vector of coordinates in OpenGL space.
         */
        template<typename T,typename U>
        Vector3D<T> getDisplayVectorFromGridVector(const Vector3D<U>& vec, T offset) const {
            Vector3D<T> castVect(vec);
            Vector3D<T> castSize(m_size);
            return Vector3D<T>((castVect.x-std::floor(castSize.x/2))*offset,(castVect.y-std::floor(castSize.y/2))*offset,(castVect.z)*offset);
        }

        /**
         * @brief Apply getDisplayVectorFromGridVector for each block in the grid
         * @tparam T : Output type 
         * @param offset : Offset between blocks
         * @return Grid in OpenGL Space
         */
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

        /**
         * @brief Apply getDisplayVectorFromGridVector for each block in the m_shape
         * @tparam T : Output type 
         * @param offset : Offset between blocks
         * @return Shape in OpenGL Space
         */
        template<typename T>
        Container_t<T> renderNextShape(T offset) const {
            Container_t<T> out;
            Vector3D<Shape::Absolute_t> shapePos = m_nextShape.getAbsolutePosition(Vector3D<Shape::Relative_t>(0,0,0));
            for (auto const& [vec, col] : (BlockContainer) m_nextShape) {
                out.insert(std::make_pair(getDisplayVectorFromGridVector(Vector3D<Shape::Relative_t>(vec)-Vector3D<Shape::Relative_t>(shapePos),offset),col));
            }
            
            return out;
        }


        // Core
    protected:
        inline virtual void onAwait() {
            m_curShape = m_nextShape;
            m_nextShape = Shape::getRandomShape(m_size);
        }

   
    public:
        /**
         * @brief Accessible method to start a game.
         * @attention A game can only be started once. 
         */
        void start();


        /**
         * @brief Change the mode. If the game isn't paused, the game become paused .
         */
        void togglePause();

        /**
         * @brief Check if a game is losed
         * @return boolean. True if the game is losed.
         * @attention It's not a getter.
         */
        bool isGameLose() const;

        static void startThread(std::shared_ptr<GameCore> corePtr) {
            return corePtr->start();
        }

        // Movements 
        /**
         * @brief Translate the current shape by the specified vector.
         * @param vec : Translation Vector
         * @attention This time the method is verifing if the shape can translate before applying the translation.
         */
        void translate(const Vector3D<Shape::Relative_t>&);

        /**
         * @brief Rotate the current shape by the specified axis and direction
         * @param ax : Axis of rotation
         * @param dir : Direction
         * @attention This time the method is verifing if the shape can rotate before applying the rotation.
         */
        void rotate(Shape::ROTATION_AXIS, Shape::ROTATION_DIRECTION);
        
        /**
         * @brief Drop the current shape until it hits the floor or an other block.
         */
        void dropUntilHit();


        // Getters and Setters

        /**
         * @brief Getter for score
         * @return Current Score
         */
        Score_t getScore() const;


        /**
         * @brief Getter for Size
         * @return Size
         */
        Size_t getSize() const;


        inline void setCurrentShape(const Shape& shape) {
            m_curShape = shape;
        }

        inline void setNextShape(const Shape& shape) {
            m_nextShape = shape;
        }


        // SFML Compatibility 
        /**
         * @brief Compatibility with SFML Networking. 
         * @param pack : An SFML packet 
         * @param core : GameCore to be added to the packet.
         * @return Updated SFML Packet with data of the GameCore append to it.
         */
        friend sf::Packet& operator << (sf::Packet&, const GameCore&);
        
        /**
         * @brief Compatibility with SFML Networking. 
         * @param pack : An SFML packet with a GameCore to be extracted. 
         * @param core : extacted GameCore from the Packet
         * @return Updated SFML Packet without the data of the GameCore.
         */
        friend sf::Packet& operator >> (sf::Packet&, GameCore&);

        
};
