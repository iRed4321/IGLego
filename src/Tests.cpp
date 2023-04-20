#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

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

/* Variables globales                           */

static int lighting = 1;
static int lightsActivation[] = { 1,0,0,0,0,0,0,0 };
static int lights[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

//parameters for gluLookAt
static float cameraPos[] = {0.0F,0.0F,20.0F};
static float cameraTarget[] = {0.0F,0.0F,0.0F};

//parameters for the view of the camera
static float frustumView[] = {10,10,10,10,-10,-30};


static int mousePos [2] = { 0,0 };
static int mouseDiff[2] = { 0,0 };
static float angle[3] = {0,0,0};

static int wTx = 1000;              // horizontal resolution of the window 
static int wTy = 1000;              // vertical resolution of the window
static int wPx = 50;               // horizontal position of the window 
static int wPy = 50;              // vertical position of the window


static float rotationX = 1;
static float rotationY = 1;
static float rotationZ = 1;

static GLenum currentView = GL_FILL;

static float rouge[4] = { 1.0F,0.0F,0.0F,0.5F };
static float vert[4] = { 0.0F,1.0F,0.0F,0.5F };
static float bleu[4] = { 0.0F,0.0F,1.0F,0.5F };

static bool animation = false;

static int facettes_x = 1;
static int facettes_y = 1;

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_CULL_FACE);
}


static void light(int i) {
    lightsActivation[i] = ~lightsActivation[i];
}

/* Scene dessinee                               */

static void scene(void) {
	double sideLength = 1.0;
	int nbFacets = 40;

	glPushMatrix();
    glScalef(0.5F,0.5F,0.5F);

    glMaterialfv(GL_FRONT,GL_DIFFUSE,rouge);

    //Si vous voulez voir un peu mieux, passez en fil de fer (barre espace) 
    
    // glPushMatrix();
    // glTranslatef(0,-3,0);
    // plate4x8_4509897(nbFacets,nbFacets);
    // glPopMatrix();
    
    // glTranslatef(-4.5,0,-3.5);
    // technicLever3x3m90deg__6271810(nbFacets,nbFacets);
    // glTranslatef(4, 0, 0);
    // liftarmThin1x2AxleHoles_4163533(nbFacets,nbFacets);
    // glTranslatef(2.2,0,0);
    // axle4_370526();
    // glTranslatef(1.2,0,0);
    // axle4WithCenterStop_4666999();
    // glTranslatef(-6,0,2);
    // axle2Notched_4142865();
    // glTranslatef(1.3,0,0);
    // axle3_4211815();
    // glTranslatef(2.2,0,0);
    // gear8ToothType2_6012451(nbFacets,nbFacets);
    // glTranslatef(2.2,0,0);
    // axle5WithStop_6159763();
    // glTranslatef(-5,0,2);
    // axleAndPinConnector1_6332573();
    // glTranslatef(3,0,0);
    // axleAndPinConnectorPerpendicular3LWith2PinHoles_6330960();
    // glTranslatef(-4,2,0);
    // liftarmThick(5);
    // axleConnectorSmoothWithXHoleOrientation_4512360();

    liftarm3x3LShapeThin_6271810();

	glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

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
  glPolygonMode(GL_FRONT_AND_BACK, currentView);
  
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

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int wx,int wy) {
  wTx = wx; 
  wTy = wy; 
  glViewport(0,0,wx,wy); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-3.0,3.0,-3.0,3.0,-3.0,3.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
  if(mouseDiff[X]!=0 || mouseDiff[Y]!=0)
  		glutPostRedisplay();
}

static void idleAnim(void){
  glRotatef(rotationX, 1, 0, 0);
  glRotatef(rotationY, 0, 1, 0);
  glRotatef(rotationZ, 0, 0, 1);
  glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key,int x,int y) {
  printf("K  %4c %4d %4d\n",key,x,y);
  switch(key){
    //espace
    case 0x20:
      currentView = (currentView == GL_FILL) ? GL_LINE : GL_FILL;
      glutPostRedisplay();
      break;

    //touche a
    case 0x61:
      animation = !animation;
      if (animation) {
        glutIdleFunc(idleAnim);
      } else{
        glutIdleFunc(idle);
      }
      glutPostRedisplay();
      break;

  }
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */
/*   - touches de fonction                      */

static void special(int specialKey,int x,int y) {
  printf("S  %4d %4d %4d\n",specialKey,x,y);

  switch (specialKey)
  {
    case GLUT_KEY_UP:
      facettes_x += 1;
      glutPostRedisplay();
      break;

    case GLUT_KEY_DOWN:
      facettes_x -= 1;
      glutPostRedisplay();
      break;

    case GLUT_KEY_LEFT:
      facettes_y -= 1;
      glutPostRedisplay();
      break;

    case GLUT_KEY_RIGHT:
      facettes_y += 1;
      glutPostRedisplay();
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

/* Fonction executee lors de l'utilisation      */
/* de la souris sur la fenetre                  */

static void mouse(int button,int state,int x,int y) {
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x, int y) {
    mouseDiff[X] = -x + mousePos[X];
    mouseDiff[Y] = y - mousePos[Y];
    mousePos[X] = x;
    mousePos[Y] = y;
    angle[X] += mouseDiff[Y];
    angle[Y] += mouseDiff[X];
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans bouton presse                           */

static void passiveMouseMotion(int x,int y) {
}

/* Fonction ex�cut�e automatiquement            */
/* lors de l'ex�cution de la fonction exit()    */

static void clean(void) {
}

/* Fonction principale                          */

int main(int argc,char **argv) {

  atexit(clean);

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(wTx,wTy);
  glutInitWindowPosition(wPx,wPy);
  glutCreateWindow("Test program");
  init();
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  //glutPassiveMotionFunc(passiveMouseMotion);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutDisplayFunc(display);
  glutMainLoop();
  return(0);
}
