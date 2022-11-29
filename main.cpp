#include <iostream>
#include <random>
#include <chrono>
#include "graph.h"
#include "graph_algorithms.h"


int main(int argc, char* argv[])
{
    std::cout << "Starting CSCE 629 Max Bandwidth Project" << std::endl;

    unsigned long num_vertex = 5000;

    for (int i = 0; i < 5; i++)
    {
        std::cout << "Starting iteration " << i << std::endl;
        std::cout << "Creating Graphs G1 and G2" << std::endl;
        Graph G1(num_vertex);
        Graph G2(num_vertex);
        // create cycles for both graphs first
        G1.createCycle();
        G2.createCycle();
        G1.createG1();
        G2.createG2();
        std::cout << "Graph G1 Properties:" << std::endl;
        G1.printProperties();
        std::cout << std::endl;
        std::cout << "Graph G2 Properaties:" << std::endl;
        G2.printProperties();
        std::cout << std::endl;
        for (int j = 0; j < 5; j++)
        {
            // path from s to t
            int s = rand() % num_vertex;
            int t = (rand() - 1) % num_vertex;

            std::cout << "Finding Max-BW path from " << s << " to " << t << std::endl;

            // deploy graph algorithms
            std::cout << "Naive Dijkstras" << std::endl;
            std::cout << "Starting on G1" << std::endl;
            auto nD_g1_start = std::chrono::high_resolution_clock::now();
            ShortestPath nD_path_g1 = Naive_Dijkstras(G1, s, t);
            auto nD_g1_stop = std::chrono::high_resolution_clock::now();
            auto nD_g1_duration = std::chrono::duration_cast<std::chrono::microseconds>(nD_g1_stop - nD_g1_start);
            std::cout << nD_path_g1 << std::endl;
            std::cout << "Naive Dijkstras time on G1: " << nD_g1_duration.count() / 1e3 << " milliseconds" << std::endl;

            std::cout << "Starting on G2" << std::endl;
            auto nD_g2_start = std::chrono::high_resolution_clock::now();
            ShortestPath nD_path_g2 = Naive_Dijkstras(G2, s, t);
            auto nD_g2_stop = std::chrono::high_resolution_clock::now();
            auto nD_g2_duration = std::chrono::duration_cast<std::chrono::microseconds>(nD_g2_stop - nD_g2_start);
            std::cout << nD_path_g2 << std::endl;
            std::cout << "Naive Dijkstras time on G2: " << nD_g2_duration.count() / 1e3 << " milliseconds" << std::endl;

            std::cout << std::endl;

            std::cout << "Heap Dijkstras" << std::endl;
            std::cout << "Starting on G1" << std::endl;
            auto D_g1_start = std::chrono::high_resolution_clock::now();
            ShortestPath D_path_g1 = Dijkstras(G1, s, t);
            auto D_g1_stop = std::chrono::high_resolution_clock::now();
            auto D_g1_duration = std::chrono::duration_cast<std::chrono::microseconds>(D_g1_stop - D_g1_start);
            std::cout << D_path_g1 << std::endl;
            std::cout << "Heap Dijkstras time on G1: " << D_g1_duration.count() / 1e3 << " milliseconds" << std::endl;

            std::cout << "Starting on G2" << std::endl;
            auto D_g2_start = std::chrono::high_resolution_clock::now();
            ShortestPath D_path_g2 = Dijkstras(G2, s, t);
            auto D_g2_stop = std::chrono::high_resolution_clock::now();
            auto D_g2_duration = std::chrono::duration_cast<std::chrono::microseconds>(D_g2_stop - D_g2_start);
            std::cout << D_path_g2 << std::endl;
            std::cout << "Heap Dijkstras time on G2: " << D_g2_duration.count() / 1e3 << " milliseconds" << std::endl;

            std::cout << std::endl;

            std::cout << "Kruskals" << std::endl;
            std::cout << "Starting on G1" << std::endl;
            auto K_g1_start = std::chrono::high_resolution_clock::now();
            ShortestPath K_path_g1 = Kruskals(G1, s, t);
            auto K_g1_stop = std::chrono::high_resolution_clock::now();
            auto K_g1_duration = std::chrono::duration_cast<std::chrono::microseconds>(K_g1_stop - K_g1_start);
            std::cout << K_path_g1 << std::endl;
            std::cout << "Naive Dijkstras time on G1: " << K_g1_duration.count() / 1e3 << " milliseconds" << std::endl;

            std::cout << "Starting on G2" << std::endl;
            auto K_g2_start = std::chrono::high_resolution_clock::now();
            ShortestPath K_path_g2 = Kruskals(G2, s, t);
            auto K_g2_stop = std::chrono::high_resolution_clock::now();
            auto K_g2_duration = std::chrono::duration_cast<std::chrono::microseconds>(K_g2_stop - K_g2_start);
            std::cout << K_path_g2 << std::endl;
            std::cout << "Naive Dijkstras time on G2: " << K_g2_duration.count() / 1e3 << " milliseconds" << std::endl;
            
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}