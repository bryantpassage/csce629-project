#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

#include "../heap.h"

class HEAP_TEST : public Max_Heap
{
private:
    unsigned long end_heap_size;
    void traverse_heap(int);
    void check_heap_validity();
    void check_heap_values(int&, int&, int&);

public:
    HEAP_TEST(int);
    bool test_heap_sequential();
};

#endif