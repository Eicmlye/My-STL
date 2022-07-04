#ifndef GRAPH_GRAPH_H_
#define GRAPH_GRAPH_H_ 2

	#if GRAPH_GRAPH_H_ == 1
	#define GRAPH_STRUCT

	#endif

	#if GRAPH_GRAPH_H_ == 2
	#define GRAPH_CLASS

	#include <vector>

	using std::vector; 

	/* -------- Undirected Graph -------- */
	template <typename GNodeType, typename EdgeType>
	class UDGraph;

	/* Edge as node in GNode */
	template <typename EdgeType = unsigned int>
	class Edge
	{
	public:
		Edge(size_t index = 0, size_t jndex = 0, \
			Edge<EdgeType>* inext = nullptr, Edge<EdgeType>* jnext = nullptr, bool flag = false);
		~Edge(void);

		inline EdgeType getVal(void) const; 
		inline Edge<EdgeType>*& getNext(size_t vertex); 
		inline size_t getOppVtx(size_t vertex);
		inline bool getFlag(void) const;
		inline void setFlag(bool newFlag);

		template <typename GNodeType, typename EdgeType>
		friend class UDGraph;

	private:
		EdgeType val_;
		size_t index_;
		size_t jndex_;
		Edge<EdgeType>* inext_;
		Edge<EdgeType>* jnext_;
		bool flag_;
	};
	
	/* GNode as LinkedList without header */
	template <typename GNodeType = unsigned int, typename EdgeType = unsigned int>
	class GNode
	{
	public:
		GNode(void);
		GNode(GNodeType val, Edge<EdgeType>* edge = nullptr, GNode<GNodeType, EdgeType>* next = nullptr, bool flag = false);
		~GNode(void); 
		
		inline GNodeType getVal(void) const; 
		inline bool getFlag(void) const;
		inline void setFlag(bool newFlag);
		inline bool isIsolated(void) const;

		friend class UDGraph<GNodeType, EdgeType>; 

	private:
		GNodeType val_;
		Edge<EdgeType>* edge_; /* The index of the other vertices should be ordered.  */
		GNode<GNodeType, EdgeType>* next_; 
		bool flag_; 
	};

	/* Adjacency multi-list implementation */
	/* Simple UDGraph as LinkedList of GNode */
	/* Self-adjoint node not allowed */
	template <typename GNodeType = unsigned int, typename EdgeType = unsigned int>
	class UDGraph
	{
	public:
		UDGraph(GNodeType val, bool weighted = false); 
		~UDGraph(void); 

		inline bool isWeighted(void) const; 
		bool isEdge(size_t head, size_t tail) const;

		size_t getDegree(size_t vertex) const;
		void print(size_t vertex) const;
		void print(void) const;

		GNodeType getVal(size_t vertex) const; // for AOV webs; 
		EdgeType getVal(size_t head, size_t tail) const; // for AOE webs; 
		void clearNodeFlags(void) const;

		void insert(const GNodeType val); 
		/* 
			* Deleting nodes is very complex for node-index-dependent representation of edges. 
			* One should update the index_ and jndex_ in all edges, 
			* which causes traversal through edge set. 
		*/
		// void del(size_t vertex); 
		/*
			* Should ensure the order of Edgelist for related GNodes. 
		*/
		void connect(size_t head, size_t tail, EdgeType val = NULL);
		void cut(size_t head, size_t tail);

		/* 
		*	unweighted: mode 0: DFS; 
		*				mode 1: BFS; 
		*	weighted:	mode 0: Prim; 
		*				mode 1: Kruskal; 
		*/
		UDGraph<GNodeType, EdgeType>& getMinimalSpanningTree(unsigned int mode = 0, bool getMST = false) const;
		/* BFS implementation */
		unsigned int getComponentNum(void) const;
		/* 
		*	BFS implementation for non-weighted graphs;
		*	For weighted graphs, EdgeType should be positive; 
		*/
		vector<EdgeType> getShortestPathLen(size_t src);
		/*
		*	BFS implementation for non-weighted graphs;
		*	For weighted graphs, EdgeType should be positive; 
		*/
		EdgeType getShortestPathLen(size_t src, size_t dest);

	private:
		GNode<GNodeType, EdgeType>* node_;
		bool weighted_;

		GNode<GNodeType, EdgeType>& at(size_t vertex) const;
		bool getNextUnvisited(GNode<GNodeType, EdgeType>*& mov, size_t& nodetag) const;
		void addEdgeToNode(GNode<GNodeType, EdgeType>*& headNode, size_t headtag, Edge<EdgeType>*& edge);

		template <typename Function>
		void DFS(Function visit, size_t vertex = 0, UDGraph<GNodeType, EdgeType>* MST = nullptr) const;
		template <typename Function>
		void BFS(Function visit, size_t vertex = 0, UDGraph<GNodeType, EdgeType>* MST = nullptr) const;
	};


	/* -------- Union Search Set -------- */
	template <typename GNodeType, typename EdgeType>
	class USSet; 

	template <typename DataType>
	class USNode
	{
	public:
		USNode(DataType val, USNode<DataType>* parent = nullptr, \
			unsigned int rank = 0, USNode<DataType>* initnext = nullptr);
		~USNode(void);

		template <typename GNodeType, typename EdgeType>
		friend class USSet;

	private:
		DataType val_;
		USNode<DataType>* parent_;
		unsigned int rank_;
		USNode<DataType>* initnext_; // for USSet node collection; 
	};

	template <typename GNodeType = int, typename EdgeType = unsigned int>
	class USSet
	{
	public:
		using NodeType = USNode<GNode<GNodeType, EdgeType>*>;

		USSet(GNode<GNodeType, EdgeType>*& node);
		~USSet(void);

		NodeType* find(NodeType* node);
		void merge(NodeType* root, NodeType* src);

	private:
		NodeType* head_;
		unsigned int connected_components_; 
	};

	#endif

/* Implementations */
#include "Graph.hpp"

#endif