#include <iostream>
#include "stack.h"
#include "tester.h"

using namespace std;

int main() {
    StackArray<int>* array = new StackArray<int>(5);
    ASSERT(array->is_empty() == true, "The function is_empty is not working");   
    array->push_back(1);
    array->push_back(2);
    array->push_back(3);
    array->pop_back();
    array->push_back(4);
    array->push_back(5);
    array->push_back(6);
    ASSERT(array->is_empty() == false, "The function is_empty is not working");
    ASSERT(array->is_full() == false, "The function is_full is not working");
    ASSERT(array->to_string() == "1 2 4 5 6 ", "The function push_front is not working");
    delete array;
    return 0;
}