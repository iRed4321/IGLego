#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "../PNG/ChargePngFile.h" 
#include "construction.h"

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
// static float cameraPos[] = {0.0F,0.0F,20.0F};
// static float cameraTarget[] = {0.0F,0.0F,0.0F};

//parameters for the view of the camera
// static float frustumView[] = {10,10,10,10,-10,-30};

unsigned int textureLego;

static int mousePos [2] = { 0,0 };
static int mouseDiff[2] = { 0,0 };
static float angle[3] = {90,90,125};

static int wTx = 1000;              // horizontal resolution of the window 
static int wTy = 1000;              // vertical resolution of the window
static int wPx = 50;               // horizontal position of the window 
static int wPy = 50;              // vertical position of the window


static float rotationX = 1;
static float rotationY = 1;
static float rotationZ = 1;

static float zoom = -5.0F;

static GLenum currentView = GL_FILL;

static const float noir[] = { 0.0F,0.0F,0.0F,1.0F };
static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const float gris[] = { 0.7F,0.7F,0.7F,1.0F };
static const float jaune[] = { 1.0F,1.0F,0.0F,1.0F };
// static const float rouge[] = { 1.0F,0.0F,0.0F,1.0F };
static const float vert[] = { 0.0F,1.0F,0.0F,1.0F };
static const float bleu[] = { 0.0F,0.0F,1.0F,1.0F };

static bool animation = false;

static float angle1 = 7;
static float angle2 = 0;


static unsigned char *image(int nc, int nl)
{
  unsigned char *img = (unsigned char *)calloc(3 * nc * nl, sizeof(unsigned char));
  if (!img)
    return NULL;
  unsigned char *p = img;
  for (int l = 0; l < nl; l++)
    for (int c = 0; c < nc; c++)
    {
      if (l % 2 == 0)
      {
        if (c % 2 == 0)
        {
          p[0] = 0x00;
          p[1] = 0x00;
          p[2] = 0x00;
        }
        else
        {
          p[0] = 0xFF;
          p[1] = 0x00;
          p[2] = 0x00;
        }
      }
      else
      {
        if (c % 2 == 0)
        {
          p[0] = 0x00;
          p[1] = 0xFF;
          p[2] = 0x00;
        }
        else
        {
          p[0] = 0x00;
          p[1] = 0x00;
          p[2] = 0xFF;
        }
      }
      p += 3;
    }
  return img;
}

static int initTexture(char* filename) {
  unsigned int textureID = 0;
  glPixelStorei(GL_UNPACK_ALIGNMENT,1); 
  glGenTextures(1,&textureID);
  glBindTexture(GL_TEXTURE_2D,textureID);
  { int rx = 16;
    int ry = 16;
    unsigned char *img1 = chargeImagePng(filename,&rx,&ry);
    if (img1) {
      glTexImage2D(GL_TEXTURE_2D,0,3,rx,ry,0,GL_RGB,GL_UNSIGNED_BYTE,img1);
      free(img1);
      printf("Texture chargee %d\n",textureID);
    }else {
      glDeleteTextures(1,&textureID);
      textureID = 0;
      printf("Texture non chargee\n");
    }
  }

  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT); 
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); 
  glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); 

  return textureID;
}

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
  const GLfloat shininess[] = { 5.0 };
  glMaterialfv(GL_FRONT,GL_AMBIENT,noir);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,blanc);
  glMaterialfv(GL_FRONT,GL_SPECULAR,gris);
  glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,blanc);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,jaune);
  glLightfv(GL_LIGHT2,GL_DIFFUSE,bleu);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_LIGHTING);
  textureLego = initTexture("lego.png");
}

static void light(int i) {
    lightsActivation[i] = ~lightsActivation[i];
}

/* Scene dessinee                               */

static void scene(void) {

	glPushMatrix();
    glScalef(.2,.2,.2);

    //textured_plate4x8_4509897(legoTexture);
    //pinWithFrictionRidgesLengthwiseAndPinHole_6282140();
    //liftarm3x5LShapeWithQuarterEllipseThin_6327162();
    construction(angle1, angle2);
    //testDemiConnexions();
    //testPieceEnCours();
    //testPieceEnCoursNathan(angle1);
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
  glTranslatef(0.0F,0.0F,zoom);
  glRotatef(angle[X],1.0F,0.0F,0.0F);
  glRotatef(angle[Y],0.0F,1.0F,0.0F);
  glRotatef(angle[2],0.0F,0.0F,1.0F);
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
  //glOrtho(-3.0,3.0,-3.0,3.0,0.0,10.0);
  gluPerspective(60.0, (float)wx/(float)wy, 0.1, 100.0);
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
  glTranslatef(0, 0, zoom);
  glRotatef(rotationY, 0, 1, 0);
  glTranslatef(0, 0, -zoom);
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

    case '+':
      zoom += 0.5F;
      glutPostRedisplay();
      break;

    case '-':
      zoom -= 0.5F;
      glutPostRedisplay();
      break;

  }
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */
/*   - touches de fonction                      */

static void special(int specialKey,int x,int y) {
  //printf("S  %4d %4d %4d\n",specialKey,x,y);

  switch (specialKey)
  {
    case GLUT_KEY_UP:
      angle1 += 1;
      if (angle1<7){
        angle1 = 7;
      }
      if (angle1>60){
        angle1 = 60;
      }
      glutPostRedisplay();
      break;

    case GLUT_KEY_DOWN:
      angle1 -= 1;
      if (angle1<5){
        angle1 = 5;
      }
      if (angle1>60){
        angle1 = 60;
      }
      glutPostRedisplay();
      break;

    case GLUT_KEY_LEFT:
      angle2 -= 1;
      if (angle2>20){
        angle2 = 20;
      }
      if (angle2<-20){
        angle2 = -20;
      }
      glutPostRedisplay();
      break;

    case GLUT_KEY_RIGHT:
      angle2 += 1;
      if (angle2>20){
        angle2 = 20;
      }
      if (angle2<-20){
        angle2 = -20;
      }
      glutPostRedisplay();
      break;
    case GLUT_KEY_F10:
      lighting = ~lighting;
      glutPostRedisplay();
      break;
    case GLUT_KEY_F1:
      light(0);
      glutPostRedisplay();
      break;
    case GLUT_KEY_F2:
      light(1);
      glutPostRedisplay();
      break;
    case GLUT_KEY_F3:
      light(2);
      glutPostRedisplay();
      break;
    case GLUT_KEY_F4:
      light(3);
      glutPostRedisplay();
      break;
    case GLUT_KEY_F5:
      light(4);
      glutPostRedisplay();
      break;
    case GLUT_KEY_F6:
      light(5);
      glutPostRedisplay();
      break;
    case GLUT_KEY_F7:
      light(6);
      glutPostRedisplay();
      break;
    case GLUT_KEY_F8:
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
/*
static void passiveMouseMotion(int x,int y) {

}
*/

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
