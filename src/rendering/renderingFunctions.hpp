#pragma once

#include <GL/glut.h>
#include <iostream>
#include "../physics/utils/Vector.hpp"

GLfloat gfPosX = 0.0;
GLfloat gfDeltaX = .0001;

void Draw() {
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
		glVertex3f(gfPosX, 0.25, 0.0);
		glVertex3f(1.0 - gfPosX, 0.75,0.0);
	glEnd();
	glFlush();
	gfPosX += gfDeltaX;
	if (gfPosX >= 1.0 || gfPosX <= 0.0) {
		gfDeltaX = -gfDeltaX;
	}
	glutPostRedisplay();
}

// Draw a rectangle
void displayRect1(void) {
    // Size of rectangle in absolute pixels
    double posXabs = 200;
    double posYabs = 200;

    double width = glutGet(GLUT_WINDOW_WIDTH);
    double height = glutGet(GLUT_WINDOW_HEIGHT);
    double posX = posXabs/width;
    double posY = posYabs/height;

    glClear(GL_COLOR_BUFFER_BIT);
    glRectf(0,0,posX,posY);
    glFlush();

    glutPostRedisplay();
}

void drawGrid(void) {
    double width = glutGet(GLUT_WINDOW_WIDTH);
    double height = glutGet(GLUT_WINDOW_HEIGHT);

    glClear(GL_COLOR_BUFFER_BIT);
    for (int x = 50; x<550 ; x+=50) {
        for (int y = 50; y<850 ; y+=50) {

        }
    }
    glRectf(0,0,-0.5,0.5);
    glFlush();
}

void glRect3D(Vector vect1, Vector vect2) {
    double X1 = vect1.x;
    double Y1 = vect1.y;
    double Z1 = vect1.z;
    double X2 = vect2.x;
    double Y2 = vect2.y;
    double Z2 = vect2.z;

    glBegin(GL_QUADS);

    //front
    glColor3f(1.0,0.0,0.0);
    glVertex3f(Y1,Y2,X2);
    glVertex3f(Y1,Z2,X2);
    glVertex3f(Z1,Z2,X2);
    glVertex3f(Z1,Y2,X2);
    //back
    glColor3f(0.0,1.0,0.0);
    glVertex3f(Z1,Y2,X1);
    glVertex3f(Z1,Z2,X1);
    glVertex3f(Y1,Z2,X1);
    glVertex3f(Y1,Y2,X1);
    //right
    glColor3f(0.0,0.0,1.0);
    glVertex3f(Z1,Y2,X2);
    glVertex3f(Z1,Z2,X2);
    glVertex3f(Z1,Z2,X1);
    glVertex3f(Z1,Y2,X1);
    //left
    glColor3f(1.0,1.0,0.0);
    glVertex3f(Y1,Y2,X1);
    glVertex3f(Y1,Z2,X1);
    glVertex3f(Y1,Z2,X2);
    glVertex3f(Y1,Y2,X2);
    //top
    glColor3f(0.0,1.0,0.0);
    glVertex3f(Y1,Y2,X1);
    glVertex3f(Y1,Y2,X2);
    glVertex3f(Z1,Y2,X2);
    glVertex3f(Z1,Y2,X1);
    //bottom
    glColor3f(1.0,0.0,1.0);
    glVertex3f(Y1,Z2,X1);
    glVertex3f(Y1,Z2,X2);
    glVertex3f(Z1,Z2,X2);
    glVertex3f(Z1,Z2,X1);

    glEnd();

    glutSwapBuffers();
}