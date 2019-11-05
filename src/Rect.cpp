/*
 * Rect.cpp
 *
 *  Created on: Oct 13, 2019
 *      Author: triforce
 */
#include "Rect.h"
#include "Vector.h"
#include <algorithm>

Rect Union(Rect r1, Rect r2) {
	float minX=std::min(r1.x, r2.x);
	float maxX=std::max(r1.x+r1.w, r2.x+r2.w);
	float minY=std::min(r1.y, r2.y);
	float maxY=std::max(r1.y+r1.h, r2.y+r2.h);
	return Rect(minX, minY, maxX-minX, maxY-minY);
}

bool RectOverlap(Rect r1, Rect r2) {
	return (std::max(r1.x+r1.w, r2.x+r2.w)-std::min(r1.x, r2.x))<=(r1.w+r2.w)
			&& (std::max(r1.y+r1.h, r2.y+r2.h)-std::min(r1.y, r2.y))<=(r1.h+r2.h);
}

float Rect::Area() {
	return w*h;
}

Rect operator +(Rect r, Vector v) {
	return Rect(r.x+v.x, r.y+v.y, r.w, r.h);
}

std::ostream& operator <<(std::ostream &out, Rect r) {
	out<<"["<<r.x<<","<<r.y<<","<<r.w<<","<<r.h<<"]";
	return out;
}
