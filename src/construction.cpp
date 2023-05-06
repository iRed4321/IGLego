#include <vector>
#include <iostream>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159235
#endif

#include "construction.h"

//********************************************************************************
// -------------------------------------------- BUILDING THE LEGO THING WOOWOWOWOW
//********************************************************************************

void construction(float angle){

    // NOTATION : 
    //  brick<numeroEtape>_<indexEtape>

    //ETAPE 1
    Brick brick1_0 = brick4249021();
    Brick brick1_1 = brick6299413();
    Brick brick1_2 = brick6299413();

    brick1_0.connect(1,0,brick1_1,0);
    brick1_0.connect(3,0,brick1_2,0);
    
    //ETAPE 2
    Brick brick2_0 = brick6055519();

    brick1_1.connect(1,0,brick2_0,0);
    

    //AFFICHAGE
    brick1_0.display();
}

void testPieceEnCours(){
    Brick brick1_0 = brick4619323();
    Brick brick1_1 = brick6321305();

    brick1_0.connect(0,2,brick1_1,0,true);

    brick1_0.display();
}

void testDemiConnexions(){
    Brick petiteBarre = brick4666999();
    //lol les entretoises sont pas codées donc on aura autre chose à la place
    Brick entretoise0 = brick6012451();
    Brick entretoise1 = brick6012451();

    petiteBarre.connect(2,0,entretoise0,0, USED_LEFT,USED_LEFT);
    petiteBarre.connect(2,0,entretoise1,0, USED_RIGHT,USED_RIGHT);

    petiteBarre.display();

}