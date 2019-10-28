/*
 * CollisionManager.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: triforce
 */

#include "CollisionManager.h"
#include "Vector.h"
#include "CollisionTerms.h"
#include <set>
#include <cmath>
CollisionManager::CollisionManager() {
	centralSystem = new CollisionTree();
}

CollisionManager::~CollisionManager() {

}

int sign(float f) {
	if (f < 0)
		return -1;
	else if (f > 0)
		return 1;
	else
		return 0;
}
CollisionResult CollisionManager::CheckCollision(CollisionHandle* h1, CollisionHandle* h2, int cflag) {
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
	float minSDst = 1000;
	Vector maxSAxis = Vector(0, 0);
	float diff, sep, maxSep, sgn;
	Vector axis = Vector(0, 0);
	for (it=axes2.begin(); it!=axes2.end(); it++) {
		axes.insert(*it);
	}
	for (it=axes.begin(); it!=axes.end(); it++) {
		axis=*it;
		Projection proj1 = s1->Proj(axis)+Projection(projection(p1, axis),projection(p1, axis));
		Projection proj2 = s2->Proj(axis)+Projection(projection(p2, axis),projection(p2, axis));
		maxSep = proj1.max-proj1.min+proj2.max-proj2.min; //maximum possible separation
		sep=std::max(proj1.max, proj2.max)-std::min(proj1.min, proj2.min);
		if (sep>=maxSep) return CollisionResult```````();
		sgn=sign(proj1.min-proj2.min+proj1.max-proj2.max);
		if (sgn<0) diff = (proj1.max-proj2.min);
		else diff=(proj2.max-proj1.min);
		//TODO: Look at this code if we ever go back to cflags
		if ((diff*sgn)!=0 && diff<std::abs(minDst)) {
			minSDst=diff*sgn;
			maxSAxis=axis;
		}
		if (std::abs(axis.x)==1) { //We know it's normalized, so no need testing y coord
		//TODO: This code probably could be cleaned up
			if ((cflag&NO_LEFT) && (cflag&NO_RIGHT)) continue;
			if (((cflag&NO_LEFT) && sgn>0) || ((cflag&NO_RIGHT) && sgn<0)) continue;
		}
		else if (std::abs(axis.y)==1) { //Can you tell this was copied and pasted?
			if ((cflag&NO_UP) && (cflag&NO_DOWN)) continue;
			if (((cflag&NO_UP) && sgn>0) || ((cflag&NO_DOWN) && sgn<0)) continue;
		}
		else {
			if (cflag&NO_WEIRD) continue;
		}
		if ((diff*sgn)!=0 && diff<std::abs(minDst)) {
			minDst=diff*sgn;
			maxAxis=axis;
		}
	}
	return CollisionResult(maxAxis*minDst, maxSAxis*minSDst);

}

void CollisionManager::RegisterHandle(CollisionHandle *handle) {
	handles.push_back(handle);
	centralSystem->Insert(handle);
	handle->moved = true;
}

std::vector<CollisionInfo> CollisionManager::CheckCollisions(
		CollisionHandle *handle) {
	Collisions collisions = Collisions();
	std::vector<CollisionInfo> collisionInfos = std::vector<CollisionInfo>();
	Collisions temp;
	CollisionHandle* first;
	CollisionHandle* second;
	CollisionInfo info;
	CollisionResult n;
	for (auto it = collisionLayers.begin(); it!=collisionLayers.end(); it++) {
		temp = (*it)->Check(handle);
		for (auto it2 = temp.begin(); it2!=temp.end(); it2++) {
			collisions.push_back(*it2);
		}
	}
	for (auto it = collisions.begin(); it!=collisions.end(); it++) {
		first = (*it).first;
		second = (*it).second;
		n = CheckCollision(first, second);
		if (!n.collision) continue;
		collisionInfos.push_back(CollisionInfo(n, first, second));
	}
	return collisions;
}

void CollisionManager::Update() {
	std::vector<CollisionHandle*> moved = centralSystem->GrabMoved();
	std::vector<CollisionInfo> collisionChecks = std::vector<CollisionInfo>();
	std::vector<CollisionInfo> colls;
	for (auto it = moved.begin(); it!=moved.end(); it++) {
		colls=CheckCollisions(*it);
		for (auto it2 = colls.begin(); it2!=colls.end(); it2++) {
			collisionChecks.push_back(*it2);
		}
		centralSystem->Insert(*it);
	}
	for (auto it = collisionChecks.begin(); it!=collisionChecks.end(); it++) {
		ResolveCollision(*it);
	}
}
