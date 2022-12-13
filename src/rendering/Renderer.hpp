#pragma once

#include "./renderingFunctions.hpp"
#include <GL/glut.h>
#include <GL/gl.h>
#include <vector>
#include "../physics/utils/Vector.hpp"
#include "./texture.hpp"
#include "../physics/utils/Color.hpp"

#define _2D 1000
#define _3D 1001

#define FPS 60

double angle = 60.0;

class Renderer {
    private:
        void (*displayFunction)();
        double offset = 2.3/2;
        unsigned int MODE = _3D;

        Vector v1 = Vector(0,0,0);
        Vector v2 = Vector(2,2,-2);

        void absoluteDrawRect2D(int x1, int y1, int x2, int y2, Color col) {
            double width = glutGet(GLUT_WINDOW_WIDTH);
            double height = glutGet(GLUT_WINDOW_HEIGHT);
            glColor3f(col.r,col.g,col.b);
            glRectf(2*x1/width-1,2*y1/height-1,2*x2/width-1,2*y2/height-1);
        }

        void absoluteDrawRect3D(Vector& vect1, Vector& vect2, Color col) {
            const Vector v = Vector(-1,-1,1);
            Vector v1 = vect1+v;
            Vector v2 = vect2+v;
            glRect3D(v1, v2, col);
        }

    public:
        int parentWin;
        int scoreWin;
        Renderer();
        Renderer(int argc, char** argv);
        ~Renderer();

        void setDisplayFunc(void (*f)()) {
            displayFunction = f;
            glutDisplayFunc(displayFunction);
        }

        void renderRoutineGrid() {
            glutSetWindow(parentWin);
            Color col = Color(1,0,0);
            if (MODE == _3D) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glLoadIdentity();
                glTranslatef(-10,-15,-35);
                glRotatef(-70,1,0,0);
                glRotatef(2.5,0,1,0);
                glRotatef(angle,0,0,1);
                
                glTranslatef(-2*offset-0.5,-2*offset-0.5,0);
                for (int z = 0; z < 24; z++) {
                    for (int y = 0; y < 5; y++) {
                        for (int x = 0; x < 5; x++) {
                            glBegin(GL_QUADS);
                            col = Color(x/5.0,y/5.0,z/24.0);
                            absoluteDrawRect3D(v1,v2,col);
                            glEnd();
                            glTranslatef(offset,0,0);
                        }
                        glTranslatef(-5*offset,0,0);
                        glTranslatef(0,offset,0);
                    }
                    glTranslatef(0,-5*offset,0);
                    glTranslatef(0,0,offset);
                }
                glTranslatef(0,0,-5*offset);

            }
            if (MODE == _2D) {
                glClear(GL_COLOR_BUFFER_BIT);
                for (int x = 50; x<550 ; x+=50) {
                    for (int y = 50; y<850 ; y+=50) {
                        absoluteDrawRect2D(x,y,x+45,y+45,col);
                    }
                }
            }
            glFlush();
        }
        void renderRoutineScore() {
            glutSetWindow(scoreWin);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();

            glClearColor(0,0,0,0);
	        glClear(GL_COLOR_BUFFER_BIT);
        
            Color col = Color(0.7,0.7,0.7);
            glColor3f(col.r,col.g,col.b);
            vBitmapOutput(0,0.9,"Tetris",GLUT_BITMAP_HELVETICA_18);

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

void reshape2(int w, int h) {
	float L; 
	float H; 

	glViewport(0,0,w,h); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	if (w<=h) 
	{ 
	  if (w==0) H=900; 
	  else H=(GLfloat) (300*h/w); 
	  L=300; 
	} 
	else 
	{ 
	  H=900; 
	  if (h==0) L=300; 
	  else L=(GLfloat) (900*w/h); 
	} 
	gluOrtho2D(-L/2,L/2,-H/2,H/2); 
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer,0);
    angle+=0.5;
    if (angle>360.0)
        angle-=360.0;
}

Renderer::Renderer() {

}

Renderer::Renderer(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 900);
    glutInitWindowPosition(100, 100);
    parentWin = glutCreateWindow("Tetris");
    scoreWin = glutCreateSubWindow(parentWin,300, 0, 300, 900);

    glutSetWindow(parentWin);
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


    glutSetWindow(scoreWin);
    if (MODE == _3D) {
        glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
        glutReshapeFunc(reshape2);
        //glEnable(GL_DEPTH_TEST);
        //glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
        //initTexture();
        glutTimerFunc(1000/FPS,timer,0);
    } 
}

Renderer::~Renderer() {
}