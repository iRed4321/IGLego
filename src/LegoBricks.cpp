#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159235
#endif

#include "LegoBricks.h"
#include "ObjetsGeometriques.h"

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
	glTranslatef(1,0,-0.45);
	glScalef(2,1,0.1);
	cube();
	//mySolidFace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.25,0,0.5);
	glScalef(1.5,1,0.1);
	cube();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(1.25,0,-0.45);
	glScalef(1.5,1,0.1);
	cube();
	//glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(1,0,0.45);
	glScalef(2,1,0.1);
	cube();
	glPopMatrix();

	glPushMatrix();
	mySolidCross();
	//mySolidCylindre(ns,nl);
	cylinder(0.2);
	glTranslatef(1,0,0);
	//mySolidCylindre(ns,nl);
	cylinder(0.2);
	glTranslatef(1,0,0);
	//mySolidCylindre(ns,nl);
	cylinder(0.2);
	mySolidCross();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	//mySolidCylindre(ns,nl);
	cylinder(0.2);
	glTranslatef(0,0,1);
	mySolidCross();
	//mySolidCylindre(ns,nl);
	cylinder(0.2);
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
	//mySolidCylindre(ns, nl);
	cylinder(0.2);
	glTranslatef(1,0,0);
	mySolidCross();
	//mySolidCylindre(ns, nl);
	cylinder(0.2);
	glPushMatrix();
	glTranslatef(-0.5,0,0.45);
	glScalef(1,1,0.1);
	cube();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.5,0,-0.45);
	glScalef(1,1,0.1);
	cube();
	glPopMatrix();
	glPopMatrix();
}


void liftarm1x2Thick_4177444(){
	glPushMatrix();
	cylinder(0.2);
	glTranslatef(1,0,0);
	cylinder(0.2);

	glTranslatef(-0.5,0,0.45);

	glPushMatrix();
	glScalef(0.9,1,0.1);
	cube();
	glPopMatrix();


	glTranslatef(0,0,-0.9);

	glPushMatrix();
	glScalef(0.9,1,0.1);
	cube();
	glPopMatrix();

	glPopMatrix();
}


void liftarmThick(int nBholes){
	glPushMatrix();

	for (int i = 0; i < nBholes; ++i)
	{
		cylinder(0.2);
		if(i != 0){
			glTranslatef(1,0,0);
			glPushMatrix();
			glTranslatef(-0.5,0,0.45);
			glPushMatrix();
			glScalef(1,1,0.1);
			cube();
			glPopMatrix();

			glTranslatef(0,0,-0.9);

			glPushMatrix();
			glScalef(1,1,0.1);
			cube();
			glPopMatrix();
			glPopMatrix();
		}
	}
	cylinder(0.2);

	glPopMatrix();
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
			//mySolidCylindre(ns,nl);
			cylinder(0.2);
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
	//mySolidCylindre(50,10);
	cylinder(1);
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

void axleAndPinConnector1_6332573(){
	glPushMatrix();
	//mySolidCylindre(40,40);
	cylinder(0.2);
	glTranslatef(1,0,0);
	glRotatef(-90,0,0,1);
	mySolidCross();
	glTranslatef(0,-0.5,0.5);
	glScalef(0.166667,1,1);
	mySolidFace();
	glTranslatef(0,0,-1);
	mySolidFace();
	glPopMatrix();
}

void axleAndPinConnectorPerpendicular3LWith2PinHoles_6330960(){
	glPushMatrix();
	cylinder(0.2);
	mySolidCross();
	glRotatef(90,1,0,0);
	glTranslatef(1,0,0);
	cylinder(0.2);
	glTranslatef(1,0,0);
	cylinder(0.2);
	glTranslatef(-0.85,0,-0.45);
	glPushMatrix();
		glScalef(1.55,1,0.1);
		cube();
	glPopMatrix();
	glTranslatef(0,0,0.9);
	glPushMatrix();
		glScalef(1.55,1,0.1);
		cube();
	glPopMatrix();
	glPopMatrix();
}

void axleAndPinConnectorPerpendicular3LWithCenterPinHole_6276951(){
	glPushMatrix();
		cylinder(0.2);

		glPushMatrix();
			glTranslatef(0,0,0.449);
			glPushMatrix();
				glScalef(1.2,1,0.1);
				cube();
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0,0.45,0);
				glScalef(2,0.1,0.1);
				cube();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,0.35,0);
				glScalef(1.40,0.1,0.1);
				cube();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,-0.45,0);
				glScalef(2,0.1,0.1);
				cube();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,-0.35,0);
				glScalef(1.40,0.1,0.1);
				cube();
			glPopMatrix();
		glPopMatrix();
		

		glPushMatrix();
			glTranslatef(0,0,-0.449);
			glPushMatrix();
				glScalef(1.2,1,0.1);
				cube();
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0,0.45,0);
				glScalef(2,0.1,0.1);
				cube();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,0.35,0);
				glScalef(1.40,0.1,0.1);
				cube();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,-0.45,0);
				glScalef(2,0.1,0.1);
				cube();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,-0.35,0);
				glScalef(1.40,0.1,0.1);
				cube();
			glPopMatrix();
		glPopMatrix();
		

		glPushMatrix();
			glTranslatef(1,0,0);
			glRotatef(90,1,0,0);
			cylinder(0.2);
			mySolidCross();
			glTranslatef(-2,0,0);
			cylinder(0.2);
			mySolidCross();
		glPopMatrix();

	glPopMatrix();
}

void axleAndPinConnectorPerpendicular_6261373(){
	glPushMatrix();
		glPushMatrix();
			cylinder(0.2);
			mySolidCross();
			glRotatef(90,1,0,0);
			glTranslatef(1,0,0);
			cylinder(0.2);
		glPopMatrix();

		glTranslatef(0.65,0,0);
		glPushMatrix();
			glTranslatef(0,0.45,0);
			glScalef(0.55,0.1,1);
			cube();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0,-0.45,0);
			glScalef(0.55,0.1,1);
			cube();
		glPopMatrix();
	glPopMatrix();
}

void axleConnectorSmoothWithXHoleOrientation_4512360(){
	glPushMatrix();
		glScalef(1,2,1);
		thickCross();
	glPopMatrix();
}

void liftarm3x5LShapeThick_6173003(){

	Model m = Model();
	m[Pos3d{0,0,0}] = LegoPart{Front, ArmAngle};
	m[Pos3d{1,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{2,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{3,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{4,0,0}] = LegoPart{Back, ArmEnd};
	m[Pos3d{0,0,1}] = LegoPart{Left, Arm};
	m[Pos3d{0,0,2}] = LegoPart{Right, ArmEnd};
	LiftArm arm = LiftArm(THICK, m);
	arm.draw();
}

void liftarm3x3TShapeThick_4552347(){
	Model m = Model();
	m[Pos3d{0,0,0}] = LegoPart{Front, ArmEnd};
	m[Pos3d{1,0,0}] = LegoPart{Back, ArmTAngle};
	m[Pos3d{2,0,0}] = LegoPart{Back, ArmEnd};
	m[Pos3d{1,0,1}] = LegoPart{Left, Arm};
	m[Pos3d{1,0,2}] = LegoPart{Right, ArmEnd};
	LiftArm arm = LiftArm(THICK, m);
	arm.draw();
}