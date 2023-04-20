#ifndef __LEGO_BRICKS__
#define __LEGO_BRICKS__

#include <string>
#include <iostream>
#include <map>

#include "ObjetsGeometriques.h"

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
    ArmEnd,
    ArmWithCross,
    Cross
};

struct LegoPart{
    Orientation orientation;
    PartKind kind;
    void draw();
};

struct Pos3d{
    uint x;
    uint y;
    uint z;
};

struct Pos3dComparator{
   bool operator() (const Pos3d& lhs, const Pos3d& rhs) const
   {
         if (lhs.x < rhs.x){
              return true;
         } else if (lhs.x == rhs.x){
              if (lhs.y < rhs.y){
                return true;
              } else if (lhs.y == rhs.y){
                return lhs.z < rhs.z;
              }
         }
         return false;
   }
};

typedef std::map<Pos3d,LegoPart, Pos3dComparator> Model;


struct LiftArm{
    Thickness thickness;
    Model model;

	LiftArm(Thickness thickness, Model model);
	LiftArm(Thickness thickness, uint nbHoles);
    void draw();
};

void liftarmThick(int nBholes);

//done
void gear8ToothType2_6012451(int ns, int nl);
// done 
void liftarmThin1x2AxleHoles_4163533(int ns, int nl);
//kinda done 
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

// leo : 
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
// ----------------

//not done
void liftarm3x5LShapeWithQuarterEllipseThin_6327162();
//not done
void liftarm3X5PerpendicularHShapeThick_6055519();

//---------Jocelyn----------
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
//--------------------------

// done
void technicLever3x3m90deg__6271810(int ns, int nl);
//not done
void tread_6271164();
//not done
void treadWithCenterPinHole_6271163();
//not done
void tire304x14OffsetTreadBandAroundCenterOfTread_4619323();



#endif