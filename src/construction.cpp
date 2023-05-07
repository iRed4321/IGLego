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

int Brick::class_id=0;

//********************************************************************************
// -------------------------------------------- BUILDING THE LEGO THING WOOWOWOWOW
//********************************************************************************

void construction(float angle){

    Brick::reset_class_id();
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

    //ETAPE 3
    Brick brick3_0 = brick4206482();
    Brick brick3_1 = brick6282140();
    
    brick2_0.connect(8,1,brick3_0,0);
    brick2_0.connect(7,0,brick3_1,0);

    //ETAPE 4
    Brick brick4_0 = brick6282158();
    Brick brick4_1 = brick6282158();

    brick1_0.connect(0,3,brick4_0,90,true);
    brick1_0.connect(4,3,brick4_1,270);

    //ETAPE 5
    Brick brick5_0 = brick6321305();
    Brick brick5_1 = brick6321305();

    brick4_0.connect(2,2,brick5_0,0,true);
    brick4_1.connect(2,2,brick5_1,0);

    //ETAPE 6
    Brick brick6_0 = brick4249021();
    Brick brick6_1 = brick6299413();

    brick4_0.connect(6,0,brick6_0,90);
    //à voir, peut-être pas bon la 3.1 (6282140) niveau dimensions
    brick3_1.connect(1,1,brick6_1,0);

    //ETAPE 7
    Brick brick7_0 = brick4177444();
    Brick brick7_1 = brick4177444();

    brick1_1.connect(2,1,brick7_0,0);
    brick1_2.connect(2,0,brick7_1,0);

    //AFFICHAGE
    brick1_0.display();


    std::vector<struct Link> vec = brick1_0.pathTo(brick6_1);

    reverseLink(vec[0]);
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

void testPieceEnCoursNathan(float angle){

    //Etape 8

    Brick brick8_0 = brick6321305(); //batonnet beige qui tourne
    Brick brick8_1 = brick4206482(); //petit machin bleu
    Brick brick8_2 = brick6279875(); //petit machin noir
    Brick brick8_3 = brick6279875(); //petit machin noir
    Brick brick8_4 = brick6271156(); //gros baton tordu
    Brick brick8_5 = brick6332573(); //truc blanc qui va bouger

    brick8_4.connect(6,0,brick8_2,0);
    brick8_4.connect(8,0,brick8_3,0,true);
    brick8_4.connect(0,0,brick8_1,0,true);
    brick8_4.connect(7,2,brick8_0,0,true);
    brick8_0.connect(1,0,brick8_5,180+angle);


    //Etape 9

    Brick brick9_0 = brick6159763(); // baton noir
    Brick brick9_1 = brick6261373(); //machin rouge

    brick9_0.connect(0,0,brick9_1,0);

    //Etape 10

    Brick brick10_0 = brick6185471(); //gearWormScrew
    Brick brick10_1 = brick6261373(); //machin rouge

    brick9_0.connect(1,0,brick10_0,0);
    brick9_0.connect(3,0,brick10_1,0);

    //Etape 11

    Brick brick11_0 = brick6276052(); //connecteur de barres blanc

    brick9_0.connect(4,0,brick11_0,0);

    //Etape 12

    
    Brick brick12_0 = brick6089119(); //barre noire

    brick10_1.connect(1,1,brick12_0,0,true);


    //Etape 13

    brick12_0.connect(0,5,brick8_4,-90);

    

    //Etape 14
    Brick brick14_0 = brick6159763(); // baton noir avec stop
    brick9_1.connect(1,1,brick14_0,0,true);


    //Etape 15
    Brick brick15_0 = brick4666999(); // baton beige avec stop
    Brick brick15_1 = brick6012451(); // petite roue crantée
    brick15_0.connect(1,0,brick15_1,0);
    brick8_4.connect(3,3,brick15_0,0);


    //Etape 16
    Brick brick16_0 = brick370826(); // grand baton noir
    Brick brick16_1 = brick6332573(); // petit truc blanc qui tourne
    brick16_0.connect(0,1,brick16_1,0); 

    //Etape 17
    brick8_5.connect(1,11,brick16_0,0,true);

    //Etape 18
    Brick brick18_0 = brick6271156(); //gros baton tordu
    Brick brick18_1 = brick6209519(); //Connecteur rouge
    Brick brick18_2 = brick6279875(); //petit machin noir
    Brick brick18_3 = brick6279875(); //petit machin noir
    Brick brick18_4 = brick4211815(); //batonnet gris

    brick18_0.connect(9,0,brick18_4,0);
    brick18_0.connect(8,0,brick18_2,0);
    brick18_0.connect(6,0,brick18_3,0,true);
    brick18_0.connect(0,0,brick18_1,0);

    //Etape 19
    brick12_0.connect(2,5,brick18_0,-90);

    //Etape 20

    //Affichage !
    brick9_0.display();
    
}