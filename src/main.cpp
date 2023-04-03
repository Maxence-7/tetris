#include "rendering/Renderer.hpp"
#include "./physics/core/game/GameCore.hpp"
#include "./physics/core/multiplayer/ServerCore.hpp"
#include "./physics/core/multiplayer/ClientCore.hpp"
#include "./physics/core/multiplayer/NetworkCore.hpp"

//#include <thread>
#include <memory>
#include <SFML/Audio/Music.hpp>
#include <SFML/Network.hpp>
#include "./physics/utils/Vector3D.hpp"
#include <boost/program_options.hpp>

#include <iostream>
std::shared_ptr<GameCore> corePtr = nullptr;
std::shared_ptr<Renderer> rdPtr = nullptr;
std::unique_ptr<ClientCore> cliPtr = nullptr;
std::unique_ptr<ServerCore> serPtr = nullptr;

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





namespace po = boost::program_options;
int main(int argc, char *argv[]) {
    bool is2DMode; 
    try {
        po::options_description desc{"Options"};
        desc.add_options()
            ("help,h", "Help screen")
            ("2d", po::bool_switch(&is2DMode), "2D Mode, only works if you start a server or if you play local.")
            ("height,", po::value<unsigned>()->default_value(24u), "Change maximum height of the allowed space.")
            ("base,b", po::value<unsigned>()->default_value(5u), "Change maximum base of the allowed space.")
            ("server,s", po::value<unsigned>(), "Specify number of clients allowed to connect to the game.")
            ("client,c", po::value<std::string>(), "Specify the ip to connect to")
            ("username,u", po::value<std::string>(), "Specify the used username for server or client. If none is indicated, the IP will be the username")
            ("port,p", po::value<NetworkCore::port_t>()->default_value(NetworkCore::DEFAULT_PORT), "Specify a port used by client/server. If none, default port will be used.");
        po::variables_map vm;
        po::store(parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        
        

        if (vm.count("help")){
            std::cout << desc << '\n';
        } else {
            GameCore::Size_t size;
            if (is2DMode) {
                size = GameCore::Size_t(vm["base"].as<unsigned>(),1,vm["height"].as<unsigned>());
            } else {
                size = GameCore::Size_t(vm["base"].as<unsigned>(),vm["base"].as<unsigned>(),vm["height"].as<unsigned>());
            }
            if (vm.count("server")){
                std::string name;
                if (vm.count("name")) {
                    name = vm["name"].as<std::string>();
                } else {
                    name = sf::IpAddress::getPublicAddress().toString();
                }
                std::shared_ptr<ServerCore> ptr(new ServerCore(size, name, vm["port"].as<ServerCore::port_t>(), vm["server"].as<unsigned>()));
                bool success = ptr->connectToClients();
                if (success) {
                    corePtr = std::dynamic_pointer_cast<GameCore>(ptr);
                }

            } else if (vm.count("client")) {
                try {
                    std::string name;
                    if (vm.count("name")) {
                        name = vm["name"].as<std::string>();
                    } else {
                        name = sf::IpAddress::getPublicAddress().toString();
                    }
                    std::shared_ptr<ClientCore> ptr(new ClientCore(name,vm["port"].as<ClientCore::port_t>()));
                    sf::IpAddress ip(vm["client"].as<std::string>());
                    bool success = ptr->initConnection(ip);
                    if (success) {
                        corePtr = std::dynamic_pointer_cast<GameCore>(ptr);
                    }

                    
                } catch (...) {
                    std::cout << "Can't cast " << vm["client"].as<std::string>() << " to a correct ip." << std::endl;
                    return -1;
                }
              
            } else {
                corePtr = std::make_shared<GameCore>(size);    
            }

            if (corePtr != nullptr) {
                std::thread coreThread(&GameCore::startThread,corePtr);  
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
                coreThread.join();           
            }

            
        }
    } catch (const po::error &ex) {
        std::cerr << ex.what() << '\n';
    }
}