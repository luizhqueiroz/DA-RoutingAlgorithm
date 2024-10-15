#ifndef ROUTING_ALGORITHM_ROUTING_H
#define ROUTING_ALGORITHM_ROUTING_H

/**
* @file Routing.h
* @brief Contains the declaration of the Routing class.
* @author Luiz, Pedro e Raphael
* @date 02/06/2023
*/

#include "data_structures/Graph.h"
#include "data_structures/VertexEdge.h"

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>

/**
@class Routing
@brief Represents a routing algorithm for finding optimal paths in a graph.
*/
class Routing {

public:

    /**
    * Calculates the minimum distance of a traveling salesperson problem (TSP) using backtracking.
    *
    * This function uses a backtracking algorithm to find the minimum distance of a TSP on a given graph.
    * The TSP aims to find the shortest possible route that visits all vertices in a graph exactly once and returns to the starting vertex.
    *
    * @param graph A pointer to the Graph object representing the graph.
    * @return The minimum distance of the TSP.
    *
    * @param graph A pointer to the Graph object representing the graph.
    *              The graph should be initialized and contain the vertices and edges.
    *
    * @return The minimum distance of the TSP. The distance is returned as a double value.
    *         If the minimum distance is not found or the graph is empty, the function returns a value of `INF` (infinity).
    *
    * @complexity The time complexity of this function depends on the backtracking algorithm used and is typically exponential, O((n-1)!), where n is the number of vertices in the graph.
    */
    static double tspBacktracking(Graph *graph);

    /**
    * @brief Finds an approximate solution to the Traveling Salesman Problem (TSP) using the Triangulation algorithm. O((V + E) log V)
    * @param graph The graph representing the TSP instance.
    * @param path[out] The approximate TSP path.
    * @return The length of the approximate TSP path.
    *
    * This function uses the Triangulation algorithm to find an approximate solution to the TSP.
    * It constructs a minimum spanning tree of the graph and then performs a depth-first traversal to generate
    * a TSP path that visits each vertex exactly once.
    */
    static double tspTriangApproximation(Graph *graph, std::vector<int> &path);

    /**
    * Approximates the Traveling Salesman Problem (TSP) tour using a Heuristic Approximation Algorithm.
    *
    * This function approximates the TSP tour using a heuristic approximation algorithm, which constructs a tour by greedily
    * selecting the nearest neighbor at each step.
    *
    * @param graph The graph representing the TSP problem.
    * @param path A reference to a vector to store the TSP tour path.
    * @return The approximate distance of the TSP tour.
    * @complexity The time complexity of this function is O(n^2), where n is the number of vertices in the graph.
    */
    static double TspHeuristicApprox(Graph *graph, std::vector<int> &path);

    /**
    * Approximates the Traveling Salesman Problem (TSP) tour using the Christofides Approximation Algorithm.
    *
    * This function approximates the TSP tour using the Christofides Approximation Algorithm, which constructs a minimum
    * spanning tree, finds a minimum-weight perfect matching of the odd-degree vertices, and combines them to form a tour.
    *
    * @param graph The graph representing the TSP problem.
    * @param path A reference to a vector to store the TSP tour path.
    * @return The approximate distance of the TSP tour.
    * @complexity The time complexity of this function depends on the complexity of constructing the minimum spanning tree, finding a minimum-weight perfect matching, and combining them to form a tour, which is typically O(n^3), where n is the number of vertices in the graph.
    */
    static double TspChristofidesApprox(Graph *graph, std::vector<int> &path);

private:

    /**
    * Recursive helper function for solving the Traveling Salesman Problem (TSP) using backtracking.
    *
    * This function performs the backtracking algorithm to find the optimal TSP tour. It explores all possible paths
    * in a recursive manner and updates the minimum distance found so far.
    *
    * @param adj The adjacency list of the current vertex.
    * @param tour The current tour being constructed.
    * @param n The total number of vertices in the graph.
    * @param nVisited The number of vertices visited so far.
    * @param minDist A reference to the minimum distance found so far.
    * @complexity The time complexity of this function is O((n-1)!), where n is the number of vertices in the graph.
    */
    static void tspBacktrackingRec(vector<Edge *> adj, std::vector<Edge *> tour, unsigned int n, unsigned int nVisited, double &minDist);
    //double preOrderWalk(Graph * graph, std::vector<int> &path);
};

#endif
