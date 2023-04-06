#pragma once

#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include "../physics/utils/Vector3D.hpp"
#include "../physics/utils/Color.hpp"


/// @brief Draw a 3D rectangle of color col based on a corner and its opposite
/// @param vect1 
/// @param vect2 
/// @param col 
void glRect3D(Vector3D<double>& vect1, Vector3D<double>& vect2, Color col);

/// @brief Draw a line based on 2 vertices
/// @param vect1 
/// @param vect2 
void drawLine3D(const Vector3D<double>& vect1, const Vector3D<double>& vect2);

/// @brief Draw the borders of the game
/// @param vec
void drawBorders(Vector3D<double>& vec);

/// @brief Function for writing text on a openGL window
/// @param x 
/// @param y 
/// @param string 
/// @param font 
void vBitmapOutput(double x, double y, char *string, void *font);

void vStrokeOutput(GLfloat x, GLfloat y, char *string, void *font);

/// @brief Update the game interface
/// @param score 
void writeText(std::string score);