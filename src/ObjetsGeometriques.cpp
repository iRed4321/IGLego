/* Objets geometriques modelises par facettes   */
/*  - Cube                                      */
/*  - Cylindre                                  */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Fevrier 2023                                 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#ifndef M_PI
#define M_PI 3.14159
#endif

static void face(float tx,float ty, int n,int m) {
  float dy = ty/m;
  float dx = tx/n;
  glPushMatrix();
  glNormal3f(0.0F,0.0F,1.0F);
  glTranslatef(-tx/2.0F,-ty/2.0F,0.0F);
  for ( int l = 0 ; l < m ; l++) {
    float yf = l * dy;
    float yi = yf + dy;
    float x = 0.0F;
    glBegin(GL_QUAD_STRIP);
    for ( int c = 0 ; c <= n ; c++ ) {
      glVertex2f(x,yi);
      glVertex2f(x,yf);
      x += dx; }
    glEnd(); }
  glPopMatrix();
}

static void mySolidDisc(int ns){

  glBegin(GL_POLYGON);
  float angle = 0;
  float increment = 2*M_PI/ns;
  for(int i = 0; i<ns; ++i){
    glVertex3f(cos(angle),0,sin(angle));
    angle+=increment;
  }
  glEnd();
}

void mySolidCube(int n) {
  double ct = 1;
  glPushMatrix();
  glPushMatrix();
  glTranslatef(0.0F,0.0F,(GLfloat) ct/2.0F);
  face((float) ct,(float) ct,n,n);
  glPopMatrix();
  glPushMatrix();
  glRotatef(90.0F,0.0F,1.0F,0.0f);
  glTranslatef(0.0F,0.0F,(GLfloat) ct/2.0F);
  face((float) ct,(float) ct,n,n);
  glPopMatrix();
  glPushMatrix();
  glRotatef(180.0F,0.0F,1.0F,0.0f);
  glTranslatef(0.0F,0.0F,(GLfloat) ct/2.0F);
  face((float) ct,(float) ct,n,n);
  glPopMatrix();
  glPushMatrix();
  glRotatef(270.0F,0.0F,1.0F,0.0f);
  glTranslatef(0.0F,0.0F,(GLfloat) ct/2.0F);
  face((float) ct,(float) ct,n,n);
  glPopMatrix();
  glPushMatrix();
  glRotatef(90.0F,1.0F,0.0F,0.0f);
  glTranslatef(0.0F,0.0F,(GLfloat) ct/2.0F);
  face((float) ct,(float) ct,n,n);
  glPopMatrix();
  glPushMatrix();
  glRotatef(-90.0F,1.0F,0.0F,0.0f);
  glTranslatef(0.0F,0.0F,(GLfloat) ct/2.0F);
  face((float) ct,(float) ct,n,n);
  glPopMatrix();
  glPopMatrix();
}

void mySolidRectangle(int length, int n) {
  double ct = 1;
  glPushMatrix();
  glScalef((float) length,1.0F,1.0F);
  mySolidCube(n);
  glPopMatrix();
}

void mySolidCylindre(int ns,int nl) {
  double hauteur = 1;
  double rayon = 0.5;
  GLboolean nm = glIsEnabled(GL_NORMALIZE);
  if ( !nm )
    glEnable(GL_NORMALIZE);
  float normale[4];
  glGetFloatv(GL_CURRENT_NORMAL,normale);
  glPushMatrix();
  for ( int j = 0 ; j < nl ; j++ ) {
    float hi =(float) (hauteur/2-j*hauteur/nl);
    float hf =(float) (hi-hauteur/nl);
    glBegin(GL_QUAD_STRIP);
    for( int i = 0 ; i <= ns ; i++ ) {
      float a =(float) ((2*M_PI*i)/ns);
      float cs =(float) cos(a);
      float sn =(float) -sin(a);
      glNormal3f(cs,0.0F,sn);
      float x =(float) (rayon*cs);
      float z =(float) (rayon*sn);
      glVertex3f(x,hi,z);
      glVertex3f(x,hf,z); }
    glEnd(); }
  glPopMatrix();
  glNormal3f(normale[0],normale[1],normale[2]);
  if ( !nm )
    glDisable(GL_NORMALIZE);
}

void mySolidCylindreInverted(int ns,int nl) {
  double hauteur = 1;
  double rayon = 0.5;
  GLboolean nm = glIsEnabled(GL_NORMALIZE);
  if ( !nm )
    glEnable(GL_NORMALIZE);
  float normale[4];
  glGetFloatv(GL_CURRENT_NORMAL,normale);
  glPushMatrix();
  //change culling roation 
  glFrontFace(GL_CW);
  for ( int j = 0 ; j < nl ; j++ ) {
    float hi =(float) (hauteur/2-j*hauteur/nl);
    float hf =(float) (hi-hauteur/nl);
    glBegin(GL_QUAD_STRIP);
    for( int i = 0 ; i <= ns ; i++ ) {
      float a =(float) ((2*M_PI*i)/ns);
      float cs =(float) cos(a);
      float sn =(float) -sin(a);
      glNormal3f(-cs,0.0F,-sn);
      float x =(float) (rayon*cs);
      float z =(float) (rayon*sn);
      glVertex3f(x,hi,z);
      glVertex3f(x,hf,z); }
    glEnd();
  }
  //reset culling roation
  glFrontFace(GL_CCW);
  glPopMatrix();
  glNormal3f(normale[0],normale[1],normale[2]);
  if ( !nm )
    glDisable(GL_NORMALIZE);
}

void mySolidCylindre(int ns,int nl,int bases) {
  double hauteur = 1;
  double rayon = 1;
  
  mySolidCylindre(ns,nl);
  GLboolean nm = glIsEnabled(GL_NORMALIZE);
  if ( !nm )
    glEnable(GL_NORMALIZE);
  float normale[4];
  glGetFloatv(GL_CURRENT_NORMAL,normale);
  glPushMatrix();
  if ( bases ) {
    glBegin(GL_POLYGON);
    glNormal3f(0.0F,1.0F,0.0F);
    for( int i = 0 ; i < ns ; i++ ) {
      float a =(float) ((2*M_PI*i)/ns);
      float cs =(float) cos(a);
      float sn =(float) -sin(a);
      float x =(float) (rayon*cs);
      float z =(float) (rayon*sn);
      glVertex3f(x,(float) (hauteur/2.0F),z); }
    glEnd();
    glBegin(GL_POLYGON);
    glNormal3f(0.0F,-1.0F,0.0F);
    for( int i = 0 ; i < ns ; i++ ) {
      float a =(float) ((2*M_PI*i)/ns);
      float cs =(float) cos(a);
      float sn =(float) sin(a);
      float x =(float) (rayon*cs);
      float z =(float) (rayon*sn);
      glVertex3f(x,(float) (-hauteur/2.0F),z); }
    glEnd(); }
  glPopMatrix();
  glNormal3f(normale[0],normale[1],normale[2]);
  if ( !nm )
    glDisable(GL_NORMALIZE);
}

/* Modelisation geometrique d'un rectangle      */
/* parallele aux axes des x et des z :           */
/*  - de longueur 1                       */
/*  - de hauteur 1                              */
void mySolidFace(){
  glBegin(GL_QUADS);

    glVertex3d(0.5F,0.5F,0);
    glVertex3d(-0.5F,0.5F,0);
    glVertex3d(-0.5F,-0.5F,0);
    glVertex3d(0.5F,-0.5F,0);

  glEnd();
}

void mySolidCross(){

  float hauteur = 1.0F;
  float largeurFace = 0.5F/3.0F;

  glBegin(GL_QUADS);
    glNormal3f(0,0,1);

    glVertex3f(largeurFace/2.0F,hauteur/2.0F,-0.5F);
    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,-0.5F);

    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,-0.5F);
    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,-0.5F);
    
    glNormal3f(1,0,0);

    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,-0.5F);
    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,-0.5F);

    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,-largeurFace/2.0F);

    glNormal3f(0,0,1);

    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,-largeurFace/2.0F);

    glVertex3f(-0.5F,-hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(-0.5F,hauteur/2.0F,-largeurFace/2.0F);

    glNormal3f(1,0,0);

    glVertex3f(-0.5F,hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(-0.5F,-hauteur/2.0F,-largeurFace/2.0F);

    glVertex3f(-0.5F,-hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(-0.5F,hauteur/2.0F,largeurFace/2.0F);
    
    glNormal3f(0,0,-1);

    glVertex3f(-0.5F,hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(-0.5F,-hauteur/2.0F,largeurFace/2.0F);

    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,largeurFace/2.0F);

    glNormal3f(1,0,0);

    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,largeurFace/2.0F);

    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,0.5F);
    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,0.5F);
    
    glNormal3f(0,0,-1);

    glVertex3f(-largeurFace/2.0F,hauteur/2.0F,0.5F);
    glVertex3f(-largeurFace/2.0F,-hauteur/2.0F,0.5F);

    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,0.5F);
    glVertex3f(largeurFace/2.0F,hauteur/2.0F,0.5F);

    glNormal3f(-1,0,0);

    glVertex3f(largeurFace/2.0F,hauteur/2.0F,0.5F);
    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,0.5F);
    
    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(largeurFace/2.0F,hauteur/2.0F,largeurFace/2.0F);

    glNormal3f(0,0,-1);

    glVertex3f(largeurFace/2.0F,hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,largeurFace/2.0F);

    glVertex3f(0.5F,-hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(0.5F,hauteur/2.0F,largeurFace/2.0F);

    glNormal3f(-1,0,0);

    glVertex3f(0.5F,hauteur/2.0F,largeurFace/2.0F);
    glVertex3f(0.5F,-hauteur/2.0F,largeurFace/2.0F);

    glVertex3f(0.5F,-hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(0.5F,hauteur/2.0F,-largeurFace/2.0F);

    glNormal3f(0,0,1);

    glVertex3f(0.5F,hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(0.5F,-hauteur/2.0F,-largeurFace/2.0F);

    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(largeurFace/2.0F,hauteur/2.0F,-largeurFace/2.0F);

    glNormal3f(-1,0,0);

    glVertex3f(largeurFace/2.0F,hauteur/2.0F,-largeurFace/2.0F);
    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,-largeurFace/2.0F);

    glVertex3f(largeurFace/2.0F,-hauteur/2.0F,-0.5F);
    glVertex3f(largeurFace/2.0F,hauteur/2.0F,-0.5F);
    
  glEnd();

}

void mySolidGear(int nbTooth){
  float increment = -M_PI/(float)nbTooth;
  float angle = 0.0F;
  float x,z;
  glBegin(GL_QUAD_STRIP);
  for(int i = 0; i < nbTooth;++i){
    
    x = cos(angle)*1;
    z = sin(angle)*1;
    glNormal3f(x,0,z);
    glVertex3f(x,0.5,z);
    glVertex3f(x,-0.5,z);

    angle+=increment;
    x = cos(angle)*1;
    z = sin(angle)*1;
    glVertex3f(x,0.5,z);
    glVertex3f(x,-0.5,z);

    x = cos(angle)*0.5;
    z = sin(angle)*0.5;
    glVertex3f(x,0.5,z);
    glVertex3f(x,-0.5,z);

    angle+=increment;
    x = cos(angle)*0.5;
    z = sin(angle)*0.5;
    glVertex3f(x,0.5,z);
    glVertex3f(x,-0.5,z);
  }
  x = cos(angle)*1;
  z = sin(angle)*1;
  glVertex3f(x,0.5,z);
  glVertex3f(x,-0.5,z);
  glEnd();

  
  
  glBegin(GL_QUADS);
  angle = 0;
  for(int i = 0; i < nbTooth;++i){
    x = cos(angle)*0.5;
    z = sin(angle)*0.5;
    glVertex3f(x,0.5,z);
    
    x = cos(angle)*1;
    z = sin(angle)*1;
    glVertex3f(x,0.5,z);

    angle+=increment;
    x = cos(angle)*1;
    z = sin(angle)*1;
    glVertex3f(x,0.5,z);

    x = cos(angle)*0.5;
    z = sin(angle)*0.5;
    glVertex3f(x,0.5,z);

    angle+=increment;
  }
  angle = 0;
  for(int i = 0; i < nbTooth;++i){
    x = cos(angle)*1;
    z = sin(angle)*1;
    glVertex3f(x,-0.5,z);
    
    x = cos(angle)*0.5;
    z = sin(angle)*0.5;
    glVertex3f(x,-0.5,z);

    angle+=increment;
    x = cos(angle)*0.5;
    z = sin(angle)*0.5;
    glVertex3f(x,-0.5,z);

    x = cos(angle)*1;
    z = sin(angle)*1;
    glVertex3f(x,-0.5,z);

    angle+=increment;
  }
  glEnd();
}