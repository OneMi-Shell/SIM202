#include "Maillage.h"
#include "Point2D.h"
#include<vector>
#include<vector>
#include<iostream>

using namespace std;

void Maillage::maille_carre_unite(int m, int n)
{
    //construction des sommets
    double dx= 1./m;
    double dy  = 1./n;
    Noeuds.resize((m+1)*(n+1));
    vector<Point2D>::iterator its = Noeuds.begin();
    for(int j=0;j<n+1;j++)
    {
        double y= j*dy;
        for(int i = 0; i<m+1; i++)
            {
                *its = Point2D(i*dx,y);
                *its++;
            }
    }
    //constuction des numéros des tianggles
    for(int j=0; j<n;j++)
    {
        for(int i =1; i <= m; i++)
        {
            int q=j*(m+1) +i; //coin bas gauche
            Num_Tri.push_back(Numeros(q,q+1,q+m+1));
            Num_Tri.push_back(Numeros(q+1,q+m+1,q+m+2));
        }
    }
    int s= Num_Tri.size();
    int p= Noeuds.size();
    Zone.resize(s);
    Rho.resize(3);
    Surface.resize(p);
    for(int i =0;i<3;i++)
    {
        Rho[i]= 1;        //Rho(i) = Rho(x,y)  ou x,y est la position du sommet i
    }
    for(int i = 0;i<p;i++)
    {
        if(Noeuds[i].Coor_x() == 0 || Noeuds[i].Coor_x() ==1) Surface[i]=1;
        if(Noeuds[i].Coor_y() == 0 ) Surface[i]=2;
    }
}

void Maillage::affiche() const
{
    cout<<"Numeros des triangles" << endl;
    vector<Numeros>::const_iterator itl;
    int i = 1;
    for(itl = Num_Tri.begin(); itl != Num_Tri.end();itl++)
    {
        cout << "triangle "  << i <<" : " << *itl << endl;
        i++;
    }

    cout<<"Coordonnees des sommets" << endl;
    vector<Point2D>::const_iterator itv;
    i=1;
    for(itv = Noeuds.begin(); itv != Noeuds.end();itv++)
    {
        cout << "sommet "  << i <<" : " << *itv << endl;
        i++;
    }

}
void Maillage::tf_affine(const vector<double> &A, const vector<double> t )
{
    vector<Point2D>::iterator its;
    for(its = Noeuds.begin(); its != Noeuds.end();its++)
    {
        its -> tf_affine_p(A,t);
    }

}

Maillage::Maillage(double a, double b, double c, double d, int m, int n)
{
    maille_carre_unite( m, n);
    vector<double> A(4);
    A[0] =b-a  ;A[1]= 0; A[2]=0;A[3]=d-c;
    vector<double> t(2);
    t[0]= a;t[1]=c;
    (*this).tf_affine(A,t);
}

Maillage Maillage:: operator+=(const Maillage & M)
{
    vector<Point2D>::const_iterator itv;
    for(itv = (M.Noeuds).begin(); itv != (M.Noeuds).end();itv++)
    {
        Noeuds.push_back(*itv);
    }
    vector<Numeros>::const_iterator itl;
    for(itl = (M.Num_Tri).begin(); itl != (M.Num_Tri).end();itl++)
    {
        Num_Tri.push_back(*itl);
    }

    return *this;
}

double Maillage::rho(int l)
{
    return Rho[Zone[l-1]];
}


Maillage operator+(Maillage M1, Maillage M2)
{
    Maillage M3=M1;
    return M3+=M2;
}
