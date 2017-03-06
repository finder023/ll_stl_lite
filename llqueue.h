#pragma once

#include "lllist.h"

__LLDS__BEGIN__NAMESPACE

template <class Value>
class llqueue {
private:
	lllist<Value> buffer;
public:
	void enqueue(Value val) {
		buffer.push_back(val);
	}
	Value dequeue() {
		return buffer.pop_front();
	}
	size_t size() {
		return buffer.size();
	}
	bool empty() {
		return buffer.empty();
	}
};


__LLDS__END__NAMESPACE