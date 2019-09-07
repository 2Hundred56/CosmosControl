/*
 * BasicTexture.h
 *
 *  Created on: Sep 6, 2019
 *      Author: triforce
 */

#ifndef BASICTEXTURE_H_
#define BASICTEXTURE_H_

#include "Texture.h"
class BasicTexture: public Texture {
public:
	BasicTexture(int, int, Pixel**);
	virtual ~BasicTexture();
	virtual Pixel getPixel(IntVector);
	virtual int getWidth() {
		return width;
	}
	virtual int getHeight() {
		return height;
	}
protected:
	int width, height;
	Pixel** pixels;
};

#endif /* BASICTEXTURE_H_ */
