#include "maillage.h"

bool operator ==(const Point2d& a,const Point2d& b){
	return (a.x==b.x) and (b.y==a.y);
}


bool operator !=(const Point2d& a,const Point2d& b){
	return (a.x!=b.x) or (b.y!=a.y);
}


ostream & operator <<(ostream & os,const Point2d & p){
	os<<"("<<p.x<<","<<p.y<<")";
	return os;
}


Point2d operator +(const Point2d& a,const Point2d& b){
	Point2d c(a.x,a.y);
	return c+=b;
}


Point2d operator -(const Point2d& a,const Point2d& b){
	Point2d c(a.x,a.y);
	return c-=b;
}


Point2d operator *(double a,const Point2d& p){
	Point2d c(p.x,p.y);
	return c*=a;
}


Point2d operator /(const Point2d& p,double a){
	Point2d c(p.x,p.y);
	return c/=a;
}


ostream & operator <<(ostream & os,const Numeros & n){
	Numeros::const_iterator itn=n.begin();
	for(;itn!=n.end();itn++)
		os<<*itn<<",";
	os<<*n.end();
	return os;
}


/*
void Maillage::maille_carre_unite(int m,int n){
	double nbx=1/m;
	double nby=1/n;
	vector<Point2d>::iterator itn=v.begin();
	
	
}

*/



void Maillage::affichage(){
	vector<Point2d>::iterator itn=v.begin();
	for(;itn!=this->v.end();itn++)
		cout<<*itn;
	list<Numeros>::iterator it=n.begin();
	for(;it!=this->n.end();it++)
		cout<<*it;
}



Point2d& Point2d::tf_affine(const vector<double> & A,const vector<double> & t){
	double a=x;
	double b=y;
	x=a*A[0]+b*A[1]+t[0];
	y=A[2]*a+b*A[3]+t[1];
	return *this;
}





Maillage& Maillage::tf_affine(const vector<double> &A,const vector<double> &t){
	vector<Point2d>::iterator itn=v.begin();
	for(;itn!=v.end();itn++)
		itn->tf_affine(A,t);
	return *this;
}


Maillage& Maillage::operator +=(const Maillage & m){
	vector<Point2d>::const_iterator it=m.v.begin();
	for(;it!=m.v.end();it++)
		v.push_back(*it);
	list<Numeros>::const_iterator itn=m.n.begin();
	for(;itn!=m.n.end();itn++)
		n.push_back(*itn);
	return *this;
}

Maillage operator +(const Maillage& a,const Maillage& b){
	Maillage m(a);
	return m+=b;
}

