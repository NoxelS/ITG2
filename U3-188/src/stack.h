#include <iostream>

#ifndef STACK_H
#define STACK_H STACK_H

/** Datatype for stack nodes */
#define T double

class stack {
   private:
    /** Current height of the stack*/
    size_t stack_size;

    /** Elements of the stack */
    struct node {
        T value;
        node* prev;
        node(T v, node* p);
    };

    /** Pointer to the top element */
    node* top;

   public:
    /** Constructor generated empty stack*/
    stack();

    /** Desctructor empties the stack */
    ~stack();

    /** Get the height of the stack */
    size_t size() const;

    /** Push a new element onto the stack*/
    void push(T v);

    /** Pop the top element and return it*/
    T pop();
};

#endif