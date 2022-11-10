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

// create a cycle in graph to enforce connectivity
void Graph::createCycle()
{
    std::vector<int> random_num(num_vertex-1);
    for (unsigned long j = 0; j < random_num.size(); j++)
    {
        random_num[j] = j+1;
    }

    int current_vertex = 0;
    for (unsigned long i = 1; i < num_vertex; i++)
    {
        int r_n_pos = rand() % random_num.size();
        int next_vertex = random_num[r_n_pos];
        
        addEdge(current_vertex, next_vertex, rand() % 1000);
        random_num.erase(random_num.begin() + r_n_pos);
        current_vertex = next_vertex;
    }

    // connect last vertex back to 0
    addEdge(current_vertex, 0, rand() % 1000);
}

// create a graph with average vertex degree of 6
// FIXME
double Graph::createG1()
{
    std::vector<std::vector<int>> adj_mat(num_vertex, std::vector<int>(num_vertex, 0));
    for (unsigned long i = 0; i < num_vertex; i++)
    {
        adj_mat[i][i] = 1;
    }

    // go through adj list and update temp adj matrix
    for (unsigned long i = 0; i < adj_list.size(); i++)
    {
        for (unsigned long j = 0; j < adj_list[i].size(); j++)
        {
            adj_mat[i][adj_list[i][j].v] = 1;
        }
    }

    // go through each element in adj matrix and have 6/num_vertex chance of connecting two vertices
    int r_chance = static_cast<int>(6.0 * 10000 / num_vertex);
    for (unsigned long i = 0; i < adj_mat.size(); i++)
    {
        for (unsigned long j = 0; j < adj_mat.size(); j++)
        {
            if (rand() % 10000 < r_chance)
            {
                if (adj_mat[i][j] != 1)
                {
                    addEdge(i, j, rand() % 1000);
                    adj_mat[i][j] = 1;
                    adj_mat[j][i] = 1;
                }
            }
        }
    }

    // calculate and return average degree
    double total_edges = 0;
    for (unsigned long i = 0; i < adj_list.size(); i++)
    {
        int num_adj_vertices = adj_list[i].size();
        total_edges += num_adj_vertices;
    }

    return total_edges / adj_list.size();
}