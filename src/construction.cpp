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
std::vector<Brick*> Brick::brickList;

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
    brick1_0.connect(4,3,brick4_1,90,true);


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

    //Etape 8

    Brick brick8_0 = brick6321305(); //batonnet beige qui tourne
    Brick brick8_1 = brick4206482(); //petit machin bleu
    Brick brick8_2 = brick6279875(); //petit machin noir
    Brick brick8_3 = brick6279875(); //petit machin noir
    Brick brick8_4 = brick6271156(); //gros baton tordu
    Brick brick8_5 = brick6332573(); //truc blanc qui va bouger

    brick8_4.connect(6,0,brick8_2,0,true);
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
    brick18_0.connect(6,0,brick18_3,0);
    brick18_0.connect(0,0,brick18_1,0);

    
    brick12_0.connect(2,5,brick18_0,-90);

    //Connexion de la partie que j'ai codé avec celle que jocelyn a codé

    brick9_0.setRoot(brick8_4);
    brick6_1.connect(0,1,brick8_4,90);

    //Etape 19

    Brick brick19_0 = brick6265135(); //petit connecteur blanc
    Brick brick19_1 = brick6330960(); //moyen connecteur blanc
    Brick brick19_2 = brick370726(); //barre de 8
    Brick brick19_3 = brick6275844(); // entretoise

    brick19_2.connect(0,0,brick19_1,180);
    brick19_2.connect(1,0,brick19_0,90);
    brick19_2.connect(2,0,brick19_3,0);

    brick2_0.connect(5,3,brick19_2,0);

    //Etape 20

    Brick brick20_0 = brick6275844(); // entretoise
    brick19_2.connect(4,0,brick20_0,0);


    //Etape 21

    Brick brick21_0 = brick4211815(); //batonnet
    Brick brick21_1 = brick6331723(); //fin gris
    Brick brick21_2 = brick6331723(); //fin gris

    brick21_0.connect(0,0,brick21_1,0,USED_LEFT,BOTH_USED);
    brick21_0.connect(1,0,brick21_2,0,USED_RIGHT,BOTH_USED);

    brick21_0.setRoot(brick21_1);
    
    brick19_2.connect(5,2,brick21_1,90,false,USED_RIGHT,BOTH_USED);

    //etape 22

    
    
    Brick brick22_0 = brick4211815(); //baton
    Brick brick22_1 = brick4211815(); //baton
    Brick brick22_2 = brick6327162(); //truc chelou

    brick22_2.connect(0,0,brick22_1,0,USED_LEFT, BOTH_USED);
    brick22_2.connect(6,0,brick22_0,0,USED_LEFT, BOTH_USED);

    brick21_0.connect(0,2,brick22_2,180,false, USED_RIGHT,BOTH_USED);



    //Etape 23
    
    Brick brick23_0 = brick4211815(); //batonnet
    Brick brick23_1 = brick4211815(); //batonnet
    Brick brick23_2 = brick4211815(); //batonnet
    Brick brick23_3 = brick6275844(); // entretoise

    Brick brick23_4 = brick6327548(); //fin noir 4
    Brick brick23_5 = brick6271810(); //fin noir perpendic

    brick23_5.connect(2,0,brick23_0,180,BOTH_USED, USED_RIGHT);
    brick23_0.connect(0,0,brick23_4,0,USED_RIGHT, BOTH_USED);
    brick23_4.connect(3,2,brick23_1,0,true, BOTH_USED, USED_RIGHT);
    brick23_5.connect(0,2,brick23_2,0,true,BOTH_USED, USED_LEFT);
    brick23_0.connect(1,0,brick23_3,0);


    brick14_0.connect(3,4,brick23_5,180, USED_RIGHT, BOTH_USED);
    
    //Etape 24

    Brick petitrouge = brick6261373();

    brick14_0.connect(4,0,petitrouge,-90,USED_RIGHT,BOTH_USED);


    // //etape 25

    Brick batongris3 = brick4211815(); 
    Brick batonConnector1 = brick4512360();
    Brick batonConnector2 = brick4512360();
    Brick batonnetrouge = brick4142865();

    batongris3.connect(2,0,batonConnector1,0);
    batonConnector1.connect(1,0,batonnetrouge,0);
    batonnetrouge.connect(1,0,batonConnector2,0);

    petitrouge.connect(1,1,batongris3,-53,true);
    


    // //etape 26
    Brick trucmarron = brick6344864();
    Brick trucmarron2 = brick6344864();


    brick23_2.connect(1,0,trucmarron,180);
    brick22_1.connect(1,0,trucmarron2,90);



    //etape27
    Brick blackwithcylinder = brick6276951();
    Brick blackthin3arm = brick6331723();

    brick23_1.connect(2,0,blackthin3arm,-90,USED_RIGHT,BOTH_USED);
    brick23_1.connect(1,1,blackwithcylinder,90);



    // // //etape 28

    Brick machinblanc = brick6265135();
    Brick barrenoire7 = brick4495935();
    Brick petitconngris = brick4211807();

    machinblanc.connect(1,0,petitconngris,0);
    petitconngris.connect(1,0,barrenoire7,93);
    batongris3.connect(0,0,machinblanc,0);
    std::cout<<angle<<std::endl;


    //etape 29

    Brick croixrondcroix1 = brick6331723();
    Brick croixrondcroix2 = brick6331723();

    brick21_0.connect(1,0,croixrondcroix2,0,USED_LEFT,BOTH_USED);
    brick21_0.connect(2,0,croixrondcroix1,0,USED_RIGHT,BOTH_USED);

    //etape 30

    Brick brick30_0 = brick6331723(); // +o+
    Brick brick30_1 = brick6271810(); // 3x3 L

    brick22_0.connect(2,0,brick30_0,-90,USED_RIGHT,BOTH_USED);
    brick22_1.connect(2,1,brick30_1,-90,true, USED_RIGHT,BOTH_USED);

    //etape 31

    Brick brick31_0 = brick6327162(); //truc chelou
    Brick brick31_1 = brick6327548(); //fin noir 4

    brick22_0.connect(2,6,brick31_0,0,USED_LEFT,BOTH_USED);
    brick23_0.connect(2,0,brick31_1,0,USED_LEFT,BOTH_USED);

    //etape 32

    Brick brick32_0 = brick4177431(); //truc rond chelou
    Brick brick32_1 = brick4211815(); //baton

    brick32_1.connect(0,0,brick32_0,0,BOTH_USED,BOTH_USED);
    blackwithcylinder.connect(0,1,brick32_1,0,BOTH_USED,BOTH_USED);

    //etape 33

    //truc bleu fonce
    Brick brick33_0 = brick4206482();

    //truc noir court
    Brick brick33_1 = brick6279875();
    Brick brick33_2 = brick6279875();

    //bleu clair
    Brick brick33_3 = brick6364749();
    Brick brick33_4 = brick6364749();

    //blanc mini
    // Brick brick33_5 = brick6177114();

    // blanc long
    Brick brick33_6 = brick6330960();

    brick33_3.connect(0,0,brick33_0,0,USED_RIGHT,BOTH_USED);
    
    brick33_1.connect(0,1,brick33_4,0,USED_RIGHT,BOTH_USED);
    brick33_1.connect(0,1,brick33_3,0,USED_LEFT,BOTH_USED);

    brick33_6.connect(1,1,brick33_2,180,USED_LEFT,USED_RIGHT);
    brick33_6.connect(2,1,brick33_1,180,USED_LEFT,USED_RIGHT);


    brick19_2.connect(7,0,brick33_6,180,USED_RIGHT,BOTH_USED);

    //etape 34

    Brick brick34_0 = brick6173003(); // L bleu
    Brick brick34_1 = brick6321305(); // jaune

    brick34_0.connect(6,2,brick34_1,0,true,BOTH_USED,BOTH_USED);
    brick18_3.connect(1,5,brick34_0,-90,USED_RIGHT,BOTH_USED);


    //etape 35

    Brick brick35_0 = brick6261643(); //Longue barre bleue
    brick18_4.connect(1,0,brick35_0,180+angle,BOTH_USED,BOTH_USED);

    //etape 36

    Brick brick36_0 = brick6173003(); // L bleu
    Brick brick36_1 = brick6321305(); // jaune

    brick36_0.connect(6,2,brick36_1,0,BOTH_USED,BOTH_USED);

    brick8_2.connect(1,5,brick36_0,90,true, USED_RIGHT,BOTH_USED);

    //etape 37

    Brick brick37_0 = brick6345239(); //thin blanche 6
    Brick brick37_1 = brick6345239(); //thin blanche 6
    Brick brick37_2 = brick4211807(); // petit conn gris

    brick37_2.connect(1,0,brick37_1,0,USED_RIGHT,BOTH_USED);
    brick37_2.connect(1,0,brick37_0,0,USED_LEFT,BOTH_USED);

    //etape 38

    Brick brick38_0 = brick4211807(); // petit conn gris
    brick37_1.connect(5,0,brick38_0,0,USED_LEFT,BOTH_USED);

    //etape 39

    Brick brick39_0 = brick6271810(); // 3x3 L
    Brick brick39_1 = brick6271810(); // 3x3 L

    brick38_0.connect(1,1,brick39_1,120,BOTH_USED,USED_LEFT);
    brick38_0.connect(1,1,brick39_0,120,BOTH_USED,USED_RIGHT);

    //etape 40

    brick35_0.connect(3,0,brick37_2,-55,true,BOTH_USED,BOTH_USED);

    //etape 41

    Brick brick41_0 = brick4177431(); //roue cheloue
    Brick brick41_1 = brick4142865(); //mini baton rouge

    brick41_1.connect(0,0,brick41_0,0,BOTH_USED,BOTH_USED);

    brick11_0.connect(1, 1, brick41_1, 0, true,BOTH_USED,BOTH_USED);

    //etape 42

    Brick brick42_0 = brick4206482(); // truc bleu

    //etape 43

    Brick brick43_0 = brick6364749(); // +oo+ bleu clair
    Brick brick43_1 = brick6364749(); // +oo+ bleu clair

    brick43_0.connect(0,0,brick42_0,0,USED_LEFT,BOTH_USED);
    brick42_0.connect(0,0,brick43_1,0,BOTH_USED,USED_LEFT);

    //etape 44

    Brick brick44_0 = brick6299413(); //3x1 cylindre bleu fonce
    Brick brick44_1 = brick6299413(); //3x1 cylindre bleu fonce

    brick44_0.connect(1,1,brick43_0,0,true,BOTH_USED,USED_RIGHT);
    brick43_0.connect(2,1,brick44_1,0,true,USED_LEFT,BOTH_USED);

    //etape 45

    // Brick brick45_0 = brick6343987(); //aileron blanc

    // etape 46

    brick19_1.connect(2,0,brick44_0,180,true,BOTH_USED,BOTH_USED);

    //etape 47

    Brick brick47_0 = brick4249021(); //5 ronds blanc
    Brick brick47_1 = brick6321305(); //cylindre jaune
    Brick brick47_2 = brick6321305(); //cylindre jaune

    brick35_0.connect(12,1,brick47_1,BOTH_USED,BOTH_USED);
    brick47_1.connect(0,0,brick47_0,75,BOTH_USED,BOTH_USED);
    brick47_0.connect(2,2,brick47_2,BOTH_USED,BOTH_USED);

    //etape 48, 49, 50, 51

    Brick brick48_0 = brick4142135(); //5 ronds noirs
    Brick brick48_1 = brick6279875(); //conn noir mini
    Brick brick48_2 = brick6279875(); //conn noir mini

    Brick brick49_0 = brick6271825(); //L noir 4x1

    Brick brick50_0 = brick4211815(); //batonnet croix gris
    Brick brick50_1 = brick6299413(); //batonnet rond bleu fonce
    Brick brick50_2 = brick6299413(); //batonnet rond bleu fonce

    Brick brick51_0 = brick4552347(); //T noir
    Brick brick51_1 = brick6299413(); //batonnet rond bleu fonce


    brick51_1.connect(1,2,brick51_0,BOTH_USED,BOTH_USED);
    
    brick51_0.connect(0,1,brick50_1,BOTH_USED,BOTH_USED);
    brick51_0.connect(1,1,brick50_2,BOTH_USED,BOTH_USED);
    brick50_1.connect(2,1,brick49_0,true,BOTH_USED,BOTH_USED);
    brick49_0.connect(0,0,brick50_0,BOTH_USED,BOTH_USED);

    brick49_0.connect(3,0,brick48_1,0,BOTH_USED,BOTH_USED);
    brick49_0.connect(4,0,brick48_2,0,BOTH_USED,BOTH_USED);

    brick48_1.connect(1,0,brick48_0,90,BOTH_USED,BOTH_USED);

    //etape 52

    Brick brick52_0 = brick6271825(); //L noir 4x1

    brick50_1.connect(0,1,brick52_0,0,BOTH_USED,BOTH_USED);

    // etape 53

    Brick brick53_0 = brick4142135(); //5 ronds noirs
    Brick brick53_1 = brick6279875(); //conn noir mini
    Brick brick53_2 = brick6279875(); //conn noir mini

    brick52_0.connect(4,1,brick53_1,0,BOTH_USED,BOTH_USED);
    brick52_0.connect(3,1,brick53_2,0,BOTH_USED,BOTH_USED);

    brick53_2.connect(0,0,brick53_0,90,BOTH_USED,BOTH_USED);

    // etape 54

    brick47_0.connect(4,2,brick51_1,30,true,BOTH_USED,BOTH_USED);

    // etape 55

    Brick brick55_0 = brick4249021(); //5 ronds blanc
    brick51_1.connect(0,4,brick55_0,30,BOTH_USED,BOTH_USED);

    // etape 56

    Brick brick56_0 = brick6275844(); //mini gris
    Brick brick56_1 = brick6275844(); //mini gris

    Brick brick56_2 = brick4163533(); //2x1 blanc fin
    Brick brick56_3 = brick4163533(); //2x1 blanc fin

    Brick brick56_4 = brick6265135(); //2x1 blanc gros
    Brick brick56_5 = brick6265135(); //2x1 blanc gros

    Brick brick56_6 = brick4142865(); //baton 2 rouge
    Brick brick56_7 = brick4142865(); //baton 2 rouge
    Brick brick56_8 = brick370526(); //baton noir

    brick56_4.connect(1,0,brick56_6,0,USED_RIGHT,USED_RIGHT);
    brick56_6.connect(1,0,brick56_2,0,BOTH_USED,USED_LEFT);
    brick56_2.connect(1,0,brick56_7,0,true,BOTH_USED,USED_LEFT);
    brick56_7.connect(0,0,brick56_5,0,true,USED_LEFT,USED_RIGHT);
    brick56_7.connect(1,0,brick56_3,180,BOTH_USED,USED_LEFT);

    brick56_5.connect(1,1,brick56_8,0,true,USED_LEFT,USED_RIGHT);

    brick56_8.connect(0,0,brick56_0,0,true,USED_LEFT,USED_RIGHT);
    brick56_8.connect(2,0,brick56_0,0,true,USED_LEFT,USED_RIGHT);

    brick50_0.connect(1,0,brick56_4,150,BOTH_USED,BOTH_USED);

    // etape 57

    Brick brick57_0 = brick4206482(); //2x1 bleu fonce
    Brick brick57_1 = brick4206482(); //2x1 bleu fonce

    Brick brick57_2 = brick6271165(); //fin gris
    Brick brick57_3 = brick6271165(); //fin gris

    Brick brick57_4 = brick6331723(); // +o+ noir fin
    Brick brick57_5 = brick6331723(); // +o+ noir fin

    brick57_0.connect(0,0,brick57_4,0,USED_LEFT,BOTH_USED);
    brick57_0.connect(0,0,brick57_2,0,USED_RIGHT,BOTH_USED);

    brick57_1.connect(0,0,brick57_5,0,USED_LEFT,BOTH_USED);
    brick57_1.connect(0,0,brick57_3,0,USED_RIGHT,BOTH_USED);

    brick55_0.connect(1,1,brick57_0,130,BOTH_USED,BOTH_USED);
    brick47_0.connect(1,1,brick57_1,230,BOTH_USED,BOTH_USED);

    // etape 58

    Brick brick58_0 = brick4619323(); // pneu noir
    Brick brick58_1 = brick4619323(); // pneu noir
    Brick brick58_2 = brick4619323(); // pneu noir
    Brick brick58_3 = brick4619323(); // pneu noir

    brick34_1.connect(0,0,brick58_1,0,BOTH_USED,BOTH_USED);
    brick36_1.connect(0,0,brick58_0,0,BOTH_USED,BOTH_USED);

    brick5_0.connect(0,0,brick58_2,0,BOTH_USED,BOTH_USED);
    brick5_1.connect(0,0,brick58_3,0,BOTH_USED,BOTH_USED);


    //etape 59

    Brick brick59_0 = brick4509897(); //grosse plaque

    brick48_0.connect(2,0,brick59_0,true,BOTH_USED,BOTH_USED);


    // Brick brick59_1 = brick4234365(); //plot jaune


    

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

void testPieceEnCoursNathan(float angle){

    
    
}