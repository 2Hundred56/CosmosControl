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
};

#endif /* COLLISIONTERMS_H_ */
