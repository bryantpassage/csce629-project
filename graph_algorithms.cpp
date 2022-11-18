#include <vector>
#include <iostream>
#include <climits>
#include "graph_algorithms.h"
#include "naive_queue.h"

static unsigned long counter = 0;

int min(int a, int b)
{
    return a <= b ? a : b;
}

ShortestPath::ShortestPath(const std::vector<int>& p, const int w) :
    path(p), path_weight(w) {}

std::ostream& operator<<(std::ostream& os, const ShortestPath& sp)
{
    os << "Max BW Path: ";
    os << "[";
    // iterate reverse
    for (std::vector<int>::const_reverse_iterator v_ptr = sp.path.rbegin(); v_ptr < sp.path.rend(); ++v_ptr)
    {
        os << " " << *v_ptr << " ";
    }
    os << "]" << std::endl;
    os << "Bandwidth: " << sp.path_weight;

    return os;
}

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

ShortestPath Naive_Dijkstras(const Graph& G, int s, int t)
{
    // status array
    // 0: unseen, 1: fringe, 2: in-tree
    std::vector<int> status(G.num_vertex, 0);
    // dad array for back tracing
    std::vector<int> dad(G.num_vertex, -1);
    // bandwidth array
    std::vector<int> bw(G.num_vertex, INT_MAX);
    status[s] = 2;

    // create Naive Max Queue
    NaiveMaxQueue mQ;

    for (Edge e : G.adj_list[s])
    {
        int w = e.v;
        status[w] = 1;
        dad[w] = s;
        bw[w] = e.weight;
        mQ.push(w, bw[w]);
    }

    while (!mQ.isempty())
    {
        int v = mQ.pop();   // max pop
        status[v] = 2;
        for (Edge e : G.adj_list[v])
        {
            int w = e.v;
            if (status[w] == 0)
            {
                status[w] = 1;
                dad[w] = v;
                bw[w] = min(bw[v], e.weight);
                mQ.push(w, bw[w]);
            }
            else if(status[w] == 1 && bw[w] < min(bw[v], e.weight))
            {
                mQ.remove(w);
                dad[w] = v;
                bw[w] = min(bw[v], e.weight);
                mQ.push(w, bw[w]);
            }
        }
    }

    // backtrace from t to s
    std::vector<int> sp;
    int current = t;
    while (current != s)
    {
        sp.push_back(current);
        current = dad[current];
    }
    sp.push_back(current);

    return ShortestPath(sp, bw[t]);
}