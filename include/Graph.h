#ifndef GRAPH_H
#define GRAPH_H

#include <list> // std::list
#include <unordered_map> // std::unordered_map
#include <utility> // std::pair
#include <vector> // std::vector

// =============================================================================================================================
// Graph class template
// =============================================================================================================================

template <typename vertex_t, typename weight_t>
class Graph {
    public:
        Graph(std::vector<vertex_t> vert, bool directed = true);

        unsigned int size();
        void print();

        void add_edge(vertex_t vert_1, vertex_t vert_2, weight_t weight = weight_t(0));
        void add_edge(vertex_t vert_1, std::vector<vertex_t> verts_2, std::vector<weight_t> weights);

        weight_t shortest_path(vertex_t start, vertex_t target);

    protected:

    private:
        template <typename v_t, typename w_t>
        struct Vertex {
            Vertex();
            Vertex(v_t vertex, w_t weight);

            std::list< std::pair<v_t, w_t> > edges;
        };

        bool directed;
        std::unordered_map< vertex_t, Vertex<vertex_t, weight_t> > vertices;
};

// =============================================================================================================================
// Implementation
// =============================================================================================================================

#include "Graph.hpp"

#endif // GRAPH_H
