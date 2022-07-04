#ifndef TREE_BTREE_H_
#define TREE_BTREE_H_

/* Binary Tree */

#define TREE_BTREE_BINARYTREE 2

/* Structure binary tree */
#if TREE_BTREE_BINARYTREE == 1
#define TREE_BTREE_STRUCT
	typedef int DataType; 
	typedef struct BTree {
		DataType val; 
		BTree* lchild; 
		BTree* rchild; 
	} BTree;

#endif

/* Class binary tree */
#if TREE_BTREE_BINARYTREE == 2
#define TREE_BTREE_CLASS

#include <vector>

	using std::vector; 

	template <typename DataType>
	class BTree; // prototype for declaring friend in BTNode; 

	template <typename DataType>
	class BTNode
	{
	public:
		BTNode(void); 
		BTNode(DataType val, BTNode<DataType>* lchild = nullptr, BTNode<DataType>* rchild = nullptr);
		~BTNode(void);
		
		#if 0
		DataType getVal(void) const; 
		#endif 

		friend class BTree<DataType>;

	private:
		DataType val_; 
		BTNode<DataType>* lchild_; 
		BTNode<DataType>* rchild_; 
	};

	template <typename DataType>
	class BTree
	{
	public:
		#if 0
		/*	
		*	enter val to levList in level-order; 
		*	enter node index to inOrdList in in-order; 
		*/
		BTree(vector<DataType> levList = {}, vector<DataType> inOrdList = {});
		
		#endif
		BTree(vector<DataType> valList = {}, vector<bool> nullList = {}); 
		BTree(const BTree<DataType>& tree); // Copy constructor; 
		~BTree(void); 

		bool isEmpty(void) const; 

		/*
		*	mode 0: pre-order
		*	mode 1: mid-order
		*	mode 2: post-order
		*	mode 3: level order
		*/
		void print(unsigned int mode = 0) const; 

		BTree<DataType>& operator=(BTree<DataType> tree); 

	private:
		BTNode<DataType>* root_; 

		template <typename Function>
		void preOrdTraversal(Function visit) const;
		template <typename Function>
		void inOrdTraversal(Function visit) const;
		template <typename Function>
		void postOrdTraversal(Function visit) const;
		template <typename Function>
		void levOrdTraversal(Function visit) const;
	};

#endif

	/* Implementations */
#include "BTree.hpp"

#endif