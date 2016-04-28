#include <iostream>
#include <string>

#include "Graph.h"

using namespace std;

using vert_t = string;
using weight_t = int;

int main() {
    int s, n, p, nr, cost, r;
    char name[12], name1[12], name2[12];
    string NAME, NAME1, NAME2;

    //cout << "Tests" << endl;
    scanf("%d", &s);

    while (s--) {
        //cout << "Cities" << endl;
        scanf("%d", &n);

        Graph<vert_t, weight_t> graph (n);

        for (int i = 0; i < n; i++) {
            //cout << "NAME" << endl;

            scanf("%10s", name);
            NAME = name;
            graph.add_vertex_by_name(NAME);

            //cout << "Neighbors" << endl;
            scanf("%d", &p);

            for(int j = 0; j < p; j++) {
                //cout << "Id/Cost" << endl;
                scanf("%d %d", &nr, &cost);

                graph.add_edge_by_id(i, nr-1, cost);
            }
        }

        //cout << "Results" << endl;
        scanf("%d", &r);

        for (int res = 0; res < r; res++) {
            scanf("%10s %10s", name1, name2);
            NAME1 = name1;
            NAME2 = name2;
            printf("%d\n", graph.shortest_path_by_name(NAME1, NAME2));
        }

        printf("\n");
    }

    return 0;
}
