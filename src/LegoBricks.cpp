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

//Nathan
/*
pièce en forme de :
	
	+
	O
	+ O +

la base du trou qui fait l'angle est en (0,0,0)
*/

void technicLever3x3m90deg__6271810(int ns, int nl){
	
	
	glPushMatrix();
	mySolidCylindre(ns,nl);
	glTranslatef(1,0,0);
	mySolidCylindre(ns,nl);
	glTranslatef(1,0,0);
	mySolidCylindre(ns,nl);
	glPopMatrix();

	glPushMatrix();
	mySolidCylindre(ns,nl);
	glTranslatef(0,0,1);
	mySolidCylindre(ns,nl);
	glTranslatef(0,0,1);
	mySolidCylindre(ns,nl);
	glPopMatrix();
	
}