/*
 * ResourceManager.cpp
 *
 *  Created on: Sep 6, 2019
 *      Author: triforce
 */

#include "ResourceManager.h"
#include "SDL2/SDL.h"
#include "Pixel.h"
#include "BasicTexture.h"
unsigned int getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;
    }
}

BasicTexture* ResourceManager::LoadTexture(char* key) {
	auto it=textures.find(std::string(key));
	if (it!=textures.end()) return it->second;
	std::string path = paths.find(std::string(key))->second;
	SDL_Surface* surface = SDL_LoadBMP(path.c_str());
	SDL_LockSurface(surface);
	Pixel** data = new Pixel*[(surface->w)];
	for (int i=0; i<surface->w; i++) {
		data[i]=new Pixel[surface->h];
	}
	unsigned int datum;
	for (int i=0; i<surface->w; i++) {
		for (int j=0;j<surface->h; j++) {
			datum = getpixel(surface, i, j);
			data[i][j]=Pixel((datum&0xFF)/255.0, ((datum>>8)&0xFF)/255.0, ((datum>>16)&0xFF)/255.0, ((datum>>24)&0xFF)/255.0);
		}
	}
	BasicTexture* tex = new BasicTexture(surface->w, surface->h, data);
	textures.insert(std::pair<std::string, BasicTexture*>(key, tex));
	return tex;

}
