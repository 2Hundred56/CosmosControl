/*
 * CollisionManager.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: triforce
 */

#include "CollisionManager.h"
#include "Vector.h"
#include "Shape.h"
#include "CollisionTerms.h"
#include <set>
#include <cmath>
CollisionManager::CollisionManager() {
	// TODO Auto-generated constructor stub

}

CollisionManager::~CollisionManager() {
	// TODO Auto-generated destructor stub
}

int sign(float f) {
	if (f < 0)
		return -1;
	else if (f > 0)
		return 1;
	else
		return 0;
}
CollisionInfo CollisionManager::CheckCollision(CollisionHandle* h1, CollisionHandle* h2) {
	Shape* s1 = h1->GetShape();
	Vector p1 = h1->GetPos();
	Shape* s2 = h2->GetShape();
	Vector p2 = h2->GetPos();
	std::set<Vector> axes, axes2;
	axes = s1->Axes(s2, p2-p1);
	axes2 = s2->Axes(s1, p1-p2);
	auto it = axes2.begin();
	float minDst = 1000;
	Vector maxAxis = Vector(0, 0);
	float diff, sep, maxSep, sgn;
	Vector axis = Vector(0, 0);
	for (it=axes2.begin(); it!=axes2.end(); it++) {
		axes.insert(*it);
	}
	for (it=axes.begin(); it!=axes.end(); it++) {
		axis=*it;
		Projection proj1 = s1->Proj(axis)+Projection(proj(p1, axis),proj(p1, axis));
		Projection proj2 = s2->Proj(axis)+Projection(proj(p2, axis),proj(p2, axis));
		maxSep = proj1.max-proj1.min+proj2.max-proj2.min; //maximum possible separation
		sep=std::max(proj1.max, proj2.max)-std::min(proj1.min, proj2.min);
		if (sep>=maxSep) return NoCollision();
		sgn=sign(proj1.min-proj2.min+proj1.max-proj2.max);
		if (sgn<0) diff = (proj1.max-proj2.min);
		else diff=(proj2.max-proj1.min);
		//TODO: Look at this code if we ever go back to cflags
		/*if (std::abs(axis.x)==1) { //We know it's normalized, so no need testing y coord
		f	//TODO: This code probably could be cleaned up
			if ((cflag&NO_LEFT) && (cflag&NO_RIGHT)) continue;
			if (((cflag&NO_LEFT) && sgn>0) || ((cflag&NO_RIGHT) && sgn<0)) continue;
		}
		else if (std::abs(axis.y)==1) { //Can you tell this was copied and pasted?
			if ((cflag&NO_UP) && (cflag&NO_DOWN)) continue;
			if (((cflag&NO_UP) && sgn>0) || ((cflag&NO_DOWN) && sgn<0)) continue;
		}
		else {
			if (cflag&NO_WEIRD) continue;
		}*/
		if ((diff*sgn)!=0 && diff<std::abs(minDst)) {
			minDst=diff*sgn;
			maxAxis=axis;
		}
	}
	return CollisionInfo(maxAxis*minDst);

}
