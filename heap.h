#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>


class Max_Heap
{
protected:
    std::vector<int> H;    // array that holds the name of each vertices (heap to actually keep sorted)
    std::vector<int> D;    // array that maps vertex name to vertex value
    std::vector<int> P;    // array that holds position of vertex in H (used for delete and swapping)
    unsigned long size;
    void swap(int, int);
    void heapify(int);
    void heapify_up(int);
public:
    Max_Heap();
    Max_Heap(int);
    void Insert(int, int);
    void Delete(int);
    int Max();
    bool isempty();
};

#endif