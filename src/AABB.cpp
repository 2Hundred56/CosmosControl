/*
 * AABB.cpp
 *
 *  Created on: Sep 7, 2019
 *      Author: triforce
 */

#include "AABB.h"
#include "Vector.h"
#include "Rect.h"
Vector AABB::Proj (Vector axis) {
	float p1 = proj(Vector(-hw, -hh), axis);
	float p2 = proj(Vector(hw, -hh), axis);
	float p3 = proj(Vector(hw, hh), axis);
	float p4 = proj(Vector(-hw, hh), axis);
	float max = std::max(std::max(p1, p2), std::max(p3, p4));
	float min = std::min(std::min(p1, p2), std::min(p3, p4));
	return Vector(min, max);
}
std::set<Vector> AABB::Axes (Vector pos, Shape* other) {
	std::set<Vector> set;
	set.insert(Vector(1, 0));
	set.insert(Vector(0, 1));
	return set;
}
Rect AABB::ContainBox() {
	return Rect(-hw, -hh, hw*2, hh*2);
}

