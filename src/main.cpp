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
#include "CollisionManager.h"
#include "CollisionTerms.h"
#include "TileLayer.h"
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
	AABB* unitBox = new AABB(0.5, 0.5);
	CollisionManager* cm = new CollisionManager();
	TileLayer* tl = new TileLayer(3, 3, 1);
	cm->collisionLayers.push_back(tl);
	tl->tileArray[1][2]=0;
	tl->tilesetArray[1][2]=0;
	std::vector<Tile*> set1 = std::vector<Tile*>();
	set1.push_back(new Tile(unitBox, 0));
	tl->tiles.push_back(set1);
	CollisionHandle* h1 = new TestHandle(Vector(1.5, 2), unitBox);
	cm->RegisterHandle(h1);
	cm->Update();
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


