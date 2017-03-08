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

void deleteTree (BinarySearchTree::Node* cur){
	//pre, have not checked either
	if (cur->left){
		deleteTree (cur->left);
	}
	//in, checked every left child
	if (cur->right){
		deleteTree (cur->right);
	}
	//post, checked every left and right child
	delete cur;
	cur=NULL;
}

BinarySearchTree::~BinarySearchTree(){
	if (root_){
		deleteTree(root_);	
	}
	
}

// Returns the number of nodes in the tree. 
unsigned int BinarySearchTree::size() const{
	return size_;
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

//int recurDepth (BinarySearchTree::Node* cur) {
//	if (cur->left){
//		recurDepth (cur->left);
//	}
//	if (cur->right){
//		recurDepth (cur->right);
//	}
//	return BinarySearchTree::getNodeDepth(cur);
//}

unsigned int BinarySearchTree::depth() const{
	Node* cur = root_;
	int maxDepth=0;
	
	
	//return recurDepth(root_);
}
// You can print the tree in whatever order you prefer. However, methods such 
// as in-order or level-order traversal could be the most useful for debugging.

void recurPrint(BinarySearchTree::Node* cur) {
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
		if (cur->left&&cur->val>val){
			//left
			cur=cur->left;
		}else if (cur->right&&cur->val<val){
			//right
			cur=cur->right;
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
	Node* newNode=new Node(val);
	if (!root_){
		root_=newNode;
		size_++;
		return true;
	}
	Node* cur = root_;
	while (cur->left||cur->right){
		if (cur->left->val==val || cur->right->val==val){
			return false;
		}
		if (cur->left&&cur->val>val){
			//left
			cur=cur->left;
		}else if (cur->right&&cur->val<val){
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
	size_++;
	return true;

}
// Removes the node with the value val from the tree. Returns true if successful, 
// and false otherwise.
bool BinarySearchTree::remove(DataType val){
	if (size_==0){
		return false;
	}
	if (!exists(val)){
		return false;
	}
	
	Node* cur = root_;
	Node* removeNode;
	if (root_->val==val){
		//root is val
		if (size_==1){
			size_--;
			delete this;
			return true;
		} else if (!cur->left){
			// no left, must have a right, since size>1
			root_=cur->right;
			delete cur;
			cur=NULL;
		}else if (!(cur->left)->right){
			//if root->left doesnt have a right
			cur->left->right=cur->right;
			root_=cur->left;
			delete cur;
			cur=NULL;
		} else {
			//find parent of max left
			cur=cur->left;
			while(cur->right->right){
				cur=cur->right;
			}
			Node* deleteNode=cur->right;
			root_->val=cur->right->val;
			if (cur->right->left){
				removeNode = cur->right;
				cur->right=removeNode->left;
				delete removeNode;
				removeNode=NULL;
			}
		}
		size_--;
		return true;
	}
	
	//find val
	Node* pVal=root_;//parent of val
	//removeNode is node to be removed
	
	val>root_->val?removeNode=root_->right:removeNode=root_->left;
	
	
	while (removeNode->val!=val){
		if(val>removeNode->val){
			pVal=removeNode;
			removeNode=removeNode->right;
		}else{
			pVal=removeNode;
			removeNode=removeNode->left;
		}
	}
	
	bool childLeft = pVal->val>val;
	if (childLeft){
		if (!removeNode->left && !removeNode->right){ // no left and no right
			pVal->left=NULL;
		}else if (!removeNode->left){ // only right
			pVal->left=removeNode->right;
		}else if (!removeNode->right){ // only left
			pVal->left=removeNode->left;
		}else{ // both left and right
			//find parent of max of left subtree
			pVal=removeNode->left;
			while(pVal->right->right){
				pVal=pVal->right;
			}
			// cur is parent of max left
			
			removeNode->val=pVal->right->val;
			removeNode=pVal->right;
			if (removeNode->left){
				pVal->right=removeNode->left;
			}
		}
	}else {
		if (!removeNode->left && !removeNode->right){ // no left and no right
			pVal->right=NULL;
		}else if (!removeNode->left){ // only right
			pVal->right=removeNode->right;	
		}else if (!removeNode->right){ // only left
			pVal->right=removeNode->left;
		}else{
			//find parent of max of left subtree
			pVal=removeNode->left;
			while(pVal->right->right){
				pVal=pVal->right;
			}
			// cur is parent of max left
			
			removeNode->val=pVal->right->val;
			removeNode=pVal->right;
			if (removeNode->left){
				pVal->right=removeNode->left;
			}
		}
	delete removeNode;
	removeNode=NULL;
	//if has left and right	
	}
}
// Update the avlBalance starting at node n
void BinarySearchTree::updateNodeBalance(Node* n){
}


