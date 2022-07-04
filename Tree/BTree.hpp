#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include "Exception.h"

#ifdef TREE_BTREE_STRUCT

#endif

#ifdef TREE_BTREE_CLASS

	using std::stack; 
	using std::queue; 
	using std::vector; 

	/* BTNode */
	template <typename DataType>
	BTNode<DataType>::BTNode(void)
	{
		memset(&this->val_, 0, sizeof(DataType)); 
		this->lchild_ = nullptr; 
		this->rchild_ = nullptr; 
	}
	template <typename DataType>
	BTNode<DataType>::BTNode(DataType val, BTNode<DataType>* lchild, BTNode<DataType>* rchild):
		val_(val), 
		lchild_(lchild), 
		rchild_(rchild)
	{

	}
	template <typename DataType>
	BTNode<DataType>::~BTNode(void)
	{

	}

	#if 0
	template <typename DataType>
	DataType BTNode<DataType>::getVal(void) const
	{
		return this->val_; 
	}
	template <typename DataType>
	BTNode<DataType>* BTNode<DataType>::getLchild(void) const
	{
		return this->lchild_; 
	}
	template <typename DataType>
	BTNode<DataType>* BTNode<DataType>::getRchild(void) const
	{
		return this->rchild_; 
	}
	#endif

	/* BTree */
	#if 0
	/*	
	*	enter val to levList in level-order; 
	*	enter node index to inOrdList in in-order; 
	*/
	template <typename DataType>
	BTree<DataType>::BTree(vector<DataType> levList, vector<DataType> inOrdList)
	{
		if (levList.size() != levList.size()) {
			throw MissingTreeNode(levList.size(), levList.size());
		}
		if (levList.empty()) {
			this->root_ = nullptr; 

			return; 
		}


	}
	#endif
	template <typename DataType>
	BTree<DataType>::BTree(vector<DataType> valList, vector<bool> nullList)
	{
		if (valList.size() != nullList.size()) {
			throw MissingTreeNode(valList.size(), nullList.size()); 
		}
		if (valList.empty() || !nullList.at(0)) {
			this->root_ = nullptr; 

			return; 
		}

		this->root_ = new BTNode<DataType>(valList.at(0)); 

		queue<BTNode<DataType>*> que = {};
		que.push(this->root_); 
		BTNode<DataType>* mov = nullptr;
		size_t index = 0; 
		size_t len = valList.size();

		while (index < len && !que.empty()) {
			mov = que.front();

			while (index < len && nullList.at(index) == false) {
				++index; 
			}

			if (2 * index + 1 < len && nullList.at(2 * index + 1)) {
				mov->lchild_ = new BTNode<DataType>(valList.at(2 * index + 1));

				que.push(mov->lchild_);
			}

			if (2 * index + 2 < len && nullList.at(2 * index + 2)) {
				mov->rchild_ = new BTNode<DataType>(valList.at(2 * index + 2));

				que.push(mov->rchild_);
			}

			++index; 
			que.pop(); 
		}
	}
	template <typename DataType>
	BTree<DataType>::BTree(const BTree<DataType>& tree)
	{
		if (tree.isEmpty()) {
			this->root_ = nullptr; 

			return;
		}

		stack<BTNode<DataType>*> newTreeStk = {}; 
		this->root_ = new BTNode<DataType>(tree.root_->val_); 
		BTNode<DataType>* newTreeMov = this->root_;

		stack<BTNode<DataType>*> stk = {};
		BTNode<DataType>* mov = tree.root_;

		while (!stk.empty() || mov != nullptr) {
			if (mov != nullptr) {
				stk.push(mov);
				newTreeStk.push(newTreeMov); 

				mov = mov->lchild_;
				if (mov != nullptr) {
					newTreeMov->lchild_ = new BTNode<DataType>(mov->val_); 
				}
				newTreeMov = newTreeMov->lchild_; 
			}
			else {	// the current nullptr node is not in the stack yet; 
				mov = stk.top();
				mov = mov->rchild_;
				stk.pop();

				newTreeMov = newTreeStk.top(); 
				if (mov != nullptr) {
					newTreeMov->rchild_ = new BTNode<DataType>(mov->val_); 
				}
				newTreeMov = newTreeMov->rchild_; 
				newTreeStk.pop(); 

			}
		}
	}
	template <typename DataType>
	BTree<DataType>::~BTree(void)
	{
		stack<BTNode<DataType>*> stk = {};
		auto inStack = [&stk](BTNode<DataType>* mov) -> void { stk.push(mov); };

		this->preOrdTraversal(inStack); 

		BTNode<DataType>* mov = nullptr; 
		while (!stk.empty()) {
			mov = stk.top(); 
			stk.pop(); 
			delete mov; 
		}
	}

	template <typename DataType>
	bool BTree<DataType>::isEmpty(void) const
	{
		return (this->root_ == nullptr); 
	}

	/*
	*	mode 0: pre-order
	*	mode 1: mid-order
	*	mode 2: post-order
	*	mode 3: level order
	*/
	template <typename DataType>
	void BTree<DataType>::print(unsigned int mode) const
	{
		auto visit = [](BTNode<DataType>* mov) -> void { std::cout << mov->val_ << ' '; };

		switch (mode) {
		case 0:
			std::cout << "前序遍历序列: "; 
			preOrdTraversal(visit); 
			break; 
		case 1:
			std::cout << "中序遍历序列: ";
			inOrdTraversal(visit); 
			break; 
		case 2:
			std::cout << "后序遍历序列: ";
			postOrdTraversal(visit); 
			break; 
		case 3:
			std::cout << "层序遍历序列: ";
			levOrdTraversal(visit); 
			break; 
		default:
			throw InvalidModeTag(mode, 0, 3); 
			break; 
		}
		std::cout << std::endl; 

		return; 
	}

	template <typename DataType>
	BTree<DataType>& BTree<DataType>::operator=(BTree<DataType> tree)
	{
		if (tree.isEmpty()) {
			this->root_ = nullptr;

			return *this;
		}

		stack<BTNode<DataType>*> newTreeStk = {};
		this->root_ = new BTNode<DataType>(tree.root_->val_);
		BTNode<DataType>* newTreeMov = this->root_;

		stack<BTNode<DataType>*> stk = {};
		BTNode<DataType>* mov = tree.root_;

		while (!stk.empty() || mov != nullptr) {
			if (mov != nullptr) {
				stk.push(mov);
				newTreeStk.push(newTreeMov);

				mov = mov->lchild_;
				if (mov != nullptr) {
					newTreeMov->lchild_ = new BTNode<DataType>(mov->val_);
				}
				newTreeMov = newTreeMov->lchild_;
			}
			else {	// the current nullptr node is not in the stack yet; 
				mov = stk.top();
				mov = mov->rchild_;
				stk.pop();

				newTreeMov = newTreeStk.top();
				if (mov != nullptr) {
					newTreeMov->rchild_ = new BTNode<DataType>(mov->val_);
				}
				newTreeMov = newTreeMov->rchild_;
				newTreeStk.pop();

			}
		}

		return *this; 
	}

	template <typename DataType>
	template <typename Function>
	void BTree<DataType>::preOrdTraversal(Function visit) const
	{
		if (this->isEmpty()) {
			return; 
		}

		stack<BTNode<DataType>*> stk = {};
		BTNode<DataType>* mov = this->root_; 

		while (!stk.empty() || mov != nullptr) {
			if (mov != nullptr) {
				stk.push(mov); 

				/* visit node */
				visit(mov); 
				
				mov = mov->lchild_; 
			}
			else {	// the current nullptr node is not in the stack yet; 
				mov = stk.top(); 
				mov = mov->rchild_; 
				stk.pop(); 
			}
		}

		return; 
	}
	template <typename DataType>
	template <typename Function>
	void BTree<DataType>::inOrdTraversal(Function visit) const
	{
		if (this->isEmpty()) {
			return;
		}

		stack<BTNode<DataType>*> stk = {};
		BTNode<DataType>* mov = this->root_;

		while (!stk.empty() || mov != nullptr) {
			if (mov != nullptr) {
				stk.push(mov);
				mov = mov->lchild_;
			}
			else {	// the current nullptr node is not in the stack yet; 
				mov = stk.top();

				/* visit node */
				visit(mov); 

				mov = mov->rchild_;
				stk.pop();
			}
		}

		return;
	}
	template <typename DataType>
	template <typename Function>
	void BTree<DataType>::postOrdTraversal(Function visit) const
	{
		if (this->isEmpty()) {
			return;
		}

		stack<BTNode<DataType>*> stk = {};
		BTNode<DataType>* mov = this->root_;
		// set probe for most recently visited node; 
		BTNode<DataType>* rtag = nullptr; 

		while (!stk.empty() || mov != nullptr) {
			if (mov != nullptr) {
				stk.push(mov);
				mov = mov->lchild_;
			}
			else {	// the current nullptr node is not in the stack yet; 
				mov = stk.top();
				if (mov->rchild_ != nullptr && mov->rchild_ != rtag) {
					mov = mov->rchild_;
				}
				else {
					/* visit node */
					visit(mov); 

					stk.pop();
					rtag = mov; 
					mov = nullptr; 
				}
			}
		}

		return;
	}
	template <typename DataType>
	template <typename Function>
	void BTree<DataType>::levOrdTraversal(Function visit) const
	{
		if (this->isEmpty()) {
			return; 
		}

		queue<BTNode<DataType>*> que = {};
		que.push(this->root_); 
		BTNode<DataType>* mov = nullptr; 
		visit(this->root_); 

		while (!que.empty()) {
			size_t len = que.size(); 

			for (size_t index = 0; index < len; ++index) {
				mov = que.front(); 

				if (mov->lchild_ != nullptr) {
					/* visit lchild node */
					visit(mov->lchild_); 

					que.push(mov->lchild_);
				}
				if (mov->rchild_ != nullptr) {
					/* visit rchild node */
					visit(mov->rchild_);

					que.push(mov->rchild_);
				}

				que.pop(); 
			}
		}
	}

#endif