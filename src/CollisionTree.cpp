/*
 * CollisionTree.cpp
 *
 *  Created on: Nov 1, 2019
 *      Author: triforce
 */
#include "CollisionTree.h"
std::vector<CollisionHandle*> CollisionTree::GrabMoved() {
	std::vector<CollisionHandle*> handles = std::vector<CollisionHandle*>();
	std::vector<CollisionNode*> unprocessedNodes = std::vector<CollisionNode*>();
	if (root==0) return handles;
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
		else if (node->handle->moved>0){
			Remove(node);
			handles.push_back(node->handle);
		}
	}
	return handles;
}

std::ostream & operator <<(std::ostream &out,
		CollisionTree* tree) {
	std::vector<CollisionNode*> unprocessedNodes = std::vector<CollisionNode*>();
	unprocessedNodes.push_back(tree->root);
	CollisionNode* node;
	while (!unprocessedNodes.empty()) {
		node=unprocessedNodes.back();
		out<<node<<" ";
		unprocessedNodes.pop_back();
		if (node->leaf1!=0) {
			unprocessedNodes.push_back(node->leaf1);
		}
		if (node->leaf2!=0) {
			unprocessedNodes.push_back(node->leaf2);
		}
	}
	return out;
}

CollisionTree::CollisionTree() {
	nodeID=0;
	root=0;
}

CollisionInfo CollisionInfo::Reverse() {
	return CollisionInfo(CollisionResult(-result.normal, -result.slopeNormal), h2, h1);
}

std::ostream& operator <<(std::ostream &out,
		CollisionNode* node) {
	out<<node->nodeID;
	if (node->leaf1!=0) {
		out<<node->leaf1->nodeID;
	}
	else {
		out<<"-";
	}
	if (node->leaf2!=0) {
		out<<node->leaf2->nodeID;
	}
	else {
		out<<"-";
	}
	if (node->handle!=0) {
		out<<node->handle->ID;
	}
	else {
		out<<"-";
	}
	return out;
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
		parent = new CollisionNode(0, sibling, 0, Union(sibling->rect, handle->GetRect()), nodeID++);
		root = parent;
	}
	else {
		parent = new CollisionNode(grandParent, sibling, 0, Union(sibling->rect, handle->GetRect()), nodeID++);
		parent->nodeID=nodeID++;
		if (grandParent->leaf1==sibling) {
			grandParent->leaf1=parent;
		}
		else {
			grandParent->leaf2=parent;
		}
	}
	parent->leaf2 = Leaf(parent, handle);
	sibling->parent=parent;
	CollisionNode* index = parent;
	while (index!=0) {
		if (index->leaf1!=0 && index->leaf2!=0) {
			index->rect=Union(index->leaf1->rect, index->leaf2->rect);
		}
		else if (index->leaf2!=0) {
			index->rect=index->leaf2->rect;
		}
		else if (index->leaf1!=0) {
			index->rect=index->leaf1->rect;
		}
		else {
			index->rect=Rect(0,0,0,0);
		}
		index=index->parent;
	}
}

Collisions CollisionTree::Check(CollisionHandle* handle) {
	Collisions collisions = Collisions();
	if (root==0) return collisions;
	CollisionNode* node;
	CollisionNode* check;
	std::vector<CollisionNode*> checks;
	checks = std::vector<CollisionNode*>();
	checks.push_back(root);
	while (!checks.empty()) {
		check=checks.back();
		checks.pop_back();
		if (RectOverlap(handle->GetRect(), check->rect)) {
			if (check->leaf1==0 && check->handle==0 && check->leaf2==0) {
				Remove(check);
			}
			if (check->handle!=0) {
				collisions.push_back(std::pair<CollisionHandle*, CollisionHandle*>(handle, check->handle));
			}
			if (check->leaf1!=0) {
				checks.push_back(check->leaf1);
			}
			if (check->leaf2!=0) {
				checks.push_back(check->leaf2);
			}
		}
	}
	return collisions;
}

void CollisionTree::Remove(CollisionNode *node) {
	if (node->parent==0) {
		root=0;
		return;
	}
	if (node->parent->leaf1==node) {
		node->parent->leaf1 = 0;
		if (node->parent->leaf2==0) {
			Remove(node->parent);
		}
	}
	if (node->parent->leaf2==node) {
		node->parent->leaf2 = 0;
		if (node->parent->leaf1==0) {
			Remove(node->parent);
		}
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

CollisionNode* CollisionTree::Leaf(CollisionNode *parent, CollisionHandle *handle) {
	CollisionNode* n = new CollisionNode(parent, 0, 0, handle->GetRect(), nodeID++);
	n->handle=handle;
	return n;
}


