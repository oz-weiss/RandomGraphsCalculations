#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <cmath>
#include <fstream>


constexpr int V = 1000;
constexpr int N = 500;

template<typename T>
void writeToCSV(std::string fileName, T n)
{
    std::fstream csvFileForGeneratedPFromArray;
    csvFileForGeneratedPFromArray.open(fileName, std::ios::out | std::ios::app);
    csvFileForGeneratedPFromArray << n << ",";
    csvFileForGeneratedPFromArray.close();
}

class Graph
{
    const int v = V;
    std::list<int> adj[V];
    int* prev;
    bool isConnected;
    int diameter;
    bool isBodedVertex;

public:

    Graph(int V);
    void buildRandomGraph(std::list<int> adj[], int v, float p);
    void addEdge(int u, int v);
    int BFS(int src);
    void setDiameter(Graph g);
    int getDiameter();
    bool getIsConnected();
    void isIsolatedVertex(Graph g);
    bool getIsIsolatedVertex();
    ~Graph();
};

float generateRandomNumber();

#endif