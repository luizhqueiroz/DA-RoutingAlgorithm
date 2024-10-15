#include "Routing.h"

void Routing::tspBacktrackingRec(vector<Edge *> adj, std::vector<Edge *> tour, unsigned int n, unsigned int nVisited, double &minDist) {
    if (adj.empty()) {
        return ;
    }

    if (nVisited == n) {
        for (auto e : adj) {
            if (e->getDest()->getId() == 0) {
                tour[nVisited-1] = e;
                double dist = e->getOrig()->getDist() + e->getWeight();
                if (dist < minDist) {
                    minDist = dist;
                    for (Edge *path : tour) {
                        path->getOrig()->setPath(path);
                    }
                }
            }
        }
        return ;
    }

    for (auto e : adj) {
        Vertex *v = e->getDest();
        if (!v->isVisited()) {
            double dist = e->getOrig()->getDist() + e->getWeight();
            if (dist < minDist) {
                tour[nVisited-1] = e;
                v->setVisited(true);
                v->setDist(dist);
                tspBacktrackingRec(v->getAdj(), tour, n, nVisited + 1, minDist);
                v->setVisited(false);
            }
        }
    }
}

double Routing::tspBacktracking(Graph *graph) {
    double minDist = INF;
    std::unordered_map<int, Vertex*> vertexSet = graph->getVertexSet();
    unsigned int n = graph->getNumVertex();
    std::vector<Edge *> tour(n);

    for (const auto& pair : graph->getVertexSet()) {
        pair.second->setVisited(false);
        pair.second->setPath(nullptr);
        pair.second->setDist(0);
    }

    Vertex *vertexInitial = graph->findVertex(0);
    vertexInitial->setVisited(true);

    tspBacktrackingRec(vertexInitial->getAdj(), tour, n, 1, minDist);
    return minDist;
}

double Routing::tspTriangApproximation(Graph *graph, std::vector<int> &path) {
    double dist = 0;

    std::vector<Vertex *> tour = graph->tourTriangApproxTsp(0);

    path.push_back(0);
    for (unsigned int i = 1; i < tour.size(); i++) {
        path.push_back(tour[i]->getId());
        if (tour[i]->getPath()->getOrig()->getId() == tour[i-1]->getId()) {
            dist += tour[i]->getPath()->getWeight();
        } else {
            dist += tour[i-1]->getEdgeWeight(tour[i]);
        }
    }

    path.push_back(0);
    Vertex *final = graph->findVertex(path[graph->getNumVertex() - 1]);
    dist += final->getEdgeWeight(tour[0]);

    return dist;
}

double Routing::TspHeuristicApprox(Graph *graph, std::vector<int> &path) {
    double dist = 0;

    std::vector<Vertex *> tour = graph->tourHeuristicApproxTsp(0);

    path.push_back(0);
    for (unsigned int i = 1; i < tour.size(); i++) {
        path.push_back(tour[i]->getId());
        if (tour[i]->getPath()->getOrig()->getId() == tour[i-1]->getId()) {
            dist += tour[i]->getPath()->getWeight();
        } else {
            dist += tour[i-1]->getEdgeWeight(tour[i]);
        }
    }

    path.push_back(0);
    Vertex *final = graph->findVertex(path[graph->getNumVertex() - 1]);
    dist += final->getEdgeWeight(tour[0]);

    return dist;
}

double Routing::TspChristofidesApprox(Graph *graph, std::vector<int> &path) {
    double dist = 0;

    std::vector<Vertex *> tour = graph->tourChristofidesApproxTsp(0);

    path.push_back(0);
    for (unsigned int i = 1; i < tour.size(); i++) {
        path.push_back(tour[i]->getId());
        if (tour[i]->getPath()->getOrig()->getId() == tour[i-1]->getId()) {
            dist += tour[i]->getPath()->getWeight();
        } else {
            dist += tour[i-1]->getEdgeWeight(tour[i]);
        }
    }

    path.push_back(0);
    Vertex *final = graph->findVertex(path[graph->getNumVertex() - 1]);
    dist += final->getEdgeWeight(tour[0]);

    return dist;
}

