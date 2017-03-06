#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>


#define __LLDS__BEGIN__NAMESPACE namespace llds{
#define __LLDS__END__NAMESPACE }

__LLDS__BEGIN__NAMESPACE

using std::cout;
using std::endl;
using std::vector;

template <class Vec>
void dataMaker(Vec& v, int range = 10);

template <class Vec>
void printVector(Vec& v);

template <class Pointer, class Val>
Pointer realloc_and_copy(Pointer p, Val, size_t& len);

template <class Pointer, class Val>
Pointer realloc_and_copy(Pointer p, Val, int len);

template <class Pointer, class Val>
void construct(Pointer p, const Val& value);








template<class Vec>
inline void dataMaker(Vec & v, int range)
{
	typedef typename Vec::value_type value_type;
	typedef value_type* pointer;
	typedef value_type& reference;

	for (size_t i = 0; i < v.size(); ++i) {
		v[i] = (value_type)((double)rand() / RAND_MAX * range);
	}
}

template<class Vec>
inline void printVector(Vec & v)
{
	typename Vec::iterator ite;
	for (ite = v.begin(); ite != v.end(); ++ite) {
		cout << *ite << " ";
	}
	cout << endl;
}

template<class Pointer, class Val>
Pointer realloc_and_copy(Pointer p, Val, size_t& len)
{
	Pointer np = new Val[len * 2];

	memcpy(np, p, len * sizeof(Val));

	len *= 2;
	delete[] p;

	return np;
}

template<class Pointer, class Val>
Pointer realloc_and_copy(Pointer p, Val, int len)
{
	Pointer np = new Val[len * 2];

	memcpy(np, p, len * sizeof(Val));

	len *= 2;
	delete[] p;

	return np;
}

template<class Pointer, class Val>
inline void construct(Pointer p, const Val & value)
{
	new(p) Val(value);
}






void test_realloc_and_copy() {
	int *a = new int[5];
	for (int i = 0; i < 5; ++i) {
		a[i] = i;
	}

	for (int i = 0; i < 5; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;

	int *b = realloc_and_copy(&(*a), int(), 5);
	b[5] = 5;

	for (int i = 0; i < 10; ++i) {
		cout << b[i] << " ";
	}
	cout << endl;


}




__LLDS__END__NAMESPACE




