/*
NOTES

Implementation of templates have to be included in header somehow, using this .hpp file and #including it in the Graph.h file
is one of the options I found to keep interface and implementation separate. However, I think this separation is merely visual,
so to speak. If I were to use the header in another project, I would also have to include the .hpp file, which has all the
details.
*/

#include <algorithm> // std::find_if
#include <iostream>
#include <list>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

// =============================================================================================================================
// Vertex struct constructors
// =============================================================================================================================

template <typename vertex_t, typename weight_t>
template <typename v_t, typename w_t>
Graph<vertex_t, weight_t>::Vertex<v_t, w_t>::Vertex() {
    // This seems to be needed for internal reasons
    edges = std::list< std::pair<v_t, w_t> > { std::make_pair(v_t(), w_t(0)) };
};

template <typename vertex_t, typename weight_t>
template <typename v_t, typename w_t>
Graph<vertex_t, weight_t>::Vertex<v_t, w_t>::Vertex(const v_t& vertex, const w_t& weight) {
    edges = std::list< std::pair<v_t, w_t> > { std::make_pair(vertex, weight) };
};

// =============================================================================================================================
// Graph template constructors
// =============================================================================================================================

template <typename vertex_t, typename weight_t>
Graph<vertex_t, weight_t>::Graph(const std::vector<vertex_t>& vert, const bool& directed):
    directed(directed) {
        vertices = std::unordered_map< vertex_t, Vertex<vertex_t, weight_t> > ();

        // at least one edge per vertex that points to self with a weight of zero
        for (auto it = vert.begin(); it != vert.end(); ++it) {
            vertices[*it] = Vertex<vertex_t, weight_t> (*it);
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
bool Graph<vertex_t, weight_t>::is_directed() {
    return directed;
}

template <typename vertex_t, typename weight_t>
void Graph<vertex_t, weight_t>::print() {
    for (auto i = vertices.begin(); i != vertices.end(); ++i) {
        std::cout << "Vertex " << i->first << ":" << std::endl;

        for (auto j = i->second.edges.begin(); j != i->second.edges.end(); ++j) {
            std::cout <<
                "\tEdge to " << j->first <<
                " with a weight of " << j->second <<
                std::endl;
        }
    }

    std::cout << std::endl;
}

// -----------------------------------------------------------------------------------------------------------------------------
// Graph::add_edge and overloads
// -----------------------------------------------------------------------------------------------------------------------------

template <typename vertex_t, typename weight_t>
void Graph<vertex_t, weight_t>::add_edge(const vertex_t& vert_1, const vertex_t& vert_2, const weight_t& weight) {
    auto vert_1_exists = vertices.find(vert_1);

    if (vert_1_exists != vertices.end()) {
        auto vert_2_exists = std::find_if(vert_1_exists->second.edges.begin(), vert_1_exists->second.edges.end(),
            [&vert_2](std::pair<vertex_t, weight_t>& element) { return element.first == vert_2; });

        if (vert_2_exists == vert_1_exists->second.edges.end()) {
            vert_1_exists->second.edges.push_back(std::make_pair(vert_2, weight));

            if (!directed) {
                auto vert_inv = vertices.find(vert_2);

                if (vert_inv != vertices.end()) {
                    // this should always be the case here
                    vert_inv->second.edges.push_back(std::make_pair(vert_1, weight));
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
void Graph<vertex_t, weight_t>::add_edge(const vertex_t& vert_1, const std::vector<vertex_t>& verts_2, const std::vector<weight_t>& weights) {
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

// =============================================================================================================================
// Graph shortest path method template
// =============================================================================================================================

template <typename vertex_t, typename weight_t>
weight_t Graph<vertex_t, weight_t>::shortest_path(const vertex_t& start, const vertex_t& target) {
    std::stack<vertex_t> order;
    std::unordered_map<vertex_t, weight_t> path;
    std::unordered_map<vertex_t, weight_t> successors;

    // find start
    auto start_exists = vertices.find(start);

    if (start_exists == vertices.end()) {
        throw "Start vertex does not exist in graph";
    }

    // each edge is already a pair with weight 0
    path.insert(start_exists->second.edges.front());
    order.push(start);

    // initialize
    weight_t dist = weight_t(0);
    weight_t succ_min = weight_t(0);

    while (!order.empty() && path.find(target) == path.end()) {
        auto current = order.top();
        auto next = current;

        // add successors if appropriate
        for (auto it = vertices[current].edges.begin(); it != vertices[current].edges.end(); ++it) {
            bool is_new = path.find(it->first) == path.end() && successors.find(it->first) == successors.end();

            if (is_new) {
                // only insert next into successors if it wasn't on path/sucessors
                successors.insert(std::make_pair(it->first, it->second + dist));

            } else {
                // if it wasn't in path, it was already in successors, but distance is better, update successor
                auto it_succ = successors.find(it->first);
                if (path.find(it->first) == path.end() && it_succ != successors.end() && it->second + dist < it_succ->second) {
                    successors[it->first] = it->second + dist;
                }
            }
        }

        // find smallest distance so far
        if (!successors.empty()) {
            auto it_succ_min = successors.begin();

            next = it_succ_min->first;
            succ_min = it_succ_min->second;

            for (auto it = it_succ_min; it != successors.end(); ++it) {
                if (it->second < succ_min) {
                    next = it->first;
                    succ_min = it->second;
                }
            }
        }

        if (next == current) {
            // if next didn't change, go back
            order.pop();

            // if stack still has values
            if (!order.empty()) {
                // adjust distance
                dist = path[order.top()];
            }

        } else {
            // update distance
            dist = succ_min;

            // update path and order to include next
            path.insert(std::make_pair(next, dist));
            order.push(next);

            // erase node from successors
            successors.erase(next);
        }
    }

    // final distance will be -1 if path could not be found
    auto res = path.find(target);

    if(res != path.end())
        return res->second;
    else
        return weight_t(-1);
}
