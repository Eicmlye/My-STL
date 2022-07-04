#include <iostream>
#include <stack> 
#include <queue>
#include <vector> /* std::pair */
#include "Exception.h"
#include "Graph.h"

using std::stack;
using std::queue; 
using std::pair; 

/* -------- Edge -------- */
template <typename EdgeType>
Edge<EdgeType>::Edge(size_t index, size_t jndex, \
	Edge<EdgeType>* inext, Edge<EdgeType>* jnext, bool flag) :
	index_(index),
	jndex_(jndex),
	inext_(inext),
	jnext_(jnext),
	flag_(flag)
{
	memset(&(this->val_), 0, sizeof(EdgeType));
}
template <typename EdgeType>
Edge<EdgeType>::~Edge(void)
{

}

template <typename EdgeType>
inline EdgeType Edge<EdgeType>::getVal(void) const
{
	return this->val_; 
}
template <typename EdgeType>
inline Edge<EdgeType>*& Edge<EdgeType>::getNext(size_t vertex)
{
	return (this->index_ == vertex) ? (this->inext_) : (this->jnext_);
}
template <typename EdgeType>
inline size_t Edge<EdgeType>::getOppVtx(size_t vertex)
{
	return (this->index_ == vertex) ? (this->jndex_) : (this->index_);
}
template <typename EdgeType>
inline bool Edge<EdgeType>::getFlag(void) const
{
	return this->flag_; 
}
template <typename EdgeType>
inline void Edge<EdgeType>::setFlag(bool newFlag)
{
	this->flag_ = newFlag; 

	return; 
}

/* -------- GNode -------- */
template <typename GNodeType, typename EdgeType>
GNode<GNodeType, EdgeType>::GNode(void) :
	edge_(nullptr), 
	next_(nullptr), 
	flag_(false)
{
	memset(&(this->val_), 0, sizeof(GNodeType)); 
}
template <typename GNodeType, typename EdgeType>
GNode<GNodeType, EdgeType>::GNode(GNodeType val, Edge<EdgeType>* edge, GNode<GNodeType, EdgeType>* next, bool flag) :
	val_(val),
	edge_(edge),
	next_(next), 
	flag_(flag)
{

}
template <typename GNodeType, typename EdgeType>
GNode<GNodeType, EdgeType>::~GNode(void)
{

}

template <typename GNodeType, typename EdgeType>
inline GNodeType GNode<GNodeType, EdgeType>::getVal(void) const
{
	return this->val_; 
}
template <typename GNodeType, typename EdgeType>
inline bool GNode<GNodeType, EdgeType>::getFlag(void) const
{
	return this->flag_;
}
template <typename GNodeType, typename EdgeType>
inline void GNode<GNodeType, EdgeType>::setFlag(bool newFlag)
{
	this->flag_ = newFlag;

	return;
}
template <typename GNodeType, typename EdgeType>
inline bool GNode<GNodeType, EdgeType>::isIsolated(void) const
{
	return this->edge_ == nullptr; 
}

/* -------- Undirected Graph -------- */
template <typename GNodeType, typename EdgeType>
UDGraph<GNodeType, EdgeType>::UDGraph(GNodeType val, bool weighted) :
	weighted_(weighted)
{
	GNode<GNodeType, EdgeType>* newNode = new GNode<GNodeType, EdgeType>(val);
	this->node_ = newNode; 
}
template <typename GNodeType, typename EdgeType>
UDGraph<GNodeType, EdgeType>::~UDGraph(void)
{
	GNode<GNodeType, EdgeType>* mov = this->node_;
	size_t nodetag = 0; 
	Edge<EdgeType>* cache = nullptr;
	Edge<EdgeType>* target = nullptr;

	while (mov != nullptr) {
		target = mov->edge_; 
		while (target != nullptr) {
			cache = target->getNext(nodetag); 
			this->cut(target->index_, target->jndex_); 
			target = cache; 
		}

		++nodetag; 
		mov = mov->next_; 
	}

	mov = this->node_; 
	while (mov != nullptr) {
		this->node_ = mov->next_; 
		delete mov; 
		mov = this->node_; 
	}
}

template <typename GNodeType, typename EdgeType>
inline bool UDGraph<GNodeType, EdgeType>::isWeighted(void) const
{
	return this->weighted_; 
}
template <typename GNodeType, typename EdgeType>
bool UDGraph<GNodeType, EdgeType>::isEdge(size_t head, size_t tail) const
{
	// check the existence of nodes required; 
	GNode<GNodeType, EdgeType>* cache = &this->at(head); 
	Edge<EdgeType>* mov = cache->edge_;
	if (tail > head) {
		for (size_t index = 0; index < tail - head; ++index) {
			cache = cache->next_;
			if (cache == nullptr) {
				throw IndexOverflow(head + index + 1, tail); 
			}
		}
	}

	if (tail == head) {
		return false; 
	}

	while (mov != nullptr) {
		if (mov->getOppVtx(head) >= tail) {
			return (mov->getOppVtx(head) == tail); 
		}
		mov = mov->getNext(head);
	}

	return false; 
}

template <typename GNodeType, typename EdgeType>
size_t UDGraph<GNodeType, EdgeType>::getDegree(size_t vertex) const
{
	Edge<EdgeType>* mov = this->at(vertex).edge_;
	size_t degree = 0; 

	while (mov != nullptr) {
		++degree;
		mov = mov->getNext(vertex);
	}

	return degree; 
}
template <typename GNodeType, typename EdgeType>
void UDGraph<GNodeType, EdgeType>::print(size_t vertex) const
{
	GNode<GNodeType, EdgeType> headNode = this->at(vertex); 
	Edge<EdgeType>* mov = headNode.edge_;

	std::cout << headNode.val_ << ": ";
	if (this->weighted_) {
		while (mov != nullptr) {
			std::cout << "(" << headNode.val_ << ", ";
			std::cout << this->at(mov->getOppVtx(vertex)).val_;
			std::cout << ")=" << mov->val_ << " ";

			mov = mov->getNext(vertex);
		}
	}
	else {
		while (mov != nullptr) {
			std::cout << "(" << headNode.val_ << ", ";
			std::cout << this->at(mov->getOppVtx(vertex)).val_;
			std::cout << ") ";

			mov = mov->getNext(vertex);
		}
	}

	std::cout << std::endl; 

	return; 
}
template <typename GNodeType, typename EdgeType>
void UDGraph<GNodeType, EdgeType>::print(void) const
{
	GNode<GNodeType, EdgeType>* mov = this->node_; 
	size_t vertex = 0; 

	while (mov != nullptr) {
		this->print(vertex); 
		++vertex; 
		mov = mov->next_; 
	}
	std::cout << std::endl; 

	return; 
}

template <typename GNodeType, typename EdgeType>
GNodeType UDGraph<GNodeType, EdgeType>::getVal(size_t vertex) const
{
	return this->at(vertex).val_; 
}
template <typename GNodeType, typename EdgeType>
EdgeType UDGraph<GNodeType, EdgeType>::getVal(size_t head, size_t tail) const
{
	if (!this->weighted_) {
		throw UnweightedGraph(); 
	}

	Edge<EdgeType>* mov = this->at(head).edge_;

	while (mov != nullptr) {
		if (mov->getOppVtx(head) == tail) {
			break; 
		}

		mov = mov->getNext(head); 
	}

	if (mov == nullptr) {
		throw EdgeNotFound(head, tail); 
	}

	return mov->val_; 
}
template <typename GNodeType, typename EdgeType>
void UDGraph<GNodeType, EdgeType>::clearNodeFlags(void) const
{
	GNode<GNodeType, EdgeType>* mov = this->node_; 

	while (mov != nullptr) {
		mov->flag_ = false;
		mov = mov->next_;
	}

	return; 
}

template <typename GNodeType, typename EdgeType>
void UDGraph<GNodeType, EdgeType>::insert(const GNodeType val)
{
	GNode<GNodeType, EdgeType>* newNode = new GNode<GNodeType, EdgeType>(val); 

	if (this->node_ == nullptr) {
		this->node_ = newNode; 

		return; 
	}

	GNode<GNodeType, EdgeType>* pre = this->node_; 

	while (pre->next_ != nullptr) {
		pre = pre->next_;
	}
	pre->next_ = newNode;

	return; 
}
template <typename GNodeType, typename EdgeType>
void UDGraph<GNodeType, EdgeType>::connect(size_t head, size_t tail, EdgeType val)
{
	// check the existence of the nodes required; 
	if (head > tail) { // swap head and tail if unordered; 
		head += tail;
		tail = head - tail;
		head -= tail;
	}
	GNode<GNodeType, EdgeType>* headNode = &(this->at(head));
	// GNode<GNodeType, EdgeType>* tailNode = &(this->at(tail));
	GNode<GNodeType, EdgeType>* tailNode = headNode;
	for (size_t index = 0; index < tail - head; ++index) {
		tailNode = tailNode->next_;
		if (tailNode == nullptr) {
			throw IndexOverflow(head + index + 1, tail);
		}
	}

	// check special cases; 
	if (this->isEdge(head, tail)) { // edge already exists; 
		return;
	}
	if (head == tail) { // self-adjoint edge; 
		throw SelfAdjointNode(); 
	}

	// edge initialization; 
	Edge<EdgeType>* newEdge = new Edge<EdgeType>(head, tail);
	if (!this->weighted_ || val == NULL) {
		memset(&(newEdge->val_), 0, sizeof(EdgeType)); 
	}
	else {
		newEdge->val_ = val;
	}

	/* link to Headlist */
	this->addEdgeToNode(headNode, head, newEdge); 
	/* link to Taillist */
	this->addEdgeToNode(tailNode, tail, newEdge); 

	return;
}
template <typename GNodeType, typename EdgeType>
void UDGraph<GNodeType, EdgeType>::cut(size_t head, size_t tail)
{
	// check the existence of the nodes required; 
	GNode<GNodeType, EdgeType>* headNode = &(this->at(head));
	// GNode<GNodeType, EdgeType>* tailNode = &(this->at(tail));
	GNode<GNodeType, EdgeType>* tailNode = headNode;
	for (size_t index = 0; index < tail - head; ++index) {
		tailNode = tailNode->next_;
		if (tailNode == nullptr) {
			throw IndexOverflow(head + index + 1, tail);
		}
	}

	if (!this->isEdge(head, tail)) {
		return; 
	}

	/* pop the edge from Headlist */
	/* need not record the edge yet */
	Edge<EdgeType>* mov = headNode->edge_;
	Edge<EdgeType>* target = nullptr;

	if (headNode->edge_->getOppVtx(head) == tail) {
		headNode->edge_ = mov->getNext(head);
	}
	else {
		while (mov->getNext(head) != nullptr) {
			if (mov->getNext(head)->getOppVtx(head) == tail) {
				mov->getNext(head) = mov->getNext(head)->getNext(head);
				break; 
			}
		}
	}
	/* pop the edge from Taillist */
	/* now record the edge for being deleted later */
	mov = tailNode->edge_; 
	if (tailNode->edge_->getOppVtx(tail) == head) {
		tailNode->edge_ = mov->getNext(tail);
		target = mov; // recording; 
	}
	else {
		while (mov->getNext(tail) != nullptr) {
			if (mov->getNext(tail)->getOppVtx(tail) == head) {
				target = mov->getNext(tail); // recording; 
				mov->getNext(tail) = mov->getNext(tail)->getNext(tail);
				break;
			}
		}
	}

	/* delete the edge */
	delete target; 

	return; 
}

template <typename GNodeType, typename EdgeType>
UDGraph<GNodeType, EdgeType>& UDGraph<GNodeType, EdgeType>::getMinimalSpanningTree(unsigned int mode, bool getMST) const
{
	GNode<GNodeType, EdgeType>* mov = this->node_->next_;

	/* Initialize node set. */
	UDGraph<GNodeType, EdgeType>* MST = nullptr; 
	if (getMST) {
		MST = new UDGraph<GNodeType, EdgeType>(this->node_->val_, this->weighted_);
		while (mov != nullptr) {
			MST->insert(mov->val_);
			mov = mov->next_;
		}
	}

	mov = this->node_; 
	size_t vertex = 0;

	/*
	 *	Initialize flags.
	 *	Flag initialization made inside DFS() and BFS() will cause error for forests.
	 */

	if (!this->weighted_) {
		if (mode == 0) { // DFS; 
			this->clearNodeFlags();

			auto visit = [](size_t nodetag, GNode<GNodeType, EdgeType>* mov) -> void { std::cout << mov->getVal() << ' '; return; };

			mov = this->node_;
			while (mov != nullptr) {
				if (!mov->flag_) {
					this->DFS(visit, vertex, MST);
					std::cout << std::endl;
				}
				mov = mov->next_;
				++vertex;
			}
			std::cout << std::endl;
		}
		else if (mode == 1) { // BFS; 
			this->clearNodeFlags();

			auto visit = [](size_t nodetag, GNode<GNodeType, EdgeType>* mov) -> void { std::cout << mov->getVal() << ' '; return; };

			mov = this->node_;
			while (mov != nullptr) {
				if (!mov->flag_) {
					this->BFS(visit, vertex, MST);
					std::cout << std::endl;
				}
				mov = mov->next_;
				++vertex;
			}
			std::cout << std::endl;
		}
		else {
			throw InvalidModeTag(mode);
		}
	}
	else {
		if (mode == 0) { // Prim's Algorithm; 
			if (this->getComponentNum() != 1) {
				throw MultiConnectedGraph(); 
			}

			this->clearNodeFlags(); 

			this->node_->flag_ = true;

			Edge<EdgeType>* edge = nullptr;
			Edge<EdgeType> minEdge = Edge<EdgeType>();
			size_t minNewNode = 0;

			bool allTrue = false; // any node with false flag will make allTrue be false; 
			while (!allTrue) {
				// initialization; 
				allTrue = true;
				minEdge.val_ = 0;
				mov = this->node_;
				vertex = 0;

				while (mov != nullptr) {
					allTrue = (allTrue && mov->flag_); // check flag; 

					if (!mov->flag_) { // current node not in the MST; 
						edge = mov->edge_;
						while (edge != nullptr) { // search all edges; 
							if (this->at(edge->getOppVtx(vertex)).flag_) { // current edge links a node in the MST; 
								if (edge->val_ < minEdge.val_ || minEdge.val_ == 0) { // shorter edge; 
									// update min val; 
									minEdge = *edge;
									minNewNode = vertex;
								}
							}

							edge = edge->getNext(vertex);
						}
					}

					mov = mov->next_;
					++vertex;
				}

				// add new edge and node; 
				this->at(minNewNode).flag_ = true;
				if (getMST) {
					MST->connect(minNewNode, minEdge.getOppVtx(minNewNode), minEdge.val_);
				}
			}
		}
		else if (mode == 1) { // Kruskal's Algorithm; 

		}
		else {
			throw InvalidModeTag(mode);
		}
	}

	return *MST; 
}
template <typename GNodeType, typename EdgeType>
unsigned int UDGraph<GNodeType, EdgeType>::getComponentNum(void) const
{
	GNode<GNodeType, EdgeType>* mov = this->node_;
	size_t vertex = 0;
	unsigned int result = 0; 
	auto visit = [](size_t nodetag, GNode<GNodeType, EdgeType>* mov) -> void {};

	this->clearNodeFlags();

	while (mov != nullptr) {
		if (!mov->flag_) {
			this->BFS(visit, vertex); 
			++result; 
		}
		mov = mov->next_;
		++vertex;
	}
	
	return result; 
}
template <typename GNodeType, typename EdgeType>
vector<EdgeType> UDGraph<GNodeType, EdgeType>::getShortestPathLen(size_t src)
{
	if (this->weighted_) {
		return vector<EdgeType>{}; 
	}
	else {
		GNode<GNodeType, EdgeType>* mov = this->node_; 

		size_t nodeNum = 0; 
		while (mov != nullptr) {
			++nodeNum;
			mov = mov->next_; 
		}
		vector<EdgeType> result(nodeNum);

		unsigned int dist = 0; 
		auto visit = [&](size_t nodetag, GNode<GNodeType, EdgeType>* mov) -> void { 
			Edge<EdgeType>* neigh = mov->edge_; 

			while (neigh != nullptr) {
				GNode<GNodeType, EdgeType> cache = this->at(neigh->getOppVtx(nodetag)); 
				if (!cache.getFlag()) {
					result.at(neigh->getOppVtx(nodetag)) = result.at(nodetag) + 1;
					cache.setFlag(true); 
				}
				neigh = neigh->getNext(nodetag); 
			}

			return; 
		};

		/* Initialize flags. */
		this->clearNodeFlags();

		this->BFS(visit, src); 

		return result; 
	}
}
template <typename GNodeType, typename EdgeType>
EdgeType UDGraph<GNodeType, EdgeType>::getShortestPathLen(size_t src, size_t dest)
{
	if (this->weighted_) {
		return NULL; 
	}
	else {
		return this->getShortestPathLen(src).at(dest); 
	}
}

template <typename GNodeType, typename EdgeType>
GNode<GNodeType, EdgeType>& UDGraph<GNodeType, EdgeType>::at(size_t vertex) const
{
	size_t count = vertex; 
	GNode<GNodeType, EdgeType>* mov = this->node_; 

	/* Notice that a graph should never be empty. */
	while (count != 0) {
		if (mov == nullptr) {
			throw IndexOverflow(vertex - count, vertex); 
		}
		--count; 
		mov = mov->next_; 
	}
	if (mov == nullptr) {
		throw IndexOverflow(vertex - count, vertex); 
	}

	return *mov; 
}
template <typename GNodeType, typename EdgeType>
bool UDGraph<GNodeType, EdgeType>::getNextUnvisited(GNode<GNodeType, EdgeType>*& mov, size_t& nodetag) const 
{
	GNode<GNodeType, EdgeType>* cache = nullptr;
	Edge<EdgeType>* edge = nullptr;

	edge = mov->edge_;
	while (edge != nullptr) {
		cache = &this->at(edge->getOppVtx(nodetag));
		if (!cache->flag_) {
			nodetag = edge->getOppVtx(nodetag);
			mov = cache;

			break;
		}
		edge = edge->getNext(nodetag);
	}

	return edge == nullptr; // true if no more edge is available; 
							// in this case, mov and nodetag weren't updated; 
}
template <typename GNodeType, typename EdgeType>
void UDGraph<GNodeType, EdgeType>::addEdgeToNode(GNode<GNodeType, EdgeType>*& node, size_t nodetag, Edge<EdgeType>*& newEdge)
{
	Edge<EdgeType>* mov = node->edge_;
	size_t oppVtxTag = newEdge->getOppVtx(nodetag); 

	if (mov == nullptr) { // the node has no edge yet; 
		node->edge_ = newEdge;
	}
	else if (mov->getOppVtx(nodetag) > oppVtxTag) { // this edge should insert to the first edge of the node; 
		newEdge->getNext(nodetag) = mov;
		node->edge_ = newEdge;
	}
	else {
		while (mov != nullptr) {
			if (mov->getNext(nodetag) == nullptr) {
				mov->getNext(nodetag) = newEdge;
				break;
			}
			if (mov->getNext(nodetag)->getOppVtx(nodetag) > oppVtxTag) {
				newEdge->getNext(nodetag) = mov->getNext(nodetag);
				mov->getNext(nodetag) = newEdge;
				break;
			}

			mov = mov->getNext(nodetag);
		}
	}
}

template <typename GNodeType, typename EdgeType>
template <typename Function>
void UDGraph<GNodeType, EdgeType>::DFS(Function visit, size_t vertex, UDGraph<GNodeType, EdgeType>* MST) const
{
	/* Assumed that flag initialization already done. */

	GNode<GNodeType, EdgeType>* mov = &this->at(vertex);
	size_t nodetag = vertex; 
	stack<pair<size_t, GNode<GNodeType, EdgeType>*>> stk = {};
	pair<size_t, GNode<GNodeType, EdgeType>*> temp = {}; 

	while (mov != nullptr || !stk.empty()) {
		if (mov != nullptr) {
			stk.push(pair<size_t, GNode<GNodeType, EdgeType>*>{ nodetag, mov });

			if (!mov->flag_) { // if mov is not being retracked from stk; 
				visit(nodetag, mov);
				mov->flag_ = true; // set flag; 
			}

			if (this->getNextUnvisited(mov, nodetag)) {
				mov = nullptr; 
			}
			else {
				temp = stk.top();
				if (MST != nullptr) {
					MST->connect(temp.first, nodetag);
				}
			}
		}
		else {
			temp = stk.top(); 
			nodetag = temp.first;
			mov = temp.second;

			if (this->getNextUnvisited(mov, nodetag)) {
				mov = nullptr;
				stk.pop(); 
			}
			else {
				temp = stk.top();
				if (MST != nullptr) {
					MST->connect(temp.first, nodetag);
				}
			}
		}
	}

	return; 
}
template <typename GNodeType, typename EdgeType>
template <typename Function>
void UDGraph<GNodeType, EdgeType>::BFS(Function visit, size_t vertex, UDGraph<GNodeType, EdgeType>* MST) const
{
	/* Assumed that flag initialization already done. */

	GNode<GNodeType, EdgeType>* mov = &this->at(vertex);
	size_t nodetag = vertex;
	queue<pair<size_t, GNode<GNodeType, EdgeType>*>> que = {}; 
	pair<size_t, GNode<GNodeType, EdgeType>*> temp = {}; 

	size_t len = 0;

	GNode<GNodeType, EdgeType>* cache = nullptr;
	Edge<EdgeType>* edge = nullptr;

	que.push(pair<size_t, GNode<GNodeType, EdgeType>*>{ nodetag, mov });
	mov->flag_ = true; 

	while (!que.empty()) {
		len = que.size(); 

		for (size_t index = 0; index < len; ++index) {
			temp = que.front(); 
			nodetag = temp.first; 
			mov = temp.second;

			visit(nodetag, mov);

			edge = mov->edge_; 
			while (edge != nullptr) {
				cache = &this->at(edge->getOppVtx(nodetag)); 
				if (!cache->flag_) {
					if (MST != nullptr) {
						MST->connect(nodetag, edge->getOppVtx(nodetag));
					}
					que.push(pair<size_t, GNode<GNodeType, EdgeType>*>{ edge->getOppVtx(nodetag), cache });
					cache->flag_ = true;
				}

				edge = edge->getNext(nodetag); 
			}

			que.pop(); 
		}
	}

	return; 
}


/* -------- Union Search Set -------- */
template <typename DataType>
USNode<DataType>::USNode(DataType val, USNode<DataType>* parent, unsigned int rank, USNode<DataType>* initnext) :
	val_(val), 
	parent_(parent), 
	rank_(rank), 
	initnext_(initnext)
{

}
template <typename DataType>
USNode<DataType>::~USNode(void)
{

}

template <typename GNodeType, typename EdgeType>
USSet<GNodeType, EdgeType>::USSet(GNode<GNodeType, EdgeType>*& node)
{

}
template <typename GNodeType, typename EdgeType>
USSet<GNodeType, EdgeType>::~USSet(void)
{

}

template <typename GNodeType, typename EdgeType>
USNode<GNode<GNodeType, EdgeType>*>* USSet<GNodeType, EdgeType>::find(NodeType* node)
{

}
template <typename GNodeType, typename EdgeType>
void USSet<GNodeType, EdgeType>::merge(NodeType* root, NodeType* src)
{

}