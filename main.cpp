#include <chrono>
#include <iostream>
#include <random>

#include "Graph.h"

using namespace std;

using vert_t = int;
using weight_t = int;

int main() {
    // clock
    chrono::high_resolution_clock::time_point tic = chrono::high_resolution_clock::now();
    auto toc = tic;

    // construct a trivial random generator engine from a time-based seed:
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);

    int num_tests = 10;
    int num_vert = 10000;
    int num_paths = 100;
    float avg = 0;

    uniform_int_distribution<int> num_neighbors (0,100);
    uniform_int_distribution<int> neighbor (0, num_vert-1);
    uniform_int_distribution<int> weight (1,100);

    for (int n = 0; n < num_tests; n++) {
        tic = chrono::high_resolution_clock::now();
        Graph<vert_t, weight_t> graph (num_vert);

        for (int i = 0; i < num_vert; i++) {
            graph.add_vertex_by_name(i);

            int nn = num_neighbors(generator);
            for(int j = 0; j < nn; j++) {
                int n2 = neighbor(generator);
                while (n2 == i) n2 = neighbor(generator);

                graph.add_edge_by_name(i, n2, weight(generator));
            }
        }

        toc = chrono::high_resolution_clock::now();

        cout << "Number of vertices = " << graph.size() << endl;
        cout << "Directed: " << (graph.is_directed() ? "yes" : "no") << endl;
        cout << "Generation time: " << chrono::duration_cast<chrono::milliseconds>( toc - tic ).count() << " miliseconds" << endl;
        cout << endl;

        for (int r = 0; r < num_paths; r++) {
            int s = neighbor(generator);
            int t = neighbor(generator);

            printf("Shortest path between %d and %d = ", s, t);
            fflush(stdout);

            tic = chrono::high_resolution_clock::now();
            auto path = graph.shortest_path_by_name(s, t);
            toc = chrono::high_resolution_clock::now();

            auto duration = chrono::duration_cast<chrono::milliseconds>( toc - tic ).count();

            avg += static_cast<float>(duration);

            printf("%d (found in %ld ms)\n", path, duration);
        }

        printf("\n");
    }

    avg /= static_cast<float>(num_tests * num_paths);
    printf("Average path finding duration = %f ms\n", avg);

    return 0;
}
