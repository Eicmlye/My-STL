#include <iostream>
#include <cstring> /* strlen() */

#include "Exception.h"

/* Structure datatype linearlist */
#ifdef LINEARLIST_STRUCT
	/* Static squential list */
	#ifdef LINEARLIST_STRUCT_SQLIST_STATIC
		/* Initializer */
		void SqList_init(SqList& list)
		{
			// initialize all the elements to 0; 
			memset(list.val, 0, kMaxSize * sizeof(DataType));
			// initialize list length; 
			list.length = 0;

			return; 
		};

		/* get - functions */
		size_t SqList_getLength(const SqList list)
		{
			return list.length;
		}
		// Random access, TC = O(1); 
		DataType SqList_getValue(const SqList list, size_t ind)
		{
			if (ind >= list.length) {
				std::cout << "IndexError: Index Overflow" << std::endl;

				return 0; 
			}

			return list.val[ind];
		}

		/* Discriminants */
		bool SqList_isEmpty(const SqList list)
		{
			return (list.length == 0);
		}

		/* print */
		void SqList_print(const SqList list)
		{
			if (SqList_isEmpty(list)) {
				// for empty list, print prompt; 
				std::cout << "Empty list. " << std::endl;
			}
			else {
				for (size_t index = 0; index < list.length; ++index) {
					std::cout << list.val[index] << ' ';
				}
				std::cout << std::endl;
			}

			return;
		}

		/* atomic functions */
		// Sequential search, TC = O(n); 
		int SqList_find(const SqList list, DataType src)
		{
			for (size_t index = 0; index < list.length; ++index) {
				if (list.val[index] == src) {
					return index;
				}
			}

			return -1;
		}
		// TC_avg = O(n); 
		// best O(1), insert at end; worst O(n), insert at front; 
		void SqList_insert(SqList& list, size_t ind, DataType src)
		{
			// check accessibility and memory; 
			if (ind >= kMaxSize) {
				std::cerr << "IndexError: Index Overflow" << std::endl;

				return; 
			}
			else if (list.length == kMaxSize) {
				std::cerr << "MemoryError: Not enough memory allocated" << std::endl;

				return; 
			}

			// check legal position; 
			if (ind > list.length) {
				std::cerr << "IndexWarning: Index out of range, ";
				std::cerr << "set insertation to the end of the list. " << std::endl;
				ind = list.length;
			}

			// insertation; 
			size_t index = list.length; 
			while (index > ind) { // shift elements behind; 
				list.val[index] = list.val[index - 1];
				--index; 
			}
			list.val[ind] = src;
			++list.length;

			return;
		}
		// TC_avg = O(n); 
		// best O(1), pop at end; worst O(n), pop at front; 
		void SqList_pop(SqList& list, size_t ind, DataType& dest)
		{
			// check accessibility; 
			if (ind >= list.length) {
				std::cerr << "IndexError: Index Overflow" << std::endl;

				return; 
			}

			// pop; 
			dest = list.val[ind];
			size_t index = ind + 1; 
			while (index < list.length) {
				list.val[index - 1] = list.val[index];
				++index;
			}
			--list.length;

			return;
		}

		/* Destructor */
		void SqList_destroy(SqList list)
		{
			// the same as init; 
			memset(list.val, 0, kMaxSize * sizeof(DataType));
			list.length = 0;

			return; 
		};
	#endif

	/* Dynamic squential list */
	#ifdef LINEARLIST_STRUCT_SQLIST_DYNAMIC
		/* Initializer */
		void SqList_init(SqList& list)
		{
			list.val = (DataType*)malloc(kInitSize * sizeof(DataType));
			if (list.val == nullptr) {
				std::cerr << "MemoryError: Memory allocation failure" << std::endl; 

				return; 
			}
			
			memset(list.val, 0, kInitSize * sizeof(DataType));
			list.length = 0;
			list.volume = kInitSize;

			return; 
		}

		/* get - functions */
		size_t SqList_getLength(const SqList list)
		{
			return list.length; 
		}
		DataType SqList_getValue(const SqList list, size_t ind)
		{
			if (ind >= list.length) {
				std::cerr << "IndexError: Index Overflow" << std::endl;

				return 0; 
			}

			return list.val[ind];
		}

		/* Discriminants */
		bool SqList_isEmpty(const SqList list)
		{
			return (list.length == 0); 
		}

		/* print */
		void SqList_print(const SqList list)
		{
			if (SqList_isEmpty(list)) {
				std::cout << "Empty list. " << std::endl; 
			}
			else {
				for (size_t index = 0; index < list.length; ++index) {
					std::cout << list.val[index] << ' '; 
				}
				std::cout << std::endl; 
			}

			return; 
		}

		/* atomic functions */
		int SqList_find(const SqList list, DataType src)
		{
			for (size_t index = 0; index < list.length; ++index) {
				if (list.val[index] == src) {
					return index; 
				}
			}

			return -1; 
		}
		void SqList_insert(SqList& list, size_t ind, DataType src)
		{
			// check legal position; 
			if (ind > list.length) {
				std::cout << "IndexWarning: Index overflow, "; 
				std::cout << "set insertation to the end of the list. " << std::endl; 
				ind = list.length; 
			}

			if (list.length == list.volume) {
				DataType* cache = (DataType*)realloc(list.val, (list.volume + kIncrement) * sizeof(DataType));
				if (cache == nullptr) {
					std::cerr << "MemoryError: Allocation Failure" << std::endl; 

					return; 
				}

				// allocation success; 
				list.val = cache; // notice that one should not free cache here; 
									// since list.val and cache point to 
									// the same memory block in user heap; 
				list.volume += kIncrement;
			}

			// now enough memory allocated; 
			size_t index = list.length;
			while (index > ind) {
				list.val[index] = list.val[index - 1];
				--index;
			}
			list.val[ind] = src;
			++list.length;

			return; 
		}
		void SqList_pop(SqList& list, size_t ind, DataType& dest)
		{
			if (list.length == 0) {
				std::cerr << "IndexError: Index Overflow" << std::endl; 
			
				return; 
			}

			dest = list.val[ind]; 
			size_t index = ind + 1; 
			while (index < list.length) {
				list.val[index - 1] = list.val[index];
				++index; 
			}
			--list.length; 

			return; 
		}

		/* Destructor */
		void SqList_destroy(SqList list)
		{
			free(list.val);
			list.length = 0;
			list.volume = 0;

			return; 
		}
	#endif /* Dynamic squential list */

	/* Linked list with header */
	#ifdef LINEARLIST_STRUCT_LINKEDLIST_COMMON
		/* Initializer */
		void LkList_init(LinkedList& list)
		{
			// create header; 
			list = (LinkedList)malloc(sizeof(LNode)); 
			if (list == nullptr) {
				std::cerr << "MemoryError: Allocation Failure" << std::endl;

				return; 
			}

			// allocation success; 
			list->val = 0;
			list->next = nullptr;

			return; 
		}

		/* get - functions */
		size_t LkList_getLength(const LinkedList list)
		{
			size_t len = 0;
			// set probe; 
			LNode* mov = list->next; 
			while (mov != nullptr) {
				++len; 
				mov = mov->next; 
			}

			return len; 
		}
		DataType LkList_getValue(const LinkedList list, size_t ind)
		{
			// set probe; 
			LNode* mov = list->next; 

			while (mov != nullptr) {
				if (ind == 0) {
					return mov->val;
				}

				mov = mov->next; 
				--ind; 
			}

			std::cerr << "IndexError: Index Overflow" << std::endl; 

			return 0; 
		}

		/* Discriminants */
		bool LkList_isEmpty(const LinkedList list)
		{
			return (list->next == nullptr); 
		}

		/* print */
		void LkList_print(const LinkedList list)
		{
			if (LkList_isEmpty(list)) {
				std::cout << "Empty list. " << std::endl; 
			}
			else {
				LNode* mov = list->next;
				while (mov != nullptr) {
					std::cout << mov->val << ' ';
					mov = mov->next;
				}
				std::cout << std::endl;
			}

			return; 
		}

		/* atomic functions */
		int LkList_find(const LinkedList list, DataType src)
		{
			size_t ind = 0; 
			// set probe; 
			LNode* mov = list->next; 
			while (mov != nullptr) {
				if (mov->val == src) {
					return ind; 
				}

				++ind; 
				mov = mov->next; 
			}

			return -1; 
		}
		void LkList_insert(LinkedList& list, size_t ind, DataType src)
		{
			// normalization; 
			size_t len = LkList_getLength(list); 
			if (ind > len) {
				std::cerr << "IndexWarning: Index out of range, "; 
				std::cerr << "set insertation to the end of the list. " << std::endl; 
				ind = len; 
			}

			// set probe; 
			LNode* mov = list; 
			// find the node for insertation; 
			while (ind != 0) {
				mov = mov->next; 
				--ind; 
			}

			// insert; 
			LNode* newNode = (LNode*)malloc(sizeof(LNode)); 
			if (newNode == nullptr) {
				std::cerr << "MemoryError: Allocation Failure" << std::endl; 

				return; 
			}
			// allocation success; 
			LkList_init(newNode); 
			newNode->val = src; 
			newNode->next = mov->next; 
			mov->next = newNode; 

			return; 
		}
		void LkList_pop(LinkedList& list, size_t ind, DataType& dest)
		{
			if (ind >= LkList_getLength(list)) {
				std::cerr << "IndexError: Index Overflow" << std::endl; 

				return; 
			}

			// set probe; 
			LNode* mov = list; 
			while (ind != 0) {
				mov = mov->next; 
				--ind; 
			}
			LNode* target = mov->next; 
			dest = target->val; 
			mov->next = target->next; 
			free(target); 

			return; 
		}

		// Destructor; 
		void LkList_destroy(LinkedList& list)
		{
			LNode* first = list->next; 
			while (first != nullptr) {
				list->next = first->next; 
				free(first); 
				first = list->next; 
			}
			free(list); 

			return; 
		}
	#endif /* Linked list with header */

	/* Static linked list, statically allocated */
	#ifdef LINEARLIST_STRUCT_LINKEDLIST_STATIC

		/* Initializer */
		void LkList_init(LinkedList& list)
		{
			list = (LinkedList)malloc(kMaxSize * sizeof(LNode));
			if (list == nullptr) {
				std::cerr << "MemoryError: Allocation Failure" << std::endl; 

				return; 
			}

			// allocation success; 
			// initialize spare list; 
			for (size_t index = 0; index < kMaxSize; ++index) {
				list[index].val = 0; 
				list[index].next = (index + 1) % kMaxSize;
			}

			return; 
		}

		/* get - functions */
		size_t LkList_getLength(const LinkedList list)
		{
			if (LkList_isEmpty(list)) {
				return 0; 
			}

			size_t len = 0; 
			// set probe; 
			size_t mov = 1; 
			while (mov != 0) {
				++len; 
				mov = list[mov].next; 
			}

			return len; 
		}
		DataType LkList_getValue(const LinkedList list, size_t ind)
		{
			if (LkList_isEmpty(list)) {
				std::cerr << "IndexError: Index Overflow" << std::endl; 
				
				return 0; 
			}

			// set probe; 
			size_t mov = 1; 
			while (mov != 0) {
				if (ind == 0) {
					return list[mov].val; 
				}

				mov = list[mov].next; 
				--ind; 
			}

			std::cerr << "IndexError: Index Overflow" << std::endl; 

			return 0; 
		}

		/* Discriminants */
		bool LkList_isEmpty(const LinkedList list)
		{
			return (list[0].next == 1); 
		}

		/* print */
		void LkList_print(const LinkedList list)
		{
			if (LkList_isEmpty(list)) {
				std::cout << "Empty list. " << std::endl; 
			}
			else {
				size_t mov = 1; 
				while (mov != 0) {
					std::cout << list[mov].val << ' '; 
					mov = list[mov].next;
				}
				std::cout << std::endl; 
			}
		}

		/* atomic functions */
		int LkList_find(const LinkedList list, DataType src)
		{
			if (LkList_isEmpty(list)) {
				return -1; 
			}

			size_t mov = 1; 
			size_t ind = 0; 
			while (mov != 0) {
				if (src == list[mov].val) {
					return ind; 
				}

				++ind; 
				mov = list[mov].next; 
			}

			return -1; 
		}
		void LkList_insert(LinkedList& list, size_t ind, DataType src)
		{
			// check legal ind; 
			size_t len = LkList_getLength(list);
			if (ind >= kMaxSize - 1) {
				std::cerr << "IndexError: Index Overflow" << std::endl;
				return;
			}
			else if (ind > len) {
				std::cerr << "IndexWarning: Index out of range, ";
				std::cerr << "set insertation to the end of the list" << std::endl;
				ind = len;
			}

			// check if there is spare space; 
			if (list[0].next == 0) {
				std::cerr << "MemoryError: Not Enough Memory Allocated" << std::endl;

				return;
			}

			// fetch new node; 
			size_t newNode = list[0].next;
			list[newNode].val = src;
			// insert; 
			if (ind == 0) { // insert at the beginning; 
				if (LkList_isEmpty(list)) {
					// modify spare list; 
					list[0].next = list[newNode].next;
					// modify new list; 
					list[newNode].next = 0; 
				}
				else {
					// modify spare list; 
					list[0].next = list[newNode].next;
					// swap data; 
					list[newNode].val += list[1].val; 
					list[1].val = list[newNode].val - list[1].val; 
					list[newNode].val -= list[1].val; 
					// insert node; 
					list[newNode].next = list[1].next; 
					list[1].next = newNode; 
				}
			}
			else {
				// modify spare list; 
				list[0].next = list[newNode].next;
				size_t mov = 1;
				while (ind != 1) { // find predecessor; 
					--ind;
					mov = list[mov].next;
				}
				list[newNode].next = list[mov].next;
				list[mov].next = newNode;
			}

			return; 
		}
		void LkList_pop(LinkedList& list, size_t ind, DataType& dest)
		{
			// check legal ind; 
			size_t len = LkList_getLength(list); 
			if (ind >= len) {
				std::cerr << "IndexError: Index Overflow" << std::endl; 

				return; 
			}

			// pop; 
			size_t sparedNode = 0; 
			if (ind == 0) { // pop at the beginning; 
				if (len == 1) {
					sparedNode = 1;
				}
				else {
					sparedNode = list[1].next; 
					// swap data; 
					list[sparedNode].val += list[1].val;
					list[1].val = list[sparedNode].val - list[1].val;
					list[sparedNode].val -= list[1].val;
					// pop node; 
					list[1].next = list[sparedNode].next; 
				}
			}
			else {
				size_t mov = 1; 
				while (ind != 1) { // find predecessor; 
					--ind; 
					mov = list[mov].next; 
				}
				sparedNode = list[mov].next; 
				list[mov].next = list[sparedNode].next; 
			}

			// send value and modify spare list; 
			dest = list[sparedNode].val;
			if (sparedNode == 1) { // if list[1] is poped, 
									// it must be inserted right after list[0] in the spared list; 
									// in this case, the current length of spared list must be maxsize - 1; 
				list[1].next = list[0].next; 
				list[0].next = 1; 
			}
			else {
				list[sparedNode].next = list[0].next; 
				list[0].next = sparedNode; 
			}

			return; 
		}

		/* Destructor */
		void LkList_destroy(LinkedList& list)
		{
			free(list); 

			return; 
		}
	#endif /* Static linked list, statically allocated */

#endif /* Structure datatype linearlist */

/* Structure datatype stack, queue and string */
#ifdef STACK_STRUCT_STATIC

	/* Static stack */
	#if 1
		/* Initializer */
		void Stack_init(Stack& stack)
		{
			// initialize all the elements to 0; 
			memset(stack.val, 0, kMaxSize * sizeof(DataType));
			// initialize list length; 
			stack.top = 0;

			return;
		}

		/* get - functions */
		void Stack_getTop(const Stack stack, DataType& dest)
		{
			dest = stack.val[stack.top];

			return;
		}

		/* Discriminants */
		bool Stack_isEmpty(const Stack stack)
		{
			return (stack.top == 0);
		}

		/* print */
		void Stack_print(const Stack stack)
		{
			if (Stack_isEmpty(stack)) {
				// for empty list, print prompt; 
				std::cout << "Empty stack. " << std::endl;
			}
			else {
				for (size_t index = 1; index <= stack.top; ++index) {
					std::cout << stack.val[index] << ' ';
				}
				std::cout << std::endl;
			}

			return;
		}

		/* atomic functions */
		void Stack_push(Stack& stack, DataType src)
		{
			if (stack.top == kMaxSize - 1) {
				std::cout << "MeomoryError: Not Enough Memory Allocated" << std::endl;

				return;
			}

			++stack.top;
			stack.val[stack.top] = src;

			return;
		}
		void Stack_pop(Stack& stack, DataType& dest)
		{
			if (Stack_isEmpty(stack)) {
				std::cout << "Warning: Nothing to pop" << std::endl;

				return;
			}

			Stack_getTop(stack, dest);
			--stack.top;

			return;
		}

		/* Destructor */
		void Stack_destroy(Stack stack)
		{
			memset(stack.val, 0, kMaxSize * sizeof(DataType));
			stack.top = 0;

			return;
		}
	#endif /* Static stack */

	/* Static queue */
	#if 1

	#endif /* Static queue */

	/* Static doubly-ended queue */
	#if 1

	#endif /* Static doubly-ended queue */

	/* Static string */
	#if 1
		/* Initializer */
		void StrInit(String& str)
		{
			str.head = (char*)malloc(kMaxSize * sizeof(char)); 
			if (str.head == nullptr) {
				std::cout << "MemoryError: Allocation Failure" << std::endl; 

				return; 
			}

			str.length = 0; 

			return; 
		}

		/* Discriminants */
		bool StrEmpty(const String str)
		{
			return (str.length == 0); 
		}

		/* get-functions */
		size_t StrLen(const String str)
		{
			return str.length; 
		}
		void StrPrint(const String str) 
		{
			size_t index = 0; 
			std::cout << '\"'; 
			while (index < str.length) {
				std::cout << str.head[index]; 
				++index; 
			}
			std::cout << '\"';
			std::cout << std::endl; 

			return; 
		}

		/* atom functions */
		void StrAssign(String& str, const char* src)
		{
			// set probe; 
			size_t index = 0; 
			str.length = 0; 

			while (src[index] != '\0') {
				if (str.length == kMaxSize) {
					std::cout << "IndexWarning: Source string longer than "; 
					std::cout << "String type could hold. " << std::endl; 

					break; 
				}

				str.head[str.length] = src[index];
				++str.length;
				++index; 
			}

			return; 
		}
		void StrCpy(String& dest, const String src)
		{
			SubStr(dest, src, 0, src.length); 

			return;
		}
		int StrCmp(const String dest, const String src)
		{
			// set probe; 
			size_t index = 0; 
			size_t jndex = 0; 
			int result = 0; 

			while (index < src.length && jndex < dest.length) {
				result = src.head[index] - dest.head[jndex]; 

				if (result != 0) {
					return result; 
				}

				++index; 
				++jndex; 
			}

			if (src.length == dest.length) {
				return result; 
			}
			else if (src.length > dest.length) {
				return src.head[index]; 
			}
			else {
				return -dest.head[jndex];
			}
		}
		void StrCat(String& dest, const String src1, const String src2)
		{
			if (src1.length + src2.length > kMaxSize) {
				std::cout << "MemoryError: Result string longer than "; 
				std::cout << "String type could hold. " << std::endl; 

				return; 
			}

			StrCpy(dest, src1);

			// set probe; 
			size_t index = 0;

			while (dest.length < src1.length + src2.length) {
				dest.head[dest.length] = src2.head[index];
				++dest.length;
				++index;
			}

			return;
		}
		void SubStr(String& dest, const String src, size_t indH, size_t len)
		{
			if (indH >= src.length || indH + len > src.length) {
				std::cout << "IndexError: Index Overflow" << std::endl; 

				return; 
			}

			// set probe; 
			size_t index = indH;
			dest.length = 0;

			while (dest.length < len) {
				dest.head[dest.length] = src.head[index];
				++dest.length;
				++index;
			}

			return;
		}
		void StrClr(String& str)
		{
			str.length = 0; 

			return; 
		}

		/* extended functions */
		// KMP algorithm; 
		// If substr[j] missed str[i], 
		// then all the chars before substr[PMT[j] - 1](included) match str 
		// when comparing substr[PMT[j]] and str[i + 1]; 
		// PMT[j] is the Partial Match Value of substr[j], 
		// which is the length of the longest matching prefix and suffix of substr[0, j-1]; 
		static int* KMPgetPMT(int*& PMT, const String substr)
		{
			PMT[0] = -1; 
			PMT[1] = 0; 

			size_t jndex = 2; 
			size_t kndex = 0; 
			while (jndex < substr.length) {
				kndex = jndex - 1; 
				while (substr.head[jndex - 1] != substr.head[PMT[kndex]]) {
					kndex = PMT[kndex]; 

					if (kndex == 0) {
						break; 
					}
				}
				PMT[jndex] = PMT[kndex] + 1; 

				++jndex;
			}

			return PMT; 
		}
		static void KMPfreePMT(int*& PMT)
		{
			free(PMT); 

			return; 
		}
		int FindSubStr(const String str, const String substr)
		{
			if (substr.length > str.length || StrEmpty(str)) {
				return -1; 
			}
			if (StrEmpty(substr)) {
				std::cout << "InputWarning: Searching for empty substring. " << std::endl; 

				return -1; 
			}

			// now substr.length > 0; 
			int* PMT = (int*)malloc(substr.length * sizeof(int));
			KMPgetPMT(PMT, substr);

			// set probe; 
			size_t index = 0; 
			size_t jndex = 0; 

			while (index < str.length && jndex < substr.length) {
				if (str.head[index] == substr.head[jndex]) {
					++index; 
					++jndex; 
				}
				else {
					jndex = PMT[jndex];

					if (jndex == -1) {
						jndex = 0; 
						++index; 
					}
				}
			}

			KMPfreePMT(PMT); 

			if (jndex == substr.length) {
				return index - substr.length; 
			}
			else {
				return -1; 
			}
		}

		/* Destructor */
		void StrDestroy(String& str)
		{
			free(str.head); 
			str.length = 0; 

			return; 
		}
	#endif /* Static string */
#endif /* Structure datatype stack, queue and string */

/* Class datatype */
#ifdef LINEARLIST_CLASS

	/* Node */
	#if 1
		template <typename DataType>
		Node<DataType>::Node(void) :
			next_(nullptr)
		{
			memset(&(this->val_), 0, sizeof(DataType));
		}
		template <typename DataType>
		Node<DataType>::Node(DataType val, Node<DataType>* next) :
			val_(val),
			next_(next)
		{

		}
		template <typename DataType>
		Node<DataType>::~Node(void)
		{

		}

		template <typename DataType>
		DataType Node<DataType>::getVal(void) const
		{
			return this->val_; 
		}
		template <typename DataType>
		Node<DataType>* Node<DataType>::getNext(void) const
		{
			return this->next_; 
		}
		template <typename DataType>
		void Node<DataType>::setVal(DataType newVal)
		{
			this->val_ = newVal; 

			return; 
		}
		template <typename DataType>
		void Node<DataType>::setNext(Node<DataType>* newNext)
		{
			this->next_ = newNext; 

			return; 
		}
	#endif /* Node */

	/* DNode */
	#if 1
		template <typename DataType>
		DNode<DataType>::DNode(void) :
			next_(nullptr),
			pred_(nullptr)
		{
			memset(&(this->val_), 0, sizeof(DataType));
		}
		template <typename DataType>
		DNode<DataType>::DNode(DataType val, DNode<DataType>* next, DNode<DataType>* pred) :
			val_(val),
			next_(next),
			pred_(pred)
		{

		}
		template <typename DataType>
		DNode<DataType>::~DNode(void)
		{

		}

		template <typename DataType>
		DataType DNode<DataType>::getVal(void) const
		{
			return this->val_;
		}
		template <typename DataType>
		DNode<DataType>* DNode<DataType>::getNext(void) const
		{
			return this->next_;
		}
		template <typename DataType>
		DNode<DataType>* DNode<DataType>::getPred(void) const
		{
			return this->pred_; 
		}
		template <typename DataType>
		void DNode<DataType>::setVal(DataType newVal)
		{
			this->val_ = newVal;

			return;
		}
		template <typename DataType>
		void DNode<DataType>::setNext(DNode<DataType>* newNext)
		{
			this->next_ = newNext;

			return;
		}
		template <typename DataType>
		void DNode<DataType>::setPred(DNode<DataType>* newPred)
	{
		this->pred_ = newPred; 
	}
	#endif /* DNode */

	/* List */
	template <typename DataType>
	List<DataType>::List(void)
	{

	}
	template <typename DataType>
	List<DataType>::~List(void)
	{

	}

	/* LinkedList */
	#if 1
		template <typename DataType>
		LinkedList<DataType>::LinkedList(void) :
			List<DataType>()
		{
			this->head_ = new Node<DataType>;
		}
		template <typename DataType>
		LinkedList<DataType>::~LinkedList(void)
		{
			// set probe; 
			Node<DataType>* mov = this->getFirst();

			// delete data nodes; 
			while (mov != nullptr) {
				this->setFirst(mov->getNext());
				delete mov;
				mov = this->getFirst();
			}
			// delete header node; 
			delete this->head_;
		}

		template <typename DataType>
		bool LinkedList<DataType>::isEmpty(void) const
		{
			return (this->getFirst() == nullptr);
		}

		template <typename DataType>
		size_t LinkedList<DataType>::getLength(void) const
		{
			// set probe; 
			Node<DataType>* mov = this->getFirst();
			// set counter; 
			size_t len = 0; 

			// count nodes; 
			while (mov != nullptr) {
				++len; 
				mov = mov->getNext(); 
			}

			return len; 
		}
		template <typename DataType>
		void LinkedList<DataType>::print(void) const
		{
			if (this->isEmpty()) {
				std::cout << "Empty list. " << std::endl; 
			}
			else {
				// set probe; 
				Node<DataType>* mov = this->getFirst(); 
			
				// traverse; 
				while (mov != nullptr) {
					std::cout << mov->getVal() << ' '; 
					mov = mov->getNext(); 
				}
				std::cout << std::endl; 
			}

			return; 
		}

		template <typename DataType>
		int LinkedList<DataType>::find(DataType target) const
		{
			// set probe; 
			Node<DataType>* mov = this->getFirst(); 
			// set counter; 
			int ind = 0; 

			// find; 
			while (mov != nullptr) {
				if (mov->getVal() == target) { // found; 
					return ind; 
				}

				++ind; 
				mov = mov->getNext(); 
			}

			// not found; 
			return -1; 
		}
		template <typename DataType>
		DataType LinkedList<DataType>::at(size_t ind) const
		{
			// check legal ind; 
			size_t len = this->getLength(); 
			if (ind >= len) { // Index Overflow; 
				throw IndexOverflow();
			}

			// set probe; 
			Node<DataType>* mov = this->getFirst(); 
			while (ind != 0) {
				--ind; 
				mov = mov->getNext(); 
			}

			return mov->getVal(); 
		}
		template <typename DataType>
		void LinkedList<DataType>::insert(size_t ind, DataType src)
		{
			// check legal ind; 
			size_t len = this->getLength(); 
			if (ind > len) {
				throw IndexOverflow(); 
			}

			// set probe; 
			Node<DataType>* prev = this->head_; 
			while (ind != 0) { // find predecessor; 
				--ind; 
				prev = prev->getNext(); 
			}
			// add to list; 
			Node<DataType>* newNode = new Node<DataType>(src, prev->getNext());
			prev->setNext(newNode); 

			return; 
		}
		template <typename DataType>
		void LinkedList<DataType>::del(size_t ind, DataType& dest)
		{
			// check legal ind; 
			size_t len = this->getLength(); 
			if (ind >= len) {
				throw IndexOverflow(); 
			}

			// set probe;
			Node<DataType>* prev = this->head_; 
			while (ind != 0) {
				--ind; 
				prev = prev->getNext(); 
			}
			// remove from list; 
			Node<DataType>* trashNode = prev->getNext(); 
			prev->setNext(trashNode->getNext()); 
			delete trashNode; 

			return; 
		}

		template <typename DataType>
		Node<DataType>* LinkedList<DataType>::getFirst(void) const
		{
			return this->head_->getNext(); 
		}
		template <typename DataType>
		void LinkedList<DataType>::setFirst(Node<DataType>* newFirst)
	{
		this->head_->setNext(newFirst); 

		return; 
	}
	#endif /* LinkedList */

	/* Stack */
	#if 1
		template <typename DataType>
		Stack<DataType>::Stack(void) :
			List<DataType>()
		{
			this->head_ = new Node<DataType>; 
		}
		template <typename DataType>
		Stack<DataType>::~Stack(void)
		{
			// set probe; 
			Node<DataType>* mov = this->getFirst(); 
			while (mov != nullptr) {
				this->setFirst(mov->getNext()); 
				delete mov; 
				mov = this->getFirst(); 
			}
			delete this->head_; 
		}

		template <typename DataType>
		bool Stack<DataType>::isEmpty(void) const
		{
			return (this->getFirst() == nullptr);
		}

		template <typename DataType>
		DataType Stack<DataType>::getTop(void) const
		{
			if (this->isEmpty()) {
				throw IndexOverflow(); 
			}

			return this->getFirst()->getVal();
		}
		template <typename DataType>
		void Stack<DataType>::print(void) const
		{
			if (this->isEmpty()) {
				std::cout << "Empty stack. " << std::endl; 

				return; 
			}

			// set probe; 
			Node<DataType>* mov = this->getFirst(); 
			while (mov != nullptr) {
				std::cout << mov->getVal() << ' '; 

				mov = mov->getNext();
			}
			std::cout << std::endl; 

			return; 
		}

		template <typename DataType>
		void Stack<DataType>::push(DataType src)
		{
			Node<DataType>* newNode = new Node<DataType>(src, this->getFirst());

			this->setFirst(newNode); 

			return; 
		}
		template <typename DataType>
		void Stack<DataType>::pop(DataType& dest)
		{
			if (this->isEmpty()) {
				throw IndexOverflow(); 
			}

			dest = this->getTop(); 
			Node<DataType>* first = this->getFirst(); 
			this->setFirst(first->getNext()); 
			delete first; 

			return; 
		}

		template <typename DataType>
		Node<DataType>* Stack<DataType>::getFirst(void) const
		{
			return this->head_->getNext();
		}
		template <typename DataType>
		void Stack<DataType>::setFirst(Node<DataType>* newFirst)
		{
			this->head_->setNext(newFirst);

			return;
		}

	#endif /* Stack */

	/* Queue */
	#if 1
		template <typename DataType>
		Queue<DataType>::Queue(void) :
			List<DataType>()
		{
			this->head_ = new Node<DataType>; 
			this->rear_ = this->head_; 
		}
		template <typename DataType>
		Queue<DataType>::~Queue(void)
		{
			Node<DataType>* mov = this->getFirst(); 
			while (mov != nullptr) {
				this->setFirst(mov->getNext()); 
				delete mov; 
				mov = this->getFirst(); 
			}
			delete this->head_; 
			// Notice: rear_ will either be head_ (for empty queues) 
			// or be mov eventually (for non-empty queues),
			// which in either way will be deleted in the end; 
			// So there is no need to write "delete this->rear_" explicitly; 
		}

		template <typename DataType>
		bool Queue<DataType>::isEmpty(void) const
		{
			return (this->getFirst() == nullptr); 
		}

		template <typename DataType>
		DataType Queue<DataType>::getFront(void) const
		{
			return (this->getFirst()->getVal()); 
		}
		template <typename DataType>
		void Queue<DataType>::print(void) const
		{
			if (this->isEmpty()) {
				std::cout << "Empty queue. " << std::endl; 

				return; 
			}

			// set probe; 
			Node<DataType>* mov = this->getFirst(); 
			while (mov != nullptr) {
				std::cout << mov->getVal() << ' '; 
			}
			std::cout << std::endl; 

			return; 
		}

		template <typename DataType>
		void Queue<DataType>::pushBack(DataType src)
		{
			Node<DataType>* newNode = new Node<DataType>(src); 

			this->rear_->setNext(newNode); 
			this->rear_ = newNode; 

			return; 
		}
		template <typename DataType>
		void Queue<DataType>::pop(DataType& dest)
		{
			if (this->isEmpty()) {
				throw IndexOverflow(); 
			}

			dest = this->getFirst()->getVal(); 
			// for queues with only one element; 
			if (this->getFirst() == this->rear_) {
				this->rear_ = this->head; 
			}

			Node<DataType>* first = this->getFirst(); 
			this->setFirst(first->getNext()); 
			delete first; 

			return; 
		}

		template <typename DataType>
		Node<DataType>* Queue<DataType>::getFirst(void) const
		{
			return this->head_->getNext();
		}
		template <typename DataType>
		void Queue<DataType>::setFirst(Node<DataType>* newFirst)
		{
			this->head_->setNext(newFirst);

			return;
		}
	#endif /* Queue */

	/* Deque */
		/* The implementation is cyclic. */
	#if 1
		template <typename DataType>
		Deque<DataType>::Deque(void)
		{
			this->head_ = new DNode<DataType>(0, this->head_, this->head_);
		}
		template <typename DataType>
		Deque<DataType>::~Deque(void)
		{
			DNode<DataType>* mov = this->getFirst(); 
			while (mov != this->head_) {
				mov->getNext()->setPred(mov->getPred()); 
				mov->getPred()->setNext(mov->getNext()); 
				delete mov; 
				mov = this->getFirst(); 
			}
			delete this->head_; 
		}

		template <typename DataType>
		bool Deque<DataType>::isEmpty(void) const
		{
			return (this->getFirst() == this->head_); 
		}

		template <typename DataType>
		DataType Deque<DataType>::getFront(void) const
		{
			if (this->isEmpty()) {
				throw IndexOverflow(); 
			}

			return (this->getFirst()->getVal()); 
		}
		template <typename DataType>
		DataType Deque<DataType>::getBack(void) const
		{
			if (this->isEmpty()) {
				throw IndexOverflow();
			}

			return (this->getLast()->getVal()); 
		}
		template <typename DataType>
		void Deque<DataType>::print(void) const
		{
			if (this->isEmpty()) {
				std::cout << "Empty doubly-ended queue. " << std::endl; 

				return; 
			}

			DNode<DataType>* mov = this->getFirst(); 
			while (mov != this->head_) {
				std::cout << mov->getVal() << ' '; 
			}
			std::cout << std::endl; 

			return; 
		}

		template <typename DataType>
		void Deque<DataType>::push(DataType src)
		{
			DNode<DataType>* newNode = new DNode<DataType>(src, this->getFirst(), this->head_); 

			this->getFirst()->setPred(newNode); 
			this->setFirst(newNode); 

			return; 
		}
		template <typename DataType>
		void Deque<DataType>::pushBack(DataType src)
		{
			DNode<DataType>* newNode = new DNode<DataType>(src, this->head_, this->getLast());

			this->getLast()->setNext(newNode);
			this->setLast(newNode);

			return;
		}
		template <typename DataType>
		void Deque<DataType>::popFront(DataType& dest)
		{
			if (this->isEmpty()) {
				throw IndexOverflow(); 
			}

			DNode<DataType>* first = this->getFirst(); 
			first->getNext()->setPred(first->getPred()); 
			first->getPred()->setNext(first->getNext()); 
			delete first; 

			return; 
		}
		template <typename DataType>
		void Deque<DataType>::pop(DataType& dest)
		{
			if (this->isEmpty()) {
				throw IndexOverflow();
			}

			DNode<DataType>* last = this->getLast();
			last->getNext()->setPred(last->getPred());
			last->getPred()->setNext(last->getNext());
			delete last;

			return;
		}

		template <typename DataType>
		DNode<DataType>* Deque<DataType>::getFirst(void) const
		{
			return (this->head_->getNext()); 
		}
		template <typename DataType>
		DNode<DataType>* Deque<DataType>::getLast(void) const
		{
			return (this->head_->getPred()); 
		}
		template <typename DataType>
		void Deque<DataType>::setFirst(DNode<DataType>* newFirst)
		{
			this->head_->setNext(newFirst); 

			return; 
		}
		template <typename DataType>
		void Deque<DataType>::setLast(DNode<DataType>* newLast)
		{
			this->head_->setPred(newLast); 
		}
	#endif /* Deque */

	/* String */
	#if 1
		String::String(const char* src)
		{
			if (src == nullptr) {
				this->length_ = 0; 
				this->capacity_ = 100;
				this->str_ = (char*)malloc((this->capacity_ + 1) * sizeof(char));

				if (this->str_ == nullptr) {
					throw AllocationFailure();
				}
			}
			else {
				this->length_ = strlen(src);
				this->capacity_ = 2 * this->length_;
				this->str_ = (char*)malloc((this->capacity_ + 1) * sizeof(char));

				if (this->str_ == nullptr) {
					throw AllocationFailure();
				}

				size_t index = 0;
				while (index < this->length_) {
					this->str_[index] = src[index];
					++index;
				}
				this->str_[index] = '\0';
			}
		}
		String::String(const String& str)
		{
			char* src = str.str_;
			if (src == nullptr) {
				this->length_ = 0;
				this->capacity_ = 100;
				this->str_ = (char*)malloc((this->capacity_ + 1) * sizeof(char));

				if (this->str_ == nullptr) {
					throw AllocationFailure();
				}
			}
			else {
				this->length_ = strlen(src);
				this->capacity_ = 2 * this->length_;
				this->str_ = (char*)malloc((this->capacity_ + 1) * sizeof(char));

				if (this->str_ == nullptr) {
					throw AllocationFailure();
				}

				size_t index = 0;
				while (index < this->length_) {
					this->str_[index] = src[index];
					++index;
				}
				this->str_[index] = '\0';
			}
		}
		String::~String(void)
		{
			free(this->str_); 
			this->length_ = 0; 
			this->capacity_ = 0; 
		}

		bool String::isEmpty(void) const
		{
			return (this->length_ == 0); 
		}

		size_t String::getLength(void) const
		{
			return (this->length_); 
		}
		void String::print(void) const
		{
			std::cout << '\"' << this->str_ << '\"' << std::endl; 

			return; 
		}

		String& String::operator=(const char* src)
		{
			this->length_ = strlen(src); 

			if (this->length_ > this->capacity_) {
				this->capacity_ = 2 * length_;
				char* temp = (char*)realloc(this->str_, (this->capacity_ + 1) * sizeof(char)); 
				if (temp == nullptr) {
					throw AllocationFailure(); 
				}
				this->str_ = temp; 
			}

			size_t index = 0;
			while (index < this->length_) {
				this->str_[index] = src[index]; 
				++index; 
			}
			this->str_[index] = '\0'; 

			return *this; 
		}
		String& String::operator=(const String& src)
		{
			return (*this = src.str_); 
		}

		bool String::operator>(const char* src) const
		{
			size_t index = 0; 
			size_t len = strlen(src); 
			while (index <= this->length_ && index <= len) {
				if (this->str_[index] < src[index]) {
					return false;
				}
				if (this->str_[index] > src[index]) {
					return true;
				}

				++index; 
			}

			return false; 
		}
		bool String::operator>(const String& src) const
		{
			return (*this > src.str_);
		}
		bool String::operator<(const char* src) const
		{
			size_t index = 0;
			size_t len = strlen(src);
			while (index <= this->length_ && index <= len) {
				if (this->str_[index] > src[index]) {
					return false;
				}
				if (this->str_[index] < src[index]) {
					return true;
				}

				++index;
			}

			return false;
		}
		bool String::operator<(const String& src) const
		{
			return (*this < src.str_);
		}
		bool String::operator==(const char* src) const
		{
			size_t len = strlen(src);
			if (this->length_ != len) {
				return false;
			}

			size_t index = 0;
			while (index < len) {
				if (this->str_[index] != src[index]) {
					return false;
				}

				++index;
			}

			return true;
		}
		bool String::operator==(const String& src) const
		{
			return (*this == src.str_);
		}
		bool String::operator!=(const char* src) const
		{
			size_t len = strlen(src);
			if (this->length_ != len) {
				return true;
			}

			size_t index = 0;
			while (index < len) {
				if (this->str_[index] != src[index]) {
					return true;
				}

				++index;
			}

			return false;
		}
		bool String::operator!=(const String& src) const
		{
			return (*this != src.str_);
		}

		String String::operator+(const char* src) const
		{
			String result; 

			result += *this; 
			result += src; 

			return result;
		}
		String String::operator+(const char src) const
		{
			char temp[2] = { src, '\0'};

			return this->operator+(temp); 
		}
		String String::operator+(const String& tail) const
		{
			return (this->operator+(tail.str_));
		}
		String& String::operator+=(const char* src)
		{
			size_t len = strlen(src);

			if (this->capacity_ < this->length_ + len) {
				char* temp = (char*)realloc(this->str_, (2 * (this->length_ + len) + 1) * sizeof(char));
				if (temp == nullptr) {
					throw AllocationFailure();
				}

				this->capacity_ = 2 * (this->length_ + len);
				this->str_ = temp;
			}

			size_t index = 0;
			while (index <= len) {
				this->str_[this->length_ + index] = src[index];

				++index;
			}
			this->length_ += len;

			return *this;
		}
		String& String::operator+=(const char src)
		{
			char temp[2] = { src, '\0'};
			
			return this->operator+=(temp); 
		}
		String& String::operator+=(const String& tail)
		{
			return (this->operator+=(tail.str_));
		}

		// Slicing; for C++23 [] can accept multiple arguments; 
		char& String::operator[](int ind) const
		{
			if (ind >= 0 && ind < this->length_) {
				return this->str_[ind]; 
			}
			else if (ind < 0 && -ind <= this->length_) {
				return this->str_[this->length_ + ind]; 
			}
			else {
				throw IndexOverflow(); 
			}
		}
		String String::operator()(int indH, int indT, int step) const
		{
			if (step == 0) {
				throw MemoryOverflow(); 
			}
			else if ((step < 0 && indH < indT) || (step > 0 && indH > indT)) {
				throw MemoryOverflow(); 
			}

			String result; 
			if (indH == indT) {
				return result; 
			}

			int index = 0; 
			if (indH < indT) {
				while (indH + index * step < indT) {
					result += (*this)[indH + index * step];

					++index; 
				}
			}
			else {
				while (indH + index * step > indT) {
					result += (*this)[indH + index * step];

					++index;
				}
			}

			return result; 
		}
		void String::clear(void)
		{
			char* temp = (char*)realloc(this->str_, sizeof(char)); 
			if (temp == nullptr) {
				throw AllocationFailure(); 
			}

			this->str_ = temp; 
			this->str_[0] = '\0'; 
			this->length_ = 0; 
			this->capacity_ = 0; 
			
			return; 
		}

		/* KMP algorithm */
		// If substr[j] missed str[i], 
		// then all the chars before substr[PMT[j] - 1](included) match str 
		// when comparing substr[PMT[j]] and str[i + 1]; 
		// PMT[j] is the Partial Match Value of substr[j], 
		// which is the length of the longest matching prefix and suffix of substr[0, j-1]; 
		static int* KMPgetPMT(int*& PMT, const char* substr)
		{
			PMT[0] = -1;
			PMT[1] = 0;

			size_t len = strlen(substr); 
			size_t jndex = 2;
			size_t kndex = 0;
			while (jndex < len) {
				kndex = jndex - 1;
				while (substr[jndex - 1] != substr[PMT[kndex]]) {
					kndex = PMT[kndex];

					if (kndex == 0) {
						break;
					}
				}
				PMT[jndex] = PMT[kndex] + 1;

				++jndex;
			}

			return PMT;
		}
		int String::find(const char* substr)
		{

			size_t len = strlen(substr); 
			if (len > this->length_ || this->isEmpty()) {
				return -1;
			}
			if (len == 0) {
				return -1;
			}

			// now len > 0; 
			int* PMT = new int[len * sizeof(int)];
			KMPgetPMT(PMT, substr);

			// set probe; 
			size_t index = 0;
			size_t jndex = 0;

			while (index < this->length_ && jndex < len) {
				if ((*this)[index] == substr[jndex]) {
					++index;
					++jndex;
				}
				else {
					jndex = PMT[jndex];

					if (jndex == -1) {
						jndex = 0;
						++index;
					}
				}
			}

			delete[] PMT; 

			if (jndex == len) {
				return index - len;
			}
			else {
				return -1;
			}
		}
		int String::find(const String& substr)
		{
			char* temp = substr.str_; 

			return this->find(temp);
		}

	#endif /* String */

#endif /* Class datatype */