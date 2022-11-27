#include <cstring>
#include <queue>
#include "muf.h"
#include "naive_queue.h"

// constructor
MUF::MUF(int n) : dad(new int[n]), rank(new int[n]), size(n) {}

// copy constructor
MUF::MUF(const MUF& rhs) : dad(new int[rhs.size]), rank(new int[rhs.size])
{
    std::memcpy(rhs.dad, this->dad, rhs.size);
    std::memcpy(rhs.rank, this->rank, rhs.size);
    // std::copy(rhs.dad, rhs.dad + rhs.size, this->dad);
    // std::copy(rhs.rank, rhs.rank + rhs.size, this->rank);
}

// copy assignment
MUF& MUF::operator=(const MUF& rhs)
{
    std::memcpy(rhs.dad, this->dad, rhs.size);
    std::memcpy(rhs.rank, this->rank, rhs.size);
    // std::copy(rhs.dad, rhs.dad + rhs.size, this->dad);
    // std::copy(rhs.rank, rhs.rank + rhs.size, this->rank);

    return *this;
}

// Destructor
MUF::~MUF()
{
    delete dad;
    delete rank;
}

void MUF::MakeSet(int v)
{
    dad[v] = -1; rank[v] = 0;
}

void MUF::Union(int r1, int r2)
{
    if(rank[r1] > rank[r2]) dad[r2] = r1;
    else if (rank[r1] < rank[r2]) dad[r1] = r2;
    else
    {
        dad[r1] = r2;
        rank[r2]++;
    }
}

int MUF::Find(int v)
{
    int r = v;
    // NaiveQueue S;
    std::queue<int> S;
    while (dad[r] != -1)
    {
        S.push(r);
        r = dad[r];
    }
    while (!S.empty())
    {
        int w = S.front();
        S.pop();
        dad[w] = r;
    }
    return r;
}