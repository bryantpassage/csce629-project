#include <iostream>
#include <vector>
#include "graph.h"


Graph::Graph(int n) : adj_list(std::vector<std::vector<Edge>>(n, std::vector<Edge>(0))), visited(std::vector<int>(n,-1)), num_vertex(n), num_edges(0) {}

void Graph::clear_visited()
{
    for (unsigned long i = 0; i < visited.size(); i++)
    {
        visited[i] = -1;
    }
}

// adds edge connecting v1 and v2 to adjacency list with weight
void Graph::addEdge(int v1, int v2, int weight)
{
    adj_list[v1].push_back(Edge{v2, weight});
    adj_list[v2].push_back(Edge{v1, weight});
}

// for completeness sake
// return true if an edge that connects v1 and v2 exists
// else return false
bool Graph::removeEdge(int v1, int v2)
{
    bool changed = false;
    for (std::vector<Edge>::iterator v_ptr = adj_list[v1].begin(); v_ptr < adj_list[v1].end(); v_ptr++)
    {
        if (v_ptr->v == v2)
        {
            adj_list[v1].erase(v_ptr);
            changed = true;
            break;
        }
    }
    for (std::vector<Edge>::iterator v_ptr = adj_list[v2].begin(); v_ptr < adj_list[v2].end(); v_ptr++)
    {
        if (v_ptr->v == v1)
        {
            if (!changed) throw std::runtime_error("v1 vertex found in v2 list but v2 not found in v1 list. Adjacency list may be corrupted!");
            adj_list[v2].erase(v_ptr);
            changed = true;
            break;
        }
    }
    return changed;
}

void Graph::printGraph()
{
    for (unsigned long i = 0; i < adj_list.size(); i++)
    {
        std::cout << i << " -> " << "[";
        for (Edge edge : adj_list[i])
        {
            std::cout << " " << edge.v << " ";
        }
        std::cout << "]" << std::endl;
    }
}