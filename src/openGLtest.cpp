#include "rendering/Renderer.hpp"
#include "./physics/GameCore.hpp"
#include <thread>
#include <memory>

 
Renderer rd;
std::shared_ptr<GameCore> corePtr = std::make_shared<GameCore>(Vector(5,5,24));



void renderLoopGrid() {
    rd.renderRoutineGrid();
    //glutPostRedisplay();
}

void renderLoopScore() {
    rd.renderRoutineScore();
    //glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int, int) {
    switch (key) {
        case 27: // ESC
            exit(0);
            break;

        case ' ':

            break;

        case 'a':
            corePtr->rotate(Shape::ROTATION_AXIS::Z,Shape::ROTATION_DIRECTION::L);
            break;
        
        case 'e':
            corePtr->rotate(Shape::ROTATION_AXIS::Z,Shape::ROTATION_DIRECTION::R);
            break;

        case 'z':
            corePtr->rotate(Shape::ROTATION_AXIS::X,Shape::ROTATION_DIRECTION::L);
            break;
        
        case 'x':
            corePtr->rotate(Shape::ROTATION_AXIS::X,Shape::ROTATION_DIRECTION::R);
            break;

        case 'q':
            corePtr->rotate(Shape::ROTATION_AXIS::Y,Shape::ROTATION_DIRECTION::L);
            break;
        
        case 'd':
            corePtr->rotate(Shape::ROTATION_AXIS::Y,Shape::ROTATION_DIRECTION::R);
            break;
        

        default:
            break;
    }
    glutPostRedisplay();
}

void proccessSpecialKeys(int key, int, int) {
    switch (key) {
        case GLUT_KEY_UP:
            corePtr->translate(Vector(1,0,0));
            break;
        case GLUT_KEY_DOWN:
            corePtr->translate(Vector(-1,0,0));
            break;
        case GLUT_KEY_LEFT:
            corePtr->translate(Vector(0,-1,0));
            break;
        case GLUT_KEY_RIGHT:
            corePtr->translate(Vector(0,1,0));
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    std::thread coreThread(&GameCore::startThread,corePtr);
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