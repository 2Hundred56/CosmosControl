/*
 * CollisionTerms.h
 *
 *  Created on: Sep 7, 2019
 *      Author: triforce
 */

#ifndef COLLISIONTERMS_H_
#define COLLISIONTERMS_H_
#include "Vector.h"
class Shape;
class CollisionAxis {
public:
	CollisionAxis(Vector v) : axis(v) {

	}
	Vector axis;
};
class Projection {
	float min;
	float max;
	Projection(float x, float y) : min(x), max(y) {

	}
};
Projection operator+ (Projection p1, Projection p2) {
	return Projection(p1.min+p2.min, p2.max+p2.max);
}
class CollisionInfo {
	Vector normal;
};
CollisionInfo collisionInfo;

#endif /* COLLISIONTERMS_H_ */
