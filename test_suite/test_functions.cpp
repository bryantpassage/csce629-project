#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include "test_functions.h"
#include "../heap.h"
#include "../graph.h"

HEAP_TEST::HEAP_TEST(int n) : Max_Heap(n), end_heap_size(n) {}


void HEAP_TEST::traverse_heap(int i)
{
    int parent_vertex = H[i];
    int parent_value = D[parent_vertex];
    int left_child_index = static_cast<int>(2 * i + 1);
    int right_child_index = static_cast<int>(2 * i + 2);
    if (static_cast<unsigned long>(left_child_index) < size)
    {
        int left_child_vertex = H[left_child_index];
        int left_child_value = D[left_child_vertex];

        if (parent_value < left_child_value)
            throw std::logic_error("One of the children values is greater than the parent value");

        traverse_heap(left_child_index);
    }
    if (static_cast<unsigned long>(right_child_index) < size)
    {
        int right_child_vertex = H[right_child_index];
        int right_child_value = D[right_child_vertex];

        if (parent_value < right_child_value)
            throw std::logic_error("One of the children values is greater than the parent value");

        traverse_heap(right_child_index);
    }
}

void HEAP_TEST::check_heap_validity()
{
    traverse_heap(0);
}

bool HEAP_TEST::test_heap_sequential()
{
    // insert sequential values
    for (unsigned long i = 0; i < end_heap_size; i++)
    {
        Insert(end_heap_size - i - 1, i); // insert vertex n-i with value i
    }

    // check heap validity
    try
    {
        check_heap_validity();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << "Failed test_heap_sequential at sequential insertion" << std::endl;
        return false;
    }

    // delete 20% random values
    int n_delete = static_cast<int>(end_heap_size * 0.2);
    std::vector<int> hash(end_heap_size);
    int random_numbers[n_delete];
    for (int d = 0; d < n_delete; d++)
    {
        int r;
        do
        {
            r = rand() % end_heap_size;
        } while (hash[r] != 0);
        hash[r] = 1;
        random_numbers[d] = r;        
    }
    for (int i = 0; i < n_delete; i++)
    {
        Delete(random_numbers[i]);
    }

    // check heap validity
    try
    {
        check_heap_validity();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << "Failed test_heap_sequential at random deletion" << std::endl;
        return false;
    }

    // add 25 more pre-determined values
    for (unsigned long i = end_heap_size; i < end_heap_size+25; i++)
    {
        int r_value = rand() % end_heap_size;   // insert random value that may already be in heap
        D.push_back(r_value);
        P.push_back(-1);
        Insert(i, r_value);
    }
    // check heap validity
    try
    {
        check_heap_validity();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << "Failed test_heap_sequential at random deletion" << std::endl;
        return false;
    }

    return true;
}

void HEAP_TEST::print_heap()
{
    std::cout << "H: ";
    for (int vertex : H)
    {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    std::cout << "D: ";
    for (int value : D)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "P: ";
    for (int index : P)
    {
        std::cout << index << " ";
    }
    std::cout << std::endl;
}

GRAPH_TEST::GRAPH_TEST(int n) : uut(n) {}

void GRAPH_TEST::check_adj_lists(std::vector<std::vector<Edge>>& correct_adj_list)
{
    if (uut.adj_list.size() != correct_adj_list.size()) throw std::runtime_error("Adjacency list sizes do not match!");

    for (unsigned long i = 0; i < correct_adj_list.size(); i++)
    {
        if (uut.adj_list[i].size() != correct_adj_list[i].size()) throw std::runtime_error("Adjaceny list at vertex " + std::to_string(i) + "'s list does not match!");
        for (unsigned long j = 0; j < correct_adj_list[i].size(); j++)
        {
            if (!(uut.adj_list[i][j] == correct_adj_list[i][j])) 
            {
                std::string uut_string = "uut edge = [ " + std::to_string(uut.adj_list[i][j].v) + "," + std::to_string(uut.adj_list[i][j].weight) + " ]";
                std::string correct_string = "correct edge = [ " + std::to_string(correct_adj_list[i][j].v) + "," + std::to_string(correct_adj_list[i][j].weight) + " ]";
                throw std::runtime_error("Adjacency lists do not match!\n" + uut_string + "\n" + correct_string);
            }
        }
    }
}

bool GRAPH_TEST::test_graph_sequential()
{
    bool passed = false;
    // add 9 edges
    for (int i = 1; i < 10; i++)
    {
        uut.addEdge(0, i, i);       // add edge from v0 to vi with weight i
    }
    // create correct adjacency list
    std::vector<std::vector<Edge>> correct_adjacency_list(10, std::vector<Edge>());
    for (int i = 0; i < 10; i++)
    {
        if (i==0)
        {
            for (int j = 1; j < 10; j++)
            {
                correct_adjacency_list[i].push_back(Edge{j, j});
            }
        }
        else
        {
            correct_adjacency_list[i].push_back(Edge{0, i});
        }
    }

    // check adjacency lists
    try
    {
        check_adj_lists(correct_adjacency_list);
        passed = true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        passed = false;
    }
    return passed;
}

bool operator==(const Edge &lhs, const Edge &rhs)
{
    return (lhs.v == rhs.v) && (lhs.weight == rhs.weight);
}
