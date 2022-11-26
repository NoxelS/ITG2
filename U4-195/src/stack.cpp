#include "stack.h"

stack::node::node(T v, node* p) : value(v), prev(p) {}

stack::stack() : stack_size(0), top(nullptr) {}

stack::stack(size_t n, T v) : stack() {
    for (size_t i = 0; i < n; i++) {
        push(v);
    }
}

stack::stack(const stack& st) : stack() { stack* tmp = new stack;
    /** I'm not sure if we can optimize this without having a next refrence on each node. */
    node* current = st.top;
    while(current != nullptr) {
        tmp->push(current->value);
        current = current->prev;
    }
    while(tmp->top != nullptr) {
        push(tmp->pop());
    }
    delete tmp;
}

stack::~stack() {
    while (size()) {
        pop();
    }
}

size_t stack::size() const { return stack_size; }

void stack::push(T v) {
    top = new node(v, top);
    stack_size++; 
}

T stack::pop() {
    T oldVlaue = top->value;
    node* newTop = top->prev;
    delete top;
    top = newTop;
    --stack_size;
    return oldVlaue;
}

stack& stack::operator=(const stack& st) {
    // Call the copy constructor
    stack* tmp = new stack(st);
    // Swap the stacks
    std::swap(stack_size, tmp->stack_size);
    std::swap(top, tmp->top);
    // Free up memory
    delete tmp;
    return *this;
}