#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>


// struct to contain the end vertex and the associated weight of the edge
struct Edge
{
public:
    int v;
    int weight;
};

class Graph
{
private:
    std::vector<std::vector<Edge>> adj_list;
    unsigned long num_vertex, num_edges;
public:
    Graph(int);
    void addEdge(int, int, int);
};


#endif