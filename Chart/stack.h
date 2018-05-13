#pragma once
#include <stack>

template<class T>
class stack {
	std::stack<T> stack;
public: 
	stack(int _size = 100);
	~stack() {};

	void push(T element);
	T pop();
	T top();
	void PopWithoutReturning();
	int size();
	void clear();
	bool isEmpty();
};

template<class T>
stack::stack(int _size = 100) {
	stack = std::stack<T>(100);
}

template<class T>
void stack::push(T element) {
	stack.push(element);
}

template<class T>
T stack::pop() {
	T tmp = stack.top();
	stack.pop();

	return tmp;
}

template<class T>
T stack::top() {
	return stack.tmp();
}

template<class T>
void stack::PopWithoutReturning() {
	stack.pop();
}

template<class T>
int stack::size() {
	return stack.size();
}

template<class T>
void stack::clear() {
	std::stack<T> tmp;

	stack = tmp;
}

template<class T>
bool isEmpty() {
	return stack.empty();
}
