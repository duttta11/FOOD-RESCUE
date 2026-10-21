#include <iostream>
#include "../include:/Dijkstra.h"

using namespace std;

int main()
{
    RoadGraph graph;
    graph.loadSampleRoads();

    vector<string> route;
    int distance;

    if (graph.shortestPath(
        "Dehradun", "Raipur", route, distance))
    {
        cout << "Shortest Route: ";

        for (int i = 0; i < route.size(); i++)
        {
            cout << route[i];

            if (i != route.size() - 1)
                cout << " -> ";
        }

        cout << "\nTotal Distance: "
             << distance << " km\n";
    }
    else
    {
        cout << "Route not found.\n";
    }

    return 0;
}
