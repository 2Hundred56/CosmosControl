/*
 * CollisionTerms.h
 *
 *  Created on: Sep 7, 2019
 *      Author: triforce
 */

#ifndef COLLISIONTERMS_H_
#define COLLISIONTERMS_H_
#include "Vector.h"
#include "Rect.h"
#include <vector>
class Shape;
class CollisionAxis {
public:
	CollisionAxis(Vector v) : axis(v) {

	}
	Vector axis;
};
class Projection {
public:
	float min;
	float max;
	Projection(float x, float y) : min(x), max(y) {

	}
};
Projection operator +(Projection p1, Projection p2);
class CollisionInfo {
public:
	Vector normal;
	CollisionInfo(Vector);
};

class CollisionHandle {
public:
	Shape* GetShape();
	Vector GetPos();
	void collisionCallback(CollisionHandle* handle, CollisionInfo collision);
	Rect GetRect();
};
CollisionInfo NoCollision();

class CollisionNode {
public:
	Rect rect;
	CollisionNode* leaf1;
	CollisionNode* leaf2;
	CollisionNode* parent;
	CollisionHandle* handle = 0;
	CollisionNode(CollisionNode* parent, CollisionNode* leaf1, CollisionNode* leaf2, Rect rect) : parent(parent), leaf1(leaf1), leaf2(leaf2), rect(rect){

	}
	float CostWith(Rect r);

};
CollisionNode* Leaf(CollisionNode* parent, CollisionHandle *handle);
class CollisionTree {
public:
	std::vector<CollisionNode*> nodes;
	CollisionNode* root;
	void InsertNode(CollisionHandle* handle);
	CollisionNode* Sibling(CollisionHandle* handle);
};


#endif /* COLLISIONTERMS_H_ */
