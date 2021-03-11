#include <iostream>
#include<cmath>
#include<vector>
#include "assemblage.h"
#include "resol_temp.h"


using namespace std;

int main()
{

    Maillage Maill(5,5);  //déclaration du maillage

    //declaration des variables du problème
    int N= Maill.taille_maillage();
    double VS=1;
    double VP=1;
    double lambda = 1;
    double mu=1;

    double t_0 = 0;
    double t_max = 1;
    double dt =0.1;


    //assemblage de la matrice de masse
    Matrice M1_1= Matrice(N,N);
    Matrice M1_2= Matrice(N,N);
    Matrice M2_1= Matrice(N,N);
    Matrice M2_2= Matrice(N,N);
    assembl_masse(M1_1, M1_2, M2_1,M2_2, Maill);
    Matrice M = construction(M1_1, M1_2, M2_1,M2_2);
    Matrice D= build_D(M);


    //assemblage de la matrice de masse surfacique
    Matrice T1_1= Matrice(N,N);
    Matrice T1_2= Matrice(N,N);
    Matrice T2_1= Matrice(N,N);
    Matrice T2_2= Matrice(N,N);
    assembl_surf(T1_1, T1_2, T2_1,T2_2, Maill,VS,VP);
    Matrice T = construction(T1_1, T1_2, T2_1,T2_2);

    //assemblage de la matrice de rigidité
    Matrice K1_1= Matrice(N,N);
    Matrice K1_2= Matrice(N,N);
    Matrice K2_1= Matrice(N,N);
    Matrice K2_2= Matrice(N,N);
    assembl_rig(K1_1, K1_2, K2_1,K2_2, Maill,lambda,mu);
    Matrice K = construction(K1_1, K1_2, K2_1,K2_2);

    //assemblage du second membre
    Vecteur F(2*N);
    F.resize(2*N);
    //à faire


    //conditions initiales
    Vecteur U(2*N);    //on prend 0 comme conditions initiales
    Vecteur V(2*N);


    evolution(t_0, t_max, dt, U, V, F, K, D, T);



return 0;

}

