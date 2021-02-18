#include "maillage.h"
using namespace std;


//fonc pour point

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




//fonc pour vect


void stop(const char * msg)
{
   cout<<"ERREUR classe vecteur, "<<msg;
   exit(-1);
}

void test_dim(int d1, int d2, const char * org)
{
   if(d1==d2)  return;
   cout<<org<<" ("<<d1<<","<<d2<<") dimensions incompatibles";
   exit(-1);
}

// constructeurs-destructeurs
vecteur::vecteur(int d, double v0) //dim et val constante
{
     std::cout<<d<<std::endl;
   init(d);
   for(int i=0;i<dim_;i++) val_[i]=v0;
}

vecteur::vecteur(const vecteur & v) //constructeur par copie
{
   init(v.dim_);
   for(int i=0;i<dim_;i++) val_[i]=v.val_[i];
}

vecteur::~vecteur() {clear();}

// outils de construction et de destruction
void vecteur::init(int d) //initialisation avec allocation dynamique
{
     std::cout<<d<<std::endl;
   if(d<=0) stop("init() : dimension <=0");
   dim_=d;
   val_ = new double[d];
}

void vecteur::clear()    //désallocation
{
     if(val_!=0) delete [] val_;
     dim_=0;
}


vecteur & vecteur::operator =(const vecteur & v){
     if(dim_!=v.dim_){
         clear();
         init(v.dim_);
     }
     for (int i=0;i<dim_;i++)
         val_[i]=v[i];
     return *this;
}



vecteur & vecteur::operator =(double x){
     for(int i=0;i<dim_;i++){
         val_[i]=x;

     }
     return *this;
}


double & vecteur::operator [](int i){
     return val_[i];
}


double vecteur::operator [](int i)const {
     return val_[i];
}


double & vecteur::operator ()(int i){
     return val_[i-1];
}


double vecteur::operator ()(int i)const {
     return val_[i-1];
}


vecteur vecteur::operator ()(int i,int j)const{
     if(i<=j){
         vecteur u(j-i+1);
         for(int k=0;k<=j-i;k++){
             u[k]=val_[i-1+k];
         }
         return u;
         }
     else{
         vecteur u(i-j+1);
         for(int k=0;k<=i-j;k++){
             u[k]=val_[j-1+k];
         }
         return u;
         }
}



vecteur& vecteur::operator +=(const vecteur & v){
    test_dim(dim_,v.dim(),"stop");
    for(int i=0;i<dim_;i++){
        val_[i]+=v[i];
    }
     return *this;
}

vecteur& vecteur::operator -=(const vecteur & v){
    test_dim(dim_,v.dim(),"stop");
    for(int i=0;i<dim_;i++){
        val_[i]-=v[i];
    }
     return *this;
}



vecteur& vecteur::operator +=(double x){
    for(int i=0;i<dim_;i++){
        val_[i]+=x;
    }
    return *this;
}


vecteur& vecteur::operator -=(double x){
    for(int i=0;i<dim_;i++){
        val_[i]-=x;
    }
    return *this;
}


vecteur operator +(const vecteur & u){
     return u;
}


vecteur operator -(const vecteur & u){
     vecteur v(u);
     for(int i=0;i<u.dim();i++){
         v[i]=u[i]*(-1);
     }
     return v;
}


vecteur operator +(const vecteur & u,const vecteur & v){
     vecteur w(u);
     w+=v;
     return w;
}

vecteur operator -(const vecteur & u,const vecteur & v){
     vecteur w(u);
     w-=v;
     return w;
}








vecteur operator +(double x,const vecteur & v){
     vecteur w(v);
     w+=x;
     return w;
}

vecteur operator -(double x,const vecteur & v){
     vecteur w=-v;
     w+=x;
     return w;
}

vecteur operator +(const vecteur & u,double x){
     return(x+u);
}


vecteur operator -(const vecteur & u,double x){
     vecteur w(u);
     w-=x;
     return w;
}


vecteur operator *=(const vecteur & u,double x){
     vecteur w(u);
     for (int i;i<u.dim();i++){
         w[i]*=x;
     }
     return w;
}


vecteur operator /=(const vecteur & u,double x){
     vecteur w(u);
     for (int i;i<u.dim();i++){
         w[i]/=x;
     }
     return w;
}



vecteur operator *(const vecteur & u,double x){
     return (u*=x);
}
vecteur operator *(double x,const vecteur & u){
     return (u*=x);
}
vecteur operator /(const vecteur & u,double x){
     return (u/=x);
}



bool operator ==(const vecteur & u,const vecteur & v){
     if(u.dim()!=v.dim())
         return false;
     else{
         for (int i=0;i<u.dim();i++){
             if (u[i]!=v[i])
                 return false;
         }
         return true;
     }
}



bool operator !=(const vecteur & u,const vecteur & v){
     return(!(u==v));
}



ostream & operator <<(ostream & out,const vecteur & u){
     out<<"(";
     for (int i;i<u.dim()-1;i++) out<<u[i]<<",";
     std::cout<<u[u.dim()-1]<<")";
     return out;
}

istream & operator>>(istream & in , vecteur & u){
     for(int i;i<u.dim();i++) in>>u[i];
     return in;
}


double operator |(const vecteur & u,const vecteur & v){
    test_dim(u.dim(),v.dim(),"stop");
    double res=0;
    for (int i=0;i<u.dim();i++)
        res+=u[i]*v[i];
    return res;
}



vecteur operator ,(const vecteur & u,const vecteur & v){
     vecteur w(u.dim()+v.dim());
     for (int i=0;i<u.dim();i++){
         w[i]=u[i];
     }
     for (int i=0;i<v.dim();i++){
         w[i+u.dim()]=v[i];
     }
     return w;
}

//
//fonc pour mat

Matrice::Matrice(int n): taille_(n)
{
   matrice_=new double * [taille_];
   for(int i=0; i<taille_; i++)
     matrice_[i]=new double [taille_];
   for (int i=0; i<taille_; i++)
    {
      for (int j=0; j<taille_; j++)
       matrice_[i][j]=0;
     }
}
 

Matrice::Matrice(const Matrice& ref): taille_(ref.taille_)
{
    if(taille_ != 0)
    {
        matrice_ = new double*[taille_];           // 
        for(int i=0; i<taille_;i++)
               matrice_[i]=ref.matrice_[i];
    }
}




Matrice::~Matrice()
{ 
    delete[] matrice_;
    taille_ = 0;
}

  

Matrice Matrice::operator=(const Matrice &m)
{
    if(m.matrice_ != matrice_){ 
        delete [] matrice_;
        taille_ = 0;
        matrice_ = nullptr;
        if(m.taille_ != 0){
            matrice_ = new double*[m.taille_];
            taille_ = m.taille_;
           for(int i=0;i<taille_;i++)
           {
               matrice_[i]=m.matrice_[i];
           }
        }
    }
    return *this;
}





int Matrice::getTaille() const
{
    return taille_;
}
 
 

int Matrice::getVal(int i, int j) const
{
    return matrice_[i][j];
}


vecteur Matrice::operator *(const vecteur & v){           //prod mat et vect
     if(v.dim()==this->taille_){
          vecteur res = vecteur(v);
          res.init(taille_);
          for (int i = 0; i < taille_; i++)
          {
               for (int j = 0; j < taille_; j++)
               {
                    res[i]=res[i]+matrice_[i][j]*v[i];
               }
               
          }
          return res;
          
     }
     else
          return vecteur();
}



ostream & operator <<(ostream & out,const Matrice &m){
     cout<<"taille ="<<m.getTaille()<<endl;
     for (int i=1;i<=m.getTaille();i++){
          for(int j=1;j<=m.getTaille();j++){
               cout<<m(i,j)<<" ";
          }
          cout<<"\n";
     }
     return out;
}
/*
istream & Matrice::operator>>(istream & in , vecteur & u){
     for(int i;i<u.dim();i++) in>>u[i];
     return in;
}
*/


//fonc pour num


ostream & operator <<(ostream & os,const Numeros & n){
	Numeros::const_iterator itn=n.begin();
	for(;itn!=n.end();itn++)
		os<<*itn<<",";
	os<<*n.end();
	return os;
}










//fonc pour maillage

void Maillage::maille_carre_unite(int m,int n){
	double nbx=1/m;
	double nby=1/n;              //on a m*n segment
	v.resize((m+1)*(n+1));        // donc +1 pour nb de points
	vector<Point2d>::iterator its=v.begin();
	for (int j=0;j<n+1;j++){
		double y=y*nby;
		for (int i = 0; i < n+1; i++,its++)
		{
			*its=Point2d(i*nbx,y);            //pour remplir v 
		}
	}
	for(int j=0;j<n;j++){                      
		for (int i = 0; i < m; i++)
		{
			int bg=j*(n+1)+i;  //en bas à gauche
			this->n.push_back(Numeros(bg,bg+1,bg+n+1));
			this->n.push_back(Numeros(bg+1,bg+n+1,bg+n+2));

		}
		
	}
		
}


int Maillage::nbtri(){
     int nb=0;
     for(list<Numeros>::iterator itn=n.begin() ; itn!=n.end();itn++)
          nb++;
     return nb;
}

int Maillage::nbsommets(){
     int nb=0;
     for(vector<Point2d>::iterator itn=v.begin();itn!=v.end();itn++)
          nb++;
     return nb;
}

/*
Maillage::Maillage(const Maillage & m){
     Numeros::const_iterator itn1=m.n.begin();
     Numeros::iterator itn2=n.begin();
	for(;itn!=n.end();itn++)
		os<<*itn<<",";
	os<<*n.end();
	return os;
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
/*
Maillage operator +(const Maillage& a,const Maillage& b){
	Maillage m(a);
	return m+=b;
}
*/


void Maillage::maiile_rectangle(double a,double b,double c,double d,int m,int n){
	maille_carre_unite(m,n);
	vector<double> A(4,0);
	A[0]=b-a;
	A[3]=d-c;
	vector<double> t(2,0);
	t[0]=a;
	t[1]=c;
	tf_affine(A,t);
}