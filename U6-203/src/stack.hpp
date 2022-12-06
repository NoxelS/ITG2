#include "stack.h"

template <typename T>
stack<T>::node::node(T v, node* p) : value(v), prev(p){};

template <typename T>
stack<T>::stack() : stack_size(0), top(nullptr){};

template <typename T>
stack<T>::stack(size_t n, T v) : stack() {
    for (size_t i = 0; i < n; i++) {
        push(v);
    }
};

template <typename T>
stack<T>::stack(const stack<T>& st) : stack() {
    stack<T>* tmp = new stack<T>;
    /** I'm not sure if we can optimize this without having a next refrence on each node. */
    node* current = st.top;
    while (current != nullptr) {
        tmp->push(current->value);
        current = current->prev;
    }
    while (tmp->top != nullptr) {
        push(tmp->pop());
    }
    delete tmp;
};

template <typename T>  // <- Why can't I write these two lines in one?!
template <typename V>  // <-|
stack<T>::stack(const stack<V>& st) : stack() {
    stack<T>* tmp = new stack<T>;

    /** 
     * This seems like an ugly fix for the problem that stack<T>::node is another calss than stack<V>::node 
     * We can either fix this by making the node class a template class or by using a void* pointer.
    */
    auto current = st.top;

    while (current != nullptr) {
        tmp->push(static_cast<T>(current->value));
        current = current->prev;
    }
    while (tmp->top != nullptr) {
        push(tmp->pop());
    }

    delete tmp;
};

template <typename T>
stack<T>::~stack() {
    while (size()) {
        pop();
    }
};

template <typename T>
size_t stack<T>::size() const {
    return stack_size;
};

template <typename T>
void stack<T>::push(T v) {
    top = new node(v, top);
    stack_size++;
};

template <typename T>
T stack<T>::pop() {
    T oldVlaue = top->value;
    node* newTop = top->prev;
    delete top;
    top = newTop;
    --stack_size;
    return oldVlaue;
}

template <typename T>
stack<T>& stack<T>::operator=(const stack& st) {
    // Call the copy constructor
    stack<T>* tmp = new stack<T>(st);
    // Swap the stacks
    std::swap(stack_size, tmp->stack_size);
    std::swap(top, tmp->top);
    // Free up memory
    delete tmp;
    return *this;
}
