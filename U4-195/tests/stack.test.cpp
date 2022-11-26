#include "../src/stack.h"

#include <cmath>

#include "acutest.h"

void test_initialization() {
    stack* test_stack = new stack();
    TEST_CHECK(test_stack->size() == 0);
    delete test_stack;

    stack* test_stack2 = new stack(5, 1.0);
    TEST_CHECK(test_stack2->size() == 5);
    TEST_CHECK(test_stack2->pop() == 1.0);
    TEST_CHECK(test_stack2->pop() == 1.0);
    TEST_CHECK(test_stack2->pop() == 1.0);
    TEST_CHECK(test_stack2->size() == 2);
    TEST_CHECK(test_stack2->pop() == 1.0);
    TEST_CHECK(test_stack2->pop() == 1.0);
    TEST_CHECK(test_stack2->size() == 0);
    delete test_stack2;
}

void test_push() {
    stack* test_stack = new stack();
    TEST_CHECK(test_stack->size() == 0);
    test_stack->push(10);
    TEST_CHECK(test_stack->size() == 1);
    test_stack->push(10);
    TEST_CHECK(test_stack->size() == 2);
    test_stack->push(0);
    TEST_CHECK(test_stack->size() == 3);
    test_stack->push(-1);
    TEST_CHECK(test_stack->size() == 4);
    test_stack->push(-1);
    TEST_CHECK(test_stack->size() == 5);

    delete test_stack;
}

void test_pop() {
    stack* test_stack = new stack();

    test_stack->push(10);
    test_stack->push(10);
    test_stack->push(0);

    TEST_CHECK(test_stack->pop() == 0);
    TEST_CHECK(test_stack->size() == 2);

    TEST_CHECK(test_stack->pop() == 10);
    TEST_CHECK(test_stack->size() == 1);

    TEST_CHECK(test_stack->pop() == 10);
    TEST_CHECK(test_stack->size() == 0);

    delete test_stack;
}

void test_deconstrcutor() {
    stack* test_stack;

    {
        test_stack = new stack();

        test_stack->push(10);
        test_stack->push(10);
        test_stack->push(0);
    }
    // I dont know how to test this

    stack* test_stack2 = new stack();
    test_stack2->push(10);
    delete test_stack2;

    // I dont know how to test this
    // TEST_CHECK( ... );
}

void test_copy_constructor() {
    stack* test_stack = new stack();
    test_stack->push(10);
    test_stack->push(10);
    test_stack->push(0);

    stack* test_stack2 = new stack(*test_stack);

    TEST_CHECK(test_stack2->size() == 3);
    TEST_CHECK(test_stack2->pop() == 0);
    TEST_CHECK(test_stack2->pop() == 10);
    TEST_CHECK(test_stack2->pop() == 10);
    TEST_CHECK(test_stack2->size() == 0);

    delete test_stack;
    delete test_stack2;
}

void test_copy_operator() {
    stack* test_stack = new stack();
    test_stack->push(10);
    test_stack->push(10);
    test_stack->push(0);

    stack* test_stack2 = new stack();
    *test_stack2 = *test_stack;

    TEST_CHECK(test_stack2->size() == 3);
    TEST_CHECK(test_stack2->pop() == 0);
    TEST_CHECK(test_stack2->pop() == 10);
    TEST_CHECK(test_stack2->pop() == 10);
    TEST_CHECK(test_stack2->size() == 0);
    TEST_CHECK(test_stack->size() == 3);

    delete test_stack;
    delete test_stack2;
}

TEST_LIST = {{"Initialization", test_initialization},
             {"Push", test_push},
             {"Pop", test_pop},
             {"Deconstructor", test_deconstrcutor},
             {"Copy Constructor", test_copy_constructor},
             {"Copy Operator", test_copy_operator},
             {0}};