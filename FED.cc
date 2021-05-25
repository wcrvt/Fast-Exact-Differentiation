#include <stdio.h>
#include <math.h>

double sgn(double s){
  return (s!=0.0)? fabs(s)/s:0.0;
}

class FED {
  private:
  private:
    const int n=1;
    const double Ts;
    const double L;
    const double lambda[2];
    const double mu[2];
    double nu[2];
    double z[2];
  public:
    FED(const double Ts, const double L, const double *lambda, const double *mu, const double *z_init)
    	: Ts(Ts),	L(L), lambda{lambda[0], lambda[1]}, mu{mu[0], mu[1]}, z{z_init[0], z_init[1]} {};
    ~FED() {};
    double phi(int i, double t, double s){
      return lambda[n-i]*pow(L, n-i+1)*pow(fabs(s), (n-i)/(n-i+1))*sgn(s) + mu[n-1]*s;
    }
    double Calculate(double t, double x){
      nu[0] = -phi(0, t, z[0]-x) + z[1];
      nu[1] = -phi(1, t, z[1]-nu[0]);
      z[0] += nu[0]*Ts;
      z[1] += nu[1]*Ts;
      return z[1];
    };
};

int main(){

  double t=0.0;
  const double Ts=1e-4;
  const double tlen=3.0;
  const int tloop = tlen/Ts;

  double x=0.0;
  const double f=3.0;
  double y=0.0;
  double y_ideal=0.0;

  const double L=10;
  const double lambda[2]={12.0, 30.0};
  const double mu[2]={55.0, 40.0};
  double z_init[2]={0.0};
  static FED* fed_u0=new FED(Ts, L, lambda, mu, z_init);

  FILE *fp=fopen("data.dat","w");

  for(int i=0; i<tloop; i++){
    x=1.0-cos(2.0*M_PI*f*t);
    y_ideal=2.0*M_PI*f*sin(2.0*M_PI*f*t);
    y=fed_u0->Calculate(t,x);
    fprintf(fp, "%lf %lf %lf\n", t, y_ideal, y);
    t+=Ts;
  }

  delete(fed_u0);

  return 0;
}


