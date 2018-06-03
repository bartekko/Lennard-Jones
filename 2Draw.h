#pragma once

#include <cmath>
#include <vector>
#include "Point.h"

#ifdef VISOR_ENABLE
#include <SDL2/SDL.h>
//typedef std::vector<std::pair<int,int>> pointList;


#define SIZE 35
#define SCALE 20	

class Draw2D
{
public:
	Draw2D(int windowSize=700)
	{	SDL_Init(SDL_INIT_VIDEO);
		win= SDL_CreateWindow("Visor",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowSize,windowSize,0);
		ren=SDL_CreateRenderer(win,-1,0);	
	}
	void FullDraw(std::vector<Point> points)
	{	SDL_SetRenderDrawColor(ren,0,0,0,255);
		SDL_RenderClear(ren);
		SDL_SetRenderDrawColor(ren,255,0,0,255);
			for(auto pt: points)
			{	while (pt.x<0)pt.x+=SIZE;
				while (pt.y<0)pt.y+=SIZE;
				while (pt.x>SIZE)pt.x-=SIZE;
				while (pt.y>SIZE)pt.y-=SIZE;
				
				SDL_RenderDrawPoint(ren,int(SCALE*(pt.x)+0.5),int(SCALE*(pt.y)+0.5));				
			
			}
		SDL_SetRenderDrawColor(ren,255,255,255,255);	
		SDL_RenderDrawPoint(ren,int(SCALE*(points[4].x)+0.5),int(SCALE*(points[4].y)+0.5));				
		
	SDL_RenderPresent(ren);	
	SDL_Event e;
	while(SDL_PollEvent(&e)!=0)
    {	if( e.type == SDL_QUIT )
		{	exit(0);
        }
        }
	}
	~Draw2D(){SDL_Quit();}

private:
	SDL_Window *win;
	SDL_Renderer *ren;	
};


#endif

#ifndef VISOR_ENABLE
class Draw2D
{
public:
	Draw2D(int windowSize=500){}
	void FullDraw(std::vector<Point> points){}
	~Draw2D(){
	}
};



#endif
