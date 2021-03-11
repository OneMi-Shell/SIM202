#include "Vecteur.h"
#include <cstdlib>

using namespace std;

void Vecteur::stop(const char * msg)
{
  cout<<"ERREUR classe Vecteur, "<<msg;
  exit(-1);
}

void Vecteur::compatible(const Vecteur& V){
    if(( size() != V.size() ))
        stop("erreur size.Vecteur != size.*this.");
}

Vecteur Vecteur::operator*=(double x)
{
    for(int i = 0;i<int(size());i++)
        (*this)[i] *=x;
    return *this;
}

Vecteur Vecteur::operator/=(double x)
{
    for(int i = 0;i<int(size());i++)
        (*this)[i] /=x;
    return *this;
}


Vecteur Vecteur::operator +=(const Vecteur& V)
{
    compatible(V);
    for(int i = 0;i<int(size());i++)
        (*this)[i] +=V[i];
    return *this;
}


Vecteur Vecteur::operator -=(const Vecteur& V)
{
    compatible(V);
    for(int i = 0;i<int(size());i++)
        (*this)[i] -=V[i];
    return *this;
}

//fin de la classe Vecteur


Vecteur operator*(double x, const Vecteur &V)
{
    Vecteur W=V;
    return W*=x;
}

Vecteur operator*(const Vecteur &V,double x)
{
    return x*V;
}


Vecteur operator/(const Vecteur &V,double x)
{
    return 1./x*V;
}

Vecteur operator+(const Vecteur& U,  const Vecteur& V)
{
    Vecteur W=V;
    return W+=U;
}

Vecteur operator-(const Vecteur& U,  const Vecteur& V)
{
    Vecteur W=V;
    return W-=U;
}


ostream & operator <<(ostream & out, const Vecteur& V)
{
    for(int i=1;i<=V.size();i++)
    {
        out << V(i) << endl;
    }

    return out;
}
