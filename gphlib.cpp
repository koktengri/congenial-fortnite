/*
*  gphlib.cpp      ---- graph representation library implementation ----
*/

#include "gphlib.hpp"
#include <unordered_map>
#include <utility>
#include <vector>

template <class V, typename W>
Graph<V, W>::Graph(const V * const * vs, int n) : m{0} {
    for (int i = 0; i < n; i++) {
        vertices.push_back(std::make_unique<const Vertex>(vs[i]));
        rev_lookup[vs[i]] = i;
    }
}

template <class V, typename W>
Graph<V, W>::Graph(const std::vector<const V *> & vs, const std::vector<std::pair<const V *, const V *>> & edges) {
    for (int i = 0; i < vs.size(); i++) {
        vertices.push_back(std::make_unique<const Vertex>(vs[i]));
        rev_lookup[vs[i]] = i;
    }
    for (std::pair<const V *, const V *> e : edges) {
        vertex(e.first)->out_edges.insert({vertex(e.second), W{}});
        vertex(e.second)->in_edges.push_back({vertex(e.first), W{}});
        m++;
    }
}

template <class V, typename W>
Graph<V, W>::Graph(const std::vector<const V *> & vs, const std::vector<std::pair<std::pair<const V *, const V *>, W>> & edges) {
    for (int i = 0; i < vs.size(); i++) {
        vertices.push_back(std::make_unique<const Vertex>(vs[i]));
        rev_lookup[vs[i]] = i;
    }
    for (std::pair<std::pair<const V *, const V *>, W> e : edges) {
        vertex(e.first.first)->out_edges.push_back({vertex(e.first.second), e.second});
        vertex(e.first.second)->in_edges.push_back({vertex(e.first.first), e.second});
        m++;
    }
}

template <class V, typename W>
Graph<V, W>::Graph(const Graph & other) {
    for (Vertex * vertex : vertices) {
        delete vertex;
    }
    vertices.clear();
    for (Vertex * v : other.vertices) {
        vertices.push_back(new Vertex{(*v).v, {}, {}});
    }
    for (int i = 0; i < vertices.size(); i++) {
        //TODO: add edges
    }
    rev_lookup = other.rev_lookup;
    m          = other.m;
}

template <class V, typename W>
Graph<V, W> & Graph<V, W>::operator=(const Graph & other) {
    for (Vertex * vertex : vertices) {
        delete vertex;
    }
    vertices.clear();
    for (Vertex * v : other.vertices) {
        vertices.push_back(new Vertex{(*v).v, {}, {}});
    }
    for (int i = 0; i < vertices.size(); i++) {
        //TODO: add edges
    }
    rev_lookup = other.rev_lookup;
    m          = other.m;
    return *this;
}

template <class V, typename W>
Graph<V, W>::Graph(Graph && other) {
    //TODO
}

template <class V, typename W>
Graph<V, W> & Graph<V, W>::operator=(Graph && other) {
    //TODO
    return *this;
}

template <class V, typename W>
bool Graph<V, W>::operator==(const Graph & other) const {
    if (m != other.m || rev_lookup != other.rev_lookup || vertices.size() != other.vertices.size()) return false;
    for (int i = 0; i < vertices.size(); i++) {
        //TODO
    }
    return true;
}

template <class V, typename W>
bool Graph<V, W>::operator!=(const Graph & other) const {
    !(*this == other);
}

template <class V, typename W>
int Graph<V, W>::vertices_n() const {
    return vertices.size();
}

template <class V, typename W>
int Graph<V, W>::edges_n() const {
    return m;
}

template <class V, typename W>
bool Graph<V, W>::has_vertex(const V * v) const {
    return rev_lookup.count(v);
}

template <class V, typename W>
bool Graph<V, W>::add_vertex(const V * v) {
    if (rev_lookup.count(v)) return false;
    vertex(v);
    return true;
}

template <class V, typename W>
bool Graph<V, W>::has_edge(const V * u, const V * v) const {
    if (!rev_lookup.count(u) || !rev_lookup.count(v)) return false;
    for (auto edge : vertex(u)->out_edges) {
        if (edge.first->v == v) return true;
    }
    return false;
}

template <class V, typename W>
bool Graph<V, W>::has_edge(const std::pair<const V *, const V *> pv) const {
    return has_edge(pv.first, pv.second);
}

template <class V, typename W>
bool Graph<V, W>::add_edge(const V * u, const V * v, W weight) {
    try {
        if (weight == get_weight(u, v)) return false;

    } catch (const std::out_of_range &) {
        add_vertex(u);
        add_vertex(v);
    }
    vertex(u)->out_edges.push_back({vertex(v), weight});
    vertex(v)->in_edges.push_back({vertex(u), weight});
    return true;
}

template <class V, typename W>
bool Graph<V, W>::add_edge(const std::pair<const V *, const V *> pvs, W weight) { return add_edge(pvs.first, pvs.second, weight); }

template <class V, typename W>
bool Graph<V, W>::add_edge(const std::pair<std::pair<const V *, const V *>, W> ppvs) { return add_edge(ppvs.first.first, ppvs.first.second, ppvs.second); }

template <class V, typename W>
W Graph<V, W>::get_weight(const V * u, const V * v) const {
    if (!rev_lookup.count(u) || !rev_lookup.count(v)) throw std::out_of_range("node(s) don't exist in graph");
    for (auto edge : vertex(u)->out_edges) {
        if (edge.first->v == v) return edge.second;
    }
    throw std::out_of_range("no such edge in graph");
}

template <class V, typename W>
W Graph<V, W>::get_weight(std::pair<const V *, const V *> pvs) const {
    return get_weight(pvs.first, pvs.second);
}
