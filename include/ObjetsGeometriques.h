#ifndef __OBJETS_GEOMETRIQUES__
#define __OBJETS_GEOMETRIQUES__

#include <map>

//need to correct makefile so this works
void mySolidDisc(int ns);
void mySolidDisc(int ns, int textureID);

/* Modelisation geometrique d'un parallèlépipède rectangle      */
/* parallele a l'axe des x et des z :           */
/*  - de longueur length                        */
void mySolidRectangle(int length, int n);

/* Modelisation geometrique d'un cylindre       */
/* sans bases :                                 */
/*  - de hauteur hauteur                        */
/*  - de rayon rayon                            */
/*  - oriente selon l'axe y                     */
/*  - centre sur l'origine du repere            */
/*  - avec ns facettes en decomposition         */
/*    longitudinale                             */
/*  - avec nl facettes en decomposition axiale  */
void mySolidCylindre(int ns,int nl);

void mySolidCylindreInverted(int ns,int nl);
void mySolidCylindreInverted(int ns,int nl, float revolution);

/* Modelisation geometrique d'un cylindre       */
/* avec ou sans bases :                         */
/*  - de hauteur hauteur                        */
/*  - de rayon rayon                            */
/*  - oriente selon l'axe y                     */
/*  - centre sur l'origine du repere            */
/*  - avec ns facettes en decomposition         */
/*    longitudinale                             */
/*  - avec nl facettes en decomposition axiale  */
/*  - avec bases si bases != 0                  */
void mySolidCylindre(int ns,int nl,int bases);
void mySolidCylindre(int ns,int nl, float revolution);

/* Face interne d'une croix */
void innerCross();

/* Modelisation d'une croix */
void mySolidCross(int withbase=0);

/* Modelisation d'une roue crantée 				*/
/* les dents commencent à une distance de 0.5 du centre */
/* et terminent à une distance 1 du centre 	    */
void mySolidGear(int nbTooth);

/* Modelisation geometrique d'un rectangle      */
/* parallele aux axes des x et des z :          */
/*  - de longueur 1                       		*/
/*  - de hauteur 1                              */
void mySolidFace();

/* Modelisation d'une croix avec une épaisseur  */
/* croix intérieur de diamètre 1                */
void thickCross();

/* Modelisation d'un cylindre de diamètre 1     */
/* avec des bitoniaux qui dépassent de chaque coté */
void thickSpiral3d(int nbSpires);

enum Thickness{
    THICK,
    THIN
};

void cylinder(float radius);
void cylinder(float radius, float revolution);

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
    ArmEmpty,
    Arm,
    ArmEnd,
    ArmAngle,
    ArmTAngle,

    Cross,
    ArmWithCross,
    ArmEndWithCross,
    ArmAngleWithCross,
    ArmHalfCylinder
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

#endif
