#ifndef PROJ_GRAPH_LIB_GRAPH_H
#define PROJ_GRAPH_LIB_GRAPH_H

#include <iostream>
#include <vector>

#define container   std::vector<Edge>
#define v_container std::vector<Vertex>
#define id_type     int

/*!
 * Namespace in which all library is defined
 */
namespace grl {

    /*!
     * Struct which is the edge of the graph
     */
    struct Edge {
        /*!
         * @param weight    weight of this edge
         * @param child_id  id of vertex in which it goes
         */
        double weight;
        id_type    child_id;

        /*!
         * Constructor with all params
         * @param weight
         * @param child_id
         */
        Edge(double weight, id_type child_id): weight(weight), child_id(child_id) {}

        /*!
         * Constructor with only child_id param
         * @param child_id
         */
        Edge(id_type child_id): Edge(0, child_id) {}

        /*!
         * Default constructor
         */
        Edge(): Edge(0, 0) {}
    };

    /*!
     * Struct which contains all the information about one Vertex
     */
    struct Vertex {

        /*!
         * Id of this Vertex and array of eds
         */
        id_type id;
        container eds;

        /*!
         * Constructor with params
         * @param id
         * @param eds
         */
        Vertex(id_type id, container& eds): id(id), eds(eds){}

        /*!
         * Default Constructor
         * @param id
         */
        Vertex(id_type id): id(id), eds(0) {}

        /*!
         * Operator of input It will read Vertex in this order:
         *  1) id param
         *  2) integer number if int variables
         *     which are id's of vertexes in which edges comes from this
         * @param in     input stream
         * @param ver    vertex in which input comes
         * @return       input stream
         */
        friend std::istream& operator>>(std::istream &in, Vertex &ver);

        /*!
         * Outs Vertex in @out stream. In the same order as >> operator
         * reads data
         * @param out   output stream
         * @param ver   Vertex
         * @return      output stream
         */
        friend std::ostream& operator<<(std::ostream &out, const Vertex &ver);
    };

    /*!
     * Graph class!!!
     */
    class Graph {
    public:
        /*!
         * Default constructor which makes
         * this v_container zero length
         */
        Graph(): vertexes(0) {}

        /*!
         * Reads Vertexes from in stream
         * in order Vertexes do
         * @param in    input stream
         * @param g     graph variable
         * @return      input stream
         */
        friend std::istream& operator>>(std::istream &in, Graph &g);

        /*!
         * Outs Graph in out stream in order
         * Vertexes do
         * @param out   output stream
         * @param g     graph variable
         * @return      output stream
         */
        friend std::ostream& operator<<(std::ostream &out, const Graph &g);
    private:
        v_container vertexes;
    };
}

#endif //PROJ_GRAPH_LIB_GRAPH_H
