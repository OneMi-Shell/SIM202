#include "Matrice.h"
#include <cstdlib>

using namespace std;

void Matrice::stop(const char * msg)
{
  cout<<"ERREUR classe Matrice, "<<msg;
  exit(-1);
}

void Matrice::compatible(const Matrice &M){
    if((dim_l != M.dim_l) || (dim_c != M.dim_c))
        stop("erreur pour la somme ou la difference");
}

void Matrice::compatible_prod(const Matrice &M){
    if((dim_l != M.dim_c) )
        stop("erreur pour la multiplication des matrices");
}

void Matrice::compatible_puissance(const Matrice &M){
    if((dim_l != M.dim_l) || (dim_c != M.dim_c) || (dim_c==dim_l))
        stop("erreur lors de l'élévation à la puissance");
}




Matrice::Matrice(int l, int c)
 {
     dim_l=l;
     dim_c=c;
     mat.resize(dim_l);
     for(int i =0; i<l;i++)
    {
        mat[i].resize(dim_c);

    }

}

Matrice& Matrice::operator+=(const Matrice & M)
{
    compatible(M);
    for(int i=1;i<=dim_l;i++)
    {
        for(int j=1;j<=dim_c;j++)
            (*this)(i,j)+=M(i,j);
    }
    return *this;
}

Matrice& Matrice::operator-=(const Matrice & M)
{
    compatible(M);
    for(int i=1;i<=dim_l;i++)
    {
        for(int j=1;j<=dim_c;j++)
            (*this)(i,j)-=M(i,j);
    }
    return *this;
}



Matrice& Matrice::operator*=(double x)
{
    for(int i=1;i<=dim_l;i++)
    {
        for(int j=1;j<=dim_c;j++)
            (*this)(i,j)*= x;
    }
    return *this;
}


Matrice& Matrice::operator/=(double x)
{
    for(int i=1;i<=dim_l;i++)
    {
        for(int j=1;j<=dim_c;j++)
            (*this)(i,j)/= x;
    }
    return *this;
}

Matrice& Matrice::operator *=(const Matrice& M)
{
    compatible_prod(M);
    *this = (*this) * M;
    return *this;
}

Matrice Matrice::operator ^(int n)
{
    if(n==0)
    {return identity(3);}

    else if(n==1){return *this;}

    else if(n>1){
        if (n%2 ==0)
            {return ( (*this)^(n/2)) *((*this^(n/2)));}
        else{return (*this) * ( (*this)^((n-1)/2)) *((*this^((n-1)/2)));}
    }
    else{stop("puissance négative");}

}

Matrice Matrice::inverse()
{
    Matrice M = Matrice(dim_c,dim_c);
    for (int i = 1; i <= dim_l; i++)
        M(i,i)=1/((*this)(i,i));
    return M;

}

//opérateurs d'accès




void Matrice::affiche()
{
    for(int i=0;i<dim_l;i++)
    {
        for(int j=0;j<dim_c;j++)
            {cout << (*this)(i,j) <<" ";}
        cout<<endl;
    }
}

void Matrice::affiche() const
{
    for(int i=1;i<=dim_l;i++)
    {
        for(int j=1;j<=dim_c;j++)
            {cout << (*this)(i,j) <<" ";}
        cout<<endl;
    }
}

bool Matrice::est_sym()
{
    if (dim_c!= dim_l) return false;
    else{
        int n=dim_c;
        for(int i =1;i<=n;i++){
            for(int j=1;j<=n;j++)
            {if ( (*this)(i,j) != (*this)(j,i) ) return false;}
        }
    return true;
    }
}

bool Matrice::est_sym() const
{
    if (dim_c!= dim_l) return false;
    else{
        int n=dim_c;
        for(int i =1;i<=n;i++){
            for(int j=1;j<=n;j++)
            {if ( (*this)(i,j) != (*this)(j,i) ) return false;}
        }
    return true;
    }
}

//fin de lasse Matrice

Matrice operator +(Matrice M, Matrice N)
{
    int l = M.diml();
    int c=M.dimc();
    Matrice A= Matrice(l,c);
    A+=M;
    A+=N;
    return A;
}

Matrice operator*(Matrice M, double x)
{
    Matrice A=M;
    return M*=x;
}

Matrice operator*(double x, Matrice M)
{
    return M*x;
}


Matrice operator/(Matrice M, double x)
{
    Matrice A=M;
    return M/=x;
}

Matrice operator/(double x, Matrice M)
{
    return M/x;
}




Matrice operator*(Matrice M1,Matrice M2)
{

    M1.compatible_prod(M2);
    Matrice M(M1.dim_l,M2.dim_c);
    for(int i=1;i<=M1.dim_l;i++)
    {
        for(int j=1;j<=M2.dimc();j++)
        {
            for(int k=0;k<M1.dimc();k++)
                {M(i,j)+=M1(i,k) * M2(k,j);}
        }

    }
    return M;

}

Vecteur operator*( Matrice M, Vecteur V)
{
    if(M.dimc() != int(V.size()) ) {M.stop("Non respect des dimensions");}
    else
    {
    Vecteur W(M.diml());
    for(int i = 1;i<=M.diml();i++)
    {
        for(int j=1;j<=M.dimc();j++)
            W(i) += M(i,j) * V(j);
    }
    return W;
    }
}


Matrice identity(int dim)
{
    Matrice M(dim,dim);
    for(int i=1;i<=dim;i++)
        M(i,i) = 1;
    return M;
}

Matrice construction(Matrice M1_1, Matrice M1_2,Matrice M2_1, Matrice M2_2)    //sert à assembler les 4 matrices que l'on a calculé avec assemblage
{
    int N= M1_1.dimc();
    Matrice M = Matrice(2*N,2*N);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
        M(i,j)=M1_1(i,j);
        M(i,N+j)=M1_2(i,j);
        M(N+i,j)=M2_1(i,j);
        M(N+i,N+j)= M2_2(i,j);
        }
    }
    return M;
}
