/*
 * Vector.h
 *
 *  Created on: Sep 2, 2019
 *      Author: triforce
 */

#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
class Vector {
public:
	float x, y;
	Vector(float x, float y) : x(x), y(y) {

	}
	Vector (const Vector& v) : x(v.x), y(v.y) {

	}
	Vector () : x(0), y(0) {

	}
};

float operator *(Vector v1, Vector v2);

bool operator <(Vector v1, Vector v2);

Vector operator *(Vector v, float f);

Vector& operator+= (Vector& orig, Vector add);

float proj(Vector v, Vector axis);

Vector operator- (Vector v);

Vector operator- (Vector, Vector);

Vector operator+ (Vector, Vector);

std::ostream& operator<<(std::ostream&, Vector);

#endif /* VECTOR_H_ */
