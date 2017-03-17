#ifndef A3_AVL_TREE_HPP
#define A3_AVL_TREE_HPP

#include "a3_binary_search_tree.hpp"

class AVLTree: public BinarySearchTree
{
public:
	typedef int DataType;
	
	// Overriden insert and remove functions 
	// Do not modify these definitions
    bool insert(DataType val);
    bool remove(DataType val);
    


	// Define additional functions and attributes that you need below
	int getNodeDepth(Node* n);
	int hDiff (Node* n);
	int depth(Node* n);
	
	void L (Node* n);
	void R (Node* n);
	void LR (Node* n);
	void RL (Node* n);
	Node* nodePointer (DataType val) ;
	Node* parentOf (Node* n);
	
private:
	 friend class BinarySearchTree;
};
#endif

