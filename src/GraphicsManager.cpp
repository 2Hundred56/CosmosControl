/*
 * GraphicsWrapper.cpp
 *
 *  Created on: Sep 2, 2019
 *      Author: triforce
 */

#include "GraphicsManager.h"
#include "Texture.h"
#include "Vector.h"
#include "Pixel.h"
#include "IntVector.h"
#include "RenderData.h"
#include <algorithm>
GraphicsManager::GraphicsManager(int w, int h) {
	width=w;
	height=h;
	data = new std::vector<Pixel>*[width];
	for (int i=0; i<width; i++) {
		data[i]=new std::vector<Pixel>[height];
	}

}

void GraphicsManager::RenderTexture(Texture* texture, Vector vector,
		RenderData renderData) {
	//TODO: Process data to align with RenderData
	Vector finalLocation;
	Pixel pixel;
	for (int i=0; i<texture->getWidth(); i++) {
		for (int j=0; j<texture->getHeight(); i++) {
			pixel=texture->getPixel(IntVector(i, j));
			finalLocation=Vector(i, j);
			AddPixel(IntVector(finalLocation), pixel);
		}
	}
}

void GraphicsManager::RenderTexture(Texture* texture, Vector vector) {
	RenderTexture(texture, vector, RenderData());
}

bool GraphicsManager::InBounds(Vector vector) {
	return vector.x>=0 && vector.x<width && vector.y>=0 && vector.y<height;
}

bool GraphicsManager::InBounds(IntVector vector) {
	return vector.x>=0 && vector.x<width && vector.y>=0 && vector.y<height;
}

unsigned int* GraphicsManager::Process() {
	unsigned int* processed = new unsigned int[width*height];
	Pixel pixel;
	Pixel p;
	std::vector<Pixel> pixels;
	for (int i=0; i<width; i++) {
		for (int j=0; j<height; j++) {
			pixel=Pixel();
			pixels=data[i][j];
			//TODO: Stare at this for 10 minutes
			std::sort(pixels.begin(), pixels.end());
			for (auto it=pixels.begin(); it!=pixels.end(); it++) {
				pixel+=(*it);
			}
			processed[j*width+i]=(((int) pixel.r*255)<<24)+(((int) pixel.g*255)<<16)+(((int) pixel.b*255)<<8)+(((int) pixel.a*255));
		}
	}
	return processed;
}
void GraphicsManager::AddPixel(IntVector intVector, Pixel pixel) {
	if (InBounds(intVector)) {
		data[intVector.x][intVector.y].push_back(pixel);
	}
}
