#ifndef ROUTING_ALGORITHM_MENU_H
#define ROUTING_ALGORITHM_MENU_H

/**
* @file Menu.h
* @brief Contains the declaration of the Menu class.
* @author Luiz, Pedro e Raphael
* @date 02/06/2023
*/

#include <iostream>
#include <chrono>

#include "data_structures/Graph.h"
#include "Routing.h"

enum GraphType{toyGraph, mediumGraph, realGraph, externGraph};

/**
 * @class Menu
 * @brief Represents the menu for the routing algorithm program.
 */
class Menu {
public:
    /**
     * @brief Constructs a Menu object.
     * @param graph The graph to be used for routing.
     * @param type The type of the graph.
     */
    Menu(Graph *graph, GraphType type);

private:
    Graph *graph;
    GraphType type;
    Routing routingOperations;

    int option;
    bool quit = false;
    /**
     * @brief Displays the menu options.
     */
    void menu();

    /**
     * @brief Handles the main menu of the program.
     */
    void principal();

    /**
     * @brief Handles the menu for the Backtracking Algorithm.
     */
    void backtrackingMenu();

    /**
     * @brief Handles the menu for the Triangular Approximation Heuristic.
     */
    void triangularHeuristicMenu();

    /**
     * @brief Handles the menu for other heuristics.
     */
    void otherHeuristicsMenu();
};

#endif
