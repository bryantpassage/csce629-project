#include <iostream>
#include <vector>
#include "test_functions.h"
#include "../heap.h"

HEAP_TEST::HEAP_TEST(int n) : Max_Heap(n), end_heap_size(n) {}


void HEAP_TEST::traverse_heap(int i)
{
    
    int parent_vertex = H[i];
    int parent_value = D[parent_vertex];
    int left_child_index = static_cast<int>(2 * i + 1);
    int right_child_index = static_cast<int>(2 * i + 2);
    if (static_cast<unsigned long>(left_child_index) < size)
    {
        int left_child_vertex = H[left_child_index];
        int left_child_value = D[left_child_vertex];

        if (parent_value < left_child_value)
            throw std::logic_error("One of the children values is greater parent value");

        traverse_heap(left_child_index);
    }
    if (static_cast<unsigned long>(right_child_index) < size)
    {
        int right_child_vertex = H[right_child_index];
        int right_child_value = D[right_child_vertex];

        if (parent_value < right_child_value)
            throw std::logic_error("One of the children values is greater parent value");
        traverse_heap(right_child_index);
    }
}

void HEAP_TEST::check_heap_validity()
{
    traverse_heap(0);
}

bool HEAP_TEST::test_heap_sequential()
{
    // insert sequential values
    for (unsigned long i = 0; i < end_heap_size; i++)
    {
        Insert(end_heap_size - i - 1, i); // insert vertex n-i with value i
    }

    // check heap validity
    try
    {
        check_heap_validity();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << "Failed test_heap_sequential" << std::endl;
        return false;
    }

    return true;
}