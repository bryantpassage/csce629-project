#include <vector>
#include <iostream>
#include <climits>
#include <queue>
#include "graph_algorithms.h"
#include "graph.h"
#include "naive_queue.h"
#include "heap.h"
#include "muf.h"

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

void BFS_util(Graph& G, int v, int dad[], int bw[])
{
    // clear graph visit array
    G.clear_visited();

    std::queue<int> Q;

    G.visited[v] = 0;
    Q.push(v);
    dad[v] = -1;
    bw[v] = INT_MAX;

    while (!Q.empty())
    {
        int w = Q.front();
        Q.pop();
        for (Edge e : G.adj_list[w])
        {
            int u = e.v;
            if (G.visited[u] == -1)
            {
                G.visited[u] = G.visited[w] + 1;
                Q.push(u);
                dad[u] = w;
                bw[u] = min(bw[w], e.weight);
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

ShortestPath Dijkstras(const Graph &G, int s, int t)
{
    // status array
    // 0: unseen, 1: fringe, 2: in-tree
    std::vector<int> status(G.num_vertex, 0);
    // dad array for back tracing
    std::vector<int> dad(G.num_vertex, -1);
    // bandwidth array
    std::vector<int> bw(G.num_vertex, INT_MAX);
    status[s] = 2;

    // create Heap structure
    Max_Heap H(G.num_vertex);

    for (Edge e : G.adj_list[s])
    {
        int w = e.v;
        status[w] = 1;
        dad[w] = s;
        bw[w] = e.weight;
        H.Insert(w, bw[w]);
    }

    while (!H.isempty())
    {
        int v = H.Max(); // get max
        H.Delete(v);    // remove v from heap
        status[v] = 2;
        for (Edge e : G.adj_list[v])
        {
            int w = e.v;
            if (status[w] == 0)
            {
                status[w] = 1;
                dad[w] = v;
                bw[w] = min(bw[v], e.weight);
                H.Insert(w, bw[w]);
            }
            else if (status[w] == 1 && bw[w] < min(bw[v], e.weight))
            {
                H.Delete(w);
                dad[w] = v;
                bw[w] = min(bw[v], e.weight);
                H.Insert(w, bw[w]);
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

bool operator>(const EdgeEdge& lhs, const EdgeEdge& rhs)
{
    return lhs.weight > rhs.weight;
}

void swap(std::vector<EdgeEdge>& el, int v1, int v2)
{
    EdgeEdge temp = el[v1];
    el[v1] = el[v2];
    el[v2] = temp;
}

/* Helper function to revalidate heap structure
(Usually after delete operation)
Make sure argument p is the index (P[v]) of a vertex */
void heapify(std::vector<EdgeEdge> &el, int p, unsigned long size)
{
    // access left and right children from root i
    unsigned long left = static_cast<int>(2 * p + 1);
    unsigned long right = static_cast<int>(2 * p + 2);

    // check if left child is larger than root i
    // remember to check value at D
    unsigned long largest = p;
    largest = (left < size && el[left] > el[p]) ? left : p;
    // check if right child is larger than root i or left child
    if (right < size && el[right] > el[largest])
        largest = right;

    // if the largest is not the root, exchange and call recursively
    if (largest != static_cast<unsigned long>(p))
    {
        // swap larger child with root
        swap(el, largest, p);
        heapify(el, largest, size);
    }
}

// will give edge_list in ascending order
void EdgeHeapSort(Graph& G)
{
    std::vector<EdgeEdge>& edge_list = G.edge_list;

    // Build max heap
    for (int i = edge_list.size() / 2 - 1; i >= 0; i--)
        heapify(edge_list, i, edge_list.size());

    // Heap sort
    for (int i = edge_list.size() - 1; i >= 0; i--)
    {
        swap(edge_list, 0, i);

        // Heapify root element to get highest element at
        // root again
        heapify(edge_list, 0, i);
    }
}

ShortestPath Kruskals(Graph& G, int s, int t)
{
    EdgeHeapSort(G); //heap sort edges list in G

    //create T graph
    Graph T(G.num_vertex);

    // create set
    MUF set(G.num_vertex);
    for (unsigned long v = 0; v < G.num_vertex; v++)
    {
        set.MakeSet((int)v);
    }

    // traverse backwards through edge list
    // and create MST
    for (int i = G.num_edges - 1; i >= 0; i--)
    {
        // std::cout << i << std::endl;
        EdgeEdge e = G.edge_list[i];
        int u = e.v1;
        int v = e.v2;

        // std::cout << "u=" << u << std::endl;
        // std::cout << "v=" << v << std::endl;
        
        int r_u = set.Find(u);
        int r_v = set.Find(v);

        if (r_u != r_v)
        {
            set.Union(r_u, r_v);
            T.addEdge(u, v, e.weight);
        }
    }

    // use BFS to traverse through MST
    int dad[T.num_vertex];
    int bw[T.num_vertex];
    for (unsigned long i = 0; i < T.num_vertex; i++) bw[i] = INT_MAX;
    BFS_util(T, s, dad, bw);
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