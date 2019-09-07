/*
 * IntVector.cpp
 *
 *  Created on: Sep 7, 2019
 *      Author: triforce
 */

#include "IntVector.h"
#include "Vector.h"

IntVector::IntVector(int x, int y) : x(x), y(y){
}

IntVector::IntVector(Vector v) : x((int) v.x), y((int) v.y){
}

IntVector::~IntVector() {
}

IntVector operator +(IntVector iv, IntVector iv2) {
	return IntVector(iv.x+iv2.x, iv.y+iv2.y);
}

IntVector operator -(IntVector iv, IntVector iv2) {
	return IntVector(iv.x-iv2.x, iv.y-iv2.y);
}

float operator *(IntVector iv, IntVector iv2) {
	return iv.x*iv2.x + iv.y*iv2.y;
}

IntVector operator *(IntVector iv, float c) {
	return IntVector(iv.x*c, iv.y*c);
}

IntVector operator /(IntVector iv, float c) {
	return IntVector(iv.x/c, iv.y/c);
}
