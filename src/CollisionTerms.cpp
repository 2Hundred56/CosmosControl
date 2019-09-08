/*
 * CollisionTerms.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: triforce
 */

#include "CollisionTerms.h"

Projection operator +(Projection p1, Projection p2) {
	return Projection(p1.min + p2.min, p2.max + p2.max);
}
