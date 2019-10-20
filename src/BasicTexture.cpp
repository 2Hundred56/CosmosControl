/*
 * BasicTexture.cpp
 *
 *  Created on: Sep 6, 2019
 *      Author: triforce
 */

#include "BasicTexture.h"
#include "IntVector.h"
#include "Pixel.h"

BasicTexture::BasicTexture(int int1, int int2, Pixel** p) : width(int1), height(int2), pixels(p) {
}

BasicTexture::~BasicTexture() {
	for (int i=0; i<width; i++) {
		delete pixels[i];
	}
	delete pixels;
}

Pixel BasicTexture::getPixel(IntVector intVector) {
	return pixels[intVector.x][intVector.y];
}
