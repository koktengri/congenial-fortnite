#ifndef GPHLIB_H
#define GPHLIB_H

/*
*  gphlib.hpp      ---- graph representation library ----
*/

#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>

//TODO: Uncomment Concepts and update to use modules when C++20 compiler support arrives

/*
template <typename W>
concept Comparable = requires(W w) { w <=> w; };
*/

/**Representation of a Graph using an adjacency list (using hashsets)
 * Graph is directed by default
 * template V for vertices, W for edge weights; W must support comparison (update for C++20) and have a default constructor
 * The graph does not contain the information stored in the nodes, only pointers V * to it;
 * the data in objects of type V is to be maintained by the user of the class,
 * pointers must be unique (not checked)
 * values of edge weights (W) are copied into the graph,
 * user of the class may modify them through add_edge
 * W must support default constructor as a default (=0) value
 */
template <class V, /*Comparable*/ typename W>
class Graph {
    struct Vertex {
        const V * v;
        std::unordered_set<std::pair<Vertex *, W>> out_edges;
        std::unordered_set<std::pair<Vertex *, W>> in_edges;
        Vertex(const V * v) : v(v) {}
    };

    /*an array of Vertex objects that is the adjacency list; all allocations of Vertex are automatically removed when vertices is destroyed, no additional destroyer necessary*/
    std::vector<std::unique_ptr<const Vertex>> vertices;

    std::unordered_map<const V *, int> rev_lookup;  //for quick lookup of index of some V (can be used to get the vertex of T)

    int m; /*number of edges, for number of vertices call vertices.size()*/

    //gets the pointer to the Vertex containing v, adds a new vertex with v if it doesn't exist in the graph
    inline Vertex * vertex(const V * v) const {
        if (!rev_lookup.count(v)) {
            rev_lookup[v] = vertices.size();
            vertices.push_back(std::make_unique<const Vertex>(v));
        }
        return vertices[rev_lookup[v]];
    }

   public:
    //---------------SPECIAL MEMBERS---------------
    //construct empty graph
    Graph() {}

    //construct graph with n vertices
    //construct vertices from a pointer to an array of const pointers to const objects T
    Graph(const V * const *, int n);

    //construct vertices from vector of  V  pointers and edges from vector of pairs of V pointers
    //if an edge contains a vertex not in the graph, that vertex is added to the graph
    Graph(const std::vector<const V *> &, const std::vector<std::pair<const V *, const V *>> & = {});

    //construct vertices from vector of V pointers and edges with weights from vector of pairs of V pointers
    //if an edge contains a vertex not in the graph, that vertex is added to the graph
    Graph(const std::vector<const V *> &, const std::vector<std::pair<std::pair<const V *, const V *>, W>> & = {});

    ~Graph() = default;  //destructor

    Graph(const Graph & other);  //copy constructor

    Graph & operator=(const Graph & other);  //copy assignment

    Graph(Graph && other);  //move constructor

    Graph & operator=(Graph && other);  //move assignment
    //---------------------------------------------

    //checks if graphs have same vertices and edges
    //this is an expensive operation on graphs with identical vertices and similar edges
    //worst case runtime and space complexity O(n^2)
    bool operator==(const Graph & other) const;

    //checks if graphs don't have same vertices and edges
    //this is an expensive operation on graphs with identical vertices and similar edges
    //worst case runtime and space complexity O(n^2)
    bool operator!=(const Graph & other) const;

    //number of vertices
    int vertices_n() const;

    //number of edges
    int edges_n() const;

    //true if pointer to object is in some Vertex
    bool has_vertex(const V *) const;

    //adds Node with pointer, returns true if a change is made to the graph (false if vertex already existed)
    bool add_vertex(const V *);

    //true if edge exists from u to v, false otherwise; also false if vertices u and v don't exist
    virtual bool has_edge(const V * u, const V * v) const;

    //true if edge exists from u to v, false otherwise; also false if vertices u and v don't exist
    virtual bool has_edge(const std::pair<const V *, const V *>) const;

    //adds edge (with weight) from u to v, returns true if a change is made to the graph
    virtual bool add_edge(const V * u, const V * v, W weight = {});

    //adds edge (with weight) indicated by the pair of pointers to objects
    virtual bool add_edge(const std::pair<const V *, const V *>, W weight = {});

    //adds edge with weight indicated by the tuple of 2 pointers and weight
    virtual bool add_edge(const std::pair<std::pair<const V *, const V *>, W>);

    /*get the weight of the edge or throw an out_of_range if no such edge exists*/
    W get_weight(const V * u, const V * v) const;

    /*get the weight of the edge or throw an out_of_range if no such edge exists*/
    W get_weight(std::pair<const V *, const V *>) const;
};
/*
//TODO
//undirected graph, not yet complete
template <class V, Comparable typename W>
class UGraph : public Graph<V, W> {
   public:
    DGraph(Graph g);

    virtual ~UGraph();
    //true if edge exists from u to v and v to u, false otherwise
    bool has_edge(const int u, const int v) const;

    //adds edge with weight in both directions
    bool add_edge(const int u, const int v, const int weight);

    //adds edge in both directions
    bool add_edge(const int u, const int v) { return add_edge(u, v, 0); }
};

template <class V, Comparable typename W>
class DGraph : public Graph<V, W> {};
*/
#endif
