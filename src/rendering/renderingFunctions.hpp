#pragma once

#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include "../physics/utils/Vector.hpp"
#include "../physics/utils/Color.hpp"

void glRect3D(Vector& vect1, Vector& vect2, Color col);

void vBitmapOutput(double x, double y, char *string, void *font);

void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font);

void writeText(std::string score,std::string state);