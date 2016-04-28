/*
NOTES

Implementations of templates have to be included in header somehow, using this .hpp file and #including it in the Graph.h file
is one of the options I found to keep interface and implementation separate. However, I think this separation is merely visual,
so to speak. If I were to use the header in another project, I would also have to include the .hpp file, which has all the
details.
*/

// =============================================================================================================================
// Vertex struct constructors
// =============================================================================================================================

// This seems to be needed for internal reasons
template <typename vertex_t, typename weight_t>
template <typename w_t>
Graph<vertex_t, weight_t>::Vertex<w_t>::Vertex() {
    id = 0;
    name = vertex_t();
    edges = std::vector< std::pair<id_t, w_t> > { std::make_pair(id, w_t(0)) };
};

template <typename vertex_t, typename weight_t>
template <typename w_t>
Graph<vertex_t, weight_t>::Vertex<w_t>::Vertex(const id_t& id, const vertex_t& name) :
    id(id), name(name) {
        edges = std::vector< std::pair<id_t, w_t> > { std::make_pair(id, w_t(0)) };
};

// =============================================================================================================================
// Graph template constructors
// =============================================================================================================================

template <typename vertex_t, typename weight_t>
Graph<vertex_t, weight_t>::Graph(const int& num_vert, const bool& directed) :
    directed(directed) {
        vertices = std::vector< Vertex<weight_t> > ();
        vertices.reserve(num_vert);
}

template <typename vertex_t, typename weight_t>
Graph<vertex_t, weight_t>::Graph(const std::vector<vertex_t>& vert_names, const bool& directed) :
    directed(directed) {
        vertices = std::vector< Vertex<weight_t> > ();
        vertices.reserve(vert_names.size());

        // at least one edge per vertex that points to self with a weight of zero
        for (auto name : vert_names) {
            // no repetitions
            if (names_to_ids.count(name) == 0) {
                vertices.push_back( Vertex<weight_t> (ids, name) );
                names_to_ids[name] = ids++;
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
    for (auto i : vertices) {
        std::cout << "Vertex " << i.name << " (" << i.id << "):" << std::endl;

        for (auto j : i.edges) {
            std::cout <<
                "\tEdge to " << vertices[j.first].name << " (" << vertices[j.first].id << ") " <<
                "with a weight of " << j.second <<
                std::endl;
        }
    }

    std::cout << std::endl;
}

// -----------------------------------------------------------------------------------------------------------------------------
// Graph::get_vertex_id
// -----------------------------------------------------------------------------------------------------------------------------

template <typename vertex_t, typename weight_t>
typename Graph<vertex_t, weight_t>::id_t Graph<vertex_t, weight_t>::get_vertex_id(const vertex_t& name) {
    if (names_to_ids.count(name) != 0) {
        return names_to_ids[name];
    } else {
        return -1;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------
// Graph::add_vertex_by_name
// -----------------------------------------------------------------------------------------------------------------------------

template <typename vertex_t, typename weight_t>
bool Graph<vertex_t, weight_t>::add_vertex_by_name(const vertex_t& name) {
    if (names_to_ids.count(name) == 0) {
        vertices.push_back( Vertex<weight_t> (ids, name) );
        names_to_ids[name] = ids++;

        return true;

    } else {
        return false;
    }
}

// -----------------------------------------------------------------------------------------------------------------------------
// Graph::add_edge_by_id
// -----------------------------------------------------------------------------------------------------------------------------

// Add single edge to existing vertex by id
template <typename vertex_t, typename weight_t>
bool Graph<vertex_t, weight_t>::add_edge_by_id(const id_t& id_1, const id_t& id_2, const weight_t& weight) {
    if (id_1 >= vertices.size() || (!directed && id_2 >= vertices.size())) {
        //std::cout << "Unexisting vertex or vertices." << std::endl;
        return false;
    }

    if (std::find_if(vertices[id_1].edges.begin(), vertices[id_1].edges.end(),
        [&id_2] (const std::pair<id_t, weight_t>& element) { return element.first == id_2; }) != vertices[id_1].edges.end())
    {
        //std::cout << "Vertex 2 already connected." << std::endl;
        return false;
    }

    vertices[id_1].edges.push_back( std::make_pair(id_2, weight) );

    if (!directed) {
        vertices[id_2].edges.push_back( std::make_pair(id_1, weight) );
    }

    return true;
}

// -----------------------------------------------------------------------------------------------------------------------------
// Graph::add_edge_by_name and overloads
// -----------------------------------------------------------------------------------------------------------------------------

// Add single edge to existing vertex by name
template <typename vertex_t, typename weight_t>
bool Graph<vertex_t, weight_t>::add_edge_by_name(const vertex_t& vert_1, const vertex_t& vert_2, const weight_t& weight) {
    id_t id_1 = get_vertex_id(vert_1);
    id_t id_2 = get_vertex_id(vert_2);

    if (id_1 < 0  || id_2 < 0) {
        //std::cout << "Unexisting vertex or vertices." << std::endl;
        return false;
    }

    return add_edge_by_id(id_1, id_2, weight);
}

// Add several edges to existing vertex by names
template <typename vertex_t, typename weight_t>
bool Graph<vertex_t, weight_t>::add_edge_by_name(const vertex_t& vert_1, const std::vector<vertex_t>& verts_2, const std::vector<weight_t>& weights) {
    if (verts_2.size() != weights.size()) {
        //std::cout << "Size mismatch between amount of vertices and amount of weights." << std::endl;
        return false;
    }

    auto vert_2 = verts_2.begin();
    auto weight = weights.begin();

    while (vert_2 != verts_2.end()) {
        add_edge_by_name(vert_1, *vert_2, *weight);
        vert_2++;
        weight++;
    }

    return true;
}

// -----------------------------------------------------------------------------------------------------------------------------
// Graph::shortest_path_by_id
// -----------------------------------------------------------------------------------------------------------------------------

template <typename vertex_t, typename weight_t>
weight_t Graph<vertex_t, weight_t>::shortest_path_by_id(const id_t& start, const id_t& target) {

}

// -----------------------------------------------------------------------------------------------------------------------------
// Graph::shortest_path_by_name
// -----------------------------------------------------------------------------------------------------------------------------

template <typename vertex_t, typename weight_t>
weight_t Graph<vertex_t, weight_t>::shortest_path_by_name(const vertex_t& start, const vertex_t& target) {

}
