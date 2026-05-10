#include "graph.cpp"
#include <iostream>
using namespace std;

void showMenu()
{
    cout << endl;
    cout << "\n        ROUTE OPTIMIZATION MENU         \n";
    cout << "\n 1. Static Greedy Algorithm";
    cout << "\n 2. Static Brute Force Algorithm";
    cout << "\n 3. Dynamic Greedy Algorithm";
    cout << "\n 4. Dynamic Brute Force Algorithm";
    cout << "\n 5. Dijkstra's Algorithm";
    cout << "\n 6. Complexity & Time Analysis";
    cout << "\n 7. Memory & Representation Comparison";
    cout << "\n 0. Exit";
    cout << endl;
    cout << "\nSelection: ";
}

void listCities()
{
    cout << endl;
    cout << "0) Islamabad\n";
    cout << "1) Lahore\n";
    cout << "2) Karachi\n";
    cout << "3) Rawalpindi\n";
    cout << endl;
}

int main()
{
    int numCities = 4;
    Graph<int> route(numCities);
    DynamicGraph<int> dynRoute(numCities);

    string names[] = { "Islamabad", "Lahore", "Karachi", "Rawalpindi" };

    for (int i = 0; i < numCities; i++)
    {
        route.addCity(i, names[i]);
        dynRoute.addCity(i, names[i]);
    }

    route.readFile("graph_small.txt");
    dynRoute.readFile("graph_small.txt");

    int choice;
    do
    {
        showMenu();
        cin >> choice;

        int source, destination;

        switch (choice)
        {
        case 1:
            listCities();
            cout << "Enter Source: "; cin >> source;
            if (source >= 0 && source < numCities) route.Greedy(source);
            else cout << "INVALID INPUT\n";
            break;

        case 2:
            listCities();
            cout << "Enter Source: "; cin >> source;
            if (source >= 0 && source < numCities) route.BruteForce(source);
            else cout << "INVALID INPUT\n";
            break;

        case 3:
            listCities();
            cout << "Enter Source: "; cin >> source;
            if (source >= 0 && source < numCities) dynRoute.Greedy(source);
            else cout << "INVALID INPUT\n";
            break;

        case 4:
            listCities();
            cout << "Enter Source: "; cin >> source;
            if (source >= 0 && source < numCities) dynRoute.BruteForce(source);
            else cout << "INVALID INPUT\n";
            break;

        case 5:
            listCities();
            cout << "Enter Source: "; cin >> source;
            cout << "Enter Destination: "; cin >> destination;
            if (source >= 0 && source < numCities && destination >= 0 && destination < numCities)
            {
                cout << "\nShortest distance between " << names[source]
                    << " and " << names[destination] << " is: "
                    << route.dijkstra(source, destination) << " units\n";
            }
            else cout << "INVALID INPUT\n";
            break;

        case 6:
            route.analyzeComplexity();
            break;

        case 7:
            route.analyzeComplexity();
            dynRoute.compareRepresentation(route.StaticMemoryUsage());
            break;
            break;

        case 0:
            cout << "\nEXITING PROGRAM\n";
            break;

        default:
            cout << "Selection not recognized.\n";
        }
    } while (choice != 0);

    return 0;
}
