#include <iostream>
#include "test_functions.h"

int main(int argc, char* argv[])
{
    std::cout << "Starting testing suite..." << std::endl;

    // Heap testing
    unsigned int test_n_elements = 50000;
    std::cout << "Creating max heap with size " << test_n_elements << std::endl;
    HEAP_TEST h_test(test_n_elements);
    if (h_test.test_heap_sequential())
        std::cout << "Passed test_heap_sequential test" << std::endl;
    else
    {
        std::cout << "[FATAL]: Failed test_heap_sequential test" << std::endl;
        h_test.print_heap();
    }
}