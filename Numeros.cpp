#include "Numeros.h"
using namespace std;


Numeros::Numeros(int i, int j, int k)
{
    resize(3);
    (*this)[0]=i;//ctor
    (*this)[1]=j;
    (*this)[2]=k;
}

int& Numeros::operator()(int num)
{
    return (*this)[num-1];
}

int Numeros::operator()(int num) const
{
    return (*this)[num-1];
}

Numeros Numeros::shift(int s) const
{
    Numeros num = *this;
    vector<int>::iterator itn;
    for(itn = num.begin();itn!=num.end();itn++)
        *itn +=s;
    return num;
}

ostream & operator <<(ostream & out, const Numeros N)
{
    out <<"(" << N(1) << " " <<  N(2) << " "  <<N(3) << ")" ;
    return out;
}
