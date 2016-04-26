/*
NOTES

Implementations of templates have to be included in header somehow, using this .hpp file and #including it in the Graph.h file
is one of the options I found to keep interface and implementation separate. However, I think this separation is merely visual,
so to speak. If I were to use the header in another project, I would also have to include the .hpp file, which has all the
details.
*/

#include <algorithm> // std::find_if
#include <iostream>
#include <list>
#include <map> // std::multimap
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// =============================================================================================================================
// Vertex struct constructors
// =============================================================================================================================

template <typename vertex_t, typename weight_t>
template <typename v_t, typename w_t>
Graph<vertex_t, weight_t>::Vertex<v_t, w_t>::Vertex() {
    // This seems to be needed for internal reasons
    id = 0;
    edges = std::list< std::pair<v_t, w_t> > { std::make_pair(v_t(), w_t(0)) };
};

template <typename vertex_t, typename weight_t>
template <typename v_t, typename w_t>
Graph<vertex_t, weight_t>::Vertex<v_t, w_t>::Vertex(const v_t& vertex, const w_t& weight, const int& id) :
    id(id) {
        edges = std::list< std::pair<v_t, w_t> > { std::make_pair(vertex, weight) };
};

// =============================================================================================================================
// Graph template constructors
// =============================================================================================================================

template <typename vertex_t, typename weight_t>
Graph<vertex_t, weight_t>::Graph(const int& num_vert, const bool& directed):
    directed(directed) {
        vertices = std::unordered_map< vertex_t, Vertex<vertex_t, weight_t> > (num_vert);
        vertices_by_id = std::vector<vertex_t> (num_vert);
}

template <typename vertex_t, typename weight_t>
Graph<vertex_t, weight_t>::Graph(const std::vector<vertex_t>& vert, const bool& directed):
    directed(directed) {
        vertices = std::unordered_map< vertex_t, Vertex<vertex_t, weight_t> > ();

        // at least one edge per vertex that points to self with a weight of zero
        for (auto it = vert.begin(); it != vert.end(); ++it) {
            // no repetitions
            if (vertices.find(*it) == vertices.end()) {
                vertices_by_id.push_back(*it);
                vertices[*it] = Vertex<vertex_t, weight_t> (*it, 0, ids++);
            }
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
        std::cout << "Vertex " << i->first << " (" << i->second.id << "):" << std::endl;

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
// Graph::add_vertex and overloads
// -----------------------------------------------------------------------------------------------------------------------------

template <typename vertex_t, typename weight_t>
void Graph<vertex_t, weight_t>::add_vertex(const vertex_t& vert) {
    // only add if it didn't exist
    if (vertices.find(vert) == vertices.end()) {
        vertices_by_id.push_back(vert);
        vertices[vert] = Vertex<vertex_t, weight_t> (vert, 0, ids++);
    }
}

// -----------------------------------------------------------------------------------------------------------------------------
// Graph::add_edge and overloads
// -----------------------------------------------------------------------------------------------------------------------------

// Add single edge to existing vertex
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

// Add several edges to existing vertex
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

// -----------------------------------------------------------------------------------------------------------------------------
// Graph::get_vertex_by_id method template
// -----------------------------------------------------------------------------------------------------------------------------

template <typename vertex_t, typename weight_t>
vertex_t Graph<vertex_t, weight_t>::get_vertex_by_id(const unsigned int& id) {
    if (id > vertices_by_id.size())
        return vertex_t();
    else
        return vertices_by_id[id-1];
}

// -----------------------------------------------------------------------------------------------------------------------------
// Graph::shortest path method template
// -----------------------------------------------------------------------------------------------------------------------------

template <typename vertex_t, typename weight_t>
weight_t Graph<vertex_t, weight_t>::shortest_path(const vertex_t& start, const vertex_t& target) {
    // find start
    auto start_exists = vertices.find(start);

    if (start_exists == vertices.end()) {
        throw "Start vertex does not exist in graph";
    }

    if (start == target) return weight_t(0);

    // initialize
    std::unordered_map< vertex_t, weight_t > successors;
    std::multimap< weight_t, vertex_t > open_set;
    std::unordered_set<vertex_t> closed_set;
    std::unordered_set<vertex_t> visited;

    closed_set.insert(start);

    weight_t dist = weight_t(0);
    vertex_t current = start;
    vertex_t next = start;
    bool found = false;

    while (true) {
        // skip if already visited
        if (visited.find(current) == visited.end()) {
            // visited now
            visited.insert(current);

            // add neighbors to open set if appropriate
            for (auto it = vertices[current].edges.begin(); it != vertices[current].edges.end(); ++it) {
                // if it's in closed set, skip
                if (closed_set.find(it->first) != closed_set.end()) continue;

                // what's its name?
                next = it->first;

                // what would be its associated distance?
                weight_t d = it->second + dist;

                // is it in succesors?
                auto it_succ = successors.find(next);
                if (it_succ == successors.end()) {
                    // it wasn't in successors
                    successors.insert(std::make_pair(next, d));
                    open_set.insert(std::make_pair(d, next));

                } else if (d < it_succ->second) {
                    // it was, but distance is better, so update
                    auto it_open = std::find_if(open_set.lower_bound(it_succ->second), open_set.upper_bound(it_succ->second),
                        [&next] (std::pair<weight_t, vertex_t> element) { return element.second == next; });

                    open_set.erase(it_open);
                    open_set.insert(std::make_pair(d, next));
                    successors[next] = d;
                }
            }
        }

        // no valid successors found
        if (successors.empty()) break;

        // extract successor with smallest distance and update current
        dist = open_set.begin()->first;
        current = open_set.begin()->second;

        // finished?
        if (current == target) {
            found = true;
            break;
        }

        // add it to closed set
        closed_set.insert(current);

        // remove it from successors
        successors.erase(current);
        open_set.erase(open_set.cbegin());
    }

    // final distance will be -1 if path could not be found
    if(found)
        return dist;
    else
        return weight_t(-1);
}
