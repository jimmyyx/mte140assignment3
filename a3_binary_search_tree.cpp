 #include <iostream>
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
	Node* cur=root;
	while (cur->left->left){
		cur=cur->left;
	}
	while (cur->right->right){
		cur=cur->right;
	}
	
}

// Returns the number of nodes in the tree. 
unsigned int BinarySearchTree::size() const{
	return size_;
}
// Returns the maximum value of a node in the tree. You can assume that 
// this function will never be called on an empty tree.
DataType BinarySearchTree::max() const{
	Node* cur=root;
	while (cur->right){
		cur=cur->right;
	}
	return cur;
}
// Returns the minimum value of a node in the tree. You can assume that 
// this function will never be called on an empty tree.
DataType BinarySearchTree::min() const{
	Node* cur=root;
	while (cur->left){
		cur=cur->left;
	}
	return cur;
}
// Returns the maximum depth of the tree. A tree with only the root node has a 
// depth of 0. You can assume that this function will never be called on an 
// empty tree.

int BinarySearchTree::getNodeDepth(Node* n) const{
	//value = n->value
	int nodeDepth=0;
	Node* cur = root_;
	while (&cur!=&n){
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

int recurDepth (Node* cur) const{
	if (cur->left){
		recurDepth (cur->left);
	}
	if (cur->right){
		recurDepth (cur->right);
	}
	return getNodeDepth(cur);
}

unsigned int BinarySearchTree::depth() const{
	return recurDepth(root_);
}
// You can print the tree in whatever order you prefer. However, methods such 
// as in-order or level-order traversal could be the most useful for debugging.

void recurPrint(Node* cur) const{
	//pre, have not checked either
	if (cur->left){
		recurPrint (cur->left);
	}
	//in, checked every left child
	cout<<cur->val<<", ";
	if (cur->right){
		recurPrint (cur->right);
	}
	//post, checked every left and right child
}

void BinarySearchTree::print() const{
	recurPrint(root_);
	cout<<endl;
}
// Returns true if a node with the value val exists in the tree; otherwise, 
// it returns false.
bool BinarySearchTree::exists(DataType val) const{
	Node* cur = root_;
	while (cur->val!=val){
		if (!cur->left&&!cur->right){
			return false;
		}
		if (cur->left&&cur->val>n->val){
			//left
			cur=cur->left;
		}else if (cur->right&&cur->val<n->val){
			//right
			cur=cur->right;
		}
	}
	return true;
}
// Returns a pointer to the root node
Node* BinarySearchTree::getRootNode(){
	return root_;
}
// Returns the root node pointer address
Node** BinarySearchTree::getRootNodeAddress(){
	return &root_;
}

// Inserts the value val into the tree. Returns false if val already exists in 
// the tree, and true otherwise.
bool BinarySearchTree::insert(DataType val){
	Node* cur = root_;
	Node* newNode=new Node(val);
	while (cur->left||cur->right){
		if (cur->left==val || cur->right==val){
			return false;
		}
		if (cur->left&&cur->val>n->val){
			//left
			cur=cur->left;
		}else if (cur->right&&cur->val<n->val){
			//right
			cur=cur->right;
		}
	}
	if (cur->val>val){
		//left
		cur->left=newNode;
		return true;
	}
	//right
	cur->right=newNode;
	return true;
	
}
// Removes the node with the value val from the tree. Returns true if successful, 
// and false otherwise.
bool BinarySearchTree::remove(DataType val){
	
}
// Update the avlBalance starting at node n
void BinarySearchTree::updateNodeBalance(Node* n);


