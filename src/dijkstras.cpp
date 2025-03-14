#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    // Initialize distances, previous nodes, and visited flags
    vector<int> distances(G.numVertices, INF);
    previous.resize(G.numVertices, -1);
    vector<bool> visited(G.numVertices, false);
    
    // Set distance to source as 0
    distances[source] = 0;
    
    // Priority queue for Dijkstra's algorithm
    // Using pair<int, int> where first is distance and second is vertex
    // We use min heap based on distances
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // Push source vertex with distance 0
    pq.push({0, source});
    
    while (!pq.empty()) {
        // Get vertex with minimum distance
        int u = pq.top().second;
        pq.pop();
        
        // If already visited, skip
        if (visited[u]) {
            continue;
        }
        
        // Mark as visited
        visited[u] = true;
        
        // Check all neighbors of u
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            
            // If there's a shorter path to v through u
            if (!visited[v] && distances[u] != INF && distances[u] + weight < distances[v]) {
                // Update distance
                distances[v] = distances[u] + weight;
                // Update previous node
                previous[v] = u;
                // Add to priority queue
                pq.push({distances[v], v});
            }
        }
    }
    
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    // If destination is unreachable
    if (previous[destination] == -1 && destination != 0) {
        return {};
    }
    
    // Reconstruct path using previous array
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    
    // Reverse to get path from source to destination
    reverse(path.begin(), path.end());
    
    return path;
}

void print_path(const vector<int>& path, int total) {
    // Changed format to match expected output in tests
    if (path.empty()) {
        cout << "\nTotal cost is " << total << endl;
        return;
    }
    
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " ";
        }
    }
    cout << " \nTotal cost is " << total << endl;
}