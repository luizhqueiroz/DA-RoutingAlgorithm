#include "Data.h"

void Data::createGraph(const std::string& filename) {
    std::ifstream file(filename, std::ifstream::in);
    std::string line;

    if (!file.is_open()) {
        std::cout << "Arquivo não pode ser aberto" << std::endl;
        exit(1);
    }

    getline(file, line);

    while(!file.eof()) {
        int origem;
        int destino;
        double distancia;
        std::string word;

        getline(file, line);

        if (line == "") {
            continue;
        }

        std::stringstream sstream(line);

        getline(sstream, word, ',');
        origem = stoi(word);
        getline(sstream, word, ',');
        destino = stoi(word);
        getline(sstream, word);
        distancia = stod(word);

        graph.addVertex(origem);
        graph.addVertex(destino);
        graph.addBidirectionalEdge(origem, destino, distancia);
    }

    file.close();
}

void Data::createMediumGraph(const std::string& filename) {
    std::ifstream file(filename, std::ifstream::in);
    std::string line;

    if (!file.is_open()) {
        std::cout << "Arquivo não pode ser aberto" << std::endl;
        exit(1);
    }

    while(!file.eof()) {
        int origem;
        int destino;
        double distancia;
        std::string word;

        getline(file, line);

        if (line == "") {
            continue;
        }

        std::stringstream sstream(line);

        getline(sstream, word, ',');
        origem = stoi(word);
        getline(sstream, word, ',');
        destino = stoi(word);
        getline(sstream, word);
        distancia = stod(word);

        graph.addVertex(origem);
        graph.addVertex(destino);
        graph.addBidirectionalEdge(origem, destino, distancia);
    }

    file.close();
};

void Data::createRealGraph(const std::string& edges, const std::string& nodes) {
    std::ifstream edgesFile(edges, std::ifstream::in);
    std::ifstream nodesFile(nodes, std::ifstream::in);
    std::string line;

    if (!nodesFile.is_open() || !edgesFile.is_open()) {
        std::cout << "Arquivo não pode ser aberto" << std::endl;
        exit(1);
    }
        getline(nodesFile, line);
        getline(edgesFile, line);

        while (!nodesFile.eof()) {
            int id;
            double longitude;
            double latitude;
            std::string word;

            getline(nodesFile, line);

            if (line.empty()) {
                continue;
            }

            std::stringstream sstream(line);

            getline(sstream, word, ',');
            id = stoi(word);
            getline(sstream, word, ',');
            longitude = stod(word);
            getline(sstream, word);
            latitude = stod(word);

            graph.addVertex(id, longitude, latitude);
        }

        while (!edgesFile.eof()) {
            int origem;
            int destino;
            double distancia;
            std::string word;

            getline(edgesFile, line);

            if (line.empty()) {
                continue;
            }

            std::stringstream sstream(line);

            getline(sstream, word, ',');
            origem = stoi(word);
            getline(sstream, word, ',');
            destino = stoi(word);
            getline(sstream, word);
            distancia = stod(word);

            graph.addBidirectionalEdge(origem, destino, distancia);
        }

        nodesFile.close();
        edgesFile.close();
}

Graph *Data::getGraph() {
    return &graph;
}
