#ifndef ROUTING_ALGORITHM_GRAPH_H
#define ROUTING_ALGORITHM_GRAPH_H

/**
* @file Graph.h
* @brief Contains the declaration of the Graph class.
* @author Luiz, Pedro e Raphael
* @date 02/06/2023
*/

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <cmath>

#include "../data_structures/MutablePriorityQueue.h"
#include "VertexEdge.h"

using namespace std;

/**
 * @class Graph
 * @brief Represents the graph that´s going to be used for the routing algorithm program.
 */
class Graph {
public:

    /**
    * @brief Destructor for the Graph class.
    * @complexity O(|V|^2), where |V| is the number of vertices in the graph.
    */
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given ID.
    */

    /**
    * @brief Finds a vertex with the given ID in the graph.
    *
    * @param id The ID of the vertex to find.
    * @return A pointer to the vertex if found, nullptr otherwise.
    * @complexity O(1)
    */
    Vertex *findVertex(const int &id) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */

    /**
    * @brief Adds a vertex with the given ID to the graph.
    *
    * @param id The ID of the vertex to add.
    * @return True if the vertex was added successfully, false if a vertex with that ID already exists.
    * @complexity O(1)
    */
    bool addVertex(const int &id);

    /**
    * @brief Adds a vertex with the given ID, longitude, and latitude to the graph.
    *
    * @param id The ID of the vertex to add.
    * @param longitude The longitude of the vertex.
    * @param latitude The latitude of the vertex.
    * @return True if the vertex was added successfully, false if a vertex with that ID already exists.
    * @complexity O(1)
    */
    bool addVertex(const int &id, double longitude, double latitude);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    /**
    * @brief Adds an edge between two vertices in the graph.
    *
    * @param source The ID of the source vertex.
    * @param dest The ID of the destination vertex.
    * @param w The weight of the edge.
    * @return True if the edge was added successfully, false if the source or destination vertex does not exist.
    * @complexity O(1)
    */
    bool addEdge(const int &sourc, const int &dest, double w) const;
    /**
    * @brief Adds a bidirectional edge between two vertices in the graph.
    *
    * @param sourc The ID of the source vertex.
    * @param dest The ID of the destination vertex.
    * @param w The weight of the edge.
    * @return True if the edge was added successfully, false if the source or destination vertex does not exist.
    * @complexity O(1)
    */
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w) const;

    /**
    * @brief Returns the number of vertices in the graph.
    *
    * @return The number of vertices in the graph.
    * @complexity O(1)
    */
    int getNumVertex() const;

    /**
    * @brief Returns a map of all the vertices in the graph.
     *
    * @return An unordered map containing all the vertices in the graph.
    * @complexity O(1)
    */
    std::unordered_map<int, Vertex*> getVertexSet() const;

    /**
    * @brief Computes the minimum spanning tree (MST) of the graph using Prim's algorithm.
    *
    * @param source The ID of the source vertex.
    * @return A list of vertices representing the MST.
    * @complexity O(|V|^2), where |V| is the number of vertices in the graph.
    */
    std::list<Vertex *> prim(const int & source);

    /**
     * Finds a TSP tour using an approximation algorithm based on the Triangular Inequality.
     * The algorithm starts from the given source vertex ID.
     *
     * @param source The ID of the source vertex.
    * @return A vector of vertices representing the approximate TSP tour.
    * @complexity O(|V|^2), where |V| is the number of vertices in the graph.
    */
    std::vector<Vertex *> tourTriangApproxTsp(const int &source);

    /**
    * @brief Computes an approximate solution to the Traveling Salesman Problem (TSP) using a minimum spanning tree (MST) and a heuristic algorithm.
    *
    * @param source The ID of the source vertex.
    * @return A vector of vertices representing the approximate TSP tour.
    * @complexity O(|V|^2), where |V| is the number of vertices in the graph.
    */
    std::vector<Vertex *> tourHeuristicApproxTsp(const int &source);

    /**
    * @brief Computes an approximate solution to the Traveling Salesman Problem (TSP) using a minimum spanning tree (MST) and the Christofides algorithm.
    *
    * @param source The ID of the source vertex.
    * @return A vector of vertices representing the approximate TSP tour.
    * @complexity O(|V|^2), where |V| is the number of vertices in the graph.
    */
    std::vector<Vertex *> tourChristofidesApproxTsp(const int &source);

protected:
    std::unordered_map<int, Vertex*> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    /**
    * @brief Finds the index of the vertex with the given ID in the graph.
    *
    * @param id The ID of the vertex to find.
    * @return The index of the vertex if found, -1 otherwise.
    * @complexity O(1)
    */
    int findVertexIdx(const int &id) const;

    /**
    * @brief Helper function for depth-first search (DFS) traversal of the graph.
    *
    * @param v The current vertex being visited.
    * @param tour The vector to store the DFS traversal.
    * @complexity O(|V|^2), where |V| is the number of vertices in the graph.
    */
    void dfsVisit(Vertex *v, std::vector<Vertex *> &tour) const;

    /**
    * @brief Helper function for the heuristic algorithm to visit the graph vertices and form cycles.
    *
    * @param v The current vertex being visited.
    * @param tour The vector to store the visited vertices forming cycles.
    * @param numVert The number of vertices visited so far.
    * @complexity O(|V|^2), where |V| is the number of vertices in the graph.
    */
    void dfsVisitCycles(Vertex *v, std::vector<Vertex *> &tour, int numVert) const;
    /**
    * @brief Helper function for the heuristic algorithm to visit the minimum spanning tree (MST) vertices.
    *
    * @param mst The minimum spanning tree (MST) of the graph.
    * @complexity O(|V|^2), where |V| is the number of vertices in the graph.
    */
    void heuristicVisit(std::list<Vertex *> &mst);

    /**
    * @brief Helper function for the Christofides algorithm to visit the graph vertices.
    *
    * @param v The current vertex being visited.
    * @param eulerian The eulerian path.
    * @complexity O(|V|^2), where |V| is the number of vertices in the graph.
    */
    void christofidesVisit(Vertex *v, std::vector<Vertex *> &eulerian) const;
};

/**
 * Deletes a dynamically allocated matrix of integers.
 *
 * @param m A pointer to the matrix to be deleted.
 * @param n The size of the matrix.
 */
void deleteMatrix(int **m, int n);

/**
 * Deletes a dynamically allocated matrix of doubles.
 *
 * @param m A pointer to the matrix to be deleted.
 * @param n The size of the matrix.
 */
void deleteMatrix(double **m, int n);

#endif
