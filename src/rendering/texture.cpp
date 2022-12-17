#include "texture.hpp"

#define SIZE 64 // Taille de la texture

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

GLubyte Texture3[SIZE*SIZE*4]; 


GLubyte* buildTexture(GLubyte* Texture, int size) {
    int row = 0;
    int columm = 0;
    while (row < size) {

        if (row == 0 || columm == 0 || row == size-1 || columm == size-1) {
            Texture3[4*size*row + 4*columm] = 0;
            Texture3[4*size*row + 4*columm + 1] = 0;
            Texture3[4*size*row + 4*columm + 2] = 0;
            Texture3[4*size*row + 4*columm + 3] = 0;
        }
        else if (row == 1 || columm == 1 || row == size-2 || columm == size-2) {
            Texture3[4*size*row + 4*columm] = 0x77;
            Texture3[4*size*row + 4*columm + 1] = 0x77;
            Texture3[4*size*row + 4*columm + 2] = 0x77;
            Texture3[4*size*row + 4*columm + 3] = 0x77;
        }
        else if (row == 2 || columm == 2 || row == size-3 || columm == size-3) {
            Texture3[4*size*row + 4*columm] = 0x99;
            Texture3[4*size*row + 4*columm + 1] = 0x99;
            Texture3[4*size*row + 4*columm + 2] = 0x99;
            Texture3[4*size*row + 4*columm + 3] = 0x99;
        }
        else if (row == 3 || columm == 3 || row == size-4 || columm == size-4) {
            Texture3[4*size*row + 4*columm] = 0xBB;
            Texture3[4*size*row + 4*columm + 1] = 0xBB;
            Texture3[4*size*row + 4*columm + 2] = 0xBB;
            Texture3[4*size*row + 4*columm + 3] = 0xBB;
        }
        else if (row == 4 || columm == 4 || row == size-5 || columm == size-5) {
            Texture3[4*size*row + 4*columm] = 0xDD;
            Texture3[4*size*row + 4*columm + 1] = 0xDD;
            Texture3[4*size*row + 4*columm + 2] = 0xDD;
            Texture3[4*size*row + 4*columm + 3] = 0xDD;
        } else {
            Texture3[4*size*row + 4*columm] = 0xFF;
            Texture3[4*size*row + 4*columm + 1] = 0xFF;
            Texture3[4*size*row + 4*columm + 2] = 0xFF;
            Texture3[4*size*row + 4*columm + 3] = 0xFF;
        }

        columm++;
        if (columm==size) {
            row++;
            columm=0;
        }
    }
}

GLuint Nom;
void initTexture() { 	
    glClearColor(0,0,0,0); 	//Change la couleur du fond
    glEnable(GL_DEPTH_TEST); 	//Active le depth test
    glEnable(GL_TEXTURE_2D); 	//Active le texturing
    glGenTextures(1,&Nom); 	//Genere un numero de texture
    glBindTexture(GL_TEXTURE_2D,Nom); 	//Selectionne ce numero
    buildTexture(Texture3,SIZE);
    glTexImage2D (
        GL_TEXTURE_2D, 	//Type : texture 2D
        0, 	//Mipmap : aucun
        4, 	//Couleurs : 4
        SIZE, 	//Largeur : 2
        SIZE, 	//Hauteur : 2
        0, 	//Largeur du bord : 0
        GL_RGBA, 	//Format : RGBA
        GL_UNSIGNED_BYTE, 	//Type des couleurs
        Texture3 	//Addresse de l'image
    ); 	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}