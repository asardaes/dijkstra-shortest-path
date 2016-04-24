#include <iostream>
#include <string>

#include "Graph.h"

using namespace std;

using vert_t = string;
using weight_t = int;

int main() {
    Graph<vert_t, weight_t> graph(vector<vert_t> {"S", "A", "B", "C", "D", "E", "F", "G"}, true);

    graph.add_vertex("T");

    graph.add_edge("S", vector<vert_t> {"A", "B", "D"}, vector<weight_t> {4, 3, 7});
    graph.add_edge("A", "C", 1);
    graph.add_edge("B", vector<vert_t> {"S", "D"}, vector<weight_t> {3, 4});
    graph.add_edge("C", vector<vert_t> {"D", "E"}, vector<weight_t> {3, 1});
    graph.add_edge("D", vector<vert_t> {"E", "F", "T"}, vector<weight_t> {1, 5, 3});
    graph.add_edge("E", vector<vert_t> {"G", "T"}, vector<weight_t> {2, 4});
    graph.add_edge("G", vector<vert_t> {"E", "T"}, vector<weight_t> {2, 3});
    graph.add_edge("T", "F", 5);

    cout << "Number of vertices = " << graph.size() << endl;
    cout << "Directed: " << (graph.is_directed() ? "yes" : "no") << endl << endl;
    graph.print();

    cout << "Shortest path from S to T = " << graph.shortest_path("S", "T") << endl;
    cout << "Shortest path from S to S = " << graph.shortest_path("S", "S") << endl;
    cout << "Shortest path from S to G = " << graph.shortest_path("S", "G") << endl;
    cout << "Shortest path from B to E = " << graph.shortest_path("B", "E") << endl;
    cout << endl;
    cout << "Shortest path from C to A = " << graph.shortest_path("C", "A") << endl;
    cout << "Shortest path from F to B = " << graph.shortest_path("F", "B") << endl;

    return 0;
}
