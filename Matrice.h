#ifndef Matrice_H
#define Matrice_H
#include <iostream>
#include"Vecteur.h"

using namespace std;

class Matrice
{
    private:
        int dim_l,dim_c;
        vector<vector <double> > mat;
    public:
        void stop(const char * msg);
        Matrice(int l, int c);
        void compatible(const Matrice& M);
        void compatible_prod(const Matrice &M);
        void compatible_puissance(const Matrice &M);

        int diml() {return dim_l;}  //accesseurs des dims
        int diml() const{return dim_l;}
        int dimc() {return dim_c;}
        int dimc() const{return dim_c;}

        double& operator()(int i, int j){return mat[i-1][j-1];}
        double operator()(int i, int j) const {return mat[i-1][j-1];}


        Matrice& operator +=(const Matrice &M);
        Matrice& operator -=(const Matrice &M);
        Matrice& operator *=(double x);
        Matrice& operator /=(double x);
        Matrice& operator *=(const Matrice& M);
        Matrice operator ^(int n);
        Matrice inverse(); // pour l'inversion de matrices

        void affiche();
        void affiche()const;
        bool est_sym();
        bool est_sym() const;

        friend Matrice operator*( Matrice M1,Matrice M2);
        friend Vecteur operator*( Matrice M, Vecteur V);

};
Matrice operator +(Matrice M,Matrice N);
Matrice operator *(Matrice M,double x);
Matrice operator *(double x, Matrice M);
Matrice operator /(Matrice M,double x);
Matrice operator /(double x, Matrice M);
Matrice identity(int dim);

Matrice construction(Matrice M1_1, Matrice M1_2,Matrice M2_1, Matrice M2_2);


#endif // Matrice_H


//stockage pas efficace pour des grosses matrices
