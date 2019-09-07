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

Pixel BasicTexture::getPixel(IntVector intVector) {
	return pixels[intVector.x][intVector.y];
}
