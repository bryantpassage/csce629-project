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