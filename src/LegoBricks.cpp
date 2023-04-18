#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "LegoBricks.h"
#include "ObjetsGeometriques.h"

//Jocelyn
void classicBar(float thickness, int rings, int ns, int nl){
    glPushMatrix();
    glScalef(1, 1, thickness);
    glTranslatef(0, 0, thickness/2);
    glPushMatrix();
    glTranslatef((float)rings/2, 0, 0);
    mySolidRectangle(rings-1, ns);
    glPopMatrix();
    for(int i = 0; i < rings; i++){
        glPushMatrix();
        glTranslatef(rings+i, 0, 0);
        mySolidCylindre(32,32);
        glPopMatrix();
    }
    glPopMatrix();
}


/*
pièce en forme de :
	
	+
	O
	+ O +

la base du trou qui fait l'angle est en (0,0,0)
*/
void technicLever3x3m90deg__6271810(int ns, int nl){
	glPushMatrix();

	glScalef(1,0.5,1);

	glPushMatrix();
	glTranslatef(1,0,-0.5);
	glScalef(2,1,1);
	glRotatef(180,1,0,0);
	mySolidFace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.25,0,0.5);
	glScalef(1.5,1,1);
	mySolidFace();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(1.25,0,-0.5);
	glScalef(1.5,1,1);
	mySolidFace();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(1,0,0.5);
	glScalef(2,1,1);
	mySolidFace();
	glPopMatrix();

	glPushMatrix();
	mySolidCross();
	mySolidCylindre(ns,nl);
	glTranslatef(1,0,0);
	mySolidCylindre(ns,nl);
	glTranslatef(1,0,0);
	mySolidCylindre(ns,nl);
	mySolidCross();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	mySolidCylindre(ns,nl);
	glTranslatef(0,0,1);
	mySolidCross();
	mySolidCylindre(ns,nl);
	glPopMatrix();
	
	glPopMatrix();
	
}


void gear8ToothType2_6012451(int ns, int nl){
	glPushMatrix();
	mySolidCross();
	glScalef(1,0.8,1);
	mySolidGear(8);
	glPopMatrix();
}


void liftarmThin1x2AxleHoles_4163533(int ns, int nl){
	glPushMatrix();
	glScalef(1,0.5,1);
	mySolidCross();
	mySolidCylindre(ns, nl);
	glTranslatef(1,0,0);
	mySolidCross();
	mySolidCylindre(ns, nl);
	glTranslatef(-0.5,0,0.5);
	mySolidFace();
	glTranslatef(0,0,-1);
	glRotatef(180,1,0,0);
	mySolidFace();
	glPopMatrix();
}

//this function should be in the ObjetsGeometriques file but makefile needs to be corrected for this to work
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159235
#endif
static void mySolidDisc(int ns){

  glBegin(GL_POLYGON);
  float angle = 0;
  float increment = -2*M_PI/ns;
  for(int i = 0; i<ns; ++i){
    glVertex3f(0.5*cos(angle),0,0.5*sin(angle));
    angle+=increment;
  }
  glEnd();
}

void plate4x8_4509897(int ns, int nl){

	glPushMatrix();
	glScalef(4,0.5,8);
	mySolidCube(ns);
	glPopMatrix();

	glPushMatrix();
	glScalef(1,0.5,1);
	glTranslatef(-1.5,1,-3.5);
	for(int i = 0; i<4; ++i){
		for(int j = 0;j<8; ++j ){
			glPushMatrix();
			glTranslatef(i,0,j);
			glScalef(0.9,1,0.9);
			mySolidCylindre(ns,nl);
			glTranslatef(0,0.5,0); 
			glRotatef(180,1,0,0);
			mySolidDisc(ns);
			glPopMatrix();
		}
	}
	
	glPopMatrix();
}

void axle2Notched_4142865(){
	glPushMatrix();
	glScalef(1,2,1);
	mySolidCross();
	glPopMatrix();
}

void axle3_4211815(){
	glPushMatrix();
	glScalef(1,3,1);
	mySolidCross();
	glPopMatrix();
}

void axle4_370526(){
	glPushMatrix();
	glScalef(1,4,1);
	mySolidCross();
	glPopMatrix();
}

void axle4WithCenterStop_4666999(){
	glPushMatrix();
	glScalef(1,4,1);
	mySolidCross();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-1,0);
	mySolidCylindre(50,10);
	glPopMatrix();
}

void axle5WithStop_6159763(){
	glPushMatrix();
	glScalef(1,5,1);
	mySolidCross();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-2.5,0);
	mySolidDisc(20);
	glPopMatrix();
}


void axle8_370726(){
	glPushMatrix();
	glScalef(1,8,1);
	mySolidCross();
	glPopMatrix();
}

void axle12_370826(){
	glPushMatrix();
	glScalef(1,12,1);
	mySolidCross();
	glPopMatrix();
}