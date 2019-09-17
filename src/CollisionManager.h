/*
 * CollisionManager.h
 *
 *  Created on: Sep 8, 2019
 *      Author: triforce
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_
class BroadPhase;
class CollisionManager {
public:
	CollisionManager();
	virtual ~CollisionManager();
	CollisionInfo CheckCollision(CollisionHandle* h1, CollisionHandle* h2);
	void RegisterHandle(CollisionHandle* handle);
protected:
	std::vector<>
};

#endif /* COLLISIONMANAGER_H_ */
