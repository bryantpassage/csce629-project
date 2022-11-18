#include <vector>
#include <iostream>
#include "graph_algorithms.h"
#include "naive_queue.h"

static unsigned long counter = 0;

ShortestPath::ShortestPath(const std::vector<int>& p, const int w) :
    path(p), path_weight(w) {}


bool check_connectivity(Graph& G, void (*traverse)(const void*, const void*))
{
    // reset visited array in G
    G.clear_visited();

    // pick random vertex to start traversing from
    int start_v = rand() % G.num_vertex;

    // traverse through
    traverse((void*)&G, (void*)&start_v);

    // check if all vertices were visited
    for (int vis : G.visited)
    {
        if (vis == -1) return false;
    }
    return true;
}


void DFS(const void* G_arg, const void* v_arg)
{
    counter += 1;
    Graph& G = *(Graph*)G_arg;
    int v = *(int*)v_arg;

    G.visited[v] = 0;

    // for each adjacent edge to v ([v, w])
    for (unsigned long i = 0; i < G.adj_list[v].size(); i++)
    {
        if (G.visited[G.adj_list[v][i].v] < 0)
        {
            DFS(G_arg, (void*)&(G.adj_list[v][i].v));
        }
    }

    G.visited[v] = 1;
}

void BFS(const void* G_arg, const void* v_arg)
{
    Graph& G = *(Graph*)G_arg;
    int v = *(int*)v_arg;

    NaiveQueue Q;

    G.visited[v] = 0;
    Q.push(v);

    while (!Q.isempty())
    {
        int w = Q.pop();
        for (Edge e : G.adj_list[w])
        {
            int u = e.v;
            if (G.visited[u] == -1)
            {
                G.visited[u] = G.visited[w]+1;
                Q.push(u);
            }
        }
    }
}