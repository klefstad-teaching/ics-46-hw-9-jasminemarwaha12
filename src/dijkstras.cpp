#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    // vector<int> distances(G.numVertices, INF);
    // previous.resize(G.numVertices, -1);
    // vector<bool> visited(G.numVertices, false);
    
    // distances[source] = 0;
    // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    // pq.push({0, source});
    
    // while (!pq.empty()) {
    //     int u = pq.top().second;
    //     pq.pop();
        
    //     if (visited[u]) {
    //         continue;
    //     }
        
    //     visited[u] = true;
        
    //     for (const Edge& edge : G[u]) {
    //         int v = edge.dst;
    //         int weight = edge.weight;
            
    //         if (!visited[v] && distances[u] != INF && distances[u] + weight < distances[v]) {
    //             distances[v] = distances[u] + weight;
    //             previous[v] = u;
    //             pq.push({distances[v], v});
    //         }
    //     }
    // }
    
    // return distances;
    vector<int> distances(G.size(), INF);
    distances[source] = 0;
    
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> queue;
    queue.push({0, source});
    
    previous = vector<int>(G.size(), -1);
    
    while (!queue.empty()) {
        int distance = queue.top().first;
        int vertex = queue.top().second;
        queue.pop();
        
        for (auto& e : G[vertex]) {
        if (distances[vertex] + e.weight < distances[e.dst]) {
            distances[e.dst] = distances[vertex] + e.weight;
            queue.push({distances[e.dst], e.dst});
            previous[e.dst] = vertex;
        }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    // If destination is unreachable
   // if (previous[destination] == -1 && destination != 0) {
    //     return {};
    // }
    
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    
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