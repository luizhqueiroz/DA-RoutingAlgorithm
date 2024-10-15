#include "Menu.h"

Menu::Menu(Graph *graph, GraphType type): graph(graph), type(type) {
    principal();
}

void Menu::menu() {
    std::cout << "\n=================================================================================================\n";
    std::cout << " \t\t\t\t\t\t\t\t\t\t\t\tMENU\n";
    std::cout << "=================================================================================================\n\n";

    std::cout << "Selecione uma das seguintes opções (0-3):\n";
    std::cout << "1- Backtracking Algorithm\n";
    std::cout << "2- Triangular Approximation Heuristic\n";
    std::cout << "3- Other Heuristics\n";
    std::cout << "0- Sair\n";
}

void Menu::principal() {
    do {
        menu();
        std::cin >> option;
        std::cin.ignore();

        switch (option) {
            case 0:
                quit = true;
                break;
            case 1:
                backtrackingMenu();
                break;
            case 2:
                triangularHeuristicMenu();
                break;
            case 3:
                otherHeuristicsMenu();
                break;

            default:
                std::cout << "Opção inválida. Favor selecionar uma opção válida\n";
                break;
        }
    } while (!quit);
}

void Menu::backtrackingMenu() {
    auto start = std::chrono::high_resolution_clock::now();
    double dist = routingOperations.tspBacktracking(graph);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

    cout << "The distance is: " << dist << '\n';
    cout << "The execution time is: " << duration << " seconds" << '\n';
    cout << "The path is: " << '\n';

    Vertex *vertexInitial= graph->findVertex(0);
    Edge *path = vertexInitial->getPath();
    while (path->getDest()->getId() != 0) {
        cout << path->getOrig()->getId() << "\t->\t" << path->getDest()->getId() << '\n';
        path = path->getDest()->getPath();
    }
    cout << path->getOrig()->getId() << "\t->\t" << path->getDest()->getId() << '\n';

}

void Menu::triangularHeuristicMenu() {
    std::vector<int> path;
    double dist;

    auto start = std::chrono::high_resolution_clock::now();
    dist = routingOperations.tspTriangApproximation(graph, path);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

    cout << "The distance is: " << dist << '\n';
    cout << "The execution time is: " << duration << " seconds" << '\n';
    cout << "The path is: ";

    for (auto i : path) {
        cout << i << " ";
    }
    cout << std::endl;
}

void Menu::otherHeuristicsMenu() {
    std::vector<int> path;
    double dist;

    do {
        std::cout << "Selecione uma das seguintes opções (0-2):\n";
        std::cout << "1- Heuristic Approximation\n";
        std::cout << "2- Christofides Approximation\n";
        std::cout << "0- Sair\n";
        std::cin >> option;
        std::cin.ignore();

        switch (option) {
            case 0:
                quit = true;
                break;
            case 1:
            {   auto start = std::chrono::high_resolution_clock::now();
                dist = routingOperations.TspHeuristicApprox(graph, path);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();


                cout << "The distance is: " << dist << '\n';
                cout << "The execution time is: " << duration << " seconds" << '\n';
                cout << "The path is: ";

                for (auto i : path) {
                    cout << i << " ";
                }
                cout << std::endl;

                quit = true;
            }
                break;
            case 2:
            {    auto start = std::chrono::high_resolution_clock::now();
                dist = routingOperations.TspChristofidesApprox(graph, path);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();

                cout << "The distance is: " << dist << '\n';
                cout << "The execution time is: " << duration << " seconds" << '\n';
                cout << "The path is: ";

                for (auto i : path) {
                    cout << i << " ";
                }
                cout << std::endl;

                quit = true;
            }
                break;
            default:
                std::cout << "Opção inválida. Favor selecionar uma opção válida\n";
                break;
        }
    } while (!quit);
    quit = false;
}
