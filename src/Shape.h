/*
 * Shape.h
 *
 *  Created on: Sep 7, 2019
 *      Author: triforce
 */

#ifndef SHAPE_H_
#define SHAPE_H_
#include <set>
class CollisionAxis;
class Projection;
class CollisionCheck;
class Rect;
class Shape {
public:
	virtual ~Shape() {

	}
	virtual std::set<CollisionAxis> Axes (CollisionCheck) = 0;
	virtual Projection Proj(CollisionAxis axis) = 0;
	virtual Rect ContainBox() = 0;
};

#endif /* SHAPE_H_ */
