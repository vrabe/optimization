#include "polys.h"
#include <deque>
#include <array>
#include <math.h>

using namespace std;

void powell(Polys& p,double x,double y,double x_max,double x_min,double y_max,double y_min,double tau){
	//direction
	deque<array<double,2> > u;
	//initialization
	array<double,2> e1 = {1,0};
	array<double,2> e2 = {0,1};
	u.push_back(e1);
	u.push_back(e2);
	
	//evaluation
	double fv = p.eval(x,y,0);
	double a[3];
	double before[3] = {fv,x,y};
	
	do{
		for(int j=0;j<3;j++){
			if(j==2){
				array<double,2> u3;
				u3[0] = a[0]*u[0][0]+a[1]*u[0][1];
				u3[1] = a[0]*u[1][0]+a[1]*u[1][1];
				u.push_back(u3);
			}
			//bound
			double acand[4];
			double amax,amin;
            acand[0] = (x_max - x)/u[j][0]; //a_x_max
            acand[1] = (x_min - x)/u[j][0]; //a_x_min
            acand[2] = (y_max - y)/u[j][1]; //a_y_max
            acand[3] = (y_min - y)/u[j][1]; //a_y_min
			for(int k=0;k<2;k++){
				if(y+acand[k]*u[j][1]<y_max && y+acand[k]*u[j][1]>y_min){
					amax = acand[k];
				}
				if(x+acand[k+2]*u[j][0]<x_max && x+acand[k+2]*u[j][0]>x_min){
					amin = acand[k+2];
				}
			}
			if(amax < amin){
				double tmp = amax;
				amax = amin;
				amin = tmp;
			}
			//search
			p.createSuber(x,u[j][0],y,u[j][1]);
			a[j] = goldenp(p,amin,amax,amin,tau);
			//iteration
			x = x+a*u[j][0];
			y = y+a*u[j][1];
			//evaluation
			fv = p.eval(x,y,0);
			
		}
		u.pop_front();
	}while(fabs(fv-before[0])>tau || fabs(pow(x-before[1],2)+pow(y-before[2],2))>tau);
	
}

double goldenp(Polys& p,double a, double b, double c, double tau){//a跟c是左右bound,b是中間的一個值, tau應該是區間誤差 
	double x;
	const double phi = (1+sqrt(5))/2;
	const double resphi = 2-phi;//(3-根號5)/2 
	if(c-b>b-a){//右側較多 
		x = b + resphi*(c-b);
	}else{//左側較多 
		x = b - resphi*(b-a);
	}
	if(abs(c-a) < tau*abs(b) + abs(x))
		return (c+a)/2;
	if(p.evalSuber(x) < p.evalSuber(b)){
		if(c-b > b-a)return goldenp(p,b,x,c,tau);
		else return goldenp(p,a,x,b,tau);
	}else{
		if(c-b > b-a)return goldenp(p,a,b,x,tau);
		else return goldenp(p,x,b,c,tau);
	}
}
