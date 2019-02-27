#define CATCH_CONFIG_MAIN
#include <iostream>
#include <stdio.h>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
//using namespace cs221util;
using namespace std;

/*TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    //cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
}
TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE( result == expected);
}

TEST_CASE("queue::empty 4 times","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    expected.push_back(4);
    intQueue.enqueue(1);
    intQueue.dequeue();
    intQueue.enqueue(2);
    intQueue.dequeue();
    intQueue.enqueue(3);
    intQueue.dequeue();
    intQueue.enqueue(5);
    intQueue.dequeue();
    intQueue.enqueue(4);
    result.push_back(intQueue.dequeue());
    REQUIRE( result == expected);
}

TEST_CASE("queue::popLTest","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 50; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 50; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE( result == expected);
}
/*
TEST_CASE("queue::resize pushpopLTest","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 25; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 50; i++) {
        intQueue.enqueue(i);
    }
    for (int i = 1; i <= 50; i++) {
        result.push_back(intQueue.dequeue());
        printf("  %i   %i\n", intQueue.get_size(), i);
    }
    REQUIRE( result == expected);
}*/

TEST_CASE("queue::to find resize bug","[weight=1][part=queue]"){
    Deque<int> intDeque;
    vector<int> result;
    vector<int> expected;

    for (int i = 1; i <= 10; i++) {
        intDeque.pushR(i);
    }
    for (int i = 1; i <= 5; i++) {
        intDeque.popR();
        printf("Yolo:   %i   %i\n", intDeque.get_sizee(), i);
    }
    intDeque.popL();
    intDeque.popL();
    printf("After popsicles  %i\n", intDeque.get_sizee());
    for (int i = 1; i <= 5; i++) {
        result.push_back(i);
    }
    REQUIRE( result == expected);
}