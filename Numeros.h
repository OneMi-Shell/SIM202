#ifndef NUMEROS_H
#define NUMEROS_H
#include"Vecteur.h"
#include<iostream>
using namespace std;

class Numeros : public std::vector<int>
{
    public:
        Numeros(int i, int j, int k);
        int& operator()(int num);
        int operator()(int num) const;
        Numeros shift(int s)const;

    protected:

    private:

};

ostream & operator <<(ostream & out, const Numeros N);


#endif // NUMEROS_H
