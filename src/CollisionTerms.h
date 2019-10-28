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
#include <set>
const int NO_UP = 1;
const int NO_LEFT = 2;
const int NO_RIGHT = 4;
const int NO_DOWN = 8;
const int NO_WEIRD = 16;

const int UP_ONLY = NO_LEFT | NO_RIGHT | NO_DOWN | NO_WEIRD;
const int LEFT_ONLY = NO_UP | NO_RIGHT | NO_DOWN | NO_WEIRD;
const int RIGHT_ONLY = NO_LEFT | NO_UP | NO_DOWN | NO_WEIRD;
const int DOWN_ONLY = NO_LEFT | NO_RIGHT | NO_UP | NO_WEIRD;
const int BAD_FLAG = NO_LEFT | NO_RIGHT | NO_DOWN | NO_UP | NO_WEIRD;

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
class Shape {
public:
	virtual ~Shape() {

	}
	virtual std::set<Vector> Axes (Shape*, Vector) = 0;
	virtual Projection Proj(Vector axis) = 0;
	virtual Rect ContainBox() = 0;
};
class AABB : public Shape {
public:
	AABB(float hw, float hh);
	virtual std::set<Vector> Axes (Shape*, Vector);
	virtual Projection Proj(Vector axis);
	virtual Rect ContainBox();
protected:
	float hw, hh;
};
Projection operator +(Projection p1, Projection p2);
class CollisionResult {
public:
	bool collision = false;
	Vector normal;
	Vector slopeNormal;
	CollisionResult(Vector, Vector);
	CollisionResult();
};
class CollisionInfo {
public:
	CollisionResult result;
	CollisionHandle* h1;
	CollisionHandle* h2;
	CollisionInfo(CollisionResult, CollisionHandle*, CollisionHandle*);
	CollisionInfo Reverse();
};
class CollisionHandle {
public:
	bool moved = false;
	virtual Shape* GetShape() = 0;
	virtual Vector GetPos() = 0;
	virtual void CollisionCallback(CollisionHandle* handle, CollisionInfo collision) {

	}
	virtual Rect GetRect();
};
class TestHandle : public CollisionHandle {
public:
	TestHandle(Vector p, Shape* s);
	Shape* GetShape();
	Vector GetPos();
protected:
	Shape* shape;
	Vector pos;
};
typedef std::vector<std::pair<CollisionHandle*, CollisionHandle*> > Collisions;
class CollisionLayer {
public:
	virtual Collisions Check(CollisionHandle* handle) = 0;
	virtual ~CollisionLayer() {

	}
};
class BroadPhase : public CollisionLayer{
public:
	virtual void Insert(CollisionHandle* handle) = 0;
	virtual std::vector<CollisionHandle*> GrabMoved() = 0;
};
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
CollisionNode* Leaf (CollisionNode* parent, CollisionHandle *handle);
class CollisionTree : public BroadPhase{
public:
	CollisionTree();
	std::vector<CollisionNode*> nodes;
	CollisionNode* root;
	void Insert(CollisionHandle* handle);
	void Remove(CollisionNode* node);
	std::vector<CollisionHandle*> GrabMoved();
	Collisions Check(CollisionHandle* handle);
	CollisionNode* Sibling(CollisionHandle* handle);
};


#endif /* COLLISIONTERMS_H_ */
