#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

#include "../heap.h"
#include "../graph.h"

bool operator==(const Edge &lhs, const Edge &rhs);

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
    void print_heap();
};


class GRAPH_TEST
{
public:
    Graph uut;
public:
    GRAPH_TEST(int);
    bool test_graph_sequential();
    void check_adj_lists(std::vector<std::vector<Edge>>&);
};

#endif