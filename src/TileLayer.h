/*
 * TileLayer.h
 *
 *  Created on: Nov 1, 2019
 *      Author: triforce
 */

#ifndef TILELAYER_H_
#define TILELAYER_H_

#include "CollisionTerms.h"
class IntVector;
class TileLayer : public CollisionLayer {
public:
	TileLayer (int w, int h, int ts);
	Tile* GetTile(IntVector i);
	virtual Collisions Check(CollisionHandle* handle);
	int width;
	int height;
	int** tileArray;
	int** tilesetArray;
	int tileSize;
	std::vector<std::vector<Tile*> > tiles;
};



#endif /* TILELAYER_H_ */
