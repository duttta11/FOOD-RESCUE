#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

class RoadGraph
{
private:
    vector<string> locations;
    vector<vector<pair<int, int>>> adj;

    int findLocation(const string& name) const
    {
        for (int i = 0; i < locations.size(); i++)
        {
            if (locations[i] == name)
                return i;
        }
        return -1;
    }

public:
    void addLocation(const string& name)
    {
        if (findLocation(name) != -1)
            return;

        locations.push_back(name);
        adj.push_back({});
    }

    void addRoad(const string& from, const string& to, int distance)
    {
        if (distance < 0)
            return;

        addLocation(from);
        addLocation(to);

        int u = findLocation(from);
        int v = findLocation(to);

       
        adj[u].push_back({v, distance});
        adj[v].push_back({u, distance});
    }

    bool shortestPath(
        const string& start,
        const string& destination,
        vector<string>& route,
        int& totalDistance) const
    {
        route.clear();
        totalDistance = 0;

        int source = findLocation(start);
        int target = findLocation(destination);

        if (source == -1 || target == -1)
            return false;

        const int INF = numeric_limits<int>::max();

        vector<int> dist(locations.size(), INF);
        vector<int> parent(locations.size(), -1);

        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty())
        {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d != dist[u])
                continue;

            if (u == target)
                break;

            for (auto road : adj[u])
            {
                int v = road.first;
                int weight = road.second;

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        if (dist[target] == INF)
            return false;

        vector<int> path;

        for (int at = target; at != -1; at = parent[at])
            path.push_back(at);

        reverse(path.begin(), path.end());

        for (int index : path)
            route.push_back(locations[index]);

        totalDistance = dist[target];
        return true;
    }

    void loadSampleRoads()
    {
     
        addRoad("Dehradun", "Prem Nagar", 8);
        addRoad("Dehradun", "ISBT", 6);
        addRoad("Prem Nagar", "Clock Tower", 10);
        addRoad("ISBT", "Clock Tower", 7);
        addRoad("ISBT", "Raipur", 9);
        addRoad("Clock Tower", "Raipur", 5);
    }
};

#endif
