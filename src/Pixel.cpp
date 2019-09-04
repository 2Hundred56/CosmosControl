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



