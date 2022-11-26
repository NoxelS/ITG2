#include "stack.h"

stack::node::node(T v, node* p) : value(v), prev(p) {}

stack::stack() : stack_size(0), top(nullptr) {}

stack::stack(size_t n, T v) : stack() {
    for (size_t i = 0; i < n; i++) {
        push(v);
    }
}

stack::stack(const stack& st): stack() {
    node* current = st.top;
    while (current != nullptr) {
        push(current->value);
        current = current->prev;
    }
}

stack::~stack() {
    while (size()) {
        pop();
    }
}

size_t stack::size() const { return stack_size; }

void stack::push(T v) {
    top = new node(v, top);
    stack_size++;  // Could be also set in the node constructor
}

T stack::pop() {
    // Currently does no error checking if top element is missing
    T oldVlaue = top->value;
    node* newTop = top->prev;
    delete top;
    top = newTop;
    --stack_size;
    return oldVlaue;
}

stack& stack::operator=(const stack& st) { return stack(st); }