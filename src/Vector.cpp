/*
 * Vector.cpp
 *
 *  Created on: Sep 4, 2019
 *      Author: triforce
 */

#include "Vector.h"
#include <iostream>
float operator *(Vector v1, Vector v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

bool operator <(Vector v1, Vector v2) {
	return v1.x < v2.x;
}

Vector operator *(Vector v, float f) {
	return Vector(v.x * f, v.y * f);
}

float projection(Vector v, Vector axis) {
	//Assume axis is normalized
	return axis * v;
}

Vector operator -(Vector v) {
	return Vector(-v.x, -v.y);
}

std::ostream& operator <<(std::ostream& out, Vector v) {
	out<<"<"<<v.x<<","<<v.y<<">";
	return out;
}

Vector operator -(Vector v1, Vector v2) {
	return Vector(v1.x-v2.x, v1.y-v2.y);
}

Vector operator +(Vector v1, Vector v2) {
	return Vector(v1.x+v2.x, v1.y+v2.y);
}

Vector& operator +=(Vector& orig, Vector add) {
	orig = Vector(orig.x+add.x, orig.y+add.y);
	return orig;
}


