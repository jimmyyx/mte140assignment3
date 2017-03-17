#include <iostream>
#include <stack>
#include <queue>
#include "a3_avl_tree.hpp"

using namespace std;

typedef BinarySearchTree::DataType DataType;

AVLTree::Node* AVLTree::parentOf (Node* n){
	if (getRootNode()==n){
		return n;
	}
	Node* cur = getRootNode();
	while ((cur->left->val != n->val) && (cur->right->val != n->val)){
		cur->val > n->val ? cur=cur->left : cur=cur->right;
	}
	return cur;
}

void AVLTree::L (Node* n){
	
}

void AVLTree::R (Node* n){
	
}

void AVLTree::LR (Node* n){
	
}

void AVLTree::RL (Node* n){
	
}


AVLTree::Node* AVLTree::nodePointer(DataType val) {
	Node* cur = getRootNode();
	while (cur->val!=val){
		if (cur->left&&cur->val>val){
			//left
			cur=cur->left;
		}else if (cur->right&&cur->val<val){
			//right
			cur=cur->right;
		}
	}
	return cur;
}

int AVLTree::getNodeDepth(Node* n) {
	int nodeDepth=0;
	Node* cur = getRootNode();
	while (cur->val!=n->val){
		if (cur->val>n->val){
			//left
			cur=cur->left;
			nodeDepth++;
		}else if (cur->val<n->val){
			//right
			cur=cur->right;
			nodeDepth++;
		}
	}
	return nodeDepth;
}

int AVLTree::depth(Node* n) {
	
	Node* cur;
	queue<Node *> q;
	int maxD=0;
	q.push(n);

	while (!q.empty()){
		cur=q.front();
		q.pop();
		maxD=std::max(maxD, getNodeDepth(cur));
		if (cur->left){
			q.push(cur->left);
		}
		if (cur->right){
			q.push(cur->right);
		}
	}
	return maxD;
}

int AVLTree::hDiff (Node* n){	
	if (n->left){
		if (n->right){
			return depth(n->left)-depth(n->right);
		}
		return depth(n->left);
	}
	if (n->right){
		return 0-depth(n->right);
	}
	return 0;
}

bool AVLTree::insert(DataType val){
	if (!BinarySearchTree::insert(val)){
		return false;
	}
	
	if (hDiff(nodePointer(val)) < -1){
		//rotate left
	}else if  (hDiff(nodePointer(val)) > 1){
		//rotate right
	}
}

bool AVLTree::remove(DataType val){
	return BinarySearchTree::remove(val);
}
