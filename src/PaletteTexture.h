/*
 * PaletteTexture.h
 *
 *  Created on: Sep 6, 2019
 *      Author: triforce
 */

#ifndef PALETTETEXTURE_H_
#define PALETTETEXTURE_H_

#include "Texture.h"
class PaletteTexture: public Texture {
public:
	PaletteTexture();
	virtual ~PaletteTexture();
	virtual Pixel getPixel(IntVector);
	virtual int getWidth() {
		return width;
	}
	virtual int getHeight() {
		return height;
	}
protected:
	int width, height;
	Pixel* palettes;
	char** data;
};

#endif /* PALETTETEXTURE_H_ */
