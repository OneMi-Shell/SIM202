#ifndef RESOL_TEMP_H_INCLUDED
#define RESOL_TEMP_H_INCLUDED

#include"Matrice.h"

void evol_temp(Vecteur U,Vecteur V, Vecteur F, double t, Matrice K, Matrice D, Matrice T);
void evolution(double t_0, double t_max,double dt, Vecteur U, Vecteur V, Vecteur F, Matrice K, Matrice D, Matrice T);
#endif // RESOL_TEMP_H_INCLUDED
