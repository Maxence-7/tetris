#pragma once

#include "renderingFunctions.hpp"
#include <GL/glut.h>

class Renderer {
    private:
        void (*displayFunction)();
    public:
        Renderer(int argc, char** argv);
        ~Renderer();

    void setDisplayFunc(void (*f)()) {
        displayFunction = f;
    }

    void refresh() {
        glutDisplayFunc(displayFunction);
    }
};

Renderer::Renderer(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tetris");
}

Renderer::~Renderer() {
}