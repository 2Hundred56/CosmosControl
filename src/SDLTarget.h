/*
 * SDLTarget.h
 *
 *  Created on: Sep 6, 2019
 *      Author: triforce
 */

#ifndef SDLTARGET_H_
#define SDLTARGET_H_

#include "RenderTarget.h"
struct SDL_Texture;
struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Window;
class SDLTarget: public RenderTarget {
public:
	SDLTarget();
	virtual ~SDLTarget();
	virtual void Render(unsigned int* data, int w, int h);
	virtual void Flip();
	virtual void BeginGraphics();
	virtual void Initialize();
	virtual void CloseGraphics();
protected:
	SDL_Texture* screenTexture;
	SDL_Renderer* renderer;
	SDL_Window* window;
	int width, height;
};

#endif /* SDLTARGET_H_ */
