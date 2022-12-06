
#ifndef STACK_H
#define STACK_H STACK_H

#include <iostream>

template <class T>
class stack {
    /** Because each template class is a diffrent class we need to define all implementations as friends*/
    template <class V>
    friend class stack;

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

    /** Initialising constructor*/
    stack(size_t n, T v);

    /** Copy constructor */
    stack(const stack& st);

    /** Cast constructor */
    template <typename V>
    stack(const stack<V>& st);

    /** Desctructor empties the stack */
    ~stack();

    /** Get the height of the stack */
    size_t size() const;

    /** Push a new element onto the stack*/
    void push(T v);

    /** Pop the top element and return it*/
    T pop();

    /** Copy operator */
    stack& operator=(const stack& st);
};

/** After long debugging I found a refrence to the c++ documentation:
 *  There the following is stated:
 *      The only portable way of using templates at the moment is
 *      to implement them in header files by using inline functions.
 *
 *  We abuse this by explicitly loading stack.tpp here.
 *
 *  I currently don't know whete this is a big no-no or not.
 *
 */
#include "stack.hpp"

#endif