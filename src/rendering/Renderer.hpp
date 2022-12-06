#pragma once

#include "./renderingFunctions.hpp"
#include "../physics/utils/Grid.hpp"
#include <GL/glut.h>
#include <GL/gl.h>
#include <vector>
#include "../physics/utils/Vector.hpp"
#include "./texture.hpp"
//#include "../physics/containers/Shape.hpp"

#define _2D 1000
#define _3D 1001

#define FPS 30

double angle = 60.0;

class Renderer {
    private:
        void (*displayFunction)();
        //std::vector<Shape*> shapesVector;
        Grid grid = Grid(550, 850, 50, 50);
        Grid grid3D = Grid(550, 850, 550, 50, 50, 50);
        double offset = 2.3;
        unsigned int MODE = _3D;

        Vector v1 = Vector(0,0,0);
        Vector v2 = Vector(2,2,-2);

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
            glRotatef(-60,1,0,0);
            glRotatef(angle,0,0,1);

            Vector ex = Vector(0,0,0);
            Vector ey = Vector(0,0,0);
            Vector ez = Vector(0,0,0);
            //absoluteDrawRect3D(v1,v2);
            //absoluteDrawRect3D(v1+ex,v2+ex);
            //absoluteDrawRect3D(v1+ey,v2+ey);
            //absoluteDrawRect3D(v1+ez,v2+ez);

            /*for (int z = 0; z < 5; z++) {
                for (int y = 0; y < 5; y++) {
                    for (int x = 0; x < 5; x++) {
                        absoluteDrawRect3D(v1,v2);
                        glTranslatef(offset,0,0);
                    }
                    glTranslatef(-5*offset,0,0);
                    glTranslatef(0,offset,0);
                }
                glTranslatef(0,-5*offset,0);
                glTranslatef(0,0,offset);
            }
            //glTranslatef(0,0,-5*offset);*/

            int sizeGrid = 5;

            /*for (int z = 0; z < sizeGrid; z++) {
                for (int y = 0; y < sizeGrid; y++) {
                    for (int x = 0; x < sizeGrid; x++) {
                        ex.x = x*offset;
                        absoluteDrawRect3D(v1+ex,v2+ex);
                    }
                    glTranslatef(offset,0,0);
                }
                glTranslatef(-sizeGrid*offset,0,0);
                glTranslatef(0,offset,0);
            }*/

            /*for (int z = 0; z < sizeGrid; z++) {
                for (int y = 0; y < sizeGrid; y++) {
                    for (int x = 0; x < sizeGrid; x++) {
                        ex.x = x*offset;
                        absoluteDrawRect3D(v1+ex+ey+ez,v2+ex+ey+ez);
                    }
                    //glRotatef(45,0,1,0);
                    ex.y = y*offset;
                }
                //glRotatef(90,1,0,0);
                ex.z = z*offset;
            }*/

            Vector u = Vector(0,2*offset,0);
            absoluteDrawRect3D(v1,v2);
            //absoluteDrawRect3D(v1+u,v2+u);
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
    glutTimerFunc(1000/FPS,timer,0);
    angle+=3;
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
        glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
        //initTexture();
        glutTimerFunc(1000/FPS,timer,0);
    }    
}

Renderer::~Renderer() {
}