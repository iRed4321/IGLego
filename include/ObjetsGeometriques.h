#ifndef __OBJETS_GEOMETRIQUES__
#define __OBJETS_GEOMETRIQUES__

/* Modelisation geometrique d'un cube :         */
/*  - de côte ct                                */
/*  - centre sur l'origine du repere            */
/*  - avec chaque face facettisee               */
/*    en n x n facettes carrees elementaires    */
void mySolidCube(double ct,int n);

/* Modelisation geometrique d'un rectangle      */
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

#endif
