#include "Graph.h"

using std::list;
using std::vector;
using std::queue;

Graph::Graph(int v) {
    prev = new int[V];
    diameter = 0;
    isConnected = false; 
    isBodedVertex = false; 
}

void Graph::buildRandomGraph(list<int> adj[], int V, float p) {

    int countEdge = 0;
    float probabiltyEdge;
    bool isConnected = false;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            probabiltyEdge = generateRandomNumber();

            if (probabiltyEdge < p && i != j) { addEdge(i, j); }
        }
    }
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);//need because undirected graph
}
int Graph::BFS(int src) {

    int maxDistancePerOneRunBFS = 0;
    int countDistances = 0;

    vector <int> dist(this->v, 0);
    vector <int> parent(this->v, -1);
    vector <bool> visited(this->v, false);

    queue<int> Q;
    dist[src] = 0;
    visited[src] = true;
    Q.push(src);

    list<int>::iterator it;

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = *it;
            if (!visited[v]) {

                dist[v] = dist[u] + 1;

                //update the max path per one BFS run
                if (dist[v] > maxDistancePerOneRunBFS) {
                    maxDistancePerOneRunBFS = dist[v];
                }
                countDistances++; //to checking connectivity

                parent[v] = u;
                visited[v] = true;
                Q.push(v);
            }
        }
    }

    if (countDistances < V - 1) { this->isConnected = false; }
    else if (countDistances == V - 1) { this->isConnected = true; }

    return maxDistancePerOneRunBFS;
}

void Graph::setDiameter(Graph g) {

    int diameter = 0;
    int tempToGetDiameter = 0;

    g.BFS(0); //run BFS to check if the graph is connected, if not, diameter is infinity (-1)

    if (g.getIsConnected()) {
    
        for (int i = 0; i < V; i++) { // run BFS on each vertex of the graph

            tempToGetDiameter = g.BFS(i); //the BFS return max path per run

            if (tempToGetDiameter > diameter) { diameter = tempToGetDiameter; } //update the max path per each BFS run
        }
        this->diameter = diameter;
    }
    else { this->diameter = -1; }
}
int Graph::getDiameter() { return this->diameter; }

bool Graph::getIsConnected() { return this->isConnected; }

void Graph::isIsolatedVertex(Graph g) {

     
    for (int i = 0; i < v; i++) {
        
        //if some list in the array is empty -> this vertex adj[i] is not connected to no one
        if (g.adj[i].empty()) { this->isBodedVertex = true; break; }
    }
}
bool Graph::getIsIsolatedVertex() { return this->isBodedVertex; }

Graph::~Graph() {}

float generateRandomNumber() { return (float(rand()) / float((RAND_MAX))); }


