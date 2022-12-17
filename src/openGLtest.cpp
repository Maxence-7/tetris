#include "rendering/Renderer.hpp"
#include "./physics/core/game/GameCore.hpp"
#include <thread>
#include <memory>
#include <SFML/Audio/Music.hpp>

// 
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

void renderLoopPreview() {
    rd.renderRoutinePreview();
    //glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int, int) {
    switch (key) {
        case 27: // ESC
            corePtr->togglePause();
            break;

        case ' ':
            corePtr->dropUntilHit();
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
    //std::thread T(&run);
    /* // Music playing
    sf::Music music;
    if (!music.openFromFile("tetris.ogg")) {
        //return 0;
    }
    music.setVolume(15);
    music.setLoop(true);
    music.play(); */

    // Start GameCore
    std::thread coreThread(&GameCore::startThread,corePtr);
    
    // INIT RENDERER
    rd = Renderer(argc, argv, corePtr);
    glutSetWindow(rd.getParentWin());
    rd.setDisplayFunc(renderLoopGrid);
    glutSetWindow(rd.getScoreWin());
    rd.setDisplayFunc(renderLoopScore);
    glutSetWindow(rd.getPreviewWin());
    rd.setDisplayFunc(renderLoopPreview);
    glutSetWindow(rd.getParentWin());

    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(proccessSpecialKeys);
    glutMainLoop();
    return 0;
}