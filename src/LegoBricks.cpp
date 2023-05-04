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


void technicLever3x3m90deg__6271810(){
	glPushMatrix();

	glScalef(1,0.5,1);

	glPushMatrix();
	glTranslatef(1,0,-0.45);
	glScalef(2,1,0.1);
	cube();
	
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
	
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90,0,1,0);
	glTranslatef(1,0,0.45);
	glScalef(2,1,0.1);
	cube();
	glPopMatrix();

	glPushMatrix();
	glPushMatrix();
		glScalef(0.8,1,0.8);
		thickCross();
	glPopMatrix();
	
	cylinder(0.2);
	glTranslatef(1,0,0);
	
	cylinder(0.2);
	glTranslatef(1,0,0);
	
	cylinder(0.2);
	glPushMatrix();
		glScalef(0.8,1,0.8);
		thickCross();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	
	cylinder(0.2);
	glTranslatef(0,0,1);
	glPushMatrix();
		glScalef(0.8,1,0.8);
		thickCross();
	glPopMatrix();
	
	cylinder(0.2);
	glPopMatrix();
	
	glPopMatrix();
	
}


void gear8ToothType2_6012451(){
	glPushMatrix();
		glScalef(0.8,1,0.8);
		thickCross();
	glPopMatrix();
	
	glPushMatrix();
		glScalef(1,0.8,1);
		mySolidGear(8);
	glPopMatrix();
}


void liftarmThin1x2AxleHoles_4163533(){
	glPushMatrix();
	glScalef(1,0.5,1);
	glPushMatrix();
		glScalef(0.8,1,0.8);
		thickCross();
	glPopMatrix();
	
	cylinder(0.2);
	glTranslatef(1,0,0);
	glPushMatrix();
		glScalef(0.8,1,0.8);
		thickCross();
	glPopMatrix();
	
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



void plate4x8_4509897(){

	glPushMatrix();
	glScalef(4,0.5,8);
	cube();
	glPopMatrix();

	glPushMatrix();
	glScalef(1,0.5,1);
	glTranslatef(-1.5,1,-3.5);
	for(int i = 0; i<4; ++i){
		for(int j = 0;j<8; ++j ){
			glPushMatrix();
			glTranslatef(i,0,j);
			glScalef(0.9,1,0.9);
			cylinder(0.2);
			glTranslatef(0,0.5,0); 
			glRotatef(180,1,0,0);
			mySolidDisc(40);
			glPopMatrix();
		}
	}
	
	glPopMatrix();
}

void axle2Notched_4142865(){
	glPushMatrix();
	glScalef(0.8,2,0.8);
	mySolidCross(1);
	glPopMatrix();
}

void axle3_4211815(){
	glPushMatrix();
	glScalef(0.8,3,0.8);
	mySolidCross(1);
	glPopMatrix();
}

void axle4_370526(){
	glPushMatrix();
	glScalef(0.8,4,0.8);
	mySolidCross(1);
	glPopMatrix();
}

void axle4WithCenterStop_4666999(){
	glPushMatrix();
		glScalef(0.8,4,0.8);
		mySolidCross(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-.5,0);
		glScalef(1,0.98,1);
		cylinder(1);
	glPopMatrix();
}


void axle5WithStop_6159763(){
	glPushMatrix();
		glScalef(0.8,5,0.8);
		mySolidCross(1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,-2.5,0);
		mySolidDisc(20);
	glPopMatrix();
}

void axle8_370726(){
	glPushMatrix();
		glScalef(0.8,8,0.8);
		mySolidCross(1);
	glPopMatrix();
}

void axle12_370826(){
	glPushMatrix();
	glScalef(0.8,12,0.8);
	mySolidCross(1);
	glPopMatrix();
}

void axleAndPinConnector1_6332573(){
	glPushMatrix();
		cylinder(0.2);
		glTranslatef(1,0,0);
		glRotatef(-90,0,0,1);
		glPushMatrix();
			glScalef(0.8,1,0.8);
			thickCross();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,-0.5,0.45);
			glScalef(0.25,1,0.05);
			cube();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,-0.5,-0.45);
			glScalef(0.25,1,0.05);
			cube();
		glPopMatrix();
	glPopMatrix();
}

void axleAndPinConnectorPerpendicular3LWith2PinHoles_6330960(){
	glPushMatrix();
	cylinder(0.2);
	glPushMatrix();
		glScalef(0.8,1,0.8);
		thickCross();
	glPopMatrix();
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
			glPushMatrix();
				glScalef(0.8,1,0.8);
				thickCross();
			glPopMatrix();
			glTranslatef(-2,0,0);
			cylinder(0.2);
			glPushMatrix();
				glScalef(0.8,1,0.8);
				thickCross();
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();
}

void axleAndPinConnectorPerpendicular_6261373(){
	glPushMatrix();
		glPushMatrix();
			cylinder(0.2);
			glPushMatrix();
				glScalef(0.8,1,0.8);
				thickCross();
			glPopMatrix();
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
		glPushMatrix();
			glScalef(0.8,1,0.8);
			thickCross();
		glPopMatrix();
	glPopMatrix();
}

void axlePin3LWithFrictionRidgesLengthwiseAnd2LAxle_6089119(){
	//changer la couleur (noir)
	glPushMatrix();
		glPushMatrix();
			glScalef(0.8,1,0.8);
			cylinder(0.2);
		glPopMatrix();
		glTranslatef(0,0.5,0);
		glPushMatrix();
		glScalef(1,0.1,1);
		cylinder(1);
		glPopMatrix();
		glTranslatef(0,1,0);
		glPushMatrix();
			glScalef(0.8,2,0.8);
			mySolidCross(1);
		glPopMatrix();
	glPopMatrix();
}


void liftarm3x5LShapeThick_6173003(){
	LiftArm arm = liftArm6173003();
	arm.draw();
}

LiftArm liftArm6173003() {
	Model m = Model();
	m[Pos3d{0,0,0}] = LegoPart{Front, ArmAngle};
	m[Pos3d{1,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{2,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{3,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{4,0,0}] = LegoPart{Back, ArmEnd};
	m[Pos3d{0,0,1}] = LegoPart{Left, Arm};
	m[Pos3d{0,0,2}] = LegoPart{Right, ArmEnd};
	return LiftArm(THICK, m);
}

void liftarm3x3TShapeThick_4552347(){
	LiftArm arm = liftArm4552347();
	arm.draw();
}

LiftArm liftArm4552347() {
	Model m = Model();
	m[Pos3d{0,0,0}] = LegoPart{Front, ArmEnd};
	m[Pos3d{1,0,0}] = LegoPart{Back, ArmTAngle};
	m[Pos3d{2,0,0}] = LegoPart{Back, ArmEnd};
	m[Pos3d{1,0,1}] = LegoPart{Left, Arm};
	m[Pos3d{1,0,2}] = LegoPart{Right, ArmEnd};
	return LiftArm(THICK, m);
}

void liftarm3x3LShapeThin_6271810(){
	LiftArm arm = liftArm6271810();
	arm.draw();
}

LiftArm liftArm6271810() {
	Model m = Model();
	m[Pos3d{0,0,0}] = LegoPart{Front, ArmAngleWithCross};
	m[Pos3d{1,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{2,0,0}] = LegoPart{Back, ArmEndWithCross};
	m[Pos3d{0,0,1}] = LegoPart{Left, Arm};
	m[Pos3d{0,0,2}] = LegoPart{Right, ArmEndWithCross};
	return LiftArm(THIN, m);
}

void liftarm2x4LShapeThick_6271825(){
	LiftArm arm = liftArm6271825();
	arm.draw();
}

LiftArm liftArm6271825() {
	Model m = Model();
	m[Pos3d{0,0,0}] = LegoPart{Front, ArmEndWithCross};
	m[Pos3d{1,0,0}] = LegoPart{Back, Arm};
	m[Pos3d{2,0,0}] = LegoPart{Back, Arm};
	m[Pos3d{3,0,0}] = LegoPart{Left, ArmAngle};
	m[Pos3d{3,0,1}] = LegoPart{Right, ArmEnd};
	return LiftArm(THICK, m);
}

void liftarm1x13Thick_6261643(){
	LiftArm arm = liftArm6261643();
	arm.draw();
}

LiftArm liftArm6261643() {
	LiftArm arm = LiftArm(THICK, 13);
	return arm;
}

void liftarm1x7Thick_4495935(){
	LiftArm arm = liftArm4495935();
	arm.draw();
}

LiftArm liftArm4495935() {
	LiftArm arm = LiftArm(THICK, 7);
	return arm;
}

void liftarm1x6Thin_6345239(){
	LiftArm arm = liftArm6345239();
	arm.draw();
}

LiftArm liftArm6345239() {
	LiftArm arm = LiftArm(THIN, 6);
	return arm;
}

void liftarm1x5Thick_4249021(){
	LiftArm arm = liftArm4249021();
	arm.draw();
}

LiftArm liftArm4249021() {
	LiftArm arm = LiftArm(THICK, 5);
	return arm;
}

void liftarm1x5Thick_4142135(){
	LiftArm arm = liftArm4142135();
	arm.draw();
}

LiftArm liftArm4142135() {
	LiftArm arm = LiftArm(THICK, 5);
	return arm;
}

void liftarm1x4Thin_6364749(){
	LiftArm arm = liftArm6364749();
	arm.draw();
}

LiftArm liftArm6364749() {
	Model m = Model();

	m[Pos3d{0,0,0}] = LegoPart{Front, ArmEndWithCross};
	m[Pos3d{1,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{2,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{3,0,0}] = LegoPart{Back, ArmEndWithCross};

	LiftArm arm = LiftArm(THIN, m);
	return arm;
}

void liftarm1x4Thin_6327548(){
	LiftArm arm = liftArm6327548();
	arm.draw();
}

LiftArm liftArm6327548() {
	return liftArm6364749();
}

void liftarm1x3Thin_6331723(){
	LiftArm arm = liftArm6331723();
	arm.draw();
}

LiftArm liftArm6331723() {
	Model m = Model();

	m[Pos3d{0,0,0}] = LegoPart{Front, ArmEndWithCross};
	m[Pos3d{1,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{2,0,0}] = LegoPart{Back, ArmEndWithCross};

	LiftArm arm = LiftArm(THIN, m);
	return arm;
}

void liftarm1x2ThickWithPinHoleAndAxleHole_6344864(){
	LiftArm arm = liftArm6344864();
	arm.draw();
}

LiftArm liftArm6344864(){
	Model m = Model();

	m[Pos3d{0,0,0}] = LegoPart{Front, ArmEndWithCross};
	m[Pos3d{1,0,0}] = LegoPart{Back, ArmEnd};

	LiftArm arm = LiftArm(THICK, m);
	return arm;
}

// void liftarm1x2ThickWithPinHoleAndAxleHole_6265135(){
// 	LiftArm arm = liftarm6265135();
// 	arm.draw();
// }

// LiftArm liftarm6265135(){
// 	return liftArm6344864();
// }

void liftarm1x2Thick_4177444(){
	LiftArm arm = liftArm4177444();
	arm.draw();
}

LiftArm liftArm4177444(){
	LiftArm arm = LiftArm(THICK, 2);
	return arm;
}

void liftarm1x115DoubleBentThick_6271156(){
	glPushMatrix();

	Model m = Model();

	m[Pos3d{0,0,0}] = LegoPart{Front, ArmEndWithCross};
	m[Pos3d{1,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{2,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{3,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{4,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{5,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{6,0,0}] = LegoPart{Back, ArmEnd};

	LiftArm arm = LiftArm(THICK, m);
	arm.draw();

	glTranslatef(6,0,0);
	glRotatef(45,0,0,1);

	m = Model();
	m[Pos3d{0,0,0}] = LegoPart{Front, ArmEnd};
	m[Pos3d{1,0,0}] = LegoPart{Front, ArmHalfCylinder};
	m[Pos3d{2,0,0}] = LegoPart{Back, ArmHalfCylinder};
	m[Pos3d{3,0,0}] = LegoPart{Back, ArmEnd};

	arm = LiftArm(THICK, m);
	arm.draw();

	glTranslatef(3,0,0);
	glRotatef(45,0,0,1);

	m = Model();
	m[Pos3d{0,0,0}] = LegoPart{Front, ArmEnd};
	m[Pos3d{1,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{2,0,0}] = LegoPart{Back, ArmEndWithCross};

	arm = LiftArm(THICK, m);
	arm.draw();

	glPopMatrix();
}

void liftarm3X5PerpendicularHShapeThick_6055519(){
	Model m = Model();

	m[Pos3d{0,0,0}] = LegoPart{Front, ArmEnd};
	m[Pos3d{1,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{2,0,0}] = LegoPart{Back, ArmEnd};

	m[Pos3d{1,0,1}] = LegoPart{Top, Arm};
	m[Pos3d{1,0,2}] = LegoPart{Top, Arm};
	m[Pos3d{1,0,3}] = LegoPart{Top, Arm};

	m[Pos3d{0,0,4}] = LegoPart{Front, ArmEnd};
	m[Pos3d{1,0,4}] = LegoPart{Front, Arm};
	m[Pos3d{2,0,4}] = LegoPart{Back, ArmEnd};

	LiftArm arm = LiftArm(THICK, m);
	arm.draw();
}

void liftarm3x5LShapeWithQuarterEllipseThin_6327162(){
	Model m = Model();

	m[Pos3d{0,0,0}] = LegoPart{Front, ArmAngleWithCross};
	m[Pos3d{1,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{2,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{3,0,0}] = LegoPart{Front, Arm};
	m[Pos3d{4,0,0}] = LegoPart{Back, ArmEndWithCross};

	m[Pos3d{0,0,1}] = LegoPart{Left, Arm};
	m[Pos3d{0,0,2}] = LegoPart{Right, ArmEndWithCross};

	LiftArm arm = LiftArm(THIN, m);
	arm.draw();

	glTranslatef(4,0,0);
	glRotatef(205, 0,0,1);
	glScalef(1,0.5,1);

	m = Model();
	m[Pos3d{0,0,0}] = LegoPart{Front, ArmEmpty};
	m[Pos3d{1,0,0}] = LegoPart{Front, ArmEmpty};
	m[Pos3d{2,0,0}] = LegoPart{Front, ArmEmpty};
	m[Pos3d{3,0,0}] = LegoPart{Front, ArmEmpty};
	m[Pos3d{4,0,0}] = LegoPart{Back, ArmEmpty};

	arm = LiftArm(THIN, m);
	arm.draw();
}

//céla Jocelyn

void cylinderBordersFace(){
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
}

void cylinderBordersSide(){
	glPushMatrix();
		glTranslatef(0,0,0.449);
		glPushMatrix();
			glScalef(1.4,1,0.1);
			cube();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0.45,0);
			glScalef(2,0.1,0.1);
			cube();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0.35,0);
			glScalef(1.60,0.1,0.1);
			cube();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,-0.45,0);
			glScalef(2,0.1,0.1);
			cube();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0,-0.35,0);
			glScalef(1.60,0.1,0.1);
			cube();
		glPopMatrix();
		
	glPopMatrix();
}

void pinConnectorPerpendicular3LWith4Pins_6282158(){
	glPushMatrix();
		glPushMatrix();
			glRotatef(90,1,0,0);
			cylinder(0.2);
			glPushMatrix();
				glRotatef(90,1,0,0);
				glTranslatef(0,1,0);
				glScalef(0.8,1,0.8);
				cylinder(0.2);
			glPopMatrix();
			glPushMatrix();
				glRotatef(-90,0,0,1);
				glTranslatef(0,1,0);
				glScalef(0.8,1,0.8);
				cylinder(0.2);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-2,0,0);
			glRotatef(90,1,0,0);
			cylinder(0.2);
			glRotatef(90,1,0,0);
			glTranslatef(0,1,0);
			glScalef(0.8,1,0.8);
			cylinder(0.2);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,2,0);
			glRotatef(90,1,0,0);
			cylinder(0.2);
			glPushMatrix();
				glRotatef(-90,0,0,1);
				glTranslatef(0,1,0);
				glScalef(0.8,1,0.8);
				cylinder(0.2);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-1,0,0);
			glPushMatrix();
				cylinderBordersFace();
				glTranslatef(0,0,-0.9);
				cylinderBordersFace();
			glPopMatrix();
			glPushMatrix();
				glRotatef(90,1,0,0);
				cylinderBordersSide();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,0.45,0);
				glScalef(2.1,0.1,1);	
				cube();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,1,0);
			glPushMatrix();
				glRotatef(90,0,0,1);
				cylinderBordersFace();
			glPopMatrix();
			glPushMatrix();
				glRotatef(90,0,1,0);
				glRotatef(90,0,0,1);
				cylinderBordersSide();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.45,0,0);
				glRotatef(90,0,0,1);
				glScalef(2.1,0.1,1);	
				cube();
			glPopMatrix();
			glTranslatef(0,0,-0.9);
			glPushMatrix();
				glRotatef(90,0,0,1);
				cylinderBordersFace();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void pinLongWithFrictionRidgesLengthwise_6299413(){
	//blue
	glPushMatrix();
		glPushMatrix();
			glScalef(0.8,2,0.8);
			cylinder(0.2);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0.3,0);
			glScalef(1,0.1,1);
			cylinder(0.2);
		glPopMatrix();
	glPopMatrix();
}	

void pinLongWithoutFrictionRidgesLengthwise_6321305(){
	//yellow
	glPushMatrix();
		glPushMatrix();
			glScalef(0.8,2,0.8);
			cylinder(0.2);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0.3,0);
			glScalef(1,0.1,1);
			cylinder(0.2);
		glPopMatrix();
	glPopMatrix();
}

void pinWithoutFrictionRidgesLengthwise_4211807(){
	//gray
	glPushMatrix();
		glPushMatrix();
			glScalef(0.8,1.5,0.8);
			cylinder(0.2);
		glPopMatrix();
		glPushMatrix();
			glScalef(1,0.1,1);
			cylinder(0.2);
		glPopMatrix();
	glPopMatrix();
}

void pinWithFrictionRidgesLengthwise_4206482(){
	//blue
	glPushMatrix();
		glPushMatrix();
			glScalef(1,0.1,1);
			cylinder(1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0.35,0);
			glScalef(0.8,0.8,0.8);
			cylinder(0.2);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,-0.375,0);
			glScalef(0.8,0.75,0.8);
			mySolidCross(1);
		glPopMatrix();
	glPopMatrix();
}

void bush_6275844(){
	//gray
	glPushMatrix();
		innerCross();
	glPopMatrix();
}

void pinWithFrictionRidgesLengthwiseAndPinHole_6282140(){
	//black
	//la jumelle de sous marin
}

//pala Jocelyn


void axlePin3LWithFrictionRidgesLengthwise_6209519(){
	//changer la couleur (rouge)
	glPushMatrix();
		glPushMatrix();
			glScalef(0.8,1,0.8);
			mySolidCross(1);
		glPopMatrix();
		glTranslatef(0,0.5,0);
		glPushMatrix();
		glScalef(1,0.1,1);
		cylinder(1);
		glPopMatrix();
		glTranslatef(0,1,0);
		glPushMatrix();
			glScalef(0.8,2,0.8);
			cylinder(0.2);
		glPopMatrix();
	glPopMatrix();
}

void axlePinWithFrictionRidgesLengthwise_4206482(){
	//changer la couleur (bleu foncé)
	glPushMatrix();
		glPushMatrix();
			glScalef(0.8,1,0.8);
			mySolidCross(1);
		glPopMatrix();
		glTranslatef(0,0.5,0);
		glPushMatrix();
		glScalef(1,0.1,1);
		cylinder(1);
		glPopMatrix();
		glTranslatef(0,0.5,0);
		glPushMatrix();
			glScalef(0.8,1,0.8);
			cylinder(0.2);
		glPopMatrix();
	glPopMatrix();
}

void gear12ToothDoubleBevel_4177431(){
	glPushMatrix();
		glScalef(0.8,1,0.8);
		thickCross();
	glPopMatrix();
	
	glPushMatrix();
		glScalef(1,0.8,1);
		mySolidGear(12);
	glPopMatrix();

	//top Bevel
	glPushMatrix();
		glTranslatef(0,0.425,0);
		// glRotatef(4,0,1,0);
		glScalef(0.95,0.05,0.95);
		mySolidGear(12);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0.45,0);
		// glRotatef(4,0,1,0);
		glScalef(0.93,0.05,0.93);
		mySolidGear(12);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0.475,0);
		// glRotatef(4,0,1,0);
		glScalef(0.9,0.05,0.9);
		mySolidGear(12);
	glPopMatrix();

	//bottom bevel
	glPushMatrix();
		glTranslatef(0,-0.425,0);
		// glRotatef(4,0,1,0);
		glScalef(0.95,0.05,0.95);
		mySolidGear(12);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,-0.45,0);
		// glRotatef(4,0,1,0);
		glScalef(0.93,0.05,0.93);
		mySolidGear(12);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,-0.475,0);
		// glRotatef(4,0,1,0);
		glScalef(0.9,0.05,0.9);
		mySolidGear(12);
	glPopMatrix();

}

void gearWormScrew_6185471(){
	glPushMatrix();
		glScalef(1,2,1);
		cylinder(0.2);
		glPushMatrix();
			glScalef(1,0.9,1);
			thickSpiral3d(5);
		glPopMatrix();
		glScalef(0.8,1,0.8);
		thickCross();
	glPopMatrix();
}