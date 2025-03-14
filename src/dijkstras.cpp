#include "dijkstras.h"
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.size(), INF);
    distances[source] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
    queue.push({0, source});
    previous.assign(G.size(), -1);
    
    while (!queue.empty()) {
        auto [distance, vertex] = queue.top();
        queue.pop();
        
        for (const auto& e : G[vertex]) {
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

void print_path(const vector<int>& v, int total) {
    // if (path.empty()) {
    //     cout << "\nTotal cost is " << total << endl;
    //     return;
    // }

    // for (int i = 0; i < v.size(); ++i) {
    //     cout << v[i];
    //     if (i < v.size() - 1) {
    //         cout << " ";
    //     }
    // }
    // cout << "\nTotal cost is " << total << endl;

    if (v.empty()) {
        cout << "\nTotal cost is " << total << endl;
        return;
    }
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i < v.size() - 1) {
            cout << " ";
        }
    }
    cout << " \nTotal cost is " << total << endl;
    
}