#define VISOR_ENABLE
//#define RANDOM_START
#define UP_START
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

//const auto SIZE=20;

auto Hamiltonian(vector<Point> particles)
{
	//Aby uniknąć powtórzeń bierzemy tylko te pary gdzie b<a
	double E=0;
	for(int a=0;a<particles.size();a++)
		for(int b=0;b<a;b++)  
		{	auto dx=abs(particles[a].x-particles[b].x);
			if(dx>SIZE/2)dx=SIZE-dx; 
			auto dy=abs(particles[a].y-particles[b].y);
			if(dy>SIZE/2)dy=SIZE-dy;	 			
			auto r2=pow(dx,2)+pow(dy,2);
			E+=4*(pow(r2,-6)-pow(r2,-3));
		}

	return E;
}


Point EnergyGradient(vector<Point> particles, int particleid)
{	
	Point dE(0,0);
	for(int b=0;b<particles.size();b++) 
		{	if(b==particleid) continue;
			auto dx=particles[particleid].x-particles[b].x;
			if(abs(dx)>SIZE/2)dx=-2*SIZE*signbit(dx)+SIZE-abs(dx); 
			
			auto dy=abs(particles[particleid].y-particles[b].y);
			if(abs(dy)>SIZE/2)dy=-2*SIZE*signbit(dy)+SIZE-abs(dy); 
			
			auto r2=pow(dx,2)+pow(dy,2);
			
			auto t=24*(pow(r2,3)-2)/pow(r2,7);			
			dE.x+=dx*t;
			dE.y+=dy*t;
		}
	return dE;
}


auto average(auto x)
{
auto ans=0.;
int count=0;
for(auto i:x){
	ans+=i;
	count+=1;
	}
	return ans/count;
}



int main(int argc, char** argv)
{	
	if(argc!=7)
	{cout<<"Usage: "<<argv[0]<<"<delay> <Steps count> <rng seed> <step size> <no. particles> <Temperature>" <<endl;
		exit(-1);
	}
	
	Draw2D visor(700);
	const int delay=atoi(argv[1]);
	const int steps=atoi(argv[2]);
	const int seed=atoi(argv[3]);				
	const double stepsize=atof(argv[4]);
	const int particlecount=atoi(argv[5]);
	const double Temp=atof(argv[6]);
	boost::random::mt19937 rng(seed);
	boost::random::uniform_int_distribution<> boolean(0,1);
	boost::random::uniform_real_distribution<> real(-1,1);
	boost::random::uniform_real_distribution<> realpos(-1,1);
	boost::random::uniform_real_distribution<> pos(0,35);	



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
			
			cout<<mcs<< ' '<<ed<<endl;
			
			if(ed<0||realpos(rng)>exp(-ed/Temp)){particles[i].x+=np.x;particles[i].y+=np.y;}
			if (particles[i].x<0) particles[i].x+=SIZE;
	 		if (particles[i].x>SIZE) particles[i].x-=SIZE;	
			if (particles[i].y<0) particles[i].y+=SIZE;
	 		if (particles[i].y>SIZE) particles[i].y-=SIZE;
 		}

		visor.FullDraw(particles);
		if(mcs<delay)continue;
	
	}
}
