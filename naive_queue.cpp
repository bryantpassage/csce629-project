#include <vector>
#include <stdexcept>
#include "naive_queue.h"

NaiveQueue::NaiveQueue() : size(0) {}


bool NaiveQueue::isempty()
{
    return this->size < 1;
}

int NaiveQueue::pop()
{
    if (isempty()) throw std::runtime_error("Queue is empty -- cannot pop element from empty queue");

    int elem = queue.front();
    queue.erase(queue.begin());
    size--;
    return elem;
}

void NaiveQueue::push(int value)
{
    queue.push_back(value);
    size++;
}

NaiveMaxQueue::NaiveMaxQueue() : NaiveQueue() {}

unsigned long NaiveMaxQueue::argmax()
{
    if (size < 1) return -1;

    int max = values.front();
    unsigned long max_i = 0;
    for (unsigned long i = 1; i < size; i++)
    {
        if (values.at(i) > max)
        {
            max = values.at(i);
            max_i = i;
        }
    }
    return max_i;
}

int NaiveMaxQueue::max()
{
    if (size < 1) return -1;

    unsigned long max_i = this->argmax();
    return queue.at(max_i);
}

void NaiveMaxQueue::push(int v, int bw)
{
    queue.push_back(v);
    values.push_back(bw);
    size++;
}

int NaiveMaxQueue::pop()
{
    if (isempty())
        throw std::runtime_error("Queue is empty -- cannot pop element from empty queue");

    unsigned long max_i = this->argmax();
    int v = queue.at(max_i);

    queue.erase(queue.begin() + max_i);
    values.erase(values.begin() + max_i);
    size--;
    return v;
}

void NaiveMaxQueue::remove(int v)
{
    for (unsigned long i = 0; i < queue.size(); i++)
    {
        if (queue[i] == v)
        {
            queue.erase(queue.begin()+i);
            values.erase(values.begin()+i);
            size--;
            return;
        }
    }

    throw std::runtime_error("Could not find vertex to remove from Max Queue");
}