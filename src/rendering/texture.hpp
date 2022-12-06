#pragma once

#include <GL/glut.h>
#include <GL/gl.h>

GLubyte Texture[16] = {
    0,0,0,0, 0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF, 0,0,0,0
};
	//Image (2x2)
GLuint Nom;
void initTexture() { 	
    glClearColor(.5,.5,.5,0); 	//Change la couleur du fond
    glEnable(GL_DEPTH_TEST); 	//Active le depth test
    glEnable(GL_TEXTURE_2D); 	//Active le texturing
    glGenTextures(1,&Nom); 	//G�n�re un n� de texture
    glBindTexture(GL_TEXTURE_2D,Nom); 	//S�lectionne ce n�
    glTexImage2D (
        GL_TEXTURE_2D, 	//Type : texture 2D
        0, 	//Mipmap : aucun
        4, 	//Couleurs : 4
        2, 	//Largeur : 2
        2, 	//Hauteur : 2
        0, 	//Largeur du bord : 0
        GL_RGBA, 	//Format : RGBA
        GL_UNSIGNED_BYTE, 	//Type des couleurs
        Texture 	//Addresse de l'image
    ); 	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}