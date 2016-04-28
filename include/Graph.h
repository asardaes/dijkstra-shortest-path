#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm> // std::find_if
#include <iostream> // std::cout
#include <limits> // std::numeric_limits<>::max
#include <map> // std::map
#include <set> // std::set
#include <utility> // std::pair
#include <vector> // std::vector

// =============================================================================================================================
// Graph class template
// =============================================================================================================================

template <typename vertex_t, typename weight_t>
class Graph {
    public: typedef int id_t;

    protected:

    private:
        template <typename w_t>
        struct Vertex {
            Vertex();
            Vertex(const id_t& id, const vertex_t& name);

            id_t id;
            vertex_t name;
            std::vector< std::pair<id_t, w_t> > edges;
        };

        id_t ids = id_t(0);
        bool directed;

        std::vector< Vertex<weight_t> > vertices;
        std::map< vertex_t, id_t > names_to_ids;

    public:
        enum class EXCEPTIONS {
            VERTEX_REPEATED
        };

        Graph(const int& num_vert = 1, const bool& directed = true);
        Graph(const std::vector<vertex_t>& vert_names, const bool& directed = true);

        unsigned int size();
        bool is_directed();
        void print();

        id_t get_vertex_id(const vertex_t& name);
        bool add_vertex_by_name(const vertex_t& name);

        bool add_edge_by_id(const id_t& id_1, const id_t& id_2, const weight_t& weight = weight_t(0));
        bool add_edge_by_name(const vertex_t& vert_1, const vertex_t& vert_2, const weight_t& weight = weight_t(0));
        bool add_edge_by_name(const vertex_t& vert_1, const std::vector<vertex_t>& verts_2, const std::vector<weight_t>& weights);

        weight_t shortest_path_by_id(const id_t& start, const id_t& target);
        weight_t shortest_path_by_name(const vertex_t& start, const vertex_t& target);
};

// =============================================================================================================================
// Implementation
// =============================================================================================================================

#include "Graph.hpp"

#endif // GRAPH_H
