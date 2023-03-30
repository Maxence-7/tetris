#pragma once

#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include "../physics/utils/Vector3D.hpp"
#include "../physics/utils/Color.hpp"

void glRect3D(Vector3D<double>& vect1, Vector3D<double>& vect2, Color col);

void drawLine3D(const Vector3D<double>& vect1, const Vector3D<double>& vect2);

void drawBorders();
void drawBorders(Vector3D<double>&);

void vBitmapOutput(double x, double y, char *string, void *font);

void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font);

void writeText(std::string score,std::string state);