/*
 * TileLayer.cpp
 *
 *  Created on: Nov 5, 2019
 *      Author: triforce
 */

#include "TileLayer.h"
#include "IntVector.h"
#include "CollisionTerms.h"
Tile* TileLayer::GetTile(IntVector i) {
	return tiles[tilesetArray[i.x][i.y]][tileArray[i.x][i.y]];
}

TileLayer::TileLayer(int w, int h) : width(w), height(h) {
	tileArray = new int*[w];
	tilesetArray = new int*[w];
	for (int i=0; i<w; i++) {
		tileArray[i]=new int[h];
		tilesetArray[i]=new int[h];
	}
}

Collisions TileLayer::Check(CollisionHandle *handle) {
	Tile* t;
	Vector v;
	TileHandle* th;
	Collisions collisions = Collisions();
	Rect r = handle->GetRect();
	int i0 = (r.x)/tileSize;
	int i1 = (r.x+r.w)/tileSize+1;
	int j0 = (r.y)/tileSize;
	int j1 = (r.y+r.h)/tileSize+1;
	for (int i=i0; i<i1; i++) {
		for (int j=j0; j<j1; j++) {
			t = GetTile(IntVector(i, j));
			if (t==0) continue;
			if (t->shape==0) continue;
			v=Vector((i+0.5)*tileSize, (j+0.5)*tileSize);
			th=new TileHandle(v, t);
			collisions.push_back(std::pair<CollisionHandle*, CollisionHandle*>(handle, th));
		}
	}
	return collisions;
}
