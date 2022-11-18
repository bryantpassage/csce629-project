#ifndef NAIVE_QUEUE_H
#define NAIVE_QUEUE_H

#include <vector>

class NaiveQueue
{
public:
    std::vector<int> queue;
    unsigned long size;

    NaiveQueue();
    bool isempty();
    void push(int);
    int pop();
};

#endif