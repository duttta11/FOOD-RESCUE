## Dijkstra's Shortest Path

The `RoadGraph` class finds the shortest route between two locations using Dijkstra's algorithm. It represents locations as a graph and roads as connections between them, with each road having a distance.

### Features

- **Location Management:** Adds locations to the road network without creating duplicates.
- **Road Management:** Connects two locations with a road and assigns a distance to it.
- **Two-Way Roads:** Allows travel in both directions between connected locations.
- **Shortest Path Calculation:** Finds the route with the minimum total distance between a starting point and a destination.
- **Route Reconstruction:** Stores the locations along the shortest route in the correct order.
- **Distance Calculation:** Returns the total distance of the selected route.
- **Sample Road Network:** Provides example roads between Dehradun, Prem Nagar, ISBT, Clock Tower and Raipur.

### How It Works

1. Locations are added to the graph.
2. Roads connect locations, with each road storing its distance.
3. The algorithm starts from the source location and assigns it a distance of zero.
4. A priority queue selects the location with the smallest known distance.
5. The algorithm checks its connected roads and updates distances whenever a shorter route is found.
6. The process continues until the destination is reached or no reachable locations remain.
7. The parent information is used to reconstruct the shortest route, and the total distance is returned.

### Main Functions

- `addLocation()` — Adds a new location to the graph if it does not already exist.
- `addRoad()` — Connects two locations with a two-way road and its distance.
- `shortestPath()` — Calculates the shortest route and total distance between two locations.
- `findLocation()` — Finds the index of a location in the graph.
- `loadSampleRoads()` — Loads an example road network for testing.

### Data Structures Used

- **Vector:** Stores location names and adjacency lists.
- **Adjacency List:** Stores each location's connected roads and their distances.
- **Priority Queue (Min-Heap):** Selects the location with the smallest known distance.
- **Parent Vector:** Records the previous location to reconstruct the route.
- **Distance Vector:** Stores the shortest known distance from the starting location.

### Example Road Network

The sample network contains these connections:

| From | To | Distance |
|---|---|---:|
| Dehradun | Prem Nagar | 8 km |
| Dehradun | ISBT | 6 km |
| Prem Nagar | Clock Tower | 10 km |
| ISBT | Clock Tower | 7 km |
| ISBT | Raipur | 9 km |
| Clock Tower | Raipur | 5 km |

These distances are examples for testing and do not represent actual road distances.

For example, the shortest route from Dehradun to Raipur is:

`Dehradun → ISBT → Raipur`

Total distance: **15 km**

### Time Complexity

Let \(V\) be the number of locations and \(E\) be the number of roads.

| Operation | Time Complexity |
|---|---|
| Add a location | O(V) |
| Find a location | O(V) |
| Add a road | O(V) |
| Shortest path | O((V + E) log V) |

The shortest-path complexity assumes the usual priority-queue analysis; the exact cost can vary because this implementation uses a linear search to find location indices.

### Purpose

The main purpose of Dijkstra's algorithm in the Food Rescue System is to identify the shortest route between locations, helping plan food deliveries to NGOs efficiently and reduce unnecessary travel distance.
