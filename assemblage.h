#ifndef ASSEMBLAGE_H_INCLUDED
#define ASSEMBLAGE_H_INCLUDED
#include"Maillage.h"
#include "Numeros.h"
#include "Point2D.h"
#include"Matrice.h"

Matrice mat_masse_elem(double D,double rho);        //matrice de masse élementaire
void assembl_masse(Matrice& M1_1,Matrice& M1_2, Matrice& M2_1,Matrice& M2_2, Maillage M);

Matrice mat_surf_elem(double D, double rho, int indice_ij, int indice_surface,double VS, double VP);       //matrice surfacique élementaire
void assembl_surf(Matrice& T1_1,Matrice& T1_2, Matrice& T2_1, Matrice& T2_2, Maillage M,double VS,double VP);

Matrice mat_rig_elem_1(int i, int j, double D,double x1,double x2,double x3,double y1,double y2,double y3); //matrice de rigidité élemntaire
Matrice mat_rig_elem_2(int i, int j, double D,double x1,double x2,double x3,double y1,double y2,double y3); //matrice de rigidité élemntaire
void assembl_rig(Matrice& K1_1,Matrice& K1_2, Matrice& K2_1,Matrice& K2_2, Maillage M,double lambda, double mu);

Matrice build_D(Matrice M);

#endif // ASSEMBLAGE_H_INCLUDED
