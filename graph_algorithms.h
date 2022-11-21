#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include <vector>
#include <iostream>
#include "graph.h"

class ShortestPath
{
public:
    std::vector<int> path;
    int path_weight;

    ShortestPath(const std::vector<int>&, const int);
};


bool check_connectivity(Graph&, void (*traverse)(const void*, const void*));

void DFS(const void*, const void*);

void BFS(const void*, const void*);

// utilizes max queue structure which takes O(n) time to get max 
// O(nm)
ShortestPath Naive_Dijkstras(const Graph &, int, int);

// utilizes heap structure which takes O(1) time to get max
// but takes O(logn) to insert or delete
// O(mlogn)
ShortestPath Dijkstras(const Graph&, int, int);

std::ostream &operator<<(std::ostream & os, const ShortestPath& sp);

#endif