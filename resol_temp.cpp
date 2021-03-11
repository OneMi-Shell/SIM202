#include"resol_temp.h"

void evol_temp(Vecteur U, Vecteur V, Vecteur F,double dt, Matrice K, Matrice D, Matrice T)
{
    Vecteur W=U;
    Matrice D_inv= D.inverse();
    U=2*U-V + dt*dt*D_inv*(F-K*U + T*(U-V)/(dt));
    V=W;
}

void evolution(double t_0, double t_max, double dt, Vecteur U, Vecteur V, Vecteur F, Matrice K, Matrice D, Matrice T)
{
    int n = int ((t_max-t_0)/dt);
    for(int i =0;i<n;i++)
        evol_temp( U, V, F, dt,  K,  D,  T);
}
