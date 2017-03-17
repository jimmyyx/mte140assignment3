#include <iostream>
#include <stack>
#include <queue>
#include "a3_avl_tree.hpp"

using namespace std;

typedef BinarySearchTree::DataType DataType;

AVLTree::AVLTree () {
	
}

unsigned int AVLTree::depth(Node* n) const{
	BinarySearchTree::Node* cur;
	queue<BinarySearchTree::Node *> q;
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

unsigned int hDiff (BinarySearchTree::Node* left, BinarySearchTree::Node* right){
	return depth(left)-depth(right);
}

bool AVLTree::insert(DataType val){
	BinarySearchTree::insert(val);
}

bool AVLTree::remove(DataType val){
	BinarySearchTree::remove(val);
}
