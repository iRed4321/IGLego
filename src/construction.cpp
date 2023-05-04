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
    /*
    Brick brick1 = brick6330960();
    Brick brick2 = brick4666999();
    Brick brick3 = brick4163533();
    Brick brick4 = brick6159763();
    
    brick1.connect(0,0,brick2,0);
    brick2.connect(1,1,brick3,90);
    brick3.connect(0,1,brick4,0);
    */
    /*
    for(size_t i = 0; i< brick1.getConnectorList().size(); ++i){
        brick1[i].showonscreen();
    }
    */

    //NOTATION brick<numeroEtape>_<indexEtape>

    Brick brick1_0 = brick4249021();
<<<<<<< HEAD
    Brick brick1_1 = brick6321305();
    Brick brick1_3 = brick6282140();
    Brick brick1_4 = brick4211807();

    brick1_0.connect(3,0,brick1_3,0);
    brick1_0.connect(1,0,brick1_4,0);
    brick1_0.connect(4,2,brick1_1,0);
=======
    Brick brick1_1 = brick6299413();
    Brick brick1_2 = brick6299413();
    Brick brick1_3 = brick6299413();

    brick1_0.connect(1,0,brick1_1,0,true);
    brick1_0.connect(3,0,brick1_2,0,true);
    brick1_0.connect(2,0,brick1_3,0);
>>>>>>> ea3e5e859628b08fd776ac0582364306a713b65d
    
    
    brick1_0.display();
}