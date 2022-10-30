#include <iostream>
#include <stdlib.h>
#include "test_functions.h"

int main(int argc, char* argv[])
{
    std::cout << "Starting testing suite..." << std::endl;

    // Heap testing
    // run for 20 times with random heap sizes
    bool pass_heap = true;
    for (int i = 0; i < 20; i++)
    {
        unsigned int test_n_elements = rand() % 1000000 + 10;
        std::cout << "Creating max heap with size " << test_n_elements << std::endl;
        HEAP_TEST h_test(test_n_elements);
        try
        {
            h_test.test_heap_sequential();
        }
        catch(...)
        {
            std::cout << "[FATAL]: Failed test_heap_sequential test at heap size " << test_n_elements << std::endl;
            pass_heap = false;
            break;
            // h_test.print_heap();
        }
    }
    if (pass_heap) std::cout << "Passed test_heap_sequential test" << std::endl;
}