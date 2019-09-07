/*
 * Shape.h
 *
 *  Created on: Sep 7, 2019
 *      Author: triforce
 */

#ifndef SHAPE_H_
#define SHAPE_H_
#include <set>
class Rect;
class Vector;
class Shape {
public:
	virtual ~Shape() {

	}
	virtual std::set<Vector> Axes (Vector, Shape* other) = 0;
	virtual Vector Proj(Vector axis) = 0;
	virtual Rect ContainBox() = 0;
};

#endif /* SHAPE_H_ */
