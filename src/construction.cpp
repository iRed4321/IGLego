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

    //NOTATION brick<numeroEtape>_<indexEtape>

    Brick brick1_0 = brick4249021();
    Brick brick1_1 = brick6299413();
    Brick brick1_2 = brick6299413();

    brick1_0.connect(1,0,brick1_1,0);
    brick1_0.connect(3,0,brick1_2,0);
    
    Brick brick2_0 = brick6055519();

    brick1_1.connect(1,0,brick2_0,0);
    
    brick1_0.display();
}