#pragma once

#include <GL/glut.h>
#include <iostream>

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