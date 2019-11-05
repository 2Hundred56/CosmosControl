/*
 * main.cpp
 *
 *  Created on: Aug 31, 2019
 *      Author: triforce
 */

/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

/*This source code copyrighted by Lazy Foo' Productions (2004-2019)
and may not be redistributed without written permission.*/

//Using SDL and standard IO

#include "GraphicsManager.h"
#include "IntVector.h"
#include "SDLTarget.h"
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	GraphicsManager* gm = new GraphicsManager(SCREEN_WIDTH, SCREEN_HEIGHT);
	RenderTarget* sdl = new SDLTarget();
	sdl->BeginGraphics();
	sdl->Initialize(IntVector(SCREEN_WIDTH, SCREEN_HEIGHT));
	sdl->Render(gm->Process(), SCREEN_WIDTH, SCREEN_HEIGHT);
	sdl->Flip();
	SDL_Event e;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN){
				quit = true;
			}
		}
	}
	sdl->CloseGraphics();
	return 0;
}


