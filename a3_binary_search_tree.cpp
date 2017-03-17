#include <iostream>
#include <stack>
#include <queue>
#include "a3_binary_search_tree.hpp"

using namespace std;

typedef BinarySearchTree::DataType DataType;

BinarySearchTree::Node::Node(DataType newval){
	val=newval;
	left=NULL;
	right=NULL;
}

BinarySearchTree::BinarySearchTree(){
	root_=NULL;
	size_=0;
}
// Destructor of the class BinarySearchTree. It deallocates the memory 
// space allocated for the binary search tree. 

BinarySearchTree::~BinarySearchTree(){
//	if (root_){
//		deleteTree(root_);	
//		delete root_;
//	}
//	root_=NULL;
}

// Returns the number of nodes in the tree. 
unsigned int BinarySearchTree::size() const{
	return size_;
}

//Returns a point to the parent of the maxLeft
BinarySearchTree::Node* pMaxLeft (BinarySearchTree::Node* n, BinarySearchTree::Node* root_){
	//never call this function on a tree with size <=1
	if (!n->left && !n->right){
		//return parent of n
		BinarySearchTree::Node* cur = root_;
		while (cur->left || cur->right){
			if (cur->val>n->val){
				//cur->left must exist
				if (cur->left->val==n->val){
					return cur;
				}
				cur=cur->left;
			} else{
				if (cur->right->val==n->val){
					return cur;
				}
				cur=cur->right;
			}
		}
	}
	if (!n->left){
		return n;
	}
	if (n->left->right){
		BinarySearchTree::Node* cur = n->left;
		while (cur->right->right){
			cur=cur->right;
		}
		return cur;
	}
	return n;
}

//Returns a pointer to the max value in the left subtree of a given node, if parameter does not have a left child, return the right child
BinarySearchTree::Node* maxLeft (BinarySearchTree::Node* n){
	if (!n->left && !n->right){
		return n;
	}else if (n->left){
		n = n->left;
		while (n->right){
			n=n->right;
		}
		return n;
	}
	return n->right;
}


// Returns the maximum value of a node in the tree. You can assume that 
// this function will never be called on an empty tree.
DataType BinarySearchTree::max() const{
	Node* cur=root_;
	while (cur->right){
		cur=cur->right;
	}
	return cur->val;
}
// Returns the minimum value of a node in the tree. You can assume that 
// this function will never be called on an empty tree.
DataType BinarySearchTree::min() const{
	Node* cur=root_;
	while (cur->left){
		cur=cur->left;
	}
	return cur->val;
}

// Returns the maximum depth of the tree. A tree with only the root node has a 
// depth of 0. You can assume that this function will never be called on an 
// empty tree.

int BinarySearchTree::getNodeDepth(Node* n) const{
	int nodeDepth=0;
	Node* cur = root_;
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

unsigned int BinarySearchTree::depth() const{
	Node* cur;
	queue<Node *> q;
	int maxD=0;
	q.push(root_);

	while (!q.empty()){
		cur=q.front();
		q.pop();
		maxD=std::max(maxD,getNodeDepth(cur));
		if (cur->left){
			q.push(cur->left);
		}
		if (cur->right){
			q.push(cur->right);
		}
	}
	return maxD;
}

// You can print the tree in whatever order you prefer. However, methods such 
// as in-order or level-order traversal could be the most useful for debugging.


void BinarySearchTree::print() const{
	if (root_){
		Node* cur=root_;
		stack<Node *> s;
		
		while (!s.empty() || cur){
			if (cur){
				s.push(cur);
				cur=cur->left;
			}else{
				cout<<s.top()->val<<", ";
				cur=(s.top()->right);
				s.pop();
			}
		}
	}else{
		cout<<"Empty tree";
	}
	cout<<endl;
}
// Returns true if a node with the value val exists in the tree; otherwise, 
// it returns false.
bool BinarySearchTree::exists(DataType val) const{
	if (!root_){
		return false;
	}
	Node* cur = root_;
	while (cur->val!=val){
		if (cur->left&&cur->val>val){
			//left
			cur=cur->left;
		}else if (cur->right&&cur->val<val){
			//right
			cur=cur->right;
		}else{
			return false;
		}
	}
	return true;
}
// Returns a pointer to the root node
BinarySearchTree::Node* BinarySearchTree::getRootNode(){
	return root_;
}
// Returns the root node pointer address
BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress(){
	return &root_;
}

// Inserts the value val into the tree. Returns false if val already exists in 
// the tree, and true otherwise.
bool BinarySearchTree::insert(DataType val){
	if (exists(val)){
		return false;
	}
	Node* newNode=new Node(val);
	if (!root_){
		root_=newNode;
	}else {
		Node* cur = root_;
		while (cur->left && cur->val>val || cur->right && cur->val<val){
			cur->left && cur->val>val ? cur=cur->left : cur=cur->right;
		}
		cur->val>val?cur->left=newNode:cur->right=newNode;
	}
	size_++;
	return true;
}
// Removes the node with the value val from the tree. Returns true if successful, 
// and false otherwise.
bool BinarySearchTree::remove(DataType val){
	//implement recursive or while loop to remove nodes that have children
	if (size_==0 || !exists(val)){
		return false;
	}
	Node* cur = root_;
	if (size_==1){
		size_--;
		delete cur;
		root_=NULL;
		return true;
	}
	
	if (root_->val!=val){
		while(cur->val!=val){
			cur->val>val? cur=cur->left: cur=cur->right;
		}
	}

	Node* removeNode=maxLeft(cur);
	Node* pVal=pMaxLeft(cur,root_);//parent of removeNode
	bool childLeft = (removeNode->val < pVal->val);
	DataType temp = cur->val;
	cur->val=removeNode->val;
	removeNode->val=temp;
	
	while (removeNode->left || removeNode->right){
		cur=removeNode;
		removeNode=maxLeft(cur);
		pVal=pMaxLeft(cur, root_);
		bool childLeft = (removeNode->val < pVal->val);
		DataType temp = cur->val;
		cur->val=removeNode->val;
		removeNode->val=temp;
	}
	childLeft ? pVal->left=NULL : pVal->right=NULL;
	
	delete removeNode;
	removeNode=NULL;
	size_--;
	return true;
}

// Update the avlBalance starting at node n
void BinarySearchTree::updateNodeBalance(Node* n){
	
}


