#include <iostream>
#include <string>

#include "Graph.h"

using namespace std;

using vert_t = string;
using weight_t = float;

int main() {
    //Graph<vert_t, weight_t> graph(vector<vert_t> {0, 1}, true);
    Graph<vert_t, weight_t> graph(vector<vert_t> {"Me", "You", "He", "She"}, false);

    cout << "Number of vertices = " << graph.size() << endl << endl;

    graph.print();

    //graph.add_edge(0, 1, 1);
    //graph.add_edge(1, 0, 2);

    graph.add_edge("Me", "You", 1);
    graph.add_edge("You", "Me", 2);

    graph.add_edge("He", vector<vert_t> {"Me", "You"}, vector<weight_t> {3.5, 4.5});
    graph.add_edge("She", vector<vert_t> {"Me", "You", "He"}, vector<weight_t> {5.5, 6.5, 7.5});

    cout << endl << "After insertion:" << endl;
    graph.print();

    return 0;
}
