#pragma once

#include <cmath>
#include <vector>
#include "Point.h"

#define SIZE 35
#define SCALE 20	


#ifdef VISOR_ENABLE
#include <SDL2/SDL.h>
//typedef std::vector<std::pair<int,int>> pointList;


int OffsetX=0;
int OffsetY=0;
class Draw2D
{
public:
	Draw2D(int windowSize=700)
	{	SDL_Init(SDL_INIT_VIDEO);
		win= SDL_CreateWindow("Visor",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,windowSize,windowSize,0);
		ren=SDL_CreateRenderer(win,-1,0);	
		wSize=windowSize;
	}
	void FullDraw(std::vector<Point> points)
	{	SDL_SetRenderDrawColor(ren,0,0,255,255);
		SDL_RenderClear(ren);
		SDL_SetRenderDrawColor(ren,255,255,0,255);
			for(auto pt: points)
			{	while (pt.x<0)pt.x+=SIZE;
				while (pt.y<0)pt.y+=SIZE;
				while (pt.x>SIZE)pt.x-=SIZE;
				while (pt.y>SIZE)pt.y-=SIZE;
				
				SDL_RenderDrawPoint(ren,(OffsetX+int(SCALE*(pt.x)+0.5))%wSize,(OffsetY+int(SCALE*(pt.y)+0.5))%wSize);				
			
			}
		SDL_SetRenderDrawColor(ren,255,255,255,255);	
		SDL_RenderDrawPoint(ren,int(SCALE*(points[4].x)+0.5),int(SCALE*(points[4].y)+0.5));				
		
		SDL_RenderPresent(ren);	
		SDL_Event e;
	
		while(SDL_PollEvent(&e)!=0)
	    {	
		    if( e.type == SDL_QUIT )exit(0);
		    if( e.type == SDL_KEYDOWN )
		    { 	
		      	if(e.key.keysym.scancode==SDL_SCANCODE_UP)OffsetY+=10;
		    	if(e.key.keysym.scancode==SDL_SCANCODE_DOWN)OffsetY-=10;
		    	if(e.key.keysym.scancode==SDL_SCANCODE_RIGHT)OffsetX+=10;
		    	if(e.key.keysym.scancode==SDL_SCANCODE_LEFT)OffsetX-=10;
		    }     
        
        }
	}
	~Draw2D(){SDL_Quit();}

private:
	SDL_Window *win;
	SDL_Renderer *ren;	
	int wSize;
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
