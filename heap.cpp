#include <iostream>
#include <math.h>
#include "heap.h"

Max_Heap::Max_Heap() : H(std::vector<int>(0)), D(std::vector<int>(0)), P(std::vector<int>(0)), size(0){};

Max_Heap::Max_Heap(int max_n) : H(std::vector<int>()), D(std::vector<int>(max_n, -1)), P(std::vector<int>(max_n, -1)), size(0){};


// returns if heap is empty or not
bool Max_Heap::isempty()
{
    return this->size < 1;
}


void Max_Heap::swap(int v1, int v2)
{
    // get indices of vertex 1 and vertex 2
    int p1 = P[v1];
    int p2 = P[v2];

    // swap operation
    int temp = H[p1];
    H[p1] = H[p2];
    H[p2] = temp;

    // also swap indices in P array
    P[v1] = p2;
    P[v2] = p1;
}

/* Helper function to revalidate heap structure 
(Usually after delete operation) 
Make sure argument p is the index (P[v]) of a vertex */
void Max_Heap::heapify(int p)
{
    // access left and right children from root i
    unsigned long left = static_cast<int>(2 * p + 1);
    unsigned long right = static_cast<int>(2 * p + 2);

    // check if left child is larger than root i
    // remember to check value at D
    unsigned long largest = p;
    largest = (left<size && D[H[left]]>D[H[p]]) ? left : p;
    // check if right child is larger than root i or left child
    if (right<size && D[H[right]]>D[H[largest]]) largest = right;

    // if the largest is not the root, exchange and call recursively
    if (largest != static_cast<unsigned long>(p))
    {
        // swap larger child with root
        swap(H[largest], H[p]);
        heapify(largest);
    }
}

/* Helper function to revalidate heap structure
(Usually after delete operation) */
void Max_Heap::heapify_up(int p)
{
    // up heapify to fix the heap
    int current_p = p;
    int parent = static_cast<int>(floor((current_p - 1) / 2)); // round down index
    while (D[H[current_p]] > D[H[parent]])
    {
        swap(H[current_p], H[parent]);
        current_p = parent;
        parent = static_cast<int>(floor((current_p - 1) / 2));
    }
}

/* Function to Delete vertex from heap 
   Argument v is the vertex to delete
*/
void Max_Heap::Delete(int v)
{
    if (P[v] == -1) throw std::runtime_error("Vertex v not in heap");
    // retrieve last vertex in heap
    int last_vertex = H[size-1];
    // swap the last element in heap with v
    swap(v, last_vertex);
    size--;
    H.pop_back();   // just in case
    if (size != H.size()) throw std::runtime_error("Max_Heap variable \"size\" does not match vector H's size()!");

    // reconstruct/revalidate heap
    if (D[last_vertex] > D[v])
        heapify_up(P[last_vertex]);
    else
        heapify(P[last_vertex]);

    // invalidate index P[v] and remove data D[v]
    P[v] = -1;
    D[v] = -1;
}

/* Function that returns max of heap H */
int Max_Heap::Max() { return H[0]; }

/* Function to insert vertex and value */
void Max_Heap::Insert(int v, int value)
{
    // insert element into last position in H
    H.push_back(v);
    D[v] = value;
    P[v] = size;

    // up heapify to fix the heap
    heapify_up(size);

    size++;
}