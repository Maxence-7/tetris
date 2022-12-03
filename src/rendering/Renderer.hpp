#pragma once

#include "./renderingFunctions.hpp"
#include "../physics/utils/Grid.hpp"
#include <GL/glut.h>
#include <vector>
#include "../physics/utils/Vector.hpp"
//#include "../physics/containers/Shape.hpp"

#define _2D 1000
#define _3D 1001

double angle = 60.0;

class Renderer {
    private:
        void (*displayFunction)();
        //std::vector<Shape*> shapesVector;
        Grid grid = Grid(550, 850, 50, 50);
        Grid grid3D = Grid(550, 850, 550, 50, 50, 50);
        unsigned int MODE = _3D;

        void absoluteDrawRect2D(int x1, int y1, int x2, int y2) {
            double width = glutGet(GLUT_WINDOW_WIDTH);
            double height = glutGet(GLUT_WINDOW_HEIGHT);
            glColor3f(0.2,0.2,0.2);
            glRectf(2*x1/width-1,2*y1/height-1,2*x2/width-1,2*y2/height-1);
        }

        void absoluteDrawRect3D(Vector vect1, Vector vect2) {
            Vector const v = Vector(-1,-1,1);
            glRect3D(vect1+v, vect2+v);
        }

    public:
        Renderer();
        Renderer(int argc, char** argv);
        ~Renderer();

    void setDisplayFunc(void (*f)()) {
        displayFunction = f;
        glutDisplayFunc(displayFunction);
    }

    void renderRoutine() {
        if (MODE == _3D) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();
            glTranslatef(0,0,-30);
            glRotatef(angle,1,1,1);

            Vector v1 = Vector(0,0,0);
            Vector v2 = Vector(2,2,-2);
            for (int x = 0; x<7 ; x+=3) {
                for (int y = 0; y<7 ; y+=3) {
                    for (int z = 0; z<7 ; z+=3) {
                        //Vector v = Vector(x,y,0);
                        //absoluteDrawRect3D(v1+v,v2+v);
                    }
                }
            }
            Vector v = Vector(3,0,0);
            absoluteDrawRect3D(v1,v2);
            absoluteDrawRect3D(v1+v,v2+v);
            absoluteDrawRect3D(v1+v+v,v2+v+v);
            //absoluteDrawRect3D(100,100,150,150,150,100);
        }
        if (MODE == _2D) {
            glClear(GL_COLOR_BUFFER_BIT);
            for (int x = grid.X; x<grid.W ; x+=50) {
                for (int y = grid.Y; y<grid.H ; y+=50) {
                    absoluteDrawRect2D(x,y,x+45,y+45);
                }
            }
        //glRectf(0,0,-0.5,0.5);
        }
        glFlush();
    }
};

void reshape(int w, int h) {
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,2.0,50.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);

    angle+=2.8;
    if (angle>360.0)
        angle-=360.0;
}

Renderer::Renderer() {

}

Renderer::Renderer(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tetris");
    if (MODE == _2D) {
        glutInitDisplayMode(GLUT_NORMAL);
    }
    if (MODE == _3D) {
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutReshapeFunc(reshape);
        glEnable(GL_DEPTH_TEST);
    }
    
}

Renderer::~Renderer() {
}