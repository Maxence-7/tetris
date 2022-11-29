#include "rendering/Renderer.hpp"
 
int main(int argc, char** argv) {
    Renderer rd = Renderer(argc, argv);
    rd.setDisplayFunc(displayRect1);
    rd.refresh();
    glutMainLoop();
    return 0;
}