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

class NaiveMaxQueue : public NaiveQueue
{
private:
    unsigned long argmax();

public:
    std::vector<int> values;

    NaiveMaxQueue();
    int max();
    void push(int, int);
    int pop();
    void remove(int);
};

#endif