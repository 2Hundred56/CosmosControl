/*
 * PaletteTexture.cpp
 *
 *  Created on: Sep 6, 2019
 *      Author: triforce
 */

#include "PaletteTexture.h"
#include "IntVector.h"
#include "Pixel.h"

Pixel PaletteTexture::getPixel(IntVector intVector) {
	return palettes[data[intVector.x][intVector.y]];
}
