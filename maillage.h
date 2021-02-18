#ifndef maillage_h
#define maillage_h


#include <iostream>
#include <vector>
#include <list>


using namespace std;

//classe point

class Point2d{
	public:
	double x;
	double y;
	Point2d():x(0),y(0){}
	Point2d(double a,double b):x(a),y(b){}
	Point2d(double a):x(a),y(0){}
	Point2d& operator +=(const Point2d & p){x+=p.x;y+=p.y;return *this;}
	Point2d& operator -=(const Point2d & p){x-=p.x;y-=p.y;return *this;}
	Point2d& operator *=(double a){x*=a;y*=a;return *this;}
	Point2d& operator /=(double a){x/=a;y/=a;return *this;}
	Point2d& tf_affine(const vector<double> &,const vector<double> &);
	
};

bool operator ==(const Point2d&,const Point2d&);
bool operator !=(const Point2d&,const Point2d&);
ostream & operator <<(ostream &,const Point2d &);
Point2d operator +(const Point2d&,const Point2d&);
Point2d operator -(const Point2d&,const Point2d&);
Point2d operator *(double,const Point2d&);
Point2d operator /(const Point2d&,double);







//
//
//
//classe vect


void stop(const char * msg);                     //message d'arr\EAt
void test_dim(int d1, int d2, const char * org); //test dimension


class vecteur
{
private :
   int dim_;          //dimension du vecteur
   double * val_;     //tableaux de valeurs

public:
   vecteur(int d=0, double v0=0); //dim et val constante   , enlever 0 de d
   vecteur(const vecteur & v);    //constructeur par copie 
   /*
   vecteur(int d){dim_=d;val_=new double [d]; for (int i = 0; i < d; i++)
   {
	   val_[i]=0;
   }
   */
   ~vecteur();

   //tools
   void init(int d);              //allocation
   void clear();                  //d\E9sallocation
   int dim() const {return dim_;} //acc\E8s dimension





   vecteur & operator =(const vecteur & v);

   vecteur & operator =(double x);

   double & operator [](int i);

   double operator [] (int i) const;

   double & operator ()(int i);

   double operator () (int i) const;


   vecteur operator ()(int i,int j)const;

   vecteur& operator +=(const vecteur & v);

   vecteur& operator -=(const vecteur & v);

   vecteur& operator +=(double x);

   vecteur& operator -=(double x);


};

vecteur operator +(const vecteur & u);
vecteur operator -(const vecteur & u);


vecteur operator +(const vecteur & u,const vecteur & v);
vecteur operator -(const vecteur & u,const vecteur & v);


vecteur operator +(double x,const vecteur & v);
vecteur operator -(double x,const vecteur & v);

vecteur operator +(const vecteur & u,double x);
vecteur operator -(const vecteur & u,double x);


vecteur operator *=(const vecteur & u,double x);
vecteur operator /=(const vecteur & u,double x);

vecteur operator *(const vecteur & u,double x);
vecteur operator *(double x,const vecteur & u);
vecteur operator /(const vecteur & u,double x);

bool operator ==(const vecteur & u,const vecteur & v);
bool operator !=(const vecteur & u,const vecteur & v);

ostream & operator <<(ostream & out,const vecteur & u);

istream & operator>>(istream & is , vecteur & u);

double operator |(const vecteur & u,const vecteur & v);

vecteur operator ,(const vecteur & u,const vecteur & v);








//matrce
class Matrice
{
  protected:
    int taille_;
    double **matrice_; 


  public:
    Matrice():taille_(0), matrice_(0){};   
    Matrice(int); 
    Matrice(const Matrice& ref);
    ~Matrice();


    Matrice operator=(const Matrice &);   
    int getTaille() const;
    int getVal(int i, int j) const;
    vecteur operator *(const vecteur &);
	double & operator ()(int i,int j){return matrice_[i-1][j-1];}

   	double operator ()(int i,int j) const{return matrice_[i-1][j-1];}
     

    /*istream& operator>>(istream &is, Matrice &m);*/
          

};
ostream& operator<<(ostream &out, const Matrice &);


//
//
//
//matrice creuse
class matcreuse : public Matrice
{
private :
   	int nbval;         //nb de val non nul
	int * posii;
	int * posij;
public:
	matcreuse():Matrice(){nbval=0;posii=NULL;posij=NULL;}
	matcreuse(int n):Matrice(n){nbval=0;posii=NULL;posij=NULL;}
/*	matcreuse(int d,int n,double* t1,int* t2,int* t3){
		dim_=d;
		nbval=n;
		for (int i = 0; i < n; i++)
		{
			val_[i]=t1[i];
			posii[i]=t2[i];
			posij[i]=t3[i];
		}
		
	}*/

	int getnbval() const{return nbval;}
	int getposii(int i) const{return posii[i];}
	int getposij(int i) const{return posij[i];}

	matcreuse(const matcreuse & M):Matrice(M){
		nbval=M.getnbval();
		for (int i = 0; i < nbval; i++){
			posii[i]=M.getposii(i);
			posij[i]=M.getposij(i);
		}
	}

	~matcreuse(){
		nbval=0;
		taille_=0;
		delete [] matrice_;
		delete[] posii;
		delete[] posij;
	}

};




//
//
//
//classe num


class Numeros:public vector<int>    //classe triangle ,un vecteur en fonction de 3 entiers
{public:
	Numeros(int a,int b,int c){
		resize(3);
		vector<int>::iterator itn=begin();
		*itn++=a;*itn++=b;*itn=c;
	}
	
	int& operator ()(int i){
		return (*this)[i-1];
	}
	
	int operator ()(int i) const{
		return (*this)[i-1];
	}
	
	Numeros shift(int b) const{
		Numeros n=*this;
		vector<int>::iterator itn=n.begin();
		for(;itn!=n.end();itn++)
			*itn+=b;
		return n;
	}
};
ostream & operator <<(ostream &,const Numeros &);










//
//
//
//classe maillage



class Maillage{
	public:
		vector<Point2d> v;     //liste de points
		vector<Numeros> n;        // liste de numero de points de triangle,car chaque rectangle est découpé en 2 triangle, donc , ici,chaque listnum est une liste de numé de chaque triangle
		                        //liste chainé:avantage pour supprimer
		vector<int> zone;
		Maillage(){};
		void maille_carre_unite(int,int);
		Maillage(const Maillage &);
		void affichage();
		int nbtri();
		int nbsommets();

		Numeros gettri(int) const;
		Maillage& tf_affine(const vector<double> &,const vector<double> &);
		Maillage& operator +=(const Maillage &);
		void maiile_rectangle(double ,double,double,double,int,int);
		
};

Maillage operator +(const Maillage&,const Maillage&);

#endif
