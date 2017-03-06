
#include "lllist.h"
#include "llvector.h"
#include "lldeque.h"
#include "llheap.h"

using namespace llds;


void tests();

int main() {

	//test_realloc_and_copy();

	//test_llstack();

	//testlist();

	//test_vector();

	test_heap();

	//test_deque();
	std::cin.get();
}

void tests()
{
	typedef int* intpointer;
	typedef intpointer* pp;
	pp a = new intpointer[5];
	for (int i = 0; i < 5; ++i)
		a[i] = nullptr;
	cout << a[0] << " " << a[1] << endl;

	cout << bool(a[0] == nullptr) << endl;
	//a->~int();
	//cout << "successful " << *a << endl;
}
