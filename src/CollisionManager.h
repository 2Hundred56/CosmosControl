/*
 * CollisionManager.h
 *
 *  Created on: Sep 8, 2019
 *      Author: triforce
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_
#include <vector>
class CollisionTree;
class CollisionLayer;
class CollisionInfo;
class CollisionResult;
class CollisionHandle;
class CollisionManager {
public:
	CollisionManager();
	virtual ~CollisionManager();
	CollisionResult CheckCollision(CollisionHandle* h1, CollisionHandle* h2, int cflag = 0);
	void RegisterHandle(CollisionHandle* handle);
	std::vector<CollisionInfo> CheckCollisions(CollisionHandle* h1);
	void Update();
	void ResolveCollision(CollisionInfo i);
protected:
	CollisionTree* centralSystem;
	std::vector<CollisionLayer*> collisionLayers;
	std::vector<CollisionHandle*> handles;
	std::vector<CollisionHandle*> waitlist;
	int ID;
};

#endif /* COLLISIONMANAGER_H_ */
