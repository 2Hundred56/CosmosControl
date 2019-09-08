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

float CollisionNode::CostWith(Rect r) {
	float cost = Union(rect, r).Area();
	CollisionNode* n = parent;
	while (parent!=0) {
		cost += Union(parent->rect, r).Area()-(parent->rect).Area();
	}
	return cost;
}

void CollisionTree::InsertNode(CollisionHandle *handle) {
	if (root==0) {
		root=Leaf(0, handle);
		nodes.push_back(root);
		return;
	}
	CollisionNode* sibling = 0;
	for (auto it = nodes.begin(); it!=nodes.end(); it++) {
		sibling=Best((*it), sibling, handle);
	}
	CollisionNode* grandParent = sibling->parent;
	CollisionNode* parent = 0;
	if (grandParent == 0) {
		parent = new CollisionNode(0, sibling, 0, Union(sibling->rect, handle->GetRect()));
		root = parent;
	}
	else {
		parent = new CollisionNode(grandParent, sibling, 0, Union(sibling->rect, handle->GetRect()));
		if (grandParent->leaf1==sibling) {
			grandParent->leaf1=parent;
		}
		else {
			grandParent->leaf2=parent;
		}
	}
	parent->leaf1 = Leaf(parent, handle);
	sibling->parent=parent;
	CollisionNode* index = parent;
	while (index!=0) {
		index->rect=Union(index->leaf1->rect, index->leaf2->rect);
		index=index->parent;
	}
}
