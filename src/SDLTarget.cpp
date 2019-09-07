/*
 * SDLTarget.cpp
 *
 *  Created on: Sep 6, 2019
 *      Author: triforce
 */

#include "SDLTarget.h"
#include "SDL2/SDL.h"

void SDLTarget::Render(unsigned int *data, int w, int h) {
	if (width!=w || height!=h) {
		width=w;
		height=h;
		SDL_DestroyTexture(screenTexture);
		screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
				SDL_TEXTUREACCESS_STATIC, width, height);
	}
	SDL_UpdateTexture(screenTexture, NULL, data, width * sizeof(unsigned int));
}

void SDLTarget::Flip() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void SDLTarget::BeginGraphics() {
}

void SDLTarget::Initialize() {
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) throw(1);
	window = SDL_CreateWindow("Generic", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if( window == NULL ) throw(2);
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) throw(3);
	screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
	if (screenTexture==NULL) throw(4);
}

void SDLTarget::CloseGraphics() {
	SDL_DestroyTexture(screenTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
