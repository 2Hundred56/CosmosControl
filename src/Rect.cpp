/*
 * Rect.cpp
 *
 *  Created on: Oct 13, 2019
 *      Author: triforce
 */
#include "Rect.h"
#include "IntVector.h"
#include <algorithm>

Rect Union(Rect r1, Rect r2) {
	int minX=std::min(r1.x, r2.x);
	int maxX=std::max(r1.x, r2.x);
	int minY=std::min(r1.y, r2.y);
	int maxY=std::max(r1.y, r2.y);
	return Rect(minX, minY, maxX-minX, maxY-minY);
}

bool RectOverlap(Rect r1, Rect r2) {
	return (std::max(r1.x+r1.w, r2.x+r2.w)-std::min(r1.x, r2.x))>=(r1.w+r2.w)
			&& (std::max(r1.y+r1.h, r2.y+r2.h)-std::min(r1.y, r2.y))>=(r1.h+r2.h);
}

float Rect::Area() {
	return w*h;
}

Rect operator +(Rect r, IntVector v) {
	return Rect(r.x+v.x, r.y+v.y, r.w, r.h);
}
