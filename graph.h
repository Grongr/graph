#ifndef PROJ_GRAPH_LIB_GRAPH_H
#define PROJ_GRAPH_LIB_GRAPH_H

#include <iostream>
#include <vector>

/*!
 * Namespace in which all library is defined
 */
namespace grl {

    /*!
     * Struct which is the edge of the graph
     * @tparam id_type  name says all you need to know
     */
    template<typename id_type>
    struct Edge {
        /*!
         * @param weight    weight of this edge
         * @param child_id  id of vertex in which it goes
         */
        double  weight;
        id_type childId;

        /*!
         * Constructor with all params
         * @param weight
         * @param childId
         */
        Edge(double weight, id_type childId): weight(weight), childId(childId) {}

        /*!
         * Constructor with only child_id param
         * @param child_id
         */
        Edge(id_type childId): Edge(0, childId) {}

        /*!
         * Default constructor
         */
        Edge(): Edge(0, 0) {}
    };

    /*!
     * Struct which contains all the information about one Vertex
     * @tparam id_type  name says all you need to know
     */
    template<typename id_type>
    struct Vertex {

        /*!
         * Id of this Vertex and array of eds
         */
        id_type id;
        std::vector<Edge<id_type>> eds;

        /*!
         * Constructor with params
         * @param id
         * @param eds
         */
        Vertex(id_type id, std::vector<Edge<id_type>>& eds): id(id), eds(eds){}

        /*!
         * Default Constructor
         * @param id
         */
        Vertex(id_type id): id(id), eds(0) {}

        /*!
         * Destructor. Deletes vector of Edges
         */
        ~Vertex() {
            delete [] this->eds;
            // TODO to read about concepts in 20cpp and do something with delete
        }

        /*!
         * Operator of input It will read Vertex in this order:
         *  1) id param
         *  2) integer number if id_type variables
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
     * This is a graph class!!!
     * @tparam id_type      name says all you need to know
     * @tparam user_data    user data class. interface for this class you may find in user_data.h file
     */
    template<typename id_type, typename user_data>
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
        // TODO operator >> for ifstream and istream different or standard

        /*!
         * Outs Graph in out stream in order
         * Vertexes do
         * @param out   output stream
         * @param g     graph variable
         * @return      output stream
         */
        friend std::ostream& operator<<(std::ostream &out, const Graph &g);
    private:
        std::vector<Vertex<id_type>> vertexes;
        user_data userData;
    };
}

#endif //PROJ_GRAPH_LIB_GRAPH_H
