/*
 * CollisionTerms.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: triforce
 */

#include "CollisionTerms.h"
#include "Shape.h"
#include "IntVector.h"
Projection operator +(Projection p1, Projection p2) {
	return Projection(p1.min + p2.min, p2.max + p2.max);
}

float CollisionNode::CostWith(Rect r) {
	float cost = Union(rect, r).Area();
	CollisionNode* n = parent;
	while (n!=0) {
		cost += Union(parent->rect, r).Area()-(parent->rect).Area();
		n=n->parent;
	}
	return cost;
}

void CollisionTree::Insert(CollisionHandle *handle) {
	if (root==0) {
		root=Leaf(0, handle);
		nodes.push_back(root);
		return;
	}
	CollisionNode* sibling = Sibling(handle);
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

Collisions CollisionTree::Update() {
	std::vector<CollisionNode*> nodes = std::vector<CollisionNode*>();
	std::vector<CollisionHandle*> handles = std::vector<CollisionHandle*>();
	nodes.push_back(root);
	Collisions collisions = Collisions();
	CollisionNode* node;
	CollisionNode* check;
	std::vector<CollisionNode*> checks;
	CollisionHandle* handle;
	while (!nodes.empty()) {
		node=nodes.back();
		nodes.pop_back();
		if (node->handle!=0) {
			if (node->handle->moved) {
				Remove(node);
				handles.push_back(node->handle);
			}
		}
		if (node->leaf1!=0) {
			nodes.push_back(node->leaf1);
		}
		if (node->leaf1!=0) {
			nodes.push_back(node->leaf1);
		}
	}
	while (!handles.empty()) {
		handle = handles.back();
		handles.pop_back();
		checks = std::vector<CollisionNode*>();
		checks.push_back(root);
		while (!checks.empty()) {
			check=checks.back();
			checks.pop_back();
			if (RectOverlap(handle->GetRect(), check->rect)) {
				if (check->handle!=0) {
					collisions.push_back(std::pair<CollisionHandle*, CollisionHandle*>(handle, check->handle));
				}
				if (check->leaf1!=0) {
					checks.push_back(check->leaf1);
				}
				if (check->leaf2!=0) {
					checks.push_back(check->leaf1);
				}
			}
		}
		Insert(handle);
	}
	return collisions;
}

void CollisionTree::Remove(CollisionNode *node) {
	if (node->handle!=0) {
		throw(3);
	}
	if (node->parent->leaf1==node) {
		node->parent->leaf1 = 0;
	}
	if (node->parent->leaf2==node) {
		node->parent->leaf2 = 0;
	}
	node->parent=0;
}

CollisionNode* CollisionTree::Sibling(CollisionHandle *handle) {
	std::vector<CollisionNode*> nodes = std::vector<CollisionNode*>();

	nodes.push_back(root);
	CollisionNode* best = root;
	float maxCost = root->CostWith(handle->GetRect());
	CollisionNode* node;
	float c, low;
	while (!nodes.empty()) {
		node=nodes.back();
		nodes.pop_back();
		c=node->CostWith(handle->GetRect());
		if (c<maxCost) {
			maxCost=c;
			best = node;
		}
		low = handle->GetRect().Area()+node->CostWith(Rect(0,0,0,0))-node->rect.Area();
		if (low<maxCost) {
			if (node->leaf1!=0) {
				nodes.push_back(node->leaf1);
			}
			if (node->leaf2!=0) {
				nodes.push_back(node->leaf2);
			}
		}
	}
	return best;
}

CollisionNode* Leaf(CollisionNode *parent, CollisionHandle *handle) {
	CollisionNode* n = new CollisionNode(parent, 0, 0, handle->GetRect());
	n->handle=handle;
	return n;
}

Rect CollisionHandle::GetRect() {
	return GetShape()->ContainBox()+IntVector(GetPos());
}

CollisionInfo::CollisionInfo(Vector vector){
	normal=vector;
	collision=true;
}

CollisionInfo::CollisionInfo() {
	normal=Vector(0, 0);
	collision=false;
}
