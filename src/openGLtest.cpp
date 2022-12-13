#include "rendering/Renderer.hpp"
 
Renderer rd;

void renderLoopGrid() {
    rd.renderRoutineGrid();
    //glutPostRedisplay();
}

void renderLoopScore() {
    rd.renderRoutineScore();
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
    glutSetWindow(rd.parentWin);
    rd.setDisplayFunc(renderLoopGrid);
    glutSetWindow(rd.scoreWin);
    rd.setDisplayFunc(renderLoopScore);
    glutSetWindow(rd.parentWin);

    glutKeyboardFunc(processNormalKeys);
    glutMainLoop();
    return 0;
}