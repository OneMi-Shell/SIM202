#ifndef MAILLAGE_H
#define MAILLAGE_H
#include "Numeros.h"
#include "Point2D.h"
#include<vector>
#include<list>
#include<iostream>
using namespace std;

class Maillage
{
    public:
        void maille_carre_unite(int m, int n);      //maillage carr� avec m lignes et n colonnes
        Maillage(int m,int n){maille_carre_unite(m-1,n-1);}
        Maillage(double a, double b, double c, double d, int m, int n); //maillage rectangulaire o� l'on a choisi la forme du rectangle

        void affiche() const;
        void tf_affine(const vector<double> &A, const vector<double> t );      //A est une matrice, t est un vecteur : on fait une transfo affine

        Maillage operator+=(const Maillage & M);

        int nb_tri(){return Num_Tri.size();}
        int taille_maillage(){return Noeuds.size();}

        Numeros& num_tri(int l){return Num_Tri[l-1];}
        Numeros num_tri(int l) const{return Num_Tri[l-1];}

        Point2D noeud(int i){return Noeuds[i-1];}
        int zone(int i){return Zone[i];}

        double rho(int n);
        int som_surface(int l){return Surface[l-1];}


    protected:

    public:
        vector<Point2D> Noeuds;     //vecteur de point : Noeuds[i] contient la position du i-�me noeud
        vector<Numeros> Num_Tri;    //vecteur de triplet : Num_Tri[l] contient les num�ros des sommets compposant le triangle num�ro l
        vector<int> Zone;           //Zone[l] contient la zone dans laquelle est situ�e le l-i�me triangle (1 pour la roche, 2 pour la terre, 3 pour les mines)
        vector<double> Rho;         //Rho est un vecteur � 3 composantes, Rho[i] = rho_i;
        vector<int> Surface;        //Surface[i] contient 0 si le i�me Noeud n'est pas la surface, 1 s'il est situ� � gauche ou � droite, 2 s'il est situ� au fond.

};


Maillage operator+(Maillage M1, Maillage M2);

#endif // MAILLAGE_H






//am�liorer la construction de Surface(construire Surface en m�me temps que Noeuds au lieu de faire 2 parcours)
