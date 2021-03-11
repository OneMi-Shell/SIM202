#include "assemblage.h"
#include<cmath>
#include <stdlib.h>
#include "Numeros.h"
#include "Point2D.h"

//matrice de masse elementaire
//On intègre les fonctions élémentaires sur le triangle, en transformant le triangkle courant en triangle de base (0,0);(1,0);(0,1)
//D est le déterminnant du changement de variable
//rho est la masse volumique du milieu dans lequel on se trouve.


Matrice mat_masse_elem(double D,double rho)       //matrice de masse élementaire
{
    Matrice Mel = Matrice(3,3);

    Mel(1,1) =2;
    Mel(1,2)=1;
    Mel(1,3)= 1;
    Mel(2,1)=1;
    Mel(2,2)= 2;
    Mel(2,3) = 1;
    Mel(3,1)=1;
    Mel(3,2)= 1;
    Mel(3,3)=2;

    Mel *=rho*D/24;
    return Mel;
}

void assembl_masse(Matrice& M1_1,Matrice& M1_2, Matrice& M2_1,Matrice& M2_2, Maillage M)
{
    int nb_tri = M.nb_tri();

    for(int l =1 ; l<= nb_tri ; l++)
    {
        Numeros T=M.num_tri(l);    //T est le i-ème triangle du maillage
        Point2D i = Point2D( M.noeud(T(1)) );
        Point2D j = Point2D( M.noeud(T(2)));
        Point2D k = Point2D( M.noeud(T(3)));      //les points i,j,k sont les points formant le triangle T_l
        double x_i,x_j,x_k,y_i,y_j,y_k;     //on simplifie les notations
        x_i = i.Coor_x() ; x_j=j.Coor_x() ; x_k=k.Coor_x();
        y_i= i.Coor_y() ; y_j=j.Coor_y() ; y_k=k.Coor_y();


        double r=M.rho(l);      //on met le rho correspondant à la zone dans laquelle se trouve le triangle

        double D= abs((x_j-x_i)*(y_k-y_i) -(x_k-x_i)*(y_j-y_i));       //déterminant du changement de variables
        Matrice Mel=mat_masse_elem(D,r);       //matrice élementaire


        M1_1(T(1),T(1)) +=Mel(1,1);             //on met les coefficients à la bonne place dans la matrice
        M1_1(T(1),T(2)) += Mel(1,2);
        M1_1(T(1),T(3)) +=Mel(1,3);

        M1_1(T(2),T(1)) +=Mel(2,1);
        M1_1(T(2),T(2)) += Mel(2,2);
        M1_1(T(2),T(3)) +=Mel(2,3);

        M1_1(T(3),T(1)) +=Mel(3,1);
        M1_1(T(3),T(2)) += Mel(3,2);
        M1_1(T(3),T(3)) +=Mel(3,3);

    }

    M2_2 = M1_1;
}

//matrice surfacique élémentaire
//On intègre les fonctions élémentaires sur [S_i,S_j]
//C'est un segment que l'on écrit y=ax + b, d'où les valeurs de a et b
//indice_IJ désigne si on est dans le cas I=J=1 ou I=J=2
//indice_surface désigne si [S_i,S_j] est un morceau du fond ou un morceau des côtés
//VP,VS désignent les valeurs propres de la matrice A

Matrice mat_surf_elem(double D, double rho, int indice_ij, int indice_surface,double VS, double VP)       //matrice de masse élementaire
{
    Matrice Sel = Matrice(2,2);
    Sel(1,1) =2;
    Sel(1,2)=1;
    Sel(2,1) = 1;
    Sel(2,2)=2;

    Sel*=1./6*D*rho;

    if ( (indice_ij== 1 && indice_surface==1) || ((indice_ij== 2 && indice_surface==1)) )
        {Sel *= VP;}
    else
        {Sel *= VS;}

    return Sel;
}


void assembl_surf(Matrice& T1_1,Matrice& T1_2, Matrice& T2_1, Matrice& T2_2, Maillage M,double VS,double VP)
{
    int nb_tri = M.nb_tri();
    int surf=0;

    for (int l =1 ; l<= nb_tri ; l++)
    {
        surf=M.som_surface(1); // chiffre donnant la partie de la surface sur laquelle on se trouve. Vaut 0 si le point n'est pas sur la surface
        if(surf != 0)
        {

            Numeros T= M.num_tri(l);    //T est le i-ème triangle du maillage
            Point2D i = Point2D( M.noeud(T(1)) );
            Point2D j = Point2D( M.noeud(T(2)));
            Point2D k = Point2D( M.noeud(T(3)));      //les points i,j,k sont les points formant le triangle T_l
            double x_i,x_j,x_k,y_i,y_j,y_k;     //on simplifie les notations
            x_i = i.Coor_x() ; x_j=j.Coor_x() ; x_k=k.Coor_x();
            y_i= i.Coor_y() ; y_j=j.Coor_y() ; y_k=k.Coor_y();


            double r=M.rho(l);      //on met le rho correspondant à la zone dans laquelle se trouve le triangle

            double D= abs((x_j-x_i)*(y_k-y_i) -(x_k-x_i)*(y_j-y_i));       //déterminant du changement de variables

            int indice_ij=1;       //cas où i=j=1

            Matrice Tel= mat_surf_elem(D, r, indice_ij, surf ,VS, VP);       //matrice élementaire

            T1_1(T(1),T(1)) += Tel(1,1);             //on met les coefficients à la bonne place dans la matrice
            T1_1(T(1),T(2)) += Tel(1,2);
            T1_1(T(2),T(1)) += Tel(2,1);
            T1_1(T(2),T(2)) += Tel(2,2);

            indice_ij=2;    //cas où i=j=2, on refait la même chose

            Tel= mat_surf_elem(D, r, indice_ij, surf ,VS, VP);       //matrice élementaire

            T2_2(T(1),T(1)) += Tel(1,1);             //on met les coefficients à la bonne place dans la matrice
            T2_2(T(1),T(2)) += Tel(1,2);
            T2_2(T(2),T(1)) += Tel(2,1);
            T2_2(T(2),T(2)) += Tel(2,2);

        }
    }

}


void assembl_rig(Matrice& K1_1,Matrice& K1_2, Matrice& K2_1,Matrice& K2_2, Maillage M,double lambda, double mu)
 {
     int nb_tri = M.nb_tri();

    for(int l =1 ; l<= nb_tri ; l++)
    {

        Numeros T=M.num_tri(l);    //T est le i-ème triangle du maillage
        Point2D i = Point2D( M.noeud(T(1)) );
        Point2D j = Point2D( M.noeud(T(2)));
        Point2D k = Point2D( M.noeud(T(3)));      //les points i,j,k sont les points formant le triangle T_l
        double x_i,x_j,x_k,y_i,y_j,y_k;     //on simplifie les notations
        x_i = i.Coor_x() ; x_j=j.Coor_x() ; x_k=k.Coor_x();
        y_i= i.Coor_y() ; y_j=j.Coor_y() ; y_k=k.Coor_y();


        double D= abs((x_j-x_i)*(y_k-y_i) -(x_k-x_i)*(y_j-y_i));       //déterminant du changement de variables


        Matrice Kel_1=mat_rig_elem_1(1,1,D,x_i,x_j,x_k,y_i,y_j,y_k);      //matrice élementaire
        Matrice Kel_2=mat_rig_elem_2(1,1,D,x_i,x_j,x_k,y_i,y_j,y_k);
        Matrice Kel=lambda/D*Kel_1 + mu/(2*D)*Kel_2;


        K1_1(T(1),T(1)) +=Kel(1,1);             //on met les coefficients à la bonne place dans la matrice
        K1_1(T(1),T(2)) += Kel(1,2);
        K1_1(T(1),T(3)) +=Kel(1,3);

        K1_1(T(2),T(1)) +=Kel(2,1);
        K1_1(T(2),T(2)) += Kel(2,2);
        K1_1(T(2),T(3)) +=Kel(2,3);

        K1_1(T(3),T(1)) +=Kel(3,1);
        K1_1(T(3),T(2)) += Kel(3,2);
        K1_1(T(3),T(3)) +=Kel(3,3);



        Kel_1=mat_rig_elem_1(1,2,D,x_i,x_j,x_k,y_i,y_j,y_k);      //matrice élementaire
        Kel_2=mat_rig_elem_1(1,2,D,x_i,x_j,x_k,y_i,y_j,y_k);
        Kel=lambda/D*Kel_1 + mu/(2*D)*Kel_2;

        K1_2(T(1),T(1)) +=Kel(1,1);             //on met les coefficients à la bonne place dans la matrice
        K1_2(T(1),T(2)) += Kel(1,2);
        K1_2(T(1),T(3)) +=Kel(1,3);

        K1_2(T(2),T(1)) +=Kel(2,1);
        K1_2(T(2),T(2)) += Kel(2,2);
        K1_2(T(2),T(3)) +=Kel(2,3);

        K1_2(T(3),T(1)) +=Kel(3,1);
        K1_2(T(3),T(2)) += Kel(3,2);
        K1_2(T(3),T(3)) +=Kel(3,3);



        Kel_1=mat_rig_elem_1(2,1,D,x_i,x_j,x_k,y_i,y_j,y_k);      //matrice élementaire
        Kel_2=mat_rig_elem_1(2,1,D,x_i,x_j,x_k,y_i,y_j,y_k);
        Kel=lambda/D*Kel_1 + mu/(2*D)*Kel_2;

        K2_1(T(1),T(1)) +=Kel(1,1);             //on met les coefficients à la bonne place dans la matrice
        K2_1(T(1),T(2)) += Kel(1,2);
        K2_1(T(1),T(3)) +=Kel(1,3);

        K2_1(T(2),T(1)) +=Kel(2,1);
        K2_1(T(2),T(2)) += Kel(2,2);
        K2_1(T(2),T(3)) +=Kel(2,3);

        K2_1(T(3),T(1)) +=Kel(3,1);
        K2_1(T(3),T(2)) += Kel(3,2);
        K2_1(T(3),T(3)) +=Kel(3,3);



        Kel_1=mat_rig_elem_1(2,2,D,x_i,x_j,x_k,y_i,y_j,y_k);      //matrice élementaire
        Kel_2=mat_rig_elem_1(2,2,D,x_i,x_j,x_k,y_i,y_j,y_k);
        Kel=lambda/D*Kel_1 + mu/(2*D)*Kel_2;

        K2_2(T(1),T(1)) +=Kel(1,1);             //on met les coefficients à la bonne place dans la matrice
        K2_2(T(1),T(2)) += Kel(1,2);
        K2_2(T(1),T(3)) +=Kel(1,3);

        K2_2(T(2),T(1)) +=Kel(2,1);
        K2_2(T(2),T(2)) += Kel(2,2);
        K2_2(T(2),T(3)) +=Kel(2,3);

        K2_2(T(3),T(1)) +=Kel(3,1);
        K2_2(T(3),T(2)) += Kel(3,2);
        K2_2(T(3),T(3)) +=Kel(3,3);


    }
}



Matrice mat_rig_elem_1(int i, int j, double D,double x1,double x2,double x3,double y1,double y2,double y3)
{
    Matrice Kel = Matrice(3,3);
    double x12=x1-x2;
    double x21=-x12;
    double x13=x1-x3;
    double x31=-x13;
    double x23 = x2-x3;
    double x32 =-x23;

    double y12=y1-y2;
    double y21= -y12;
    double y13=y1-y3;
    double y31= -y13;
    double y23 = y2-y3;
    double y32=-y23;

    if(i==1 && j== 1)       //on calcule (Kel)_11
    {
        Kel(1,1)=y23*y23;
        Kel(1,2)=y13*y31;
        Kel(1,3)=y23*y21;

        Kel(2,1)=y23*y31;
        Kel(2,2)=y31*y31;
        Kel(2,3)=y21*y31;

        Kel(3,1)=y23*y21;
        Kel(3,2)=y31*y21;
        Kel(3,3)=y21*y21;

    }

        if(i==1 && j== 2)       //on calcule (Kel)_12
    {
        Kel(1,1)=y23*x32;
        Kel(1,2)=y23*x13;
        Kel(1,3)=y23*x21;

        Kel(2,1)=y23*x13;
        Kel(2,2)=y31*x13;
        Kel(2,3)=y31*x21;

        Kel(3,1)=y12*x32;
        Kel(3,2)=y31*x21;
        Kel(3,3)=y12*x21;

    }    if(i==2 && j== 1)       //on calcule (Kel)_21
    {
        Kel(1,1)=y23*x32;
        Kel(2,1)=y23*x13;
        Kel(3,1)=y23*x21;

        Kel(1,2)=y23*x13;
        Kel(2,2)=y31*x13;
        Kel(3,2)=y31*x21;

        Kel(1,3)=y12*x32;
        Kel(2,3)=y31*x21;
        Kel(3,3)=y12*x21;
    }
        if(i==2 && j== 2)       //on calcule (Kel)_11
    {
        Kel(1,1)=x23*x23;
        Kel(1,2)=x32*x13;
        Kel(1,3)=x32*x21;

        Kel(2,1)=x32*x13;
        Kel(2,2)=x13*x13;
        Kel(2,3)=x21*x13;

        Kel(3,1)=x32*x21;
        Kel(3,2)=x13*x21;
        Kel(3,3)=x21*x21;
    }

return Kel;

}

Matrice mat_rig_elem_2(int i, int j, double D,double x1,double x2,double x3,double y1,double y2,double y3)
{
    return mat_rig_elem_1(j,i,D,x1,x2,x3,y1,y2,y3);     //contribution de epsilon
}



Matrice build_D(Matrice M)
{
    int N = M.dimc();
    Matrice D = Matrice(N,N);
    for(int l=1;l<=N;l++)    {
        for(int p=1;p<=N;p++)
            D(l,l) +=M(l,p);
    }
    return D;
}

