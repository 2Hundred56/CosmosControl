/*
 * CollisionTree.h
 *
 *  Created on: Nov 1, 2019
 *      Author: triforce
 */

#ifndef COLLISIONTREE_H_
#define COLLISIONTREE_H_
#include "CollisionTerms.h"
class CollisionHandle;

class CollisionNode {
public:
	Rect rect;
	CollisionNode* leaf1;
	CollisionNode* leaf2;
	int nodeID;
	CollisionNode* parent;
	CollisionHandle* handle = 0;
	CollisionNode(CollisionNode* parent, CollisionNode* leaf1, CollisionNode* leaf2, Rect rect, int nodeID) : parent(parent), leaf1(leaf1), leaf2(leaf2), rect(rect), nodeID(nodeID){

	}
	float CostWith(Rect r);
};
std::ostream& operator<<(std::ostream&, CollisionNode*);
class CollisionTree : public BroadPhase{
public:
	int nodeID;
	CollisionTree();
	std::vector<CollisionNode*> nodes;
	CollisionNode* root;
	void Insert(CollisionHandle* handle);
	void Remove(CollisionNode* node);
	CollisionNode* Leaf (CollisionNode* parent, CollisionHandle *handle);
	Collisions Check(CollisionHandle* handle);
	CollisionNode* Sibling(CollisionHandle* handle);
	std::vector<CollisionHandle*> GrabMoved();
};
std::ostream& operator<<(std::ostream&, CollisionTree*);



#endif /* COLLISIONTREE_H_ */
