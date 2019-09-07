/*
 * Pixel.cpp
 *
 *  Created on: Sep 4, 2019
 *      Author: triforce
 */
#include "Pixel.h"
bool operator <(const Pixel& p1, const Pixel& p2) {
	return p1.z<p2.z;
}

Pixel& operator +=(Pixel& p1, Pixel p2) {
	p1=Pixel(p1.r * (1-p2.a) + p2.r * p2.a, p1.g * (1-p2.a) + p2.g * p2.a, p1.b * (1-p2.a) + p2.b * p2.a, 1);
	return p1;
}
