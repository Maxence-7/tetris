#include "rendering/Renderer.hpp"
 
Renderer rd;

void renderLoop() {
    rd.renderRoutine();
    //glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC
            exit(0);
            break;
        
        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    rd = Renderer(argc, argv);
    rd.setDisplayFunc(renderLoop);
    glutKeyboardFunc(processNormalKeys);
    glutMainLoop();
    return 0;
}