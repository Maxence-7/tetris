#pragma once

#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include "../physics/utils/Vector.hpp"
#include "texture.hpp"
#include "../physics/utils/Color.hpp"

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

void glRect3D(Vector& vect1, Vector& vect2, Color col) {
    double X1 = vect1.x/2;
    double Y1 = vect1.y/2;
    double Z1 = vect1.z/2;
    double X2 = vect2.x/2;
    double Y2 = vect2.y/2;
    double Z2 = vect2.z/2;
    glColor3f(col.r,col.g,col.b);

    //glBegin(GL_QUADS);

    //front
    //glColor3f(1.0,0.0,0.0); //red
    glTexCoord2i(0,0);glVertex3f(Y1,Y2,X2);
    glTexCoord2i(1,0);glVertex3f(Y1,Z2,X2);
    glTexCoord2i(1,1);glVertex3f(Z1,Z2,X2);
    glTexCoord2i(0,1);glVertex3f(Z1,Y2,X2);
    //back
    //glColor3f(0.0,1.0,0.0); //green
    glTexCoord2i(0,0);glVertex3f(Z1,Y2,X1);
    glTexCoord2i(1,0);glVertex3f(Z1,Z2,X1);
    glTexCoord2i(1,1);glVertex3f(Y1,Z2,X1);
    glTexCoord2i(0,1);glVertex3f(Y1,Y2,X1);
    //right
    //glColor3f(0.0,0.0,1.0); //blue
    glTexCoord2i(0,0);glVertex3f(Z1,Y2,X2);
    glTexCoord2i(1,0);glVertex3f(Z1,Z2,X2);
    glTexCoord2i(1,1);glVertex3f(Z1,Z2,X1);
    glTexCoord2i(0,1);glVertex3f(Z1,Y2,X1);
    //left
    //glColor3f(1.0,1.0,0.0);
    glTexCoord2i(0,0);glVertex3f(Y1,Y2,X1);
    glTexCoord2i(1,0);glVertex3f(Y1,Z2,X1);
    glTexCoord2i(1,1);glVertex3f(Y1,Z2,X2);
    glTexCoord2i(0,1);glVertex3f(Y1,Y2,X2);
    //top
    //glColor3f(0.0,1.0,0.0);
    glTexCoord2i(0,0);glVertex3f(Y1,Y2,X1);
    glTexCoord2i(1,0);glVertex3f(Y1,Y2,X2);
    glTexCoord2i(1,1);glVertex3f(Z1,Y2,X2);
    glTexCoord2i(0,1);glVertex3f(Z1,Y2,X1);
    //bottom
    //glColor3f(1.0,0.0,1.0);
    glTexCoord2i(0,0);glVertex3f(Y1,Z2,X1);
    glTexCoord2i(1,0);glVertex3f(Y1,Z2,X2);
    glTexCoord2i(1,1);glVertex3f(Z1,Z2,X2);
    glTexCoord2i(0,1);glVertex3f(Z1,Z2,X1);

    //glEnd();

    glutSwapBuffers();
}

void vBitmapOutput(double x, double y, char *string, void *font) {
	int len,i; // len donne la longueur de la chaîne de caractères

	glRasterPos2f(x,y); // Positionne le premier caractère de la chaîne
	len = (int) strlen(string); // Calcule la longueur de la chaîne
	for (i = 0; i < len; i++) glutBitmapCharacter(font,string[i]); // Affiche chaque caractère de la chaîne
}

void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font) {
	char *p;

	glPushMatrix();	// glPushMatrix et glPopMatrix sont utilisées pour sauvegarder 
			// et restaurer les systèmes de coordonnées non translatés
	glTranslatef(x, y, 0); // Positionne le premier caractère de la chaîne
	for (p = string; *p; p++) glutStrokeCharacter(font, *p); // Affiche chaque caractère de la chaîne
	glPopMatrix();
}