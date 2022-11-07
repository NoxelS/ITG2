#include "../src/stack.h"

#include <cmath>

#include "acutest.h"

void test_initialization() {
    stack* test_stack = new stack();
    TEST_CHECK(test_stack->size() == 0);
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

TEST_LIST = {{"Initialization", test_initialization},
             {"Push", test_push},
             {"Pop", test_pop},
             {"Deconstructor", test_deconstrcutor},
             {0}};