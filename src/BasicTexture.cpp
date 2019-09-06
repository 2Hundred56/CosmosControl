/*
 * BasicTexture.cpp
 *
 *  Created on: Sep 6, 2019
 *      Author: triforce
 */

#include "BasicTexture.h"
#include "IntVector.h"
BasicTexture::BasicTexture() {
	// TODO Auto-generated constructor stub

}

BasicTexture::~BasicTexture() {
	// TODO Auto-generated destructor stub
}

Pixel BasicTexture::getPixel(IntVector intVector) {
	return pixels[intVector.x][intVector.y];
}
