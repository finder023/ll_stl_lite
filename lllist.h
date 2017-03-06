#pragma once

#include "llbase.h"

__LLDS__BEGIN__NAMESPACE

template <class Value>
struct list_node {
	Value val;
	list_node* prev;
	list_node* next;
	list_node() :prev(nullptr), next(nullptr) {}
	list_node(Value _val) :prev(nullptr), next(nullptr) { construct(&val, _val); }
};


template <class Value>
struct list_iterator {
	typedef Value value_type;
	typedef Value* pointer;
	typedef Value& reference;
	typedef list_iterator<Value> self;

	list_node<Value>* node;

	list_iterator():node(nullptr){}
	list_iterator(list_node<Value>* n) :node(n) {  }
	list_iterator(const self& x) :node(x.node) {  }

	bool operator==(self& x)const { return x.node == node; }
	bool operator!=(self& x)const { return x.node != node; }

	self& operator++() {
		node = node->next;
		return *this;
	}

	self operator++(int) {
		self temp = *this;
		++*this;
		return temp;
	}

	self& operator--() {
		node = node->prev;
		return *this;
	}

	self operator--(int) {
		self temp = *this;
		--*this;
		return temp;
	}

	reference operator*() const {
		return node->val;
	}

	pointer operator->()const  {
		return &(operator*());
	}
};

template <class Value>
class lllist {
public:
	typedef Value value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef list_node<value_type> node;
	typedef node* node_pointer;
	typedef list_iterator<Value> iterator;
private:
	size_t Size;
	//哨兵
	node_pointer nil;

private:
	node_pointer create_node(value_type val) {
		return new node(val);
	}

public:
	lllist() :Size(0){ 
		nil = create_node(0); 
		nil->prev = nil;
		nil->next = nil;
	}

	~lllist() {
		node_pointer n = nil->next;
		node_pointer m = n->next;
		for (; n != nil; m = m->next) {
			delete n;
			n = m;
		}
		delete nil;
	}

	bool empty() const { return Size == 0; }
	size_t size()const { return Size; }

	iterator begin() const  { return iterator(nil->next); }
	iterator end() const { return iterator(nil); }

	void push_front(value_type val);
	
	void push_back(value_type val);
	
	value_type pop_front();
	
	value_type pop_back();
	//在n节点之后插入新节点
	void insert(node_pointer n, value_type val);

	void erase(node_pointer n);
	
};



template<class Value>
inline void lllist<Value>::push_front(value_type val)
{
	insert(nil, val);
}


template<class Value>
inline void lllist<Value>::push_back(value_type val)
{
	insert(nil->prev, val);
}

template<class Value>
inline typename lllist<Value>::value_type lllist<Value>::pop_front()
{
	if (nil->next == nil)
		return value_type();
	value_type v = nil->next->val;
	erase(nil->next);
	return v;
}

template<class Value>
inline typename lllist<Value>::value_type lllist<Value>::pop_back()
{
	if (nil->prev == nil)
		return value_type();
	value_type v = nil->prev->val;
	erase(nil->prev);
	return v;
}

template<class Value>
inline void lllist<Value>::insert(node_pointer n, value_type val)
{
	node_pointer nn = create_node(val);
	nn->next = n->next;
	nn->next->prev = nn;
	n->next = nn;
	nn->prev = n;
	++Size;
}

template<class Value>
inline void lllist<Value>::erase(node_pointer n)
{
	if (n == nil)
		return;
	n->prev->next = n->next;
	n->next->prev = n->prev;
	delete n;
	--Size;
}



void testlist() {
	lllist<int> llist;
	cout << llist.size() << endl;

	for (int i = 0; i < 5; ++i)
		llist.push_back(i);
	cout << llist.size() << endl;

	for (int i = 0; i < 5; ++i)
		llist.push_front(i);
	cout << llist.size() << endl;

	lllist<int>::iterator x;
	for (x = llist.begin(); x != llist.end(); ++x) {
		cout << *x << " ";
	}
	cout << endl;

	cout << llist.size() << endl;
}


__LLDS__END__NAMESPACE

