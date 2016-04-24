#include <iostream>
#include <string>

#include "Graph.h"

using namespace std;

using vert_t = string;
using weight_t = int;

int main() {
    vector<vert_t> vertices = {"S", "A", "B", "C", "D", "E", "F", "G", "T"};

    Graph<vert_t, weight_t> graph(vertices , true);

    graph.add_edge("S", vector<vert_t> {"A", "B", "D"}, vector<weight_t> {4, 3, 7});
    graph.add_edge("A", "C", 1);
    graph.add_edge("B", vector<vert_t> {"S", "D"}, vector<weight_t> {3, 4});
    graph.add_edge("C", vector<vert_t> {"D", "E"}, vector<weight_t> {3, 1});
    graph.add_edge("D", vector<vert_t> {"E", "F", "T"}, vector<weight_t> {1, 5, 3});
    graph.add_edge("E", vector<vert_t> {"G", "T"}, vector<weight_t> {2, 4});
    graph.add_edge("G", vector<vert_t> {"E", "T"}, vector<weight_t> {2, 3});
    graph.add_edge("T", "F", 5);

    cout << "Number of vertices = " << graph.size() << endl;
    cout << "Directed: " << (graph.is_directed() ? "yes" : "no") << endl;
    cout << "Name of vertex 3 is " << graph.get_vertex_by_id(3) << endl << endl;
    graph.print();

    graph.shortest_path("A", "D");

    for (auto i = vertices.begin(); i != vertices.end(); ++i) {
        for (auto j = vertices.begin(); j != vertices.end(); ++j) {
            cout << "Shortest path from " << *i << " to " << *j << " = "
                << graph.shortest_path(*i, *j) << endl;
        }

        cout << endl;
    }

    return 0;
}
