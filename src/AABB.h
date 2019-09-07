/*
 * AABB.h
 *
 *  Created on: Sep 7, 2019
 *      Author: triforce
 */

#ifndef AABB_H_
#define AABB_H_
#include "Shape.h"
class AABB : public Shape {
public:
	float hw, hh;
	AABB (float w, float h) : hw(w), hh(h) {

	}
	std::set<Vector> Axes (Vector pos, Shape* other);
	Vector Proj (Vector axis);
	Rect ContainBox();
};




#endif /* AABB_H_ */
