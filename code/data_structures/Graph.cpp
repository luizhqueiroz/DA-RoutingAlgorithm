#include "Graph.h"

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::unordered_map<int, Vertex*> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const int &id) const {
    auto it = vertexSet.find(id);
    if (it != vertexSet.end())
        return it->second;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const int &id) const {
    auto it = vertexSet.find(id);
    if (it != vertexSet.end())
        return it->first;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */

bool Graph::addVertex(const int &id) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.insert({id, new Vertex(id)});
    return true;
}

bool Graph::addVertex(const int &id, double longitude, double latitude) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.insert({id,new Vertex(id, longitude, latitude)});

    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const int &sourc, const int &dest, double w) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w) const {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

std::list<Vertex *> Graph::prim(const int & source) {
    std::list<Vertex *> mst;
    if (vertexSet.empty()) {
        return mst;
    }

    for(auto v : vertexSet) {
        v.second->setDist(INF);
        v.second->setPath(nullptr);
        v.second->setVisited(false);
        v.second->setMstDegree(1);
    }

    Vertex *s = findVertex(source);
    s->setDist(0);
    s->setMstDegree(0);

    MutablePriorityQueue<Vertex> q;
    q.insert(s);

    while(!q.empty()) {
        auto v = q.extractMin();
        mst.push_back(v);
        if (v->getPath() != nullptr) {
            v->getPath()->getOrig()->increaseMstDegree();
            v->getPath()->setSelected(true);
            v->getPath()->getReverse()->setSelected(true);
        }
        v->setVisited(true);
        std::vector<Edge *> adj = v->getAdj();
        std::sort(adj.begin(), adj.end(), [](const Edge* a, const Edge* b){
            return a->getWeight() < b->getWeight();
        });
        for (auto &e : adj) {
            Vertex *w = e->getDest();
            if (!w->isVisited()) {
                double oldDist = w->getDist();
                if (e->getWeight() < oldDist) {
                    w->setDist(e->getWeight());
                    w->setPath(e);

                    if (oldDist == INF) {
                        q.insert(w);
                    }
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }
    }

    return mst;
}

std::vector<Vertex *> Graph::tourTriangApproxTsp(const int &source) {
    std::vector<Vertex *> tour;

    this->prim(source);

    auto s = findVertex(source);
    if (s == nullptr) {
        return tour;
    }

    for (auto v : vertexSet) {
        v.second->setVisited(false);
    }

    dfsVisit(s, tour);

    return tour;
}

void Graph::dfsVisit(Vertex *v, std::vector<Vertex *> &tour) const {
    v->setVisited(true);
    tour.push_back(v);
    auto adj = v->getAdj();
    std::sort(adj.begin(), adj.end(), [](const Edge* a, const Edge* b){
        return a->getWeight() < b->getWeight();
    });
    for (auto &e : adj) {
        auto w = e->getDest();
        if (!w->isVisited() && w->getPath()->getOrig()->getId() == v->getId()) {
            dfsVisit(w, tour);
        }
    }
}

std::vector<Vertex *> Graph::tourHeuristicApproxTsp(const int &source) {
    std::list<Vertex *> mst = prim(source);

    for (auto v : vertexSet) {
        v.second->setVisited(false);
        v.second->setProcessing(false);
    }

    Vertex *initial = mst.front();
    initial->setVisited(true);
    mst.pop_front();

    heuristicVisit(mst);
    std::vector<Vertex *> tour;

    dfsVisitCycles(initial, tour, 1);

    return tour;
}

void Graph::heuristicVisit(std::list<Vertex *> &mst) {
    Vertex *v = mst.front();
    mst.pop_front();

    if (!v->getPath()->getOrig()->isProcessing()) {
        v->getPath()->getOrig()->setProcessing(true);
    } else {
        double min = INF;
        Edge *tmp = nullptr;
        for (auto e : v->getAdj()) {
            if (!e->getDest()->isProcessing() && e->getWeight() < min) {
                min = e->getWeight();
                tmp = e->getReverse();
            }
        }

        if (tmp != nullptr) {
            v->setPath(tmp);
            tmp->getOrig()->setProcessing(true);
        }
    }

    if (mst.empty()) {
        return ;
    }

    heuristicVisit(mst);
}

std::vector<Vertex *> Graph::tourChristofidesApproxTsp(const int &source) {
    std::list<Vertex *> mst = prim(source);
    vector<Vertex *> oddVertices;

    for (auto &v : mst) {
        if (v->getMstDegree() % 2 != 0) {
            oddVertices.push_back(v);
        }
    }

    for (auto v : vertexSet) {
        v.second->setVisited(false);
    }

    for (int i = 0; i < oddVertices.size(); ++i) {
        if (!oddVertices[i]->isVisited()) {
            double minWeight = INF;
            int u = -1, v = -1;

            for (int j = i + 1; j < oddVertices.size(); j++) {
                double weight = oddVertices[i]->getEdgeWeight(oddVertices[j]);
                if (!oddVertices[j]->isVisited() && weight < minWeight) {
                    minWeight = weight;
                    u = i;
                    v = j;
                }
            }

            Edge *e = oddVertices[u]->getEdge(oddVertices[v]);
            e->setPerfectMatch(true);
            e->getReverse()->setPerfectMatch(true);
            oddVertices[u]->setVisited(true);
            oddVertices[v]->setVisited(true);
        }
    }

    for (auto v : vertexSet) {
        v.second->setVisited(false);
    }

    std::vector<Vertex *> eulerian;
    christofidesVisit(mst.front(), eulerian);

    std::reverse(eulerian.begin(), eulerian.end());
    for (auto &v : eulerian) {
        v->setVisited(false);
    }

    std::vector<Vertex *> tour;
    for (auto &v : eulerian) {
        if (!v->isVisited()) {
            tour.push_back(v);
            v->setVisited(true);
        }
    }

    return tour;
}

void Graph::christofidesVisit(Vertex *v, std::vector<Vertex *> &eulerian) const {
    std::stack<Vertex *> stack;
    Vertex *vertex = v;
    std::vector<Edge *> adj;

    for (auto &e: vertex->getAdj()) {
        if (e->isSelected() || e->isPerfectMatch()) {
            adj.push_back(e);
        }
    }

    std::sort(adj.begin(), adj.end(), [](const Edge* a, const Edge* b){
        return a->getWeight() < b->getWeight();
    });
    while (!stack.empty() || adj.size() > 0) {
        if (adj.empty()) {
            eulerian.push_back(vertex);
            vertex = stack.top();
            stack.pop();
        } else {
            stack.push(vertex);
            Edge *neighbor = nullptr;
            for (auto &e : adj) {
                if (e->isPerfectMatch()) {
                    neighbor = e;
                    neighbor->setPerfectMatch(false);
                    neighbor->getReverse()->setPerfectMatch(false);
                }
            }

            if (neighbor == nullptr) {
                neighbor = adj.front();
                neighbor->setSelected(false);
                neighbor->getReverse()->setSelected(false);
            }

            vertex = neighbor->getDest();
        }

        adj.clear();
        for (auto &e: vertex->getAdj()) {
            if (e->isSelected() || e->isPerfectMatch()) {
                adj.push_back(e);
            }
        }

        std::sort(adj.begin(), adj.end(), [](const Edge* a, const Edge* b){
            return a->getWeight() < b->getWeight();
        });
    }

    eulerian.push_back(vertex);
}

void Graph::dfsVisitCycles(Vertex *v, std::vector<Vertex *> &tour, int numVert) const {
    v->setVisited(true);
    tour.push_back(v);
    auto adj = v->getAdj();
    std::sort(adj.begin(), adj.end(), [](const Edge* a, const Edge* b){
        return a->getWeight() < b->getWeight();
    });
    bool has_cycles = true;
    for (auto &e : adj) {
        auto w = e->getDest();
        if (!w->isVisited() && w->getPath()->getOrig()->getId() == v->getId()) {
            dfsVisitCycles(w, tour, numVert + 1);
            has_cycles = false;
        }
    }

    if (numVert != vertexSet.size() && has_cycles) {
        double min = INF;
        Vertex *newVertex;
        for (auto &e : v->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited() && e->getWeight() < min) {
                min = e->getWeight();
                newVertex = w;
            }
        }

        dfsVisitCycles(newVertex, tour, numVert + 1);
    }
}


void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}