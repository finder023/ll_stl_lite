#pragma once

#include "llbase.h"
#include <string>


__LLDS__BEGIN__NAMESPACE


/*
��iterator�е�start_node����Ԫ����deque�е�Ԫ��ͬ������Ҫд��erase��insert�ĺ���
*/

//����������ڲ���ɣ���ϸע��д��ȥ�ɣ���Ҫ����δ��뾡���ܵ����ƣ�д�����Ƶ����ݽṹ���㷨�������Ķ�����


template <class Val, size_t num_elem, size_t num_node >
struct deque_iterator {
	typedef Val value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef pointer* map_pointer;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef deque_iterator<Val, num_elem, num_node> self;

public:
	map_pointer cur_node;
	
	pointer cur_elem;

public:
	deque_iterator() :cur_node(nullptr), cur_elem(nullptr) {  }
	deque_iterator(map_pointer c_n, pointer c_e) :
		cur_node(c_n), cur_elem(c_e) { }

	reference operator*() const { return *cur_elem; }

	pointer operator->()const { return &(operator*()); }

	self& operator++() {
		//����Ѿ������һ��Ԫ�أ���Ϊ�Ƿ�����
		/*if (cur_node == last_node && cur_elem == last_elem ) {
			std::cerr << std::endl << "operation++() forbiden! " << std::endl;
		}*/
		//����ȡ����++������Խ���ж������ǿͻ���Ӧ�ÿ��ǵ�����
		//���Ԫ�����ڴ��������һ��Ԫ�أ����ұ�Ȼ�������һ������ʱ��ת�Ƶ��µĽڵ�ĵ�һ��ֵ
		if (cur_elem == *cur_node + num_elem - 1) {
			++cur_node;
			cur_elem = *cur_node;
		}
		else
			++cur_elem;
		return *this;
	}

	self& operator--() {
		if (cur_elem == *cur_node) {
			--cur_node;
			cur_elem = *cur_node + num_elem - 1;
		}
		else
			--cur_elem;
		return *this;
	}

	self operator--(int) {
		self tmp = *this;
		operator--();
		return tmp;
	}

	self operator++(int) {
		self tmp = *this;
		operator++();
		return tmp;
	}

	self operator+(size_t n) {
		self temp = *this;
		if (n > 0)
			temp += n;
		else
			temp += -n;
		return temp;
	}

	self operator-(size_t n) {
		self temp = *this;
		if (n > 0)
			temp -= n;
		else
			temp += n;
		return temp;
	}

	void operator+=(int n) {
		if (n == 0)
			return;
		if (n > 0) {
			//��������ͬһ�ڵ�
			if (cur_elem + n < *cur_node + num_elem)
				cur_elem += n;
			else {
				//�������½ڵ�����Ҫ������Ԫ�ظ���
				n -= (num_elem - difference_type(cur_elem - *cur_node));
				++cur_node;
				cur_node += n / num_elem;
				cur_elem = *cur_node + n % num_elem;
			}
		}
		else
			operator-=(n);
	}

	void operator-=(int n) {
		if (n == 0)
			return;
		if (n > 0) {
			if (cur_elem - *cur_node >= n)
				cur_elem -= n;
			else {
				n -= (cur_elem - *cur_node + 1);
				--cur_node;
				cur_node -= n / num_elem;
				cur_elem = *cur_node + (num_elem - n % num_elem);
			}
		}
		else
			operator+=(n);
	}


	bool operator!=( self& n) {
		return !(operator==(n));
	}
	bool operator==( self& n) {
		if (n.cur_elem == cur_elem && n.cur_node == cur_node)
			return true;
		return false;
	}

};



template <class Value, size_t num_elem = 10, size_t num_node = 5>
class lldeque {
public:
	typedef Value value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	
	typedef pointer* map_pointer;

	typedef deque_iterator<Value, num_elem, num_node> iterator;
	

private:
	//��������endָ���ǿռ䷶�룬last��ָ����Ԫ�ط���endֻ���жϿռ��Ƿ���ʱ�Żᷢ������

	map_pointer map;

	size_type Size;
	size_type map_size;

	//ע��first �� last ָ�����ʵ�ڵ�Ԫ�أ� ��end,ָ���������λ�ã���ĩβ
	map_pointer first_node;
	map_pointer last_node;

	pointer first_elem;
	pointer last_elem;

	map_pointer start_node;
	map_pointer end_node;


private:
	void realloc_map() {
		map_size *= 2;
		map_pointer new_map = new pointer[map_size];
		//��ʼ���ڴ�ռ䣬����Ҫ
		for (size_t i = 0; i < map_size; ++i)
			new_map[i] = nullptr;
		difference_type node_len = difference_type(last_node - first_node + 1);
		//��ԭ�ڵ�����ֱ�ӿ������µ�ַ��ע�⿽�������ڴ���м䲿�֣�����ǰ�����
		memcpy(new_map + (map_size - node_len) / 2, first_node, sizeof(pointer) * node_len);
		delete[] map;
		map = new_map;
		start_node = map;
		end_node = map + map_size;
		first_node = map + (map_size - node_len) / 2;
		last_node = first_node + node_len - 1;
	}



public:
	lldeque():map(nullptr), Size(0), map_size(num_node), first_node(nullptr), last_node(nullptr),
		first_elem(nullptr), last_elem(nullptr), start_node(nullptr), end_node(nullptr)
	{ 
		map = new pointer[num_node];
		for (int i = 0; i < num_node; ++i) {
			map[i] = nullptr;
		}
		map[num_node / 2] = new value_type[num_elem];
		first_node = last_node = map + num_node / 2;
		start_node = map;
		end_node = map + map_size;
	}

	~lldeque() {
		for (;start_node < end_node; ++start_node)
			if(*start_node != nullptr)
				delete[] (*start_node);
		delete[] map;
		cout << "~lldeque()" << endl;
	}

	size_type size()const { return Size; }

	iterator begin()const { 
		return iterator(first_node,  first_elem); 
	}

	iterator back()const {
		return iterator(last_node, last_elem);
	}

	iterator end() {
		return ++(back());
	}

	void push_back(value_type val) {
		//��ʼ״̬
		if (size() == 0 && first_elem == nullptr && last_elem == nullptr) {
			first_elem = *first_node;
			last_elem = first_elem;
			construct(first_elem, val);
			++Size;
			return;
		}
		
		//��push�������ڴ������һ��Ԫ��ʱ�������һ���ڵ���ָ���ڴ���Ƿ����
		if (last_elem == *last_node + num_elem - 1) {
			//��β���ռ�ڵ�����ʱ�����·���ڵ�ռ�
			if (last_node == end_node - 1)
				realloc_map();
			if(*(++last_node) == nullptr)
				*last_node = new value_type[num_elem];
			last_elem = *last_node;
			construct(last_elem, val);
		}
		else
			construct(++last_elem, val);
		++Size;
	}

	void push_front(value_type val) {
		if (size() == 0 && first_elem == nullptr && last_elem == nullptr) {
			first_elem = *first_node + num_node;
			last_elem = first_elem;
			construct(first_elem, val);
			++Size;
			return;
		}
		if (first_elem == *first_node) {
			if (first_node == start_node)
				realloc_map();
			if (*(--first_node) == nullptr)
				*first_node = new value_type[num_elem];
			first_elem = *first_node + num_elem - 1;
			construct(first_elem, val);
		}
		else
			construct(--first_elem, val);
		++Size;
	}

	value_type pop_back() {
		iterator tmp = back();
		value_type t = *tmp;
		--tmp;
		last_elem = tmp.cur_elem;
		last_node = tmp.cur_node;
		--Size;
		//delete &(*(++tmp));
		return t;
	}

	reference operator[](size_type n) {
		map_pointer cur_n = first_node;
		//������Ԫ�ض���ͬһ���ڴ����ʱ��ֱ�ӷ���
		if (first_elem != *first_node && first_node == last_node)
			return *(*first_node + n);
		//����ʼԪ�ز�λ���ڴ��ͷʱ���������м�ȥ��һ���ڴ���е�Ԫ�ظ�����ͼ�ڵ�������ƶ�һ��λ�ã�ָ����һ���ڴ��
		else if (first_elem != *first_node) {
			n -= (num_elem - difference_type(first_elem - *first_node));
			++cur_n;
		}
		cur_n += n / num_elem;
		return *(*cur_n + n % num_elem);
	}



	void erase(iterator pos, size_type n) {
		iterator pos_end = pos + n;
		iterator src_end;

		//�����ƶ��Ժ��Ԫ���µ��жϵ�
		iterator n_st;
		iterator n_end;

		difference_type left_len = 0;
		difference_type dst_len = num_elem - difference_type(pos_end.cur_elem - *pos_end.cur_node);
		difference_type src_len = num_elem - difference_type(pos.cur_elem - *pos.cur_node);

		//�������Ǹ��Ƚϸ��ӵ������ڲ����ϸ�Ч�Ĳ��������������
		//�ƶ�ʹ������������µ�Ԫ����㶼�ǿ����ʼ��
		if (src_len >= dst_len) {
			memmove(pos.cur_elem, pos_end.cur_elem, sizeof(value_type) * dst_len);
		}
		else {
			memmove(pos.cur_elem, pos_end.cur_elem, sizeof(value_type) * src_len);
			memmove(*(pos + src_len).cur_node, pos_end.cur_elem + src_len, sizeof(value_type)*(dst_len - src_len));
		}
		n_st = pos + dst_len;
		n_end = pos_end + dst_len;

		//����ֱ��дͨ�õ�Ԫ����ǰ����
		//copy_forward
		left_len = num_elem - difference_type(n_st.cur_elem - *n_st.cur_node);
		
		while (n_end.cur_node != last_node) {
			memmove(n_st.cur_elem, n_end.cur_elem, sizeof(value_type)*left_len);
			n_st += num_elem;
			n_end += left_len;
			memmove(*n_st.cur_node, n_end.cur_elem, sizeof(value_type) * (num_elem - left_len));
			n_end += (num_elem - left_len);
		}
		difference_type last_node_len = last_elem - *last_node + 1;
		if (last_node_len > left_len) {
			memmove(n_st.cur_elem, *last_node, sizeof(value_type) * left_len);
			n_st += left_len;
			memmove(*n_st.cur_node, *last_node + left_len, sizeof(value_type) * (last_node_len - left_len));
			n_st += (last_node_len - left_len - 1);
		}
		else {
			memmove(n_st.cur_elem, *last_node, sizeof(value_type) * last_node_len);
			n_st += (last_node_len - 1);
		}


		Size -= n;
		last_node = n_st.cur_node;
		last_elem = n_st.cur_elem;
	}

	void erase(iterator pos) {
		erase(pos, 1);
	}


	void insert(iterator pos, value_type val, size_type n) {
		//�ȼ��ʣ��ڵ��Ƿ��㹻
		difference_type end_len = last_elem - *last_node + 1;
		size_type required_node = (end_len + n) / num_node;
		//�ڵ㲻�������·���ڵ�ռ�
		if (end_node - last_node - 1 < required_node)
			realloc_map();
		//�������ڵ���ڴ���������ָ��Ϊ����Ϊ�����ռ�
		for (int i = 1; i <= required_node; ++i)
			if (*(last_node + i) == nullptr)
				*(last_node + i) = new value_type[num_node];

		/*difference_type new_end_len = (end_len + n%num_elem) % num_elem;
		map_pointer */

		iterator new_pos = back() + n;
		iterator old_pos = back();
		char *dst, *src;
		size_type len; 
		for (; old_pos != pos; --old_pos, --new_pos) {
			dst = (char*)(&(*new_pos));
			src = (char*)(&(*old_pos));
			len = sizeof(value_type);
			while(len--)
				*(dst++) = *(src++);
		}
		len = n;
		while (len--)
			construct(&(*(++pos)), val);

		new_pos = back() + n;
		last_elem = new_pos.cur_elem;
		last_node = new_pos.cur_node;

		Size += n;
	}

	void insert(iterator pos, value_type val) {
		insert(pos, val, 1);
	}

};



void test_deque() {
	lldeque<int, 5, 5> de;
	cout << de.size() << endl;
	for (int i = 0; i < 50; ++i)
		de.push_back(i);
	cout << de.size() << endl;
	lldeque<int, 5, 5>::iterator it = de.begin();
	for (; it != de.end(); ++it)
		cout << *it << " ";
	cout << endl;
	for (size_t i = 0; i < de.size(); ++i)
		cout << de[i] << " ";
	cout << endl;

	it = de.begin();
	it += 10;
	cout << *it << endl;
	it += 5;
	cout << *it << endl;
	it -= 10;
	cout << *it << endl;
	cout << *it << endl;
	cout << "test ++" << endl;
	cout << *(++it) << endl;
	cout << *(++it) << endl;

	cout << *(--it) << endl;
	cout << *(--it) << endl;
	


	for (int i = 0; i < 50; ++i) {
		de.push_front(i);
	}
	for (it = de.begin(); it != de.end(); ++it)
		cout << *it << " ";
	cout << endl;

	cout << "erase test" << endl;
	it = de.begin()+1;
	cout << *it << endl;
	de.erase(it, 15);
	cout << *it << endl;
	for (it = de.begin(); it != de.end(); ++it)
		cout << *it << " ";
	cout << endl;

	cout << "insert test" << endl;
	it = de.begin() + 1;
	de.insert(it, 99, 9);
	for (it = de.begin(); it != de.end(); ++it)
		cout << *it << " ";
	cout << endl;


}


__LLDS__END__NAMESPACE


