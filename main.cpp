#define VISOR_ENABLE

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
		
			if(dx<-SIZE/2)dx+=SIZE;
			if(dx>SIZE/2)dx-=SIZE;						
			if(dy<-SIZE/2)dy+=SIZE;
			if(dy>SIZE/2)dy-=SIZE;	
			
			auto r2=pow(dx,2)+pow(dy,2);
			
			return r2;
}

void Density(vector<Point> particles,vector<double>& densities)
{

	for(int a=0;a<particles.size();a++) 
		for(int b=0;b<a;b++) 
		{
			densities[int(1000*sqrt(rsquare(particles[a],particles[b])))]+=1;
		}
	
	return;
}

Point EnergyGradient(vector<Point> particles, int particleid)
{	
	Point dE(0,0);
	for(int b=0;b<particles.size();b++) 
		{	if(b==particleid) continue;
			
			auto dx=particles[particleid].x-particles[b].x;
			auto dy=particles[particleid].y-particles[b].y;
			
			if(dx<-SIZE/2)dx+=SIZE;
			if(dx>SIZE/2)dx-=SIZE;						
			if(dy<-SIZE/2)dy+=SIZE;
			if(dy>SIZE/2)dy-=SIZE;
			
			
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
	if(argc!=8)
	{cout<<"Usage: "<<argv[0]<<"<delay> <Steps count> <rng seed> <step size> <no. particles> <Temperature> <analysis rate>" <<endl;
		exit(-1);
	}
	
	Draw2D visor(700);
	const int delay=atoi(argv[1]);
	const int steps=atoi(argv[2]);
	const int seed=atoi(argv[3]);				
	const double stepsize=atof(argv[4]);
	const int particlecount=atoi(argv[5]);
	const double Temp=atof(argv[6]);
	auto rate=atoi(argv[7]);
	auto dx=atof(argv[8]);
	boost::random::mt19937 rng(seed);
	boost::random::uniform_int_distribution<> boolean(0,1);
	boost::random::uniform_real_distribution<> real(-1,1);
	boost::random::uniform_real_distribution<> realpos(0,1);
	boost::random::uniform_real_distribution<> pos(0,35);	
	
	
	vector<double> dens(35000);

	vector<Point> particles(particlecount);
	for (auto& p:particles){p.x=pos(rng);p.y=pos(rng);}
	visor.FullDraw(particles);
	for(int mcs=0;mcs<steps;mcs++)
	{	
		for(int i=0;i<particles.size();i++)
		{	
			auto de=EnergyGradient(particles,i);
			Point np(real(rng)*stepsize,real(rng)*stepsize);
			auto ed=np.x*de.x+np.y*de.y;
			
			
			if(ed<0||realpos(rng)<exp(-ed/Temp)){particles[i].x+=np.x;particles[i].y+=np.y;}
			if (particles[i].x<0) particles[i].x+=SIZE;
	 		if (particles[i].x>SIZE) particles[i].x-=SIZE;	
			if (particles[i].y<0) particles[i].y+=SIZE;
	 		if (particles[i].y>SIZE) particles[i].y-=SIZE;
 		}

		visor.FullDraw(particles);
		cerr<<mcs<<endl;
		if(mcs<delay||mcs%rate!=0)continue;

		Density(particles,dens);				
		
	}

		for(int i=0;i<dens.size();i++)
		cout<<double(i)/1000<<' '<<dens[i]<<endl;
		
}

