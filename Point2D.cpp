#include "Point2D.h"
#include <iostream>

using namespace std;


Point2D::Point2D(double Coor_x,double Coor_y)
{
    x=Coor_x;
    y=Coor_y;

    //ctor
}


Point2D::Point2D(const Point2D& other)
{
    x=other.x;y=other.y;//copy ctor
}


double& Point2D::Coor_x()
{
    return x;
}

double& Point2D::Coor_y()
{
    return y;
}

double Point2D::Coor_x() const
{
    return x;
}

double Point2D::Coor_y() const
{
    return y;
}


Point2D Point2D::operator +=(const Point2D& P)
{
    x+=P.x;
    y+=P.y;
    return *this;
}

Point2D Point2D::operator -=(const Point2D& P)
{
    x-=P.x;
    y-=P.y;
    return *this;
}

Point2D Point2D::operator *=(double z)
{
    x*=z;
    y*=z;
    return *this;
}


Point2D Point2D::operator /=(double z)
{
    x/=z;
    y/=z;
    return *this;
}

Point2D& Point2D::tf_affine_p(const vector<double>& A, const vector<double>& t)
{
    double xx=x;
    double yy=y;
    x=xx*A[0]+yy*A[1]+t[0];
    y=xx*A[3]+yy*A[4]+t[1];
    return *this;
}

Point2D operator +(const Point2D& P,const Point2D& Q)
{
    Point2D R(P.Coor_x(),P.Coor_y());
    R+=Q;
    return R;
}

Point2D operator -(const Point2D& P,const Point2D& Q)
{
    Point2D R(P.Coor_x(),P.Coor_y());
    R-=Q;
    return R;
}

Point2D operator *(const Point2D& P,double z)
{
    Point2D R(P.Coor_x(),P.Coor_y());
    R*=z;
    return R;
}

Point2D operator *(double z, const Point2D& P)
{
    return P*z;
}

Point2D operator /(const Point2D& P,double z)
{
    Point2D R(P.Coor_x(),P.Coor_y());
    R/=z;
    return R;
}

bool operator==(const Point2D& P,const Point2D& Q)
{
    return ((P.Coor_x() == Q.Coor_y()) && (P.Coor_y() == Q.Coor_y()));
}

bool operator !=(const Point2D& P,const Point2D& Q)
{
    return !(P==Q);
}

ostream & operator <<(ostream & out, const Point2D &P)
{
    out <<"("<<P.Coor_x()<< "," << P.Coor_y() << ")";
    return out;
}
