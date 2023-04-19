#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "ObjetsGeometriques.h"
#include "LegoBricks.h"

//makes the use of 3D arrays clearer
#define X 0
#define Y 1
#define Z 2

//makes the use of glFrustum parameters clearer
#define LEFT 0
#define RIGHT 1
#define BOTTOM 2
#define TOP 3 
#define CMIN 4
#define CMAX 5



static int lighting = 1;
static int lightsActivation[] = { 0,1,1,0,0,0,0,0 };
static int lights[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

//parameters for gluLookAt
static float cameraPos[] = {0.0F,0.0F,20.0F};
static float cameraTarget[] = {0.0F,0.0F,0.0F};

//parameters for the view of the camera
static float frustumView[] = {10,10,10,10,-10,-30};


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
    // glEnable(GL_CULL_FACE);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shinines);


    glLightfv(lights[1], GL_AMBIENT, midGrey);
    glLightfv(lights[2], GL_DIFFUSE, red);
    glLightfv(lights[3], GL_SPECULAR, cyan);

    frustumView[LEFT] = 10 ;
    frustumView[RIGHT] = 10;
    frustumView[BOTTOM] = 10;
    frustumView[TOP] = 10;
    frustumView[CMIN] = -5;
    frustumView[CMAX] = -40;

    glFrustum(frustumView[LEFT],frustumView[RIGHT],frustumView[BOTTOM],frustumView[TOP],frustumView[CMIN],frustumView[CMAX]);
    cameraPos[X] = 0 ;
    cameraPos[Y] = 0;
    cameraPos[Z] = 50;
    cameraTarget[X] = 0 ;
    cameraTarget[Y] = 0 ;
    cameraTarget[Z] = 0 ;
    gluLookAt(cameraPos[X],cameraPos[Y],cameraPos[Z],cameraTarget[X],cameraTarget[Y],cameraTarget[Z],0,1,0);
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
    //gluPerspective(10,(double)wx/(double)wy, 10, 100); // -> pas bien reglé
    glFrustum(frustumView[LEFT],frustumView[RIGHT],frustumView[BOTTOM],frustumView[TOP],frustumView[CMIN],frustumView[CMAX]);
    //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void scene(void) {
	double sideLength = 1.0;
	int nbFacets = 40;

	glPushMatrix();
  	//glRotatef(rz,0.0F,0.0F,1.0F);
	//glColor3f(0.3F,0.7F,0.3F);
	//mySolidCube(sideLength,nbFacets);
    glScalef(0.25F,0.25F,0.25F);
    

    //Si vous voilez voir un peu mieux, passez en fil de fer (barre espace) 
    
    glPushMatrix();
    glTranslatef(0,-3,0);
    plate4x8_4509897(nbFacets,nbFacets);
    glPopMatrix();

    glTranslatef(-4.5,0,-3.5);
    technicLever3x3m90deg__6271810(nbFacets,nbFacets);
    glTranslatef(4, 0, 0);
    liftarmThin1x2AxleHoles_4163533(nbFacets,nbFacets);
    glTranslatef(2.2,0,0);
    axle4_370526();
    glTranslatef(1.2,0,0);
    axle4WithCenterStop_4666999();
    glTranslatef(-6,0,2);
    axle2Notched_4142865();
    glTranslatef(1.3,0,0);
    axle3_4211815();
    glTranslatef(2.2,0,0);
    gear8ToothType2_6012451(nbFacets,nbFacets);
    glTranslatef(2.2,0,0);
    axle5WithStop_6159763();
    glTranslatef(-5,0,2);
    axleAndPinConnector1_6332573();
    glTranslatef(3,0,0);
    axleAndPinConnectorPerpendicular3LWith2PinHoles_6330960();
    glTranslatef(-4,2,0);
    liftarmThick(5);
    //classicBar(1.0,4,32,32);
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
  glutCreateWindow("TESTING"); 
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