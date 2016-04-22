#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <utility>
#include <vector>

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
        void add_edge(std::vector<vertex_t> verts_1, std::vector<vertex_t> verts_2, std::vector<weight_t> weights);

    protected:

    private:
        template <typename v_t, typename w_t>
        struct Vertex {
            Vertex();
            Vertex(unsigned int id, v_t vertex, w_t weight);

            unsigned int id;
            std::list< std::pair<v_t, w_t> > edges;
        };

        unsigned int num_vert;
        bool directed;
        std::vector< Vertex<vertex_t, weight_t> > vertices;
};

// =============================================================================================================================
// Implementation
// =============================================================================================================================

#include "Graph.hpp"

#endif // GRAPH_H
