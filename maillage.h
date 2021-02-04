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
   vecteur(int d=0, double v0=0); //dim et val constante
   vecteur(const vecteur & v);    //constructeur par copie
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




//
//
//
//matrice creuse
class matcreuse
{
private :
   int dim_;          //dimension de mat
   int nbval;         //nb de val non nul
   double * val_;     //tableaux de val non nul de matcreuse
	int * posii;
	int * posij;
public:
	matcreuse(){dim_=0;nbval=0;val_=NULL;posii=NULL;posij=NULL;}
	matcreuse(int n){dim_=n;nbval=0;val_=NULL;posii=NULL;posij=NULL;}
	matcreuse(int d,int n,double* t1,int* t2,int* t3){
		dim_=d;
		nbval=n;
		for (int i = 0; i < n; i++)
		{
			val_[i]=t1[i];
			posii[i]=t2[i];
			posij[i]=t3[i];
		}
		
	}

	int getdim() const{return dim_;}
	int getnbval() const{return nbval;}
	double getval(int i) const{return val_[i];}
	int getposii(int i) const{return posii[i];}
	int getposij(int i) const{return posij[i];}

	matcreuse(const matcreuse & M){
		dim_=M.getdim();
		nbval=M.getnbval();
		for (int i = 0; i < nbval; i++){
			val_[i]=M.getval(i);
			posii[i]=M.getposii(i);
			posij[i]=M.getposij(i);
		}
	}

	~matcreuse(){
		nbval=0;
		dim_=0;
		delete[] val_;
		delete[] posii;
		delete[] posij;
	}


};




//
//
//
//classe num


class Numeros:public vector<int>
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
		list<Numeros> n;        // liste de numero de points de triangle,car chaque rectangle est découpé en 2 triangle, donc , ici,chaque listnum est une liste de numé de chaque triangle
		
		void maille_carre_unite(int,int);
		void affichage();
		Maillage& tf_affine(const vector<double> &,const vector<double> &);
		Maillage& operator +=(const Maillage &);
		void maiile_rectangle(double ,double,double,double,int,int);
		
};


Maillage operator +(const Maillage&,const Maillage&);

#endif
