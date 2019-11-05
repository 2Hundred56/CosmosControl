/*
 * CollisionTerms.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: triforce
 */

#include "CollisionTerms.h"
#include "IntVector.h"
#include <algorithm>
Projection operator +(Projection p1, Projection p2) {
	return Projection(p1.min + p2.min, p1.max + p2.max);
}

Rect CollisionHandle::GetRect() {
	return GetShape()->ContainBox()+GetPos();
}

CollisionInfo::CollisionInfo(CollisionResult result, CollisionHandle* h1, CollisionHandle* h2) : result(result), h1(h1), h2(h2){
}

std::set<Vector> AABB::Axes(Shape*, Vector vector) {
	std::set<Vector> axes;
	axes.insert(Vector(0, 1));
	axes.insert(Vector(1, 0));
	return axes;
}

Projection AABB::Proj(Vector axis) {
	float a = projection(Vector(-hw, -hh), axis);
	float b = projection(Vector(hw, -hh), axis);
	float c = projection(Vector(-hw, hh), axis);
	float d = projection(Vector(hw, hh), axis);
	return Projection(std::min(std::min(a, b), std::min(c, d)), std::max(std::max(a, b), std::max(c, d)));
}

Rect AABB::ContainBox() {
	return Rect(-hw, -hh, hw*2, hh*2);
}

AABB::AABB(float hw, float hh) : hw(hw), hh(hh){
}

TestHandle::TestHandle(Vector p, Shape *s) : pos (p), shape(s) {
}

Shape* TestHandle::GetShape() {
	return shape;
}

Vector TestHandle::GetPos() {
	return pos;
}

CollisionResult::CollisionResult(Vector vector, Vector sn) {
	normal=vector;
	slopeNormal=sn;
	collision=true;
}

CollisionResult::CollisionResult() {
	collision=false;
}

TileHandle::TileHandle(Vector p, Tile *t) : pos(p), tile(t) {
}

Shape* TileHandle::GetShape() {
	return tile->shape;
}

Vector TileHandle::GetPos() {
	return pos;
}
