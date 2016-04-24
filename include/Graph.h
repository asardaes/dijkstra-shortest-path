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
        Graph(const int& num_vert = 1, const bool& directed = true);
        Graph(const std::vector<vertex_t>& vert, const bool& directed = true);

        unsigned int size();
        bool is_directed();
        void print();

        void add_edge(const vertex_t& vert_1, const vertex_t& vert_2, const weight_t& weight = weight_t(0));
        void add_edge(const vertex_t& vert_1, const std::vector<vertex_t>& verts_2, const std::vector<weight_t>& weights);

        weight_t shortest_path(const vertex_t& start, const vertex_t& target);

    protected:

    private:
        template <typename v_t, typename w_t>
        struct Vertex {
            Vertex();
            Vertex(const v_t& vertex, const w_t& weight = w_t(0));

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
