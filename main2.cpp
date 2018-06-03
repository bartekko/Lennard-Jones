#define HORIZONTAL_PBC

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <vector>

#include "2Draw.h"
#include "Point.h"

using namespace std;

double rsquare(Point a,Point b)
{
			auto dx=a.x-b.x;
			auto dy=a.y-b.y;
			if (abs(dx)>SIZE/2)dx=-2*signbit(dx)*SIZE+SIZE-dx;
			if (abs(dy)>SIZE/2)dy=-2*signbit(dy)*SIZE+SIZE-dy;		
			auto r2=pow(dx,2)+pow(dy,2);
			
			return r2;
}


Point EnergyGradient(vector<Point> particles, int particleid)
{	
	Point dE(0,0);
	for(int b=0;b<particles.size();b++) 
		{	if(b==particleid) continue;
			
			auto dx=particles[particleid].x-particles[b].x;
			auto dy=particles[particleid].y-particles[b].y;
			
			if (abs(dx)>SIZE/2)dx=2*signbit(dx)*SIZE-SIZE-dx;
			if (abs(dy)>SIZE/2)dy=2*signbit(dy)*SIZE-SIZE-dy;
			
			
			//if(abs(dx)>2.5*1.12*1.4||abs(dy)>2.5*1.12*1.4)continue;
			auto r2=pow(dx,2)+pow(dy,2);
			if (r2>2.5*1.12*2.5*1.12)continue;
			
			auto t=24*(pow(r2,3)-2)/pow(r2,7);			
			dE.x+=dx*t;
			dE.y+=dy*t;
		}
		
/*	//GRAVITATIONAL COMPONENT
	dE.y-=GRAV;*/
	return dE;
}

int main(int argc, char** argv)
{	
	if(argc!=6)
	{cout<<"Usage: "<<argv[0]<<" ax,bx,ay,dy,dx" <<endl;
		exit(-1);
	}
	
	Draw2D visor(700);
	const double ax=atof(argv[1]);
	const double bx=atof(argv[2]);
	const double ay=atof(argv[3]);
	const double by=atof(argv[4]);
	auto dx=atof(argv[5]);
	
	vector<Point> particles(5);
	particles[0].x=ax;
	particles[0].y=ay;
	particles[1].x=bx;
	particles[1].y=by;		
	cout<<int(sqrt(rsquare(particles[0],particles[1])))<<endl;
	

}
