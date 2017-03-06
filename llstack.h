#pragma once

#include "llbase.h"


__LLDS__BEGIN__NAMESPACE

template <class Value, size_t init_capability = 10>
class llstack {
public:
	typedef Value value_type;
	typedef Value* pointer;
	typedef Value& reference;


private:
	//内存指针
	pointer buffer;
	//元素头索引
	int p;
	//内存池大小
	size_t capability;


public:
	llstack():  buffer(nullptr), p(-1), capability(init_capability) { buffer = new Value[capability]; }
	llstack(size_t _capability): buffer(nullptr), p(-1), capability(_capability) { buffer = new Value[capability]; }

	~llstack() { delete[] buffer; }

	void push(Value val) {
		if (++p >= capability) {
			pointer n_buffer = realloc_and_copy(buffer, *buffer, capability);
			delete[] buffer;
			buffer = n_buffer;
		}
		buffer[p] = val;
	}

	value_type pop() {
		if (!empty())
			return buffer[p--];
		else {
			std::cerr << "empty stack!" << endl;
			return Value();
		}

	}

	bool empty() { return p == -1; }
	size_t size() { return p + 1; }
	size_t get_capability() { return capability; }
	reference get_top() { return buffer[p]; }


};



void test_llstack() {
	llds::llstack<int> st;
	for (int i = 0; i < 10; ++i) {
		st.push(i);
	}

	std::cout << st.size() << std::endl;
	std::cout << st.get_capability() << std::endl;
	st.push(10);
	std::cout << st.get_capability() << std::endl;

	for (int i = 0; i < 11; ++i) {
		std::cout << st.pop() << " ";
	}
	std::cout << std::endl;
	std::cout << st.pop() << std::endl;

}


__LLDS__END__NAMESPACE
