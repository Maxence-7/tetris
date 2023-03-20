#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include "./renderingFunctions.hpp"
#include "../physics/utils/Vector3D.hpp"
#include "./texture.hpp"
#include "../physics/core/game/GameCore.hpp"
#include "../physics/utils/Color.hpp"
#include <vector>
#include <memory>

#define _2D 1000
#define _3D 1001

#define FPS 60

class Renderer {
    private:
        /**
         * @brief Shared pointer : link with game physics
         * 
         */
        std::shared_ptr<GameCore> m_gc;
        void (*displayFunction)();
        double offset = 1.0;
        double angleCam = 0;
        /**
         * @brief To change the mode of the game 2D or 3D (3D is better so 2D is deprecated)
         * 
         */
        unsigned int MODE = _3D;

        /**
         * @brief Vector which work with absoluteDrawRect3D(...) so let's keep it :)
         * 
         */
        Vector3D<double> v1 =  Vector3D<double>(); Vector3D<double> v2 = Vector3D<double>(2.,2.,-2.);

        /**
         * @brief Get the average position of the next piece in order the place it in the middle for a nicer rotation
         * 
         * @param map 
         * @return Average Position (Vector object) 
         */
        template<typename T>
        Vector3D<T> getAvgPos(GameCore::Container_t<T> map) {
            Vector3D<T> moy (0,0,0);
            unsigned nb = 0;
            for (auto const& [vec,col] : map) {
                moy += vec;
                nb++;
            }
            moy/=nb;
            return moy;
        }


    public:
        /**
         * @brief Constructor by default
         * 
         */
        Renderer();
        /**
         * @brief Construct a new Renderer object
         * 
         * @param argc 
         * @param argv 
         * @param gc 
         */
        Renderer(int argc, char** argv, std::shared_ptr<GameCore> gc);
        /**
         * @brief Destroy the Renderer object
         * 
         */
        ~Renderer();

        /**
         * @brief Draw a 2D rectangle based on the coordinates of 2 opposite corners (bottom left and up right)
         * @param x1 
         * @param y1 
         * @param x2 
         * @param y2 
         * @param col 
         */
        void absoluteDrawRect2D(int x1, int y1, int x2, int y2, Color col);
        /**
         * @brief Draw a 3D cube based on the coordinates of 2 opposite corners (bottom left front and up right back)
         * 
         * @param vect1 
         * @param vect2 
         * @param col 
         */
        void absoluteDrawRect3D(Vector3D<double>& vect1, Vector3D<double>& vect2, Color col);

        /**
         * @brief Set the Display Function used to render the window
         * 
         * @param f 
         */
        void setDisplayFunc(void (*f)());

        /**
         * @brief Display Function used to render the Grid window
         * 
         */
        void renderRoutineGrid();
        /**
         * @brief Display Function used to render the Score window
         * 
         */
        void renderRoutineScore();
        /**
         * @brief Display Function used to render the Preview window
         * 
         */
        void renderRoutinePreview();

        /**
         * @brief Get the ID of the parent window
         * 
         * @return ID 
         */
        int getParentWin();
        /**
         * @brief Get the ID of the score window
         * 
         * @return ID 
         */
        int getScoreWin();
        /**
         * @brief Get the ID of the preview window
         * 
         * @return ID 
         */
        int getPreviewWin();

        void setAngleCam(double ang);
        double getAngleCam() const;
};

/**
 * @brief Reshape function needed by GLUT to render the parent window
 * 
 * @param w 
 * @param h 
 */
void reshape(int w, int h);

/**
 * @brief Reshape function needed by GLUT to render the score window
 * 
 * @param w 
 * @param h 
 */
void reshape2(int w, int h);

/**
 * @brief Reshape function needed by GLUT to render the preview window
 * 
 * @param w 
 * @param h 
 */
void reshape3(int w, int h);

/**
 * @brief Loop function used to update the parent window
 * 
 */
void timer(int);

/**
 * @brief Loop function used to update the score window
 * 
 */
void timer2(int);

/**
 * @brief Loop function used to update the preview window
 * 
 */
void timer3(int);