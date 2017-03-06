#pragma once

#include "llbase.h"
#include "llvector.h"

__LLDS__BEGIN__NAMESPACE

template <class Value>
class llheap {
public:
	typedef Value value_type;
	typedef value_type* pointer;
	typedef value_type& reference;

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;


private:
	size_t Size;
	//数据内存指针
	pointer buffer;

private:
	size_type left(size_type n) {
		return 2 * n + 1;
	}
	size_type right(size_type n) {
		return 2 * n + 2;
	}
	size_type parent(size_type n) {
		return (n + 1) / 2 - 1;
	}

	void max_heapify(size_type i) {
		size_type largest = i;
		size_type l = left(i);
		size_type r = right(i);
		//找出父节点，两子节点的最大值
		if (l < Size && buffer[l] > buffer[largest])
			largest = l;
		if (r < Size && buffer[r] > buffer[largest])
			largest = r;
		//将大值替换至父节点，然后再对交换后的子节点进行变换矫正
		if (largest != i) {
			value_type tmp = buffer[i];
			buffer[i] = buffer[largest];
			buffer[largest] = tmp;
			max_heapify(largest);
		}
	}



public:
	llheap(llvector<value_type>& v)  {
		Size = v.size();
		buffer = v.begin();
	}

	llheap(pointer p, size_type s):buffer(p), Size(s){ }

	void build_max_heap() {
		for (int i = Size / 2 - 1; i >= 0; --i) {
			max_heapify(i);
		}
	}

	void heap_sort() {
		build_max_heap();
		size_type size_ = Size;
		value_type tmp;
		//建好堆以后，将最大值替换到末尾，如此buffer[0]的位置不符合堆性质，堆减小一，排除最后一个最大值，
		//新堆进行性质矫正，如此往复，排序完成。
		for (int i = Size - 1; i >= 1; --i) {
			tmp = buffer[Size - 1];
			buffer[Size - 1] = buffer[0];
			buffer[0] = tmp;
			--Size;
			max_heapify(0);
		}
		Size = size_;
	}

};



void test_heap() {
	
	int a[10] = { 4,1,3,2,16,9,10,14,8,7 };

	llvector<int> vi(a, a + 10);

	for (size_t i = 0; i < vi.size(); ++i) {
		cout << vi[i] << "  ";
	}
	cout << endl;

	llheap<int> lhp(vi);
	//lhp.build_max_heap();
	lhp.heap_sort();

	for (size_t i = 0; i < vi.size(); ++i) {
		cout << vi[i] << "  ";
	}

	cout << endl;
}


__LLDS__END__NAMESPACE