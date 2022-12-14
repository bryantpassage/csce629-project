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

struct EdgeEdge
{
public:
    int v1, v2;
    int weight;
};

class Graph
{
public:
    std::vector<std::vector<Edge>> adj_list;
    std::vector<EdgeEdge> edge_list;
    std::vector<int> visited;
    unsigned long num_vertex, num_edges;
public:
    Graph(int);
    void clear_visited();
    void addEdge(int, int, int);
    bool removeEdge(int, int);
    void printGraph();
    void printProperties();

    void createCycle();
    double createG1();
    double createG2();
};


#endif