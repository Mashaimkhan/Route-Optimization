#include "graph.h"

template <typename T>
Graph<T>::Graph(int n)
{
    cities = n;
    cityNames = new string[cities];
    adjMatrix = new T * [cities];
    for (int i = 0; i < cities; i++)
    {
        adjMatrix[i] = new T[cities];
        for (int j = 0; j < cities; j++)
        {
            adjMatrix[i][j] = (i == j) ? 0 : 999;
        }
    }
}

template <typename T>
Graph<T>::~Graph()
{
    for (int i = 0; i < cities; i++)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
    delete[] cityNames;
}

template <typename T>
void Graph<T>::addCity(int index, string name)
{
    if (index >= 0 && index < cities)
        cityNames[index] = name;
}

template <typename T>
void Graph<T>::createRoute(int city1, int city2, T distance)
{
    adjMatrix[city1][city2] = distance;
    adjMatrix[city2][city1] = distance;
}

template <typename T>
void Graph<T>::readFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
        return;
    int city1, city2;
    T distance;
    while (file >> city1 >> city2 >> distance)
    {
        if (city1 < cities && city2 < cities)
            createRoute(city1, city2, distance);
    }
    file.close();
}

template <typename T>
void Graph<T>::Greedy(int source)
{
    bool* visited = new bool[cities] {false};
    int* path = new int[cities + 1];
    int currentCity = source;
    visited[source] = true;
    path[0] = source;
    T totalDistance = 0;

    for (int i = 1; i < cities; i++)
    {
        int nextCity = -1;
        T minDist = 999;
        for (int j = 0; j < cities; j++)
        {
            if (!visited[j] && adjMatrix[currentCity][j] < minDist)
            {
                minDist = adjMatrix[currentCity][j];
                nextCity = j;
            }
        }
        if (nextCity != -1)
        {
            currentCity = nextCity;
            visited[currentCity] = true;
            path[i] = currentCity;
            totalDistance += minDist;
        }
    }
    totalDistance += adjMatrix[currentCity][source];
    path[cities] = source;

    cout << "\nStatic Greedy Path (Start: " << cityNames[source] << "):\n";
    for (int i = 0; i <= cities; i++)
    {
        cout << cityNames[path[i]] << (i == cities ? "" : " -> ");
    }
    cout << "\nTotal Distance: " << totalDistance << endl;
    delete[] visited; delete[] path;
}

template <typename T>
void Graph<T>::BruteForceHelper(int* cityList, int start, int end, int source, T& minPath, int* bestPath)
{
    if (start == end)
    {
        T currentDistance = 0;
        int currentCity = source;

        for (int i = 0; i <= end; i++)
        {
            currentDistance += adjMatrix[currentCity][cityList[i]];
            currentCity = cityList[i];
        }
        currentDistance += adjMatrix[currentCity][source];

        if (currentDistance < minPath)
        {
            minPath = currentDistance;
            for (int i = 0; i <= end; i++) bestPath[i] = cityList[i];
        }
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            swap(cityList[start], cityList[i]);
            BruteForceHelper(cityList, start + 1, end, source, minPath, bestPath);
            swap(cityList[start], cityList[i]);
        }
    }
}

template <typename T>
void Graph<T>::BruteForce(int source)
{
    T minPath = 9999;
    int* cityList = new int[cities - 1];
    int* bestPath = new int[cities - 1];

    int index = 0;
    for (int i = 0; i < cities; i++)
    {
        if (i != source)
        {
            cityList[index++] = i;
        }
    }

    BruteForceHelper(cityList, 0, cities - 2, source, minPath, bestPath);

    cout << "\n OPTIMAL ROUTE  \n";
    cout << "Departure: " << cityNames[source] << "\n";
    for (int i = 0; i < cities - 1; i++)
    {
        cout << "  -> " << cityNames[bestPath[i]] << "\n";
    }
    cout << "Return to: " << cityNames[source] << "\n";
    cout << endl;
    cout << "Total Distance: " << minPath << " units" << endl;

    delete[] cityList;
    delete[] bestPath;
}

template <typename T>
T Graph<T>::dijkstra(int source, int destination)
{
    T* distance = new T[cities];
    bool* visited = new bool[cities] {false};
    for (int i = 0; i < cities; i++) distance[i] = 999;
    distance[source] = 0;

    for (int count = 0; count < cities - 1; count++)
    {
        T minVal = 999;
        int currentCity = -1;
        for (int neighborCity = 0; neighborCity < cities; neighborCity++)
            if (!visited[neighborCity] && distance[neighborCity] <= minVal)
            {
                minVal = distance[neighborCity];
                currentCity = neighborCity;
            }

        if (currentCity == -1)
            break;
        visited[currentCity] = true;
        for (int neighborCity = 0; neighborCity < cities; neighborCity++)
            if (!visited[neighborCity] && adjMatrix[currentCity][neighborCity] != 999 && distance[currentCity] + adjMatrix[currentCity][neighborCity] < distance[neighborCity])
                distance[neighborCity] = distance[currentCity] + adjMatrix[currentCity][neighborCity];
    }
    T result = distance[destination];
    delete[] distance;
    delete[] visited;
    return result;
}

template <typename T>
int Graph<T>::StaticMemoryUsage()
{
    return (cities * cities * sizeof(T)) + (cities * sizeof(string));
}

template <typename T>
void Graph<T>::analyzeComplexity()
{
    int n = cities;

    long long nSquared = n * n;
    long long nFactorial = 1;
    for (int i = 1; i <= n; i++) nFactorial *= i;

    cout << "\n TIME COMPLEXITY ANALYSIS \n";

    cout << "1. Greedy Algorithm: O(N^2)\n";
    cout << "   Formula: " << n << "^2\n";
    cout << "   Estimated Operations: " << nSquared << " checks\n\n";

    cout << "2. Brute Force: O(N!)\n";
    cout << "   Formula: " << n << "!\n";
    cout << "   Total Paths Evaluated: " << nFactorial << " combinations\n\n";

    cout << "3. Dijkstra Algorithm: O(V^2)\n";
    cout << "   Formula: " << n << " cities squared\n";
    cout << "   Scanning the " << n << "x" << n << " adjacency matrix.\n";

    cout << endl;
}

template <typename T>
DynamicGraph<T>::DynamicGraph(int nodes) : cities(nodes)
{
    adjList = new Node * [cities];
    cityNames = new string[cities];
    for (int i = 0; i < cities; i++)
        adjList[i] = NULL;
}

template <typename T>
DynamicGraph<T>::~DynamicGraph()
{
    for (int i = 0; i < cities; i++)
    {
        Node* temp = adjList[i];
        while (temp)
        {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
    delete[] adjList;
    delete[] cityNames;
}

template <typename T>
void DynamicGraph<T>::addCity(int index, string name)
{
    if (index >= 0 && index < cities) cityNames[index] = name;
}

template <typename T>
T DynamicGraph<T>::getDistance(int city1, int city2)
{
    if (city1 == city2)
        return 0;
    Node* temp = adjList[city1];
    while (temp)
    {
        if (temp->destination == city2)
            return (T)temp->distance;
        temp = temp->next;
    }
    return 999;
}

template <typename T>
void DynamicGraph<T>::createRoute(int city1, int city2, T distance)
{
    adjList[city1] = new Node{ city2, (int)distance, adjList[city1] };
    adjList[city2] = new Node{ city1, (int)distance, adjList[city2] };
}

template <typename T>
void DynamicGraph<T>::readFile(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
        return;
    int city1, city2;
    T distance;
    while (file >> city1 >> city2 >> distance)
    {
        if (city1 < cities && city2 < cities)
            createRoute(city1, city2, distance);
    }
    file.close();
}

template <typename T>
void DynamicGraph<T>::Greedy(int source)
{
    bool* visited = new bool[cities] {false};
    int currentCity = source;
    visited[source] = true;
    T totalDistance = 0;

    cout << "\nDynamic Greedy Path (Start: " << cityNames[source] << "):\n";
    cout << cityNames[source];

    for (int i = 1; i < cities; i++)
    {
        int nextCity = -1;
        T minDist = 999;
        Node* current = adjList[currentCity];
        while (current)
        {
            if (!visited[current->destination] && current->distance < minDist)
            {
                minDist = current->distance;
                nextCity = current->destination;
            }
            current = current->next;
        }
        if (nextCity != -1)
        {
            currentCity = nextCity;
            visited[currentCity] = true;
            totalDistance += minDist;
            cout << " -> " << cityNames[currentCity];
        }
    }
    totalDistance += getDistance(currentCity, source);
    cout << " -> " << cityNames[source] << "\nTotal Distance: " << totalDistance << endl;
    delete[] visited;
}

template <typename T>
void DynamicGraph<T>::BruteForceHelper(int* cityList, int start, int end, int source, T& minPath, int* bestPath)
{
    if (start == end)
    {
        T currentDistance = 0;
        int currentCity = source;

        for (int i = 0; i <= end; i++)
        {
            currentDistance += getDistance(currentCity, cityList[i]);
            currentCity = cityList[i];
        }
        currentDistance += getDistance(currentCity, source);

        if (currentDistance < minPath)
        {
            minPath = currentDistance;
            for (int i = 0; i <= end; i++) bestPath[i] = cityList[i];
        }
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            swap(cityList[start], cityList[i]);
            BruteForceHelper(cityList, start + 1, end, source, minPath, bestPath);
            swap(cityList[start], cityList[i]);
        }
    }
}

template <typename T>
void DynamicGraph<T>::BruteForce(int source)
{
    T minPath = 9999;
    int* cityList = new int[cities - 1];
    int* bestPath = new int[cities - 1];

    int index = 0;
    for (int i = 0; i < cities; i++)
    {
        if (i != source) cityList[index++] = i;
    }

    BruteForceHelper(cityList, 0, cities - 2, source, minPath, bestPath);

    cout << "\nDynamic Brute Force Path\n";
    cout << "Optimal Path: " << cityNames[source];
    for (int i = 0; i < cities - 1; i++)
    {
        cout << " -> " << cityNames[bestPath[i]];
    }
    cout << " -> " << cityNames[source] << endl;
    cout << "Total Distance: " << minPath << " km" << endl;

    delete[] cityList;
    delete[] bestPath;
}

template <typename T>
int DynamicGraph<T>::DynamicMemoryUsage()
{
    int total = (cities * sizeof(Node*)) + (cities * sizeof(string));
    for (int i = 0; i < cities; i++)
    {
        Node* temp = adjList[i];
        while (temp)
        {
            total += sizeof(Node);
            temp = temp->next;
        }
    }
    return total;
}

template <typename T>
void DynamicGraph<T>::compareRepresentation(int staticBytes)
{
    int dynamicBytes = DynamicMemoryUsage();
    cout << "\n Memory Comparison \n";
    cout << "Static (Matrix): " << staticBytes << " bytes\n";
    cout << "Dynamic (List):  " << dynamicBytes << " bytes\n";
    if (dynamicBytes < staticBytes)
    {
        cout << "Dynamic is more efficient. This is a Sparse Graph.\n";
    }
    else
    {
        cout << "Static is more efficient. This is a Dense Graph where pointer overhead is high.\n";
    }
}

template class Graph<int>;
template class DynamicGraph<int>;