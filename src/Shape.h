/*
 * Shape.h
 *
 *  Created on: Sep 7, 2019
 *      Author: triforce
 */

#ifndef SHAPE_H_
#define SHAPE_H_
#include <set>
class Vector;
class Projection;
class Rect;
class Shape {
public:
	virtual ~Shape() {

	}
	virtual std::set<Vector> Axes (Shape*, Vector) = 0;
	virtual Projection Proj(Vector axis) = 0;
	virtual Rect ContainBox() = 0;
};

#endif /* SHAPE_H_ */
