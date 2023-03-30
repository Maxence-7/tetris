#include "Renderer.hpp"
#include <omp.h>

#define _2D 1000
#define _3D 1001

#define FPS 60

double angle = 60.0;
std::shared_ptr<GameCore> gc;
int parentWin;
int scoreWin;
int previewWin;

Renderer::Renderer() {

}

Renderer::Renderer(int argc, char** argv, std::shared_ptr<GameCore> c_gc) : m_gc(c_gc) {
    gc = m_gc;
    glutInit(&argc, argv);
    glutInitWindowSize(600, 900);
    glutInitWindowPosition(100, 100);
    parentWin = glutCreateWindow("Tetris");
    scoreWin = glutCreateSubWindow(parentWin,300, 300, 300, 900);
    previewWin = glutCreateSubWindow(parentWin,300, 00, 300, 300);

    glutSetWindow(parentWin);
    if (MODE == _2D) {
        glutInitDisplayMode(GLUT_NORMAL);
    }
    if (MODE == _3D) {
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutReshapeFunc(reshape);
        glEnable(GL_DEPTH_TEST);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
        initTexture();
        glutTimerFunc(1000/FPS,timer,0);
    }

    glutSetWindow(scoreWin);
    if (MODE == _3D) {
        glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
        glutReshapeFunc(reshape2);
        //glEnable(GL_DEPTH_TEST);
        //glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
        //initTexture();
        glutTimerFunc(1000/FPS,timer2,0);
    } 

    glutSetWindow(previewWin);
    if (MODE == _3D) {
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutReshapeFunc(reshape3);
        glEnable(GL_DEPTH_TEST);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
        initTexture();
        glutTimerFunc(1000/FPS,timer3,0);
    }
}

Renderer::~Renderer() {
}

void Renderer::absoluteDrawRect2D(int x1, int y1, int x2, int y2, Color col) {
    double width = glutGet(GLUT_WINDOW_WIDTH);
    double height = glutGet(GLUT_WINDOW_HEIGHT);
    glColor3f(col.r,col.g,col.b);
    glRectf(2*x1/width-1,2*y1/height-1,2*x2/width-1,2*y2/height-1);
}

void Renderer::absoluteDrawRect3D(Vector3D<double>& vect1, Vector3D<double>& vect2, Color col) {
    const Vector3D<double> v(-1,-1,1);
    Vector3D<double> v1 = vect1+v;
    Vector3D<double> v2 = vect2+v;
    glRect3D(v1, v2, col);
}

void Renderer::setDisplayFunc(void (*f)()) {
    displayFunction = f;
    glutDisplayFunc(displayFunction);
}

void Renderer::renderRoutineGrid() {
    glutSetWindow(parentWin);
    GameCore::Container_t<double> map = gc->render(offset);
    Color col = Color(1,0,0);
    if (MODE == _3D) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glClearColor(0.5,0.5,0.5,0);
        // Camera positionning
        glTranslatef(-10,-15,-35);
        glRotatef(-70,1,0,0);
        glRotatef(2.5,0,1,0);
        // Animation (rotation)
        glRotatef(angleCam,0,0,1);

        glPointSize(3.0);  

        glBegin(GL_LINES);
        Color col = Color(0.1,0.1,0.1);
        glColor3f(col.r,col.g,col.b);
        Vector3D<double> size = Vector3D<double>(gc->getSize());
        drawBorders(size);
        glEnd();

        //#pragma omp parallel for //GOTTA GO FAST
        for (auto const& [vec,col] : map) {
            glPushMatrix();
            glTranslatef(vec.x,vec.y,vec.z);
            glBegin(GL_QUADS);
            absoluteDrawRect3D(v1,v2,col);
            glEnd();
            glPopMatrix();
        }
    }
    if (MODE == _2D) {
        glClear(GL_COLOR_BUFFER_BIT);
        for (int x = 50; x<550 ; x+=50) {
            for (int y = 50; y<850 ; y+=50) {
                absoluteDrawRect2D(x,y,x+45,y+45,col);
            }
        }
    }
    glFlush();
}
void Renderer::renderRoutineScore() {
    glutSetWindow(scoreWin);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glClearColor(0.2,0.2,0.2,0);
    glClear(GL_COLOR_BUFFER_BIT);

    Color col = Color(0.7,0.7,0.7);
    glColor3f(col.r,col.g,col.b);
    writeText(std::to_string(gc->getScore()),std::to_string((int)gc->getState()));

    glFlush();
}
void Renderer::renderRoutinePreview() {
    glutSetWindow(previewWin);
    GameCore::Container_t<double> map = gc->renderNextShape(offset);
    Color col = Color(1,0,0);
    if (MODE == _3D) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glClearColor(0.1,0.1,0.1,0);
        // Camera positionning
        glTranslatef(0,0,-5);
        glRotatef(-70,1,0,0);
        glRotatef(2.5,0,1,0);
        // Animation (rotation)
        glRotatef(angle,0,0,1);

        Vector3D<double> moy = getAvgPos(map);
        for (auto const& [vec,col] : map) {
            glPushMatrix();
            glTranslatef(vec.x-moy.x,vec.y-moy.y,vec.z-moy.z);
            glBegin(GL_QUADS);
            Renderer::absoluteDrawRect3D(v1,v2,col);
            glEnd();
            glPopMatrix();
        }
    }
}

int Renderer::getParentWin() {
    return parentWin;
}
int Renderer::getScoreWin() {
    return scoreWin;
}
int Renderer::getPreviewWin() {
    return previewWin;
}

void Renderer::setAngleCam(double ang) {
    angleCam=ang;
}

double Renderer::getAngleCam() const {
    return angleCam;
}

void reshape(int w, int h) {
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,2.0,50.0);
    glMatrixMode(GL_MODELVIEW);
}

void reshape2(int w, int h) {
	float L; 
	float H; 

	glViewport(0,0,w,h); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	if (w<=h) 
	{ 
	  if (w==0) H=900; 
	  else H=(GLfloat) (300*h/w); 
	  L=300; 
	} 
	else 
	{ 
	  H=900; 
	  if (h==0) L=300; 
	  else L=(GLfloat) (900*w/h); 
	} 
	gluOrtho2D(-L/2,L/2,-H/2,H/2); 
}

void reshape3(int w, int h) {
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,2.0,50.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutSetWindow(parentWin);
    glutPostRedisplay();
    glutReshapeWindow(600, 900);
    glutTimerFunc(1000/FPS,timer,0);

    angle+=0.5;
    if (angle>360.0)
        angle-=360.0;
}

void timer2(int) {
    glutSetWindow(scoreWin);
    glutPostRedisplay();
    glutTimerFunc(1000/1,timer2,0);

    writeText(std::to_string(gc->getScore()),std::to_string((int)gc->getState()));
}

void timer3(int) {
    glutSetWindow(previewWin);
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer3,0);
}