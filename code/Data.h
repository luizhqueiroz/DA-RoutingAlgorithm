#ifndef ROUTING_ALGORITHM_DATA_H
#define ROUTING_ALGORITHM_DATA_H

/**
* @file Data.h
* @brief Contains the declaration of the Data class for the creattion of Graphs.
* @author Luiz, Pedro e Raphael
* @date 02/06/2023
*/


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "data_structures/Graph.h"

/**
 * @class Data
 * @brief Represents Graphs creation used for the routing algorithm program.
 */
class Data {
public:

    /**
    * Creates a graph from a file with edges and distances.
    *
    * This function reads a file containing edges and distances and creates a graph based on that information.
    * The file format should have each line representing an edge in the format "origin, destination, distance".
    *
    * @param filename The name of the file to read.
    * @complexity The time complexity of this function is O(E), where E is the number of edges in the file.
    */
    void createGraph(const std::string& filename);

    /**
    * Creates a medium-sized graph from a file with edges and distances.
    *
    * This function reads a file containing edges and distances and creates a medium-sized graph based on that information.
    * The file format should have each line representing an edge in the format "origin, destination, distance".
    *
    * @param filename The name of the file to read.
    * @complexity The time complexity of this function is O(E), where E is the number of edges in the file.
    */
    void createMediumGraph(const std::string& filename);

    /**
    * Creates a real-sized graph from files with edges and nodes information.
    *
    * This function reads two files containing information about edges and nodes and creates a real-sized graph based on that information.
    * The edges file format should have each line representing an edge in the format "origin, destination, distance".
    * The nodes file format should have each line representing a node in the format "id, longitude, latitude".
     *
    * @param edges The name of the file containing edge information.
    * @param nodes The name of the file containing node information.
    * @complexity The time complexity of this function is O(E + N), where E is the number of edges and N is the number of nodes in the files.
    */
    void createRealGraph(const std::string& edges, const std::string& nodes);

    /**
    * Returns a pointer to the created graph.
    *
     * This function returns a pointer to the graph that was created using the `createGraph` or `createMediumGraph` or `createRealGraph` functions.
    * It allows accessing the graph for further operations or analysis.
    *
    * @return A pointer to the created Graph object.
    * @complexity The time complexity of this function is O(1).
    */
    Graph *getGraph();
private:
    Graph graph;
};

#endif
