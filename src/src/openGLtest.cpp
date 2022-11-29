#include <GL/glut.h>
 
void displayMe(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    /*glBegin(GL_POLYGON);
        glVertex3f(0.5, 0.0, 0.5);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
        glVertex3f(0.0, 0.0, 0.5);
    glEnd();*/

    glRectf(0,0,0.5,0.5);
    glFlush();
}
 
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tetris");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}