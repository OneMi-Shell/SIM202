#ifndef POINT2D_H
#define POINT2D_H
#include <iostream>
#include "Vecteur.h"
using namespace std;
class Point2D
{
    public:
        Point2D(double Coor_x=0,double Coor_y=0);
        Point2D(const Point2D& other);

        double& Coor_x();
        double& Coor_y();
        double Coor_x() const;
        double Coor_y() const;

        Point2D operator +=(const Point2D& P);
        Point2D operator -=(const Point2D& P);
        Point2D operator *=(double z);
        Point2D operator /=(double z);
        Point2D& tf_affine_p(const vector<double>& A, const vector<double>& t);

    protected:

    private:
        double x,y;
};


Point2D operator +(const Point2D& P,const Point2D& Q);
Point2D operator -(const Point2D& P,const Point2D& Q);
Point2D operator *(const Point2D& P,double z);
Point2D operator *(double z, const Point2D& P);
Point2D operator /(const Point2D& P,double z);
bool operator==(const Point2D& P,const Point2D& Q);
bool operator!=(const Point2D& P,const Point2D& Q);
ostream & operator <<(ostream & out, const Point2D &P);

#endif // POINT2D_H
