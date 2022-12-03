#include "rendering/Renderer.hpp"
 
Renderer rd;

void renderLoop() {
    rd.renderRoutine();
    //glutPostRedisplay();
}

int main(int argc, char** argv) {
    rd = Renderer(argc, argv);
    rd.setDisplayFunc(renderLoop);
    glutMainLoop();
    return 0;
}