#include "texture.hpp"

GLubyte Texture[16] = { //Image 2x2
    0,0,0,0, 0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF, 0,0,0,0,
    
};

GLubyte Texture2[64] = { //Image 4x4
    0,0,0,0,            0,0,0,0,                    0,0,0,0,                    0,0,0,0,
    0,0,0,0,            0xFF,0xFF,0xFF,0xFF,        0xFF,0xFF,0xFF,0xFF,        0,0,0,0,
    0,0,0,0,            0xFF,0xFF,0xFF,0xFF,        0xFF,0xFF,0xFF,0xFF,        0,0,0,0,
    0,0,0,0,            0,0,0,0,                    0,0,0,0,                    0,0,0,0
};

GLubyte* buildTexture(int size) {

}

GLuint Nom;
void initTexture() { 	
    glClearColor(0,0,0,0); 	//Change la couleur du fond
    glEnable(GL_DEPTH_TEST); 	//Active le depth test
    glEnable(GL_TEXTURE_2D); 	//Active le texturing
    glGenTextures(1,&Nom); 	//Genere un numero de texture
    glBindTexture(GL_TEXTURE_2D,Nom); 	//Selectionne ce numero
    glTexImage2D (
        GL_TEXTURE_2D, 	//Type : texture 2D
        0, 	//Mipmap : aucun
        4, 	//Couleurs : 4
        4, 	//Largeur : 2
        4, 	//Hauteur : 2
        0, 	//Largeur du bord : 0
        GL_RGBA, 	//Format : RGBA
        GL_UNSIGNED_BYTE, 	//Type des couleurs
        Texture2 	//Addresse de l'image
    ); 	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}