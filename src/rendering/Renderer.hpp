#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include "./renderingFunctions.hpp"
#include "../physics/utils/Vector.hpp"
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
        std::shared_ptr<GameCore> m_gc;
        void (*displayFunction)();
        double offset = 1.0;
        unsigned int MODE = _3D;

        Vector v1 = Vector(0,0,0);
        Vector v2 = Vector(2,2,-2);

    public:
        Renderer();
        Renderer(int argc, char** argv, std::shared_ptr<GameCore> gc);
        ~Renderer();

        void absoluteDrawRect2D(int x1, int y1, int x2, int y2, Color col);
        void absoluteDrawRect3D(Vector& vect1, Vector& vect2, Color col);

        void setDisplayFunc(void (*f)());

        void renderRoutineGrid();
        void renderRoutineScore();
        void renderRoutinePreview();

        int getParentWin();
        int getScoreWin();
        int getPreviewWin();
};

void reshape(int w, int h);

void reshape2(int w, int h);

void reshape3(int w, int h);

void timer(int);

void timer2(int);

void timer3(int);