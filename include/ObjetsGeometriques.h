#ifndef __OBJETS_GEOMETRIQUES__
#define __OBJETS_GEOMETRIQUES__

/* Modelisation geometrique d'un cube :         */
/*  - de côte ct                                */
/*  - centre sur l'origine du repere            */
/*  - avec chaque face facettisee               */
/*    en n x n facettes carrees elementaires    */
void mySolidCube(int n);

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

/* Modelisation d'une croix */
void mySolidCross();

/* Modelisation d'une roue crantée 				*/
/* les dents commencent à une distance de 0.5 du centre */
/* et terminent à une distance 1.5 du centre 	*/
void mySolidGear(int nbTooth);

/* Modelisation geometrique d'un rectangle      */
/* parallele aux axes des x et des z :          */
/*  - de longueur 1                       		*/
/*  - de hauteur 1                              */
void mySolidFace();

void thickCross();
//need to correct makefile so this works
//void mySolidDisc(int ns);


#endif
