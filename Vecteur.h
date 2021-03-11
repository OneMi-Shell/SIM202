#ifndef VECTEUR_H
#define VECTEUR_H
#include <iostream>
#include<vector>

using namespace std;

class Vecteur : public std::vector<double>
{
    public:
        void stop(const char * msg);
        void compatible(const Vecteur& V);
        Vecteur(int n=0){(*this).resize(n);}    //constructeur

        double& operator()(int i){return (*this)[i-1];}     //accesseurs
        double operator()(int i) const {return (*this)[i-1];}

        Vecteur operator *=(double x);
        Vecteur operator /=(double x);
        Vecteur operator +=(const Vecteur& V);
        Vecteur operator -=(const Vecteur& V);

    protected:

    private:
};

Vecteur operator *(const Vecteur & V, double x);
Vecteur operator *(double x, const Vecteur& V);
Vecteur operator /(const Vecteur & V, double x);
Vecteur operator+(const Vecteur& U,  const Vecteur& V);
Vecteur operator-(const Vecteur& U,  const Vecteur& V);

ostream & operator <<(ostream & out, const Vecteur& V);

#endif // VECTEUR_H
