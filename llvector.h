#pragma once
#include "llbase.h"

__LLDS__BEGIN__NAMESPACE

template <class Value, size_t init_capa = 0>
class llvector {
public:
	typedef Value value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef pointer iterator;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

private:
	//内存容量
	size_type Capability;
	size_type Size;
	//内存块头指针
	pointer buffer;
	
public:
	llvector() :Capability(0), Size(0), buffer(nullptr) {  }
	~llvector() { delete[] buffer; }

	llvector(size_type len, value_type val) :Capability(len), Size(len), buffer(nullptr) {
		buffer = new value_type[Capability];
		for (size_type i = 0; i != Size; ++i) {
			construct(buffer++, val);
		}
	}
	llvector(pointer st, pointer end):Capability(difference_type(end-st)), 
		Size(difference_type(end-st)), buffer(nullptr){
		buffer = new value_type[Size];
		memcpy(buffer, st, sizeof(value_type) * Size);
	}

	size_type size()const { return Size; }
	size_type capability() const { return Capability; }

	bool empty()const { return Size == 0; }

	iterator begin()const { return buffer; };
	iterator end()const { return buffer + size(); }

	void erase(iterator first, iterator last) {
		memmove(first, last, sizeof(value_type) * difference_type(end() - last));
		Size -= difference_type(last - first);
	}
	void erase(iterator it) {
		erase(it, it + 1);
	}
	
	void push_back(value_type val) {
		if (capability() == 0) {
			buffer = new value_type();
			++Capability;
		}
		else if (capability() == size())
			buffer = realloc_and_copy(buffer, value_type(), Capability);
		construct(buffer + size(), val);
		++Size;
	}

	value_type pop_back() {
		if (!size()) {
			std::cerr << std::endl << "pop_back() failure, empty vector!" << endl;
			return value_type();
		}
		return buffer[--Size];
	}

	reference operator[](size_type n) { return *(begin() + n); }
	reference front() { return *begin(); }
	reference back() { return *(end() - 1); }
};



void test_vector() {
	llvector<int> lv;
	cout << lv.size() << " " << lv.capability() << endl;

	for (int i = 0; i < 9; ++i) {
		lv.push_back(i);
	}
	cout << lv.size() << " " << lv.capability() << endl;

	llvector<int>::iterator it;
	for (it = lv.begin(); it != lv.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	lv.erase(lv.begin() + 1, lv.begin() + 4);

	for (it = lv.begin(); it != lv.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	for (int i = 0; i < 8; ++i) {
		cout << lv.pop_back() << " ";
	}
	cout << endl;

	cout << lv.size() << " " << lv.capability() << endl;


}

__LLDS__END__NAMESPACE