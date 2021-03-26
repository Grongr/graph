#ifndef PROJ_GRAPH_LIB_GRAPH_H
#define PROJ_GRAPH_LIB_GRAPH_H

#include <iostream>
#include <vector>

/*!
 * Namespace in which all library is defined
 */
namespace ogl {

    /*!
     * Struct which is the edge of the graph
     * @tparam id_type  name says all you need to know
     */
    template<typename id_type = int, typename w_type = int>
    struct Edge {
        /*!
         * @param weight    weight of this edge
         * @param child_id  id of vertex in which it goes
         */
        w_type  weight;
        id_type childId;

        /*!
         * Constructor with all params
         * @param weight
         * @param childId
         */
        Edge(w_type weight, id_type childId): weight(weight), childId(childId) {}

        /*!
         * Constructor with only child_id param
         * @param child_id
         */
        Edge(id_type childId): weight(), childId(childId) {}

        /*!
         * Default constructor
         */
        Edge(): weight(), childId() {}

        /*!
         * in >> child_id >> weight
         * @param in
         * @param e
         * @return
         */
        friend std::istream& operator>>(std::istream &in, Edge<id_type, w_type> &e);

        /*!
         * out << childId << " " << weight
         * @param out
         * @param e
         * @return
         */
        friend std::ostream& operator<<(std::ostream &out, const Edge<id_type, w_type> &e);
    };

    /*!
     * Struct which contains all the information about one Vertex
     * @tparam id_type  name says all you need to know
     */
    template<typename id_type, typename user_data, typename w_type = int>
    struct Vertex {

        /*!
         * Id of this Vertex, array of eds, some user data in userData
         */
        id_type id;
        std::vector<Edge<id_type, w_type>> eds;
        user_data userData;

        /*!
         * Constructor with params
         * @param id
         * @param eds
         * @param userData
         */
        Vertex(id_type id, std::vector<Edge<id_type, w_type>>& eds, user_data userData):
        id(id), eds(eds), userData(userData) {}

        /*!
         * Default Constructor
         * @param id
         * @param userData
         */
        Vertex(id_type id, user_data userData): id(id), eds(0), userData(userData) {}

        /*!
         * Method which is made for my comfort
         * @return count of edges in this Vertex
         */
        unsigned long long count_of_edges() const {
            return this->eds.size();
        }

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
         *  2) number of edges of this Vertex
         *  3) integer number if id_type variables
         *     which are id's of vertexes in which edges comes from this
         *  4) user data in the order depends on what >> realisation it has
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
    template<typename id_type, typename user_data, typename w_type>
    class Graph {
    public:
        /*!
         * Default constructor which makes
         * this v_container zero length
         */
        Graph(): vertexes(0) {}

        /*!
         * [] operator which returns reference on the Vertex in the vertexes vector
         * @param i number if element in vector
         * @return  reference to the vertexes i element
         */
        Vertex<id_type, user_data, w_type>& operator[] (unsigned long long i) const {
            return this->vertexes[i];
        }

        /*!
         * Method which is made for comfort
         * @return  returns size of vertexes vector
         */
        unsigned long long count_of_ver() const {
            return this->vertexes.size();
        }

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

        /*!
         * The most standart destructor you can see in this scope
         */
        ~Graph() {
            delete this->vertexes;
        }

    private:
        std::vector<Vertex<id_type, user_data, w_type>> vertexes;
    };
}

//----------------------------------------Graph_In_Out---------------------------------------------
template<typename id_type, typename user_data, typename w_type>
std::istream& operator>>(std::istream &in, ogl::Graph<id_type, user_data, w_type> &g) {
    int count_of_vertexes;
    in >> count_of_vertexes;

    g.vertexes.resize(count_of_vertexes);

    // read vertexes one by one
    for (auto &i : g)
        in >> i;

    return in;
}

template<typename id_type, typename user_data, typename w_type>
std::ostream& operator<<(std::ostream &out, const ogl::Graph<id_type, user_data, w_type> &g) {
    out << g.count_of_ver() << std::endl;

    for (const auto &i : g) {
        out << i << std::endl;
    }
    return out;
}
//-------------------------------------------------------------------------------------------------

//--------------------------------------Vertexes_In_Out--------------------------------------------
template<typename id_type, typename user_data, typename w_type>
std::istream& operator>>(std::istream &in, ogl::Vertex<id_type, user_data, w_type> &ver) {

    in >> ver.id;

    size_t edges_count;
    in >> edges_count;

    ver.eds.resize(edges_count);

    for (auto& i : ver)
        in >> i;
    return in;
}

template<typename id_type, typename user_data, typename w_type>
std::ostream& operator<<(std::ostream &out, const ogl::Vertex<id_type, user_data> &ver) {
    out << ver.id;
    out << ver.count_of_edges();

    for (const auto& i : ver)
        out << i;

    return out;
}
//-------------------------------------------------------------------------------------------------

//---------------------------------------Edges_In_Out------------------------------------------
template<typename id_type, typename w_type>
std::istream& operator>>(std::istream &in, ogl::Edge<id_type, w_type> &e) {
    in >> e.childId;
    in >> e.weight;

    return in;
}

template<typename id_type, typename w_type>
std::ostream& operator<<(std::ostream &out, const ogl::Edge<id_type, w_type> &e) {
    out << e.childId << " " << e.weight;

    return out;
}
//-------------------------------------------------------------------------------------------------

#endif //PROJ_GRAPH_LIB_GRAPH_H
