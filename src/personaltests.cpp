#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ObjetsGeometriques.h"

#define X 0
#define Y 1
#define Z 2

static int lighting = 0;
static int lightsActivation[] = { 0,0,0,0,0,0,0,0 };
static int lights[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

static float cameraPos[] = {0.0F,0.0F,-5.0F};

static int mousePos [2] = { 0,0 };
static int mouseDiff[2] = { 0,0 };
static float angle[3] = {0,0,0};

static int wSx = 1000;              // horizontal resolution of the window 
static int wSy = 1000;              // vertical resolution of the window
static int wPx = 50;               // horizontal position of the window 
static int wPy = 50;              // vertical position of the window

// printing mode (1 = full, 0 = lines)
static int printMode = 1;

GLfloat diffuse[] = { 0.5,0.5,0.5,1.0 };
GLfloat specular[] = { 1.0,1.0,1.0,1.0 };
GLfloat shinines[] = { 50.0 };

static float l_angle = 0;
GLfloat l_pos[] = { 0.0,0,0,1 };
GLfloat l_dir[] = {0,0,0};

static float midGrey[] = { 0.5F,0.5F,0.5F, 1 };
static float red[] = { 1.0F,0,0, 1 };
static float cyan[] = { 0,1,1,1 };

static void init(void) {
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_CULL_FACE);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, shinines);


    glLightfv(lights[1], GL_AMBIENT, midGrey);
    glLightfv(lights[2], GL_DIFFUSE, red);
    //glLightfv(lights[3], GL_SPECULAR, cyan);

    gluLookAt(cameraPos[X],cameraPos[Y],cameraPos[Z],0,0,0,0,1,0);
}

static void light(int i) {
    lightsActivation[i] = ~lightsActivation[i];
}

static void reshape(int wx, int wy) {
    wSx = wx;
    wSy = wy;
    glViewport(0, 0, wx, wy);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void scene(void) {
	double sideLength = 1.0;
	int nbFacets = 10;

	glPushMatrix();
  	//glRotatef(rz,0.0F,0.0F,1.0F);
	//glColor3f(0.3F,0.7F,0.3F);
	mySolidCube(sideLength,nbFacets);
	glPopMatrix();
	
}

static void display(void) {
	//Enabling lights
	if (lighting)
      glEnable(GL_LIGHTING);
  	else
      glDisable(GL_LIGHTING);
	
	//selecting lights to activate
	for (int i = 0; i < 8; ++i) {
      	if (lightsActivation[i]) {
        	glEnable(lights[i]);
      	}
      	else {
        	glDisable(lights[i]);
      	}
  	}

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, (printMode) ? GL_FILL : GL_LINE);
    glPushMatrix();
    glRotatef(angle[X],1.0F,0.0F,0.0F);
  	glRotatef(angle[Y],0.0F,1.0F,0.0F);
    scene();
    glPopMatrix();
    
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if ( error != GL_NO_ERROR )
        printf("Attention erreur %d\n",error);
}

static void mouseMotion(int x, int y) {
    printf("MM %4d %4d\n", x, y);
    mouseDiff[X] = -x + mousePos[X];
    mouseDiff[Y] = y - mousePos[Y];
    mousePos[X] = x;
    mousePos[Y] = y;
    angle[X] += mouseDiff[Y];
    angle[Y] += mouseDiff[X];
}

static void keyboard(unsigned char key, int x, int y) {
    printf("K  %4c %4d %4d\n", key, x, y);
    switch (key) {
    case 0x20:
        printMode = (printMode + 1) % 2;
        glutPostRedisplay();
        break;
    case 0x1B:
        exit(0);
        break;
    }
}

static void idle(void) {
	if(mouseDiff[X]!=0 || mouseDiff[Y]!=0)
  		glutPostRedisplay();
}

static void special(int specialKey,int x,int y) {
	printf("%d\n",specialKey);
    switch(specialKey) {
        case GLUT_KEY_RIGHT :
            //glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT :
            //glutPostRedisplay();
            break; 
        case GLUT_KEY_F10:
            lighting = ~lighting;
            glutPostRedisplay();
            break;
        case GLUT_KEY_F1:
            light(1);
            glutPostRedisplay();
            break;
        case GLUT_KEY_F2:
            light(2);
            glutPostRedisplay();
            break;
        case GLUT_KEY_F3:
            light(3);
            glutPostRedisplay();
            break;
        case GLUT_KEY_F4:
            light(4);
            glutPostRedisplay();
            break;
        case GLUT_KEY_F5:
            light(5);
            glutPostRedisplay();
            break;
        case GLUT_KEY_F6:
            light(6);
            glutPostRedisplay();
            break;
        case GLUT_KEY_F7:
            light(7);
            glutPostRedisplay();
            break;
    }
}

int main(int argc,char **argv) {
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(wSx,wSy);
  glutInitWindowPosition(50,50); 
  glutCreateWindow("personal test"); 
  init();
  glutIdleFunc(idle);
  glutMotionFunc(mouseMotion);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMainLoop();
  return(0);
}