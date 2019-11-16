/*
 * GameObject.h
 *
 *  Created on: Nov 13, 2019
 *      Author: triforce
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
class CentralManager;
class CollisionHandle;
#include <vector>
class GameObject {
public:
	virtual ~GameObject() {

	}
	virtual void InitialUpdate() {

	}
	virtual void GeneralUpdate() {

	}
	virtual void LateUpdate() {

	}

protected:
	CentralManager* manager;
	std::vector<CollisionHandle*> handles;
};

#endif /* GAMEOBJECT_H_ */
