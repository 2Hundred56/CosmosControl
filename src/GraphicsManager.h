/*
 * GraphicsWrapper.h
 *
 *  Created on: Sep 2, 2019
 *      Author: triforce
 */

#ifndef GRAPHICSMANAGER_H_
#define GRAPHICSMANAGER_H_
#include <vector>
class Vector;
class RenderData;
class Texture;
class RenderTarget;
class Pixel;
class IntVector;
class GraphicsManager {
public:
	GraphicsManager(int, int);
	virtual ~GraphicsManager();
	void RenderTexture(Texture*, Vector, RenderData);
	void RenderTexture(Texture*, Vector);
	unsigned int* Process();
	bool InBounds(Vector);
	bool InBounds(IntVector);
	void AddPixel(IntVector, Pixel);
private:
	std::vector<Pixel>** data;
	int width;
	int height;
};

#endif /* GRAPHICSMANAGER_H_ */
