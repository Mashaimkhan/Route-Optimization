#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

struct Node
{
    int destination;
    int distance;
    Node* next;
};

template <typename T>
class Graph
{
private:
    int cities;
    string* cityNames;
    T** adjMatrix;
    void BruteForceHelper(int* cityList, int start, int end, int source, T& minPath, int* bestPath);

public:
    Graph(int n);
    ~Graph();
    void addCity(int index, string name);
    void createRoute(int city1, int city2, T distance);
    void readFile(string filename);
    void Greedy(int source);
    void BruteForce(int source);
    T dijkstra(int source, int destination);
    int StaticMemoryUsage();
    void analyzeComplexity();
};

template <typename T>
class DynamicGraph
{
private:
    int cities;
    Node** adjList;
    string* cityNames;
    T getDistance(int city1, int city2);
    void BruteForceHelper(int* cityList, int start, int end, int source, T& minPath, int* bestPath);

public:
    DynamicGraph(int nodes);
    ~DynamicGraph();
    void addCity(int index, string name);
    void createRoute(int city1, int city2, T distance);
    void readFile(string filename);
    void Greedy(int source);
    void BruteForce(int source);
    int DynamicMemoryUsage();
    void compareRepresentation(int staticBytes);
};