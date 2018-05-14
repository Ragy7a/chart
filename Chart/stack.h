#pragma once
#include <stack>

template<class T>
class Stack {
private:
	std::stack<T> st;
public: 
	Stack();
	~Stack() {};

	void push(T element);
	T pop();
	T top();
	void PopWithoutReturning();
	int size();
	void clear();
	bool isEmpty();
};

template<class T>
Stack<T>::Stack() {
	std::stack<T> tmp;
	st = tmp;
}

template<class T>
void Stack<T>::push(T element) {
	st.push(element);
}

template<class T>
T Stack<T>::pop() {
	T tmp = st.top();
	st.pop();

	return tmp;
}

template<class T>
T Stack<T>::top() {
	return st.top();
}

template<class T>
void Stack<T>::PopWithoutReturning() {
	st.pop();
}

template<class T>
int Stack<T>::size() {
	return st.size();
}

template<class T>
void Stack<T>::clear() {
	std::stack<T> tmp;
	
	st = tmp;
}

template<class T>
bool Stack<T>::isEmpty() {
	return st.empty();
}
