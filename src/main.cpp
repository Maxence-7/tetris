#include "rendering/Renderer.hpp"
#include "./physics/core/game/GameCore.hpp"
#include <thread>
#include <memory>
#include <SFML/Audio/Music.hpp>
#include "./physics/utils/Vector3D.hpp"

std::shared_ptr<GameCore> corePtr = std::make_shared<GameCore>(GameCore::Size_t(5,5,24));
std::shared_ptr<Renderer> rdPtr;


class Mouse {
    public:
    int x;
    int y;
    double angle;
    Mouse(int x, int y,double angle) : x(x), y(y),angle(angle) {}
};

std::unique_ptr<Mouse> mousePtr = nullptr;

void onMove(int x, int) {
    if (mousePtr != nullptr) {
        double newAngle = (mousePtr->angle+200.*(x-mousePtr->x))/360.;
        rdPtr->setAngleCam(newAngle);
    } 
    
}

void onClick(int button, int state,int x,int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mousePtr = std::make_unique<Mouse>(x,y,rdPtr->getAngleCam());
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        mousePtr.release();
        mousePtr = nullptr;
    }
}




void renderLoopGrid() {
    rdPtr->renderRoutineGrid();
    //glutPostRedisplay();
}

void renderLoopScore() {
    rdPtr->renderRoutineScore();
    //glutPostRedisplay();
}

void renderLoopPreview() {
    rdPtr->renderRoutinePreview();
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

void processSpecialKeys(int key, int, int) {
    double angle = rdPtr->getAngleCam();
    Vector3D<int> v;
    if (315  <= angle || angle < 45) {
        v = Vector3D<int>(0,1,0);
    } else if (45 <= angle && angle < 135) {
        v = Vector3D<int>(1,0,0);
    } else if (135 <= angle && angle < 225) {
        v = Vector3D<int>(0,-1,0);
    } else if (225 <= angle && angle < 315) {
        v = Vector3D<int>(-1,0,0);
    } else {
        std::cout << "Cur angle error : "<<angle <<std::endl;
    }
    
    switch (key) {
        case GLUT_KEY_UP:
            corePtr->translate(v);
            break;
        case GLUT_KEY_DOWN:
            corePtr->translate(-v);
            break;
        case GLUT_KEY_LEFT:
            corePtr->translate(-Vector3D<int>(v.y,v.x,0));
            break;
        case GLUT_KEY_RIGHT:
            corePtr->translate(Vector3D<int>(v.y,v.x,0));
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    // Start GameCore
    std::thread coreThread(&GameCore::startThread,corePtr);
    // INIT RENDERER
    //rd = Renderer(argc, argv, corePtr);
    rdPtr = std::make_shared<Renderer>(argc,argv,corePtr);
    glutSetWindow(rdPtr->getParentWin());
    rdPtr->setDisplayFunc(renderLoopGrid);
    glutSetWindow(rdPtr->getScoreWin());
    rdPtr->setDisplayFunc(renderLoopScore);
    glutSetWindow(rdPtr->getPreviewWin());
    rdPtr->setDisplayFunc(renderLoopPreview);
    glutSetWindow(rdPtr->getParentWin());
    glutMotionFunc(onMove);
    glutMouseFunc(onClick);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutMainLoop();
    return 0;
}