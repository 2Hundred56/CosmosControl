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
	Vector v;

};
class CollisionCheck {
public:
	Shape* s1;
	Vector p1;
	Shape* s2;
	Vector p2;
};


#endif /* COLLISIONTERMS_H_ */
