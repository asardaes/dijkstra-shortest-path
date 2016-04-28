#include <iostream>
#include <string>

#include "Graph.h"

using namespace std;

using vert_t = string;
using weight_t = int;

int main() {
    vector<vert_t> vertices = {"S", "A", "B", "C", "D", "E", "F", "G", "T"};

    Graph<vert_t, weight_t> graph(vertices , true);

    graph.add_edge_by_name("S", vector<vert_t> {"A", "B", "D"}, vector<weight_t> {4, 3, 7});
    graph.add_edge_by_name("A", "C", 1);
    graph.add_edge_by_name("B", vector<vert_t> {"S", "D"}, vector<weight_t> {3, 4});
    graph.add_edge_by_name("C", vector<vert_t> {"D", "E"}, vector<weight_t> {3, 1});
    graph.add_edge_by_name("D", vector<vert_t> {"E", "F", "T"}, vector<weight_t> {1, 5, 3});
    graph.add_edge_by_name("E", vector<vert_t> {"G", "T"}, vector<weight_t> {2, 4});
    graph.add_edge_by_name("G", vector<vert_t> {"E", "T"}, vector<weight_t> {2, 3});
    graph.add_edge_by_name("T", "F", 5);

    cout << "Number of vertices = " << graph.size() << endl;
    cout << "Directed: " << (graph.is_directed() ? "yes" : "no") << endl;
    //cout << "Id of vertex M is " << graph.get_vertex_id("M") << endl;
    cout << "Id of vertex A is " << graph.get_vertex_id("A") << endl << endl;
    graph.print();

    return 0;
}
