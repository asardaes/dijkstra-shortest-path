#include <algorithm>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

// =============================================================================================================================
// Vertex struct constructors
// =============================================================================================================================

template <typename vertex_t, typename weight_t>
template <typename v_t, typename w_t>
Graph<vertex_t, weight_t>::Vertex<v_t, w_t>::Vertex() {
    // This seems to be needed for whatever reason
};

template <typename vertex_t, typename weight_t>
template <typename v_t, typename w_t>
Graph<vertex_t, weight_t>::Vertex<v_t, w_t>::Vertex(unsigned int id, v_t vertex, w_t weight = w_t(0)):
    id(id) {
        edges = std::list< std::pair<v_t, w_t> > { std::make_pair(vertex, weight) };
};

// =============================================================================================================================
// Graph template constructors
// =============================================================================================================================

template <typename vertex_t, typename weight_t>
Graph<vertex_t, weight_t>::Graph(std::vector<vertex_t> vert, bool directed): directed(directed) {
    num_vert = vert.size();

    vertices = std::vector< Vertex<vertex_t, weight_t> > (num_vert);

    // at least one edge per vertex that points to self with a weight of zero
    int id = 0;
    for (auto it = vert.begin(); it != vert.end(); ++it) {
        vertices[id] = Vertex<vertex_t, weight_t> (id, *it);
        id++;
    }
}

// =============================================================================================================================
// Graph methods templates
// =============================================================================================================================

template <typename vertex_t, typename weight_t>
unsigned int Graph<vertex_t, weight_t>::size() {
    return vertices.size();
}

template <typename vertex_t, typename weight_t>
void Graph<vertex_t, weight_t>::print() {
    for (auto i = vertices.begin(); i != vertices.end(); ++i) {
        std::cout << "Vertex " << i->id << " - " <<
            i->edges.front().first << ":" << std::endl;

        for (auto j = i->edges.begin(); j != i->edges.end(); ++j) {
            std::cout <<
                "\tEdge to " << j->first <<
                " with a weight of " << j->second <<
                std::endl;
        }
    }
}

template <typename vertex_t, typename weight_t>
void Graph<vertex_t, weight_t>::add_edge(vertex_t vert_1, vertex_t vert_2, weight_t weight) {
    auto vert_1_exists = std::find_if(vertices.begin(), vertices.end(),
        [&vert_1](Vertex<vertex_t, weight_t>& vert) { return vert.edges.front().first == vert_1; });

    if (vert_1_exists != vertices.end()) {
        auto vert_2_exists = std::find_if(vert_1_exists->edges.begin(), vert_1_exists->edges.end(),
            [&vert_2](std::pair<vertex_t, weight_t>& element) { return element.first == vert_2; });

        if (vert_2_exists == vert_1_exists->edges.end()) {
            vert_1_exists->edges.push_back(std::make_pair(vert_2, weight));

            if (!directed) {
                auto vert_inv = std::find_if(vertices.begin(), vertices.end(),
                    [&vert_2](Vertex<vertex_t, weight_t>& vert) { return vert.edges.front().first == vert_2; });

                if (vert_inv != vertices.end()) {
                    // this should always be the case here
                    vert_inv->edges.push_back(std::make_pair(vert_1, weight));
                }
            }
        } else {
            //std::cout << "Vertex already connected." << std::endl;
        }
    } else {
        //std::cout << "Invalid vertex." << std::endl;
    }
}

template <typename vertex_t, typename weight_t>
void Graph<vertex_t, weight_t>::add_edge(vertex_t vert_1, std::vector<vertex_t> verts_2, std::vector<weight_t> weights) {
    if (verts_2.size() != weights.size()) {
        //std::cout << "Size mismatch between amount of vertices and amount of weights." << std::endl;
        return;
    }

    auto j = verts_2.begin();
    auto k = weights.begin();

    while (j != verts_2.end()) {
        add_edge(vert_1, *j, *k);

        j++;
        k++;
    }
}

template <typename vertex_t, typename weight_t>
void Graph<vertex_t, weight_t>::add_edge(std::vector<vertex_t> verts_1, std::vector<vertex_t> verts_2, std::vector<weight_t> weights) {
    if (verts_1.size() != verts_2.size() || verts_2.size() != weights.size()) {
        //std::cout << "Size mismatch between amount of vertices and amount of weights." << std::endl;
        return;
    }

    auto i = verts_1.begin();
    auto j = verts_2.begin();
    auto k = weights.begin();

    while (i != verts_1.end()) {
        add_edge(*i, *j, *k);

        i++;
        j++;
        k++;
    }
}
