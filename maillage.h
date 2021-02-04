#ifndef maillage_h
#define maillage_h


#include <iostream>
#include <vector>
#include <list>


using namespace std;



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
ostream & operator <<(ostream &,Numeros &);


class Maillage{
	public:
		vector<Point2d> v;
		list<Numeros> n;
		
		/*void maille_carre_unite(int,int);*/
		void affichage();
		Maillage& tf_affine(const vector<double> &,const vector<double> &);
		Maillage& operator +=(const Maillage &);
		
};


Maillage operator +(const Maillage&,const Maillage&);

#endif
