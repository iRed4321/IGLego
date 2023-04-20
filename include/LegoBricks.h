#ifndef __LEGO_BRICKS__
#define __LEGO_BRICKS__

#include <string>
#include <iostream>
#include <vector>

// Unused
// 6279875 Black
// 6299413 Blue
// 4206482 Blue
// 6209519 Red
// 4142865 Red
// 4211807 Gray
// 6275844 Gray
// 6271165 Gray
// 6177114 White

enum Thickness{
    THICK,
    THIN
};

void cylinder(float radius);
void cube();

enum Orientation{
    Top,
    Bottom,
    Right,
    Left,
    Front,
    Back
};

enum PartKind{
    Arm,
    ArmEnd
};

struct LegoPart{
    Orientation orientation;
    PartKind kind;

    void draw(){
        glPushMatrix();
        switch (orientation){
            case Top:
                glRotatef(90,1,0,0);
                break;
            case Bottom:
                glRotatef(-90,1,0,0);
                break;
            case Right:
                glRotatef(90,0,1,0);
                break;
            case Left:
                glRotatef(-90,0,1,0);
                break;
            case Front:
                break;
            case Back:
                glRotatef(180,0,1,0);
                break;
        }

        switch (kind){
            case Arm:
                cylinder(0.2);

                glPushMatrix();
                    glTranslatef(0,0,0.45);
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

                break;
            case ArmEnd:
                cylinder(0.2);

                glPushMatrix();
                    glTranslatef(0.25,0,0);
                    glTranslatef(0,0,0.45);
                    glPushMatrix();
                        glScalef(0.5,1,0.1);
                        cube();
                    glPopMatrix();

                    glTranslatef(0,0,-0.9);

                    glPushMatrix();
                        glScalef(0.5,1,0.1);
                        cube();
                    glPopMatrix();
                glPopMatrix();
                break;
        }

        glPopMatrix();
    }

};


typedef std::vector<std::vector<LegoPart>> Model;

struct LiftArm{
    Thickness thickness;
    Model model;

	LiftArm(Thickness thickness, Model model){
		this->thickness = thickness;
		this->model = model;
	}

	LiftArm(Thickness thickness, int nbHoles){
		this->thickness = thickness;
        this->model = Model();
        model.push_back(std::vector<LegoPart>());
        for (int i = 0; i < nbHoles; ++i){
            if (i == 0){
                model[0].push_back(LegoPart{Front, ArmEnd});
                continue;
            } else if (i == nbHoles - 1){
                model[0].push_back(LegoPart{Back, ArmEnd});
                continue;
            } else {
                model[0].push_back(LegoPart{Front, Arm});
            }
        }
	}

    void draw(){

        int lego_width = model[0].size();
        int lego_height = model.size();

        glPushMatrix();

        if (thickness == THIN){
            glScalef(1,1,0.1);
        }

        for(auto row : model){
            glPushMatrix();
            for(auto part : row){
                part.draw();
                glTranslatef(1,0,0);
            }
            glPopMatrix();
            glTranslatef(0,1,0);
        }

        glPopMatrix();

    }
};



void classicBar(float thickness, int rings, int ns, int nl);
void liftarmThick(int nBholes);

//done
void gear8ToothType2_6012451(int ns, int nl);
// done 
void liftarmThin1x2AxleHoles_4163533(int ns, int nl);
//kinda done (needs correction)
void plate4x8_4509897(int ns, int nl);
// done 
void axle2Notched_4142865();
//done 
void axle3_4211815();
// done
void axle4_370526();
// done
void axle4WithCenterStop_4666999();
//done 
void axle5WithStop_6159763();
//done
void axle8_370726();
//done
void axle12_370826();
//done 
void axleAndPinConnector1_6332573();
//done 
void axleAndPinConnectorPerpendicular3LWith2PinHoles_6330960();
//done
void axleAndPinConnectorPerpendicular3LWithCenterPinHole_6276951();
//done 
void axleAndPinConnectorPerpendicular_6261373();
//done
void axleConnectorSmoothWithXHoleOrientation_4512360();
//not done (nathan)
void axlePin3LWithFrictionRidgesLengthwiseAnd2LAxle_6089119();
//not done (nathan)
void axlePin3LWithFrictionRidgesLengthwise_6209519();
//not done (nathan)
void axlePinWithFrictionRidgesLengthwise_4206482();
//not done
void bush_6275844();
//not done
void bush1By2Smooth_6271165();
//not done
void drivingRingConnector_6276052();
//not done
void gear12ToothDoubleBevel_4177431();
//not done
void gearWormScrew_6185471();
//not done
void liftarm1x2Thick_4177444();
//not done
void liftarm1x2ThickWithPinHoleAndAxleHole_6265135();
//not done
void liftarm1x2ThickWithPinHoleAndAxleHole_6344864();
//not done
void liftarm1x3Thin_6331723();
//not done
void liftarm1x4Thin_6327548();
//not done
void liftarm1x4Thin_6364749();
//not done
void liftarm1x5Thick_4142135();
//not done
void liftarm1x5Thick_4249021();
//not done
void liftarm1x6Thin_6345239();
//not done
void liftarm1x7Thick_4495935();
//not done
void liftarm1x13Thick_6261643();
//not done
void liftarm1x115DoubleBentThick_6271156();
//not done
void liftarm2x4LShapeThick_6271825();
//not done
void liftarm3x3LShapeThin_6271810();
//not done
void liftarm3x3TShapeThick_4552347();
//not done
void liftarm3x5LShapeThick_6173003();
//not done
void liftarm3x5LShapeWithQuarterEllipseThin_6327162();
//not done
void liftarm3X5PerpendicularHShapeThick_6055519();
//not done
void pinConnectorPerpendicular3LWith4Pins_6282158();
//not done
void pinLongWithFrictionRidgesLengthwise_6299413();
//not done
void pinLongWithoutFrictionRidgesLengthwise_6321305();
//not done
void pinWithoutFrictionRidgesLengthwise_4211807();
//not done
void pinWithFrictionRidgesLengthwiseAndPinHole_6282140();
//not done
void pinWithFrictionRidgesLengthwise_4206482();
// done
void technicLever3x3m90deg__6271810(int ns, int nl);
//not done
void tread_6271164();
//not done
void treadWithCenterPinHole_6271163();
//not done
void tire304x14OffsetTreadBandAroundCenterOfTread_4619323();



#endif