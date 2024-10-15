#ifndef ROUTING_ALGORITHM_VERTEX_EDGE_H
#define ROUTING_ALGORITHM_VERTEX_EDGE_H

/**
* @file VertexEdge.h
* @brief Contains the declaration of the Vertex and Edges used to build a Graphs.
* @author Luiz, Pedro e Raphael
* @date 02/06/2023
*/


#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>

#include "../data_structures/MutablePriorityQueue.h"

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

/**
 * @class Vertex
 * @brief Represents a vertex in a graph.
 */

class Vertex {
public:

    /**
 * @brief Constructs a Vertex object with the given ID.
 * @param id The ID of the vertex.
 * @complexity O(1)
 */
    Vertex(int id);

    /**
 * @brief Constructs a Vertex object with the given ID, longitude, and latitude.
 * @param id The ID of the vertex.
 * @param longitude The longitude of the vertex.
 * @param latitude The latitude of the vertex.
 * @complexity O(1)
 */
    Vertex(int id, double longitude, double latitude);

    /**
 * @brief Compares this vertex with the specified vertex for sorting purposes.
 * @param vertex The vertex to compare.
 * @return True if this vertex is less than the specified vertex, false otherwise.
 * @complexity O(1)
 */
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    /**
 * @brief Gets the ID of the vertex.
 * @return The ID of the vertex.
 * @complexity O(1)
 */
    int getId() const;

    /**
 * @brief Gets the outgoing edges from this vertex.
 * @return A vector of pointers to the outgoing edges.
 * @complexity O(1)
 */
    std::vector<Edge *> getAdj() const;

    /**
 * @brief Gets the latitude of the vertex.
 * @return The latitude of the vertex.
 * @complexity O(1)
 */
    double getLat() const;

    /**
 * @brief Gets the longitude of the vertex.
 * @return The longitude of the vertex.
 * @complexity O(1)
 */
    double getLong() const;

    /**
 * @brief Checks if the vertex has been visited during graph traversal.
 * @return True if the vertex has been visited, false otherwise.
 * @complexity O(1)
 */
    bool isVisited() const;

    /**
 * @brief Checks if the vertex is being processed during graph traversal.
 * @return True if the vertex is being processed, false otherwise.
 * @complexity O(1)
 */
    bool isProcessing() const;

    /**
 * @brief Gets the indegree of the vertex.
 * @return The indegree of the vertex.
 * @complexity O(1)
 */
    unsigned int getIndegree() const;

    /**
 * @brief Gets the distance of the vertex from the source vertex.
 * @return The distance of the vertex from the source vertex.
 * @complexity O(1)
 */
    double getDist() const;

    /**
 * @brief Gets the path leading to this vertex.
 * @return A pointer to the edge representing the path, or nullptr if no path exists.
 * @complexity O(1)
 */
    Edge *getPath() const;

    /**
 * @brief Gets the degree of the vertex in the minimum spanning tree (MST).
 * @return The degree of the vertex in the MST.
 * @complexity O(1)
 */
    int getMstDegree() const;

    /**
 * @brief Gets the incoming edges to this vertex.
 * @return A vector of pointers to the incoming edges.
 * @complexity O(1)
 */
    std::vector<Edge *> getIncoming() const;

    /**
 * @brief Gets the edge from this vertex to the specified destination vertex.
 * @param d The destination vertex.
 * @return A pointer to the edge, or nullptr if the edge does not exist.
 * @complexity O(|E|), where |E| is the number of outgoing edges from the vertex.
 */
    Edge *getEdge(Vertex *d);

    /**
 * @brief Gets the weight of the edge from this vertex to the specified destination vertex.
 * @param d The destination vertex.
 * @return The weight of the edge, or the haversine distance if the edge does not exist.
 * @complexity O(|E|), where |E| is the number of outgoing edges from the vertex.
 */
    double getEdgeWeight(Vertex *);

    /**
 * @brief Sets the ID of the vertex.
 * @param id The ID to set.
 * @complexity O(1)
 */
    void setId(int info);

    /**
 * @brief Sets the longitude of the vertex.
 * @param longitude The longitude to set.
 * @complexity O(1)
 */
    void setLon(double longitude);

    /**
 * @brief Sets the latitude of the vertex.
 * @param latitude The latitude to set.
 * @complexity O(1)
 */
    void setLat(double latitude);

    /**
 * @brief Sets the visited status of the vertex during graph traversal.
 * @param visited The visited status to set.
 * @complexity O(1)
 */
    void setVisited(bool visited);

    /**
 * @brief Sets the processing status of the vertex during graph traversal.
 * @param processing The processing status to set.
 * @complexity O(1)
 */
    void setProcessing(bool processing);

    /**
 * @brief Sets the indegree of the vertex.
 * @param indegree The indegree to set.
 * @complexity O(1)
 */
    void setIndegree(unsigned int indegree);

    /**
 * @brief Sets the distance of the vertex from the source vertex.
 * @param dist The distance to set.
 * @complexity O(1)
 */
    void setDist(double dist);

    /**
 * @brief Sets the path leading to this vertex.
 * @param path A pointer to the edge representing the path.
 * @complexity O(1)
 */
    void setPath(Edge *path);

    /**
 * @brief Sets the degree of the vertex in the minimum spanning tree (MST).
 * @param mstDegree The degree to set.
 * @complexity O(1)
 */
    void setMstDegree(int mstDegree);

    /**
 * @brief Increases the degree of the vertex in the minimum spanning tree (MST) by 1.
 * @complexity O(1)
 */
    void increaseMstDegree();

    /**
 * @brief Decreases the degree of the vertex in the minimum spanning tree (MST) by 1.
 * @complexity O(1)
 */
    void decreaseMstDegree();

    /**
 * @brief Adds an outgoing edge from this vertex to the specified destination vertex with the given weight.
 * @param d The destination vertex.
 * @param w The weight of the edge.
 * @return A pointer to the created edge.
 * @complexity O(1)
 */
    Edge * addEdge(Vertex *dest, double w);

    /**
 * @brief Removes an outgoing edge from this vertex to the specified destination vertex.
 * @param destID The ID of the destination vertex.
 * @return True if the edge was successfully removed, false if the edge does not exist.
 * @complexity O(|E|), where |E| is the number of outgoing edges from the vertex.
 */
    bool removeEdge(int destID);

    /**
 * @brief Removes all outgoing edges from this vertex.
 * @complexity O(|E|), where |E| is the number of outgoing edges from the vertex.
 */
    void removeOutgoingEdges();

    /**
 * @brief Computes the haversine distance between this vertex and the specified vertex.
 * @param d The destination vertex.
 * @return The haversine distance between the two vertices.
 * @complexity O(1)
 */
    double haversine_distance(Vertex *d) const;

    friend class MutablePriorityQueue<Vertex>;
protected:
    int id;                // identifier
    double longitude = 0;
    double latitude = 0;
    std::vector<Edge *> adj;  // outgoing edges
    int mstDegree;

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree{}; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

/**
 * @brief Deletes an edge from the vertex.
 * @param edge A pointer to the edge to delete.
 * @complexity O(|E|), where |E| is the number of incoming edges to the destination vertex.
 */
    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/


/**
 * @class Edge
 * @brief Represents an edge in a graph.
 */
class Edge {
public:

    /**
 * @brief Constructs an Edge object with the specified source vertex, destination vertex, and weight.
 * @param orig The source vertex.
 * @param dest The destination vertex.
 * @param w The weight of the edge.
 * @complexity O(1)
 */
    Edge(Vertex *orig, Vertex *dest, double w);


    /**
 * @brief Gets the destination vertex of the edge.
 * @return A pointer to the destination vertex.
 * @complexity O(1)
 */
    Vertex * getDest() const;

    /**
 * @brief Gets the weight of the edge.
 * @return The weight of the edge.
 * @complexity O(1)
 */
    double getWeight() const;

    /**
 * @brief Checks if the edge is selected.
 * @return true if the edge is selected, false otherwise.
 * @complexity O(1)
 */
    bool isSelected() const;
/**
 * @brief Checks if the perfect edge is selected.
 * @return true if the perfect match edge is selected, false otherwise.
 * @complexity O(1)
 */
    bool isPerfectMatch() const;

    /**
 * @brief Gets the source vertex of the edge.
 * @return A pointer to the source vertex.
 * @complexity O(1)
 */
    Vertex * getOrig() const;

    /**
 * @brief Gets the reverse edge of the current edge.
 * @return A pointer to the reverse edge.
 * @complexity O(1)
 */
    Edge *getReverse() const;

    /**
 * @brief Gets the flow of the edge.
 * @return The flow of the edge.
 * @complexity O(1)
 */
    double getFlow() const;

    /**
 * @brief Sets the selection status of the edge.
 * @param selected The selection status of the edge.
 * @complexity O(1)
 */
    void setSelected(bool selected);


    /**
 * @brief Sets the perfect match for the edge.
 * @param perfectMatch The perfect match status for the edge.
 * @complexity O(1)
 */
    void setPerfectMatch(bool perfectMatch);


    /**
 * @brief Sets the reverse edge of the current edge.
 * @param reverse A pointer to the reverse edge.
 * @complexity O(1)
 */
    void setReverse(Edge *reverse);

    /**
 * @brief Sets the flow of the edge.
 * @param flow The flow of the edge.
 * @complexity O(1)
 */
    void setFlow(double flow);


protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity
    // auxiliary fields
    bool selected = false;
    bool perfectMatch = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};

#endif