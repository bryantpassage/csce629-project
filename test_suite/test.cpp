#include <iostream>
#include "test_functions.h"

int main(int argc, char* argv[])
{
    std::cout << "Starting testing suite..." << std::endl;

    // Heap testing
    std::cout << "Creating max heap with size 10" << std::endl;
    HEAP_TEST h_test(10);
    if (h_test.test_heap_sequential())
        std::cout << "Passed test_heap_sequential test" << std::endl;
    else
        std::cout << "[FATAL]: Failed test_heap_sequential test" << std::endl;
}