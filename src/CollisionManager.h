/*
 * CollisionManager.h
 *
 *  Created on: Sep 8, 2019
 *      Author: triforce
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_
class Shape;
class Vector;
class CollisionInfo;
class CollisionManager {
public:
	CollisionManager();
	virtual ~CollisionManager();
	CollisionInfo CheckCollision(CollisionHandle* h1, CollisionHandle* h2);
};

#endif /* COLLISIONMANAGER_H_ */
