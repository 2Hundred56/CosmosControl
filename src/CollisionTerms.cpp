/*
 * CollisionTerms.cpp
 *
 *  Created on: Sep 8, 2019
 *      Author: triforce
 */

#include "CollisionTerms.h"
#include "IntVector.h"
#include <algorithm>
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

Collisions CollisionTree::Check(CollisionHandle* handle) {
	Collisions collisions = Collisions();
	CollisionNode* node;
	CollisionNode* check;
	std::vector<CollisionNode*> checks;
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
	return collisions;
}

void CollisionTree::Remove(CollisionNode *node) {
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
	return GetShape()->ContainBox()+GetPos();
}

CollisionInfo::CollisionInfo(CollisionResult result, CollisionHandle* h1, CollisionHandle* h2) : result(result), h1(h1), h2(h2){
}

std::set<Vector> AABB::Axes(Shape*, Vector vector) {
	std::set<Vector> axes;
	axes.insert(Vector(0, 1));
	axes.insert(Vector(1, 0));
	return axes;
}

Projection AABB::Proj(Vector axis) {
	float a = projection(Vector(-hw, -hh), axis);
	float b = projection(Vector(hw, -hh), axis);
	float c = projection(Vector(-hw, hh), axis);
	float d = projection(Vector(hw, hh), axis);
	return Projection(std::min(std::min(a, b), std::min(c, d)), std::max(std::max(a, b), std::max(c, d)));
}

Rect AABB::ContainBox() {
	return Rect(-hw, -hh, hw*2, hh*2);
}

AABB::AABB(float hw, float hh) : hw(hw), hh(hh){
}

TestHandle::TestHandle(Vector p, Shape *s) : pos (p), shape(s) {
}

Shape* TestHandle::GetShape() {
	return shape;
}

Vector TestHandle::GetPos() {
	return pos;
}

CollisionResult::CollisionResult(Vector vector, Vector sn) {
	normal=vector;
	slopeNormal=sn;
	collision=true;
}

CollisionResult::CollisionResult() {
	collision=false;
}

std::vector<CollisionHandle*> CollisionTree::GrabMoved() {
	std::vector<CollisionHandle*> handles = std::vector<CollisionHandle*>();
	std::vector<CollisionNode*> unprocessedNodes = std::vector<CollisionNode*>();
	unprocessedNodes.push_back(root);
	CollisionNode* node;
	while (!unprocessedNodes.empty()) {
		node=unprocessedNodes.back();
		unprocessedNodes.pop_back();
		if (node->handle==0) {
			if (node->leaf1==0 && node->leaf2==0) {
				Remove(node);
			}
			if (node->leaf1!=0) {
				unprocessedNodes.push_back(node->leaf1);
			}
			if (node->leaf2!=0) {
				unprocessedNodes.push_back(node->leaf2);
			}
		}
		else {
			handles.push_back(node->handle);
		}
	}
	return handles;
}

CollisionTree::CollisionTree() {
	root=0;
}
