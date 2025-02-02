#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

typedef pair<int, int> pii; // (cost, node)
typedef unordered_map<int, vector<pii>> Graph;

class Dijkstra {
public:
    Dijkstra(Graph& graph) : graph(graph) {}

    void findShortestPath(int start, int end) {
        unordered_map<int, int> dist;  // Store  shortest distances
        unordered_map<int, int> prev;  // Store previous nodes for path reconstruction
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        // Initialize distances to infinity
        for (const auto& node : graph) {
            dist[node.first] = numeric_limits<int>::max();
        }

        // Starting node distance is 0
        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int cost = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            // If we reached the destination, break early
            if (node == end) break;

            for (auto& neighbor : graph[node]) {
                int nextNode = neighbor.second;
                int edgeWeight = neighbor.first;

                int newDist = dist[node] + edgeWeight;
                if (newDist < dist[nextNode]) {
                    dist[nextNode] = newDist;
                    prev[nextNode] = node;
                    pq.push({newDist, nextNode});

                }
            }
        }

        // Print result
        printResult(start, end, dist, prev);
    }

private:
    Graph& graph;

    void printResult(int start, int end, unordered_map<int, int>& dist, unordered_map<int, int>& prev) {
        if (dist[end] == numeric_limits<int>::max()) {
            cout << "No path found from " << start << " to " << end << endl;
            return;
        }

        cout << "Shortest path cost: " << dist[end] << endl;
        cout << "Path: ";

        vector<int> path;
        for (int at = end; at != start; at = prev[at]) {
            path.push_back(at);
        }
        path.push_back(start);

        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
};

int main() {
    Graph graph;
    
    // Hardcoded graph (node -> {(cost, neighbor)})
    graph[0] = {{4, 1}, {1, 2}};
    graph[1] = {{4, 0}, {2, 2}, {5, 3}};
    graph[2] = {{1, 0}, {2, 1}, {8, 3}, {10, 4}};
    graph[3] = {{5, 1}, {8, 2}, {3, 4}};
    graph[4] = {{10, 2}, {3, 3}};

    int start, end;
    cout << "Enter start node: ";
    cin >> start;
    cout << "Enter end node: ";
    cin >> end;

    Dijkstra dijkstra(graph);
    dijkstra.findShortestPath(start, end);

    return 0;
}