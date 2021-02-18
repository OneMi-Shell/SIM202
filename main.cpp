#include "maillage.h"
#include <ctime>
using namespace std;
int main( int argc, char * argv[] )
{ //initialisation du générateur aleatoire 
  srand (time(0));
  //test de la classe Point2d
  Point2d O, P(0,1), Q(1,1), R(1);
  cout<<"O+P+2.*Q-R/2.="<<(O+P+2.*Q-R/2.) <<endl;
  cout<<"O!=P -> "<<(O!=P)<<"O==P -> "<<(O==P)<<endl;
  //test de la classe Numeros
  Numeros ns(1,2,3);
  cout<<"Numeros ns(1,2,3) -> "<<ns<<endl;
  cout<<"ns(2)="<<ns(2)<<endl;
  cout<<"ns.shift(2) -> "<<ns.shift(2)<<endl;
  //test de la classe Maillage
  cout<<"Maillage du carre unite"<<endl;



  //test de produit mat vect
  Matrice m=Matrice(2);
  m(1,1)=1;
  m(1,2)=1;
  m(2,1)=2;
  m(2,2)=2;
  cout<<"matrice m est"<<m<<endl;
  vecteur v(2);
  v(1)=3;
  v(2)=4;
  cout<<"le vecteur v est-> "<<v<<endl;
  vecteur res(2);
  res = m*v;
  cout<<"produit de mat m et v est-> "<<res<<endl;
  Maillage mail;
  mail.maille_carre_unite(4,2);
  mail.affichage();
/*  cout<<"Copie du maillage du carre unite"<<endl;
  Maillage mail2(mail);
  mail2.affiche();
  cout<<"Maillage du rectangle [2,4]x[10,20]"<<endl;
  Maillage mailr(2,4,10,20,4,5);
  mailr.affiche();
  cout<<"Transformation affine du maillage du carre unite"<<endl;
  vector<double> A(4,0); A[0]=4;A[3]=1;
  vector<double> t(2,0);
  mail2.tf_affine(A,t); //transformation affine de maillage
  mail2.affiche();
  Maillage mail3(2,2);  //maillage carré unité
  t[0]=-1;A[0]=1;
  mail3.tf_affine(A,t); //transformation affine de maillage
  mail3.affiche();
  cout<<"Concatenation de maillage"<<endl;
  Maillage mail4=mail2+mail3; //concaténation de maillages
  mail4.affiche();
  mail4.saveToFile("mail4.dat");*/
  return 0;
}
