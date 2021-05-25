#include <stdio.h>
#include <math.h>

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
    double sgn(double s){
      return (s!=0.0)? fabs(s)/s:0.0;
    }
    double phi(int i, double t, double s){
      return lambda[n-i]*pow(L, ((double) 1.0/(n-i+1.0)))*pow(fabs(s), ((double) (n-i)/(n-i+1.0)))*sgn(s) + mu[n-1]*s;
    }
    double Calculate(double t, double x){
      nu[0] = -phi(0, t, z[0]-x) + z[1];
      nu[1] = -phi(1, t, z[1]-nu[0]);
      z[0] += nu[0]*Ts;
      z[1] += nu[1]*Ts;
      return z[1];
    };
};

double evaluate(const double L, const double *lambda, const double *mu, const double *z_init, int plt){
  double t=0.0;
  const double Ts=1e-4;
  const double tlen=3.0;
  const int tloop = tlen/Ts;

  double x=0.0;
  const double f=3.0;
  double y=0.0;
  double y_ideal=0.0;
  double score=0.0;
  FED* fed_u0=new FED(Ts, L, lambda, mu, z_init);

  FILE *fp=fopen("data.dat","w");

  for(int i=0; i<tloop; i++){
    x=1.0-cos(2.0*M_PI*f*t);
    y_ideal=2.0*M_PI*f*sin(2.0*M_PI*f*t);
    y=fed_u0->Calculate(t,x);
    if(plt==1) fprintf(fp, "%lf %lf %lf\n", t, y_ideal, y);
    t+=Ts;
    score+=pow(y-y_ideal,2.0);
  }
  fclose(fp);

  printf("%lf\n%lf\n", fed_u0->phi(0,2,5), fed_u0->phi(1,2,5) );

  delete(fed_u0);
  return score;
}

int main(){
  double L=29.72092247591221;
  double lambda[2]={12.077045929605777, 7.6435615091873546};
  double mu[2]={30.222768931147865, 20.179890831467514};

  const double z_init[2]={0.0};
  double score=evaluate(L, lambda, mu, z_init, 1);
  printf("score=%lf\n", score);
  return 0;
}

