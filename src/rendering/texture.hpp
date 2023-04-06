#pragma once

#include <GL/glut.h>
#include <GL/gl.h>

/// @brief Procedural shaded texture (size by size texture) 
/// @param Texture 
/// @param size 
void buildTexture(GLubyte* Texture, int size);

void initTexture();