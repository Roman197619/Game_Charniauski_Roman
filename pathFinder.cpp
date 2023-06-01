#include "hexagon.h"
#include <vector>
#include <queue>
#include <limits>
#include <cmath>


double length(QPointF a, QPointF b)
{
    auto diff = a - b;
    return std::sqrt(diff.rx() * diff.rx() +  diff.ry() * diff.ry());
}


std::vector<int> dijkstra(std::vector<std::vector<int>>& graph, int start, int end)
{
   int size = graph.size();

    std::vector<int> distance(size, std::numeric_limits<int>::max());

    std::vector<int> parent(size, -1);

    std::vector<bool> visited(size, false);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    distance[start] = 0;
    pq.push(std::make_pair(0, start));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;

        visited[u] = true;

        for (int v = 0; v < size; ++v) {
            if (graph[u][v] != 0) {
                int weight = graph[u][v];
                int new_distance = distance[u] + weight;

                if (new_distance < distance[v]) {
                    distance[v] = new_distance;
                    parent[v] = u;
                    pq.push(std::make_pair(new_distance, v));
                }
            }
        }
    }

    std::vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());

    return path;
}


std::vector<int> FindPath(QVector<Hexagon*> hexagons, double centerDistance, int start, int end) {
    
    int size = hexagons.size();

    std::vector<std::vector<int>> graph(size, std::vector<int>(size, 0));

    for(int i = 0; i < hexagons.size(); i++){
        QPointF hexagonCenter = hexagons[i]->getCenter();
        for(int j = 0; j < size; j++){
            QPointF otherHexagonCenter = hexagons[j]->getCenter();
            if(length(hexagonCenter, otherHexagonCenter) == centerDistance) {
                graph[i][j] = hexagons[i]->weight;
                graph[j][i] = hexagons[j]->weight;
            }
        }
    }
    return dijkstra(graph, start, end);
}

