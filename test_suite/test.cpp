#include <iostream>
#include <stdlib.h>
#include "test_functions.h"

int main(int argc, char* argv[])
{
    std::cout << "Starting testing suite..." << std::endl;

    // // Heap testing
    // // run for 20 times with random heap sizes
    // bool pass_heap = true;
    // for (int i = 0; i < 20; i++)
    // {
    //     unsigned int test_n_elements = rand() % 1000000 + 10;
    //     std::cout << "Creating max heap with size " << test_n_elements << std::endl;
    //     HEAP_TEST h_test(test_n_elements);
    //     try
    //     {
    //         h_test.test_heap_sequential();
    //     }
    //     catch(...)
    //     {
    //         std::cout << "[FATAL]: Failed test_heap_sequential test at heap size " << test_n_elements << std::endl;
    //         pass_heap = false;
    //         break;
    //         // h_test.print_heap();
    //     }
    // }
    // if (pass_heap) std::cout << "Passed test_heap_sequential test" << std::endl << std::endl;


    // graph testing
    // test graph on 10 vertices
    std::cout << "Testing graph module on 10 vertices" << std::endl;
    GRAPH_TEST g_test(10);
    if (g_test.test_graph_sequential())
    {
        std::cout << "Passed test_graph_sequential test" << std::endl;
    }
    else
    {
        std::cout << "[FATAL] Failed test_graph_sequential test" << std::endl;
        g_test.uut.printGraph();
    }

    std::cout << "Creating graph G1 module with 5000 vertices" << std::endl;
    GRAPH_TEST g_cycle(5000);
    g_cycle.uut.createCycle();
    double avg_degree = g_cycle.uut.createG1();
    if (avg_degree >= 5 && avg_degree <= 7)
    {
        std::cout << "Graph G1 satisfies requirement of average degree around 6" << std::endl;
    }
    else
    {
        std::cout << "[FATAL] Graph G1 does not have average degree around 6" << std::endl;
    }
    std::cout << "Average degree = " << avg_degree << std::endl;
    // g_cycle.uut.printGraph();

    std::cout << "Creating graph G2 module with 5000 vertices" << std::endl;
    GRAPH_TEST g2(5000);
    g2.uut.createCycle();
    avg_degree = g2.uut.createG2();
    // g2.uut.printGraph();
    if (avg_degree >= 5000*0.18 && avg_degree <= 5000*0.22)
    {
        std::cout << "Graph G1 satisfies requirement of average degree around 20%" << std::endl;
    }
    else
    {
        std::cout << "[FATAL] Graph G2 does not have average degree around 20%" << std::endl;
    }
    std::cout << "Average degree = " << avg_degree << std::endl;
}