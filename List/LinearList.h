/* LinearList */
#ifndef LIST_LINEARLIST_H_
#define LIST_LINEARLIST_H_ 2

	/* Structure datatype */
	#if (LIST_LINEARLIST_H_ == 1)

		typedef int DataType;

	#define LINEARLIST_STRUCT 0

		/* Static squential list */
		#if (LINEARLIST_STRUCT == 1)
		#define LINEARLIST_STRUCT_SQLIST_STATIC
			constexpr size_t kMaxSize = 13;

			typedef struct {
				DataType val[kMaxSize];
				size_t length; 
			} SqList; 

			/* Initializer */
			void SqList_init(SqList& list); 

			/* get - functions */
			size_t SqList_getLength(const SqList list);
			DataType SqList_getValue(const SqList list, size_t ind);

			/* Discriminants */
			bool SqList_isEmpty(const SqList list); 

			/* print */
			void SqList_print(const SqList list); 

			/* atomic functions */
			int SqList_find(const SqList list, DataType src); 
			void SqList_insert(SqList& list, size_t ind, DataType src); 
			void SqList_pop(SqList& list, size_t ind, DataType& dest); 

			/* Destructor */
			void SqList_destroy(SqList list);
		#endif /* Static squential list */

		/* Dynamic squential list */
		#if (LINEARLIST_STRUCT == 2)
		#define LINEARLIST_STRUCT_SQLIST_DYNAMIC
			constexpr size_t kInitSize = 2; 
			constexpr size_t kIncrement = 3; 

			typedef struct {
				DataType* val;
				size_t length;
				size_t volume; 
			} SqList;

			// Initializer; 
			void SqList_init(SqList& list);
			// get-functions; 
			size_t SqList_getLength(const SqList list);
			// Discriminants; 
			bool SqList_isEmpty(const SqList list);
			// print; 
			void SqList_print(const SqList list);

			// atomic functions; 
			int SqList_find(const SqList list, DataType src);
			DataType SqList_getValue(const SqList list, size_t ind);
			void SqList_insert(SqList& list, size_t ind, DataType src);
			void SqList_pop(SqList& list, size_t ind, DataType& dest);

			// Destructor; 
			void SqList_destroy(SqList list);
		#endif /* Dynamic squential list */

		/* Linked list with header */
		#if (LINEARLIST_STRUCT == 3)
		#define LINEARLIST_STRUCT_LINKEDLIST_COMMON
			typedef struct LNode {
				DataType val; 
				LNode* next; 
			} LNode, *LinkedList;

			/* Initializer */
			void LkList_init(LinkedList& list); // reference here is necessary
												// since new memory is allocated to list; 

			/* get - functions */
			size_t LkList_getLength(const LinkedList list);
			DataType LkList_getValue(const LinkedList list, size_t ind);

			/* Discriminants */
			bool LkList_isEmpty(const LinkedList list);
			
			/* print */
			void LkList_print(const LinkedList list);

			/* atomic functions */
			int LkList_find(const LinkedList list, DataType src);
			void LkList_insert(LinkedList& list, size_t ind, DataType src);
			void LkList_pop(LinkedList& list, size_t ind, DataType& dest);

			/* Destructor */
			void LkList_destroy(LinkedList& list); 
		#endif /* Linked list with header */

		/* Static linked list, statically allocated */
		#if (LINEARLIST_STRUCT == 4)
		#define LINEARLIST_STRUCT_LINKEDLIST_STATIC
			constexpr size_t kMaxSize = 13;

			typedef struct {
				DataType val; 
				size_t next; 
			} LNode, *LinkedList;

			/* Initializer */
			void LkList_init(LinkedList& list);

			/* get - functions */
			size_t LkList_getLength(const LinkedList list);
			DataType LkList_getValue(const LinkedList list, size_t ind);

			/* Discriminants */
			bool LkList_isEmpty(const LinkedList list);

			/* print */
			void LkList_print(const LinkedList list);

			/* atomic functions */
			int LkList_find(const LinkedList list, DataType src);
			void LkList_insert(LinkedList& list, size_t ind, DataType src);
			void LkList_pop(LinkedList& list, size_t ind, DataType& dest);

			/* Destructor */
			void LkList_destroy(LinkedList& list);
		#endif /* Static linked list, statically allocated */

	#define STACK_STRUCT 1

		constexpr size_t kMaxSize = 20;
	
		/* Static stack */
		#if (STACK_STRUCT == 1)
		#define STACK_STRUCT_STATIC

			typedef struct {
				DataType val[kMaxSize]; 
				size_t top; 
			} Stack;

			/* Initializer */
			void Stack_init(Stack& stack);

			/* get - functions */
			void Stack_getTop(const Stack stack, DataType& dest);

			/* Discriminants */
			bool Stack_isEmpty(const Stack stack);

			/* print */
			void Stack_print(const Stack stack);

			/* atomic functions */
			void Stack_push(Stack& stack, DataType src);
			void Stack_pop(Stack& stack, DataType& dest);

			/* Destructor */
			void Stack_destroy(Stack stack);
		#endif /* Static stack */

		/* Static queue */
		#if (STACK_STRUCT == 1)

		#endif /* Static queue */

		/* Static doubly-ended queue */
		#if (STACK_STRUCT == 1)

		#endif /* Static doubly-ended queue */

		/* Static string */
		#if (STACK_STRUCT == 1)
			typedef struct {
				char* head; 
				size_t length; 
			} String;

			/* Initializer */
			void StrInit(String& str); 

			/* Discriminants */
			bool StrEmpty(const String str); 

			/* get-functions */
			size_t StrLen(const String str); 
			void StrPrint(const String str); 

			/* atom functions */
			void StrAssign(String& str, const char* src); 
			void StrCpy(String& dest, const String src); 
			int StrCmp(const String dest, const String src); 
			void StrCat(String& dest, const String src1, const String src2); 
			void SubStr(String& dest, const String src, size_t indH, size_t len); 
			void StrClr(String& str); 

			/* extended functions */
			int FindSubStr(const String str, const String substr); 

			/* Destructor */
			void StrDestroy(String& str); 
		#endif /* Static string */

	#endif /* Structure datatype */

	/* Class datatype */
	#if (LIST_LINEARLIST_H_ == 2)
	#define LINEARLIST_CLASS

		/* Node classes */
		template <typename DataType>
		class Node
		{
		public:
			Node(void); 
			Node(DataType val, Node<DataType>* next = nullptr); 
			~Node(void); 

			DataType getVal(void) const;
			Node<DataType>* getNext(void) const;
			void setVal(DataType newVal);
			void setNext(Node<DataType>* newNext);

		private:
			DataType val_; 
			Node<DataType>* next_; 
		};

		template <typename DataType>
		class DNode
		{
		public:
			DNode(void); 
			DNode(DataType val, DNode<DataType>* next = nullptr, DNode<DataType>* pred = nullptr); 
			~DNode(void); 

			DataType getVal(void) const;
			DNode<DataType>* getNext(void) const;
			DNode<DataType>* getPred(void) const;
			void setVal(DataType newVal);
			void setNext(DNode<DataType>* newNext);
			void setPred(DNode<DataType>* newPred);

		private:
			DataType val_;
			DNode<DataType>* next_;
			DNode<DataType>* pred_; 
		};

		/* List classes */
		template <typename DataType>
		class List
		{
		public:
			virtual ~List(void);

		protected:
			List(void);

			virtual bool isEmpty(void) const = 0;

			// virtual size_t getLength(void) const { return 0 };
			virtual void print(void) const = 0;

			// virtual int find(DataType target) const { return 0 };
			// virtual DataType at(size_t ind) const { return NULL };
			// virtual void insert(size_t ind, DataType src) {};
			// virtual void del(size_t ind, DataType& dest) {};
		}; 

		template <typename DataType>
		class LinkedList : public List<DataType> 
		{
		public:
			LinkedList(void); 
			~LinkedList(void); 

			bool isEmpty(void) const override;

			size_t getLength(void) const;
			void print(void) const override;

			int find(DataType target) const;
			DataType at(size_t ind) const;
			void insert(size_t ind, DataType src);
			void del(size_t ind, DataType& dest);

		private:
			Node<DataType>* head_; 

			Node<DataType>* getFirst(void) const; 
			void setFirst(Node<DataType>* newFirst); 
		};

		template <typename DataType>
		class Stack : public List<DataType>
		{
		public:
			Stack(void);
			~Stack(void);

			bool isEmpty(void) const override;

			DataType getTop(void) const;
			void print(void) const override;

			void push(DataType src);
			void pop(DataType& dest);

		private:
			Node<DataType>* head_; // the first node after head_ will be top_; 

			Node<DataType>* getFirst(void) const;
			void setFirst(Node<DataType>* newFirst); 
		};

		template <typename DataType>
		class Queue : public List<DataType>
		{
		public:
			Queue(void);
			~Queue(void);

			bool isEmpty(void) const override;

			DataType getFront(void) const;
			void print(void) const override;

			void pushBack(DataType src);
			void pop(DataType& dest);

		protected:
			/* Notice: the implementation of Queue is non-cyclic. */
			Node<DataType>* head_; // the first node after head_ will be front_; 
			Node<DataType>* rear_; // initial rear_ will be head_; 

			Node<DataType>* getFirst(void) const;
			void setFirst(Node<DataType>* newFirst); 
		};

		template <typename DataType>
		class Deque
		{
			/* The implementation is cyclic. */
		public:
			Deque(void);
			~Deque(void);

			bool isEmpty(void) const;

			DataType getFront(void) const;
			DataType getBack(void) const; 
			void print(void) const;

			void push(DataType src); 
			void pushBack(DataType src);
			void popFront(DataType& dest); 
			void pop(DataType& dest);

		private:
			DNode<DataType>* head_;

			DNode<DataType>* getFirst(void) const;
			DNode<DataType>* getLast(void) const;
			void setFirst(DNode<DataType>* newFirst);
			void setLast(DNode<DataType>* newLast);
		};

		class String
		{
		public:
			String(const char* src = nullptr);
			String(const String& str); // Copy Constructor; 
			~String(void);

			bool isEmpty(void) const;

			size_t getLength(void) const;
			void print(void) const;

			String& operator=(const char* src);
			String& operator=(const String& src);

			bool operator>(const char* src) const;
			bool operator>(const String& src) const;
			bool operator<(const char* src) const;
			bool operator<(const String& src) const;
			bool operator==(const char* src) const;
			bool operator==(const String& src) const;
			bool operator!=(const char* src) const;
			bool operator!=(const String& src) const;

			String operator+(const char* src) const;
			String operator+(const char src) const;
			String operator+(const String& tail) const;
			String& operator+=(const char* src); 
			String& operator+=(const char src); 
			String& operator+=(const String& tail);

			// Slicing; for C++23 [] can accept multiple arguments; 
			char& operator[](int ind) const; 
			String operator()(int indH, int indT, int step = 1) const; 
			void clear(void);

			// KMP algorithm; 
			int find(const char* substr); 
			int find(const String& substr);

		private:
			char* str_; // ending with '\0'; 
			size_t length_; // length of str_ without ending '\0'; 
			size_t capacity_; // current max size without ending '\0'; 
		};

	#endif /* Class datatype */

	/* Implementations */
		/* Template class header files must contain their implementations, */
		/* otherwise VS will throw LNK2019 error to constructors.  */
		/* To make code highlighting available, */
		/* it's convenient to use .hpp file instead of .inc. */
	#include "LinearList.hpp"

#endif /* LinearList */