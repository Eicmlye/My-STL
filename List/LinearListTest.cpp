#include <iostream>

#include "LinearList.h"
#include "Exception.h"	

using std::cout; 
using std::endl; 

#define TEST_EMPTY_STR(str) \
			cout << "Is " #str " empty? " << str.isEmpty() << endl
#define TEST_LEN_STR(str) \
			cout << "The length of " #str " is " << str.getLength() << endl
#define TEST_BOOL_STRING(str, cache, sign) \
			cout << "Is str " #sign " cache? " << (str sign cache) << endl

static void test_all_bool_str(const String str, const String cache);
static void test_str(const String str, const String cache, const char* strstr, const char* cachestr); 

int main(void)
{
	cout << std::boolalpha;

#if 1
	/* Struct linkedlist */
	#if 0
		LinkedList list = nullptr;

		LkList_init(list);
		LkList_print(list);
		cout << std::boolalpha << "List is empty? " << LkList_isEmpty(list) << endl << endl;

		for (int num = 0; num < 9; ++num) {
			LkList_insert(list, LkList_getLength(list), num - 4);
		}

		LkList_print(list);
		cout << "List is empty? " << LkList_isEmpty(list) << endl ;
		cout << LkList_getLength(list) << endl << endl;

		LkList_insert(list, 5, 10);
		LkList_print(list);
		LkList_insert(list, 0, 11);
		LkList_print(list);
		LkList_insert(list, 12, -20);
		LkList_print(list);
		cout << "List is empty? " << LkList_isEmpty(list) << endl;
		cout << LkList_getLength(list) << endl << endl;

	#if 1
		cout << LkList_find(list, -1) << endl;
		cout << LkList_find(list, -100) << endl;
		cout << LkList_getValue(list, 5) << endl;
		cout << LkList_getValue(list, 500) << endl;
	#endif

		int temp = 0; 
		for (int num = 0; num < 9; ++num) {
			LkList_pop(list, LkList_getLength(list) - 1, temp);
		}
		LkList_print(list);
		cout << "List is empty? " << LkList_isEmpty(list) << endl;
		cout << LkList_getLength(list) << endl << endl;

		LkList_pop(list, 0, temp);
		LkList_print(list);
		LkList_pop(list, 0, temp);
		LkList_print(list);
		LkList_pop(list, 0, temp);
		LkList_print(list);
		cout << "List is empty? " << LkList_isEmpty(list) << endl;
		cout << LkList_getLength(list) << endl << endl;

		for (int num = 0; num < 9; ++num) {
			LkList_insert(list, LkList_getLength(list), num - 4);
		}

		LkList_print(list);
		cout << "List is empty? " << LkList_isEmpty(list) << endl;
		cout << LkList_getLength(list) << endl << endl;

		LkList_destroy(list); 
	#endif

	/* Class linkedlist */
	#if 0
		#define LENGTH(list) \
			cout << "The length of the list is " << list.getLength() << ". " << endl
		#define EMPTY(list) \
			cout << "Is the list empty? " << std::boolalpha << list.isEmpty() << endl
		#define CHECK(list) \
			do {\
				list.print(); \
				LENGTH(list); \
				EMPTY(list); \
				cout << endl; \
			} while (0)

	LinkedList<int> list;

	CHECK(list); 
	
	for (int index = 0; index < 9; ++index) {
		list.insert(list.getLength(), index - 4);
	}
	CHECK(list); 

	cout << "The data at index 2 is " << list.at(2) << endl;
	cout << "The data 2 is at index " << list.find(2) << endl;
	cout << "The data at index 10 is "; 
	try {
		cout << list.at(10) << endl;
	}
	catch (IndexOverflow& e) {
		e.what(); 
	}
	cout << "The data 10 is at index " << list.find(10) << endl << endl;

	int temp; 
	for (int index = 0; index < 9; ++index) {
		list.del(list.getLength() - 1, temp);
	}
	CHECK(list);
	#endif

	/* Struct stack */
	#if 0
		Stack stack; 
		Stack_init(stack); 

		Stack_print(stack);
		cout << std::boolalpha << Stack_isEmpty(stack) << endl << endl; 

		DataType temp = 0; 
		for (size_t index = 1; index <= 9; ++index) {
			Stack_push(stack, index - 5); 
		}
		Stack_print(stack); 
		Stack_getTop(stack, temp); 
		cout << temp << endl; 
		cout << std::boolalpha << Stack_isEmpty(stack) << endl << endl;

		for (size_t index = 1; index <= 5; ++index) {
			Stack_pop(stack, temp);
		}
		Stack_print(stack);
		Stack_getTop(stack, temp);
		cout << temp << endl;
		cout << std::boolalpha << Stack_isEmpty(stack) << endl << endl;

		Stack_destroy(stack); 

	#endif

	/* Class stack */
	#if 0
		Stack<int> stk; 

		for (int index = 0; index < 9; ++index) {
			stk.push(index - 4); 
		}
		stk.print(); 
		cout << "Stack top: " << stk.getTop() << endl; 
		cout << std::boolalpha << "Is stack empty? " << stk.isEmpty() << endl << endl; 

		int temp = 0; 
		stk.pop(temp); 
		cout << "temp = " << temp << endl;
		stk.print();
		cout << "Stack top: " << stk.getTop() << endl;
		cout << std::boolalpha << "Is stack empty? " << stk.isEmpty() << endl << endl;

		for (int index = 0; index < 8; ++index) {
			stk.pop(temp);
		}
		stk.print();
		cout << "Stack top: "; 
		try {
			cout << stk.getTop();
		}
		catch (IndexOverflow& e) {
			e.what();
		}
		cout << endl;
		cout << std::boolalpha << "Is stack empty? " << stk.isEmpty() << endl << endl;

	#endif

	/* Struct string */
	#if 0
		String str, head, tail, littletail; 
		StrInit(str); 
		StrInit(head);
		StrInit(tail);
		StrInit(littletail);

		cout << "-------- Init --------" << endl; 
		cout << std::boolalpha; 
		cout << "Is str empty? " << StrEmpty(str) << endl;
		cout << "Is head empty? " << StrEmpty(head) << endl;
		cout << "Is tail empty? " << StrEmpty(tail) << endl << endl;

		cout << "-------- Assign --------" << endl;
		StrAssign(str, "Hello world!");
		StrPrint(str);
		cout << "Is str empty? " << StrEmpty(str) << endl;
		cout << "Length: " << StrLen(str) << endl << endl;
		StrAssign(head, "I am");
		StrPrint(head);
		cout << "Is head empty? " << StrEmpty(head) << endl;
		cout << "Length: " << StrLen(head) << endl << endl;
		StrAssign(tail, " Eric Monlye");
		StrPrint(tail);
		cout << "Is tail empty? " << StrEmpty(tail) << endl;
		cout << "Length: " << StrLen(tail) << endl << endl;
		StrAssign(littletail, " Eric");
		StrPrint(littletail);
		cout << "Is littletail empty? " << StrEmpty(littletail) << endl;
		cout << "Length: " << StrLen(littletail) << endl << endl;

		cout << "-------- Copy --------" << endl;
		StrCpy(str, head);
		StrPrint(str);
		cout << "Is str empty? " << StrEmpty(str) << endl;
		cout << "Length: " << StrLen(str) << endl << endl;

		cout << "-------- Clear --------" << endl;
		StrClr(str);
		StrPrint(str);
		cout << "Is str empty? " << StrEmpty(str) << endl;
		cout << "Length: " << StrLen(str) << endl << endl;

		cout << "-------- Concat --------" << endl;
		StrCat(str, head, tail);
		StrPrint(str);
		cout << "Is str empty? " << StrEmpty(str) << endl;
		cout << "Length: " << StrLen(str) << endl << endl;
		StrCat(str, head, littletail);
		StrPrint(str);
		cout << "Is str empty? " << StrEmpty(str) << endl;
		cout << "Length: " << StrLen(str) << endl << endl;

		cout << "-------- Compare --------" << endl;
		cout << "str: "; StrPrint(str);
		cout << "head: "; StrPrint(head);
		cout << "tail: "; StrPrint(tail);
		cout << "littletail: "; StrPrint(littletail);
		cout << StrCmp(head, str) << endl;
		cout << StrCmp(head, tail) << endl;

		StrAssign(head, "Hello");
		cout << "str: "; StrPrint(str);
		cout << "head: "; StrPrint(head);
		cout << StrCmp(head, str) << endl;

		cout << "-------- KMP --------" << endl;
		StrAssign(str, "ababcabcacbab"); 
		StrAssign(head, "abaabcaba"); 
		cout << "str: "; StrPrint(str);
		cout << "head: "; StrPrint(head);
		cout << FindSubStr(str, head) << endl;

		StrDestroy(str);
		StrDestroy(head);
		StrDestroy(tail);
		StrDestroy(littletail);
	#endif 

	/* Class string */
	#if 0
		String str, cache;
		test_str(str, cache, "Hello", "Hi");
		test_str(str, cache, "Hello", "Hello");
		test_str(str, cache, "01233", "01234");
		test_str(str, cache, "01223", "01233");
		test_str(str, cache, "0", "01233");
		test_str(str, cache, "0", "");
		test_str(str, cache, "", "");

		str = "Hello"; cache = "Hi";
		str += cache;
		str.print();
		str = str + cache;
		str.print();

		str = "Hello"; cache = "Hi";
		str[-3] = cache[1];
		str.print();
		str = str(4, 0, -1);
		str.print();
		str.clear(); 
		str.print(); 

		str = "ababcabcacac"; 
		str.print(); 
		cout << str.find("abaabcaba") << endl; 

	#endif
#endif

	return 0; 
}


static void test_all_bool_str(const String str, const String cache)
{
	TEST_BOOL_STRING(str, cache, ==);
	TEST_BOOL_STRING(str, cache, >);
	TEST_BOOL_STRING(str, cache, <);
	TEST_BOOL_STRING(str, cache, !=);

	return;
}

static void test_str(String str, String cache, const char* strstr, const char* cachestr)
{
	cout << "--------" << endl; 
	str = strstr; cache = cachestr;
	TEST_EMPTY_STR(str); TEST_EMPTY_STR(cache);
	TEST_LEN_STR(str); TEST_LEN_STR(cache);
	cout << "str = "; str.print();
	cout << "cache = "; cache.print();
	test_all_bool_str(str, cache);
	cout << endl; 

	return; 
}