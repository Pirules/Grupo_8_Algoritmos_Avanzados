/*
 * Descripción breve del programa:
 * Implementación de los algoritmos de Dijkstra y Floyd-Warshall para encontrar las distancias más cortas en un grafo dirigido
 * representado como una matriz de adjacencia de un grafo dirijido.
 * 
 *    Autores: Luis Angel Alba Alfaro - A01640314
 *             Fernando García Tejeda - A01642285
 *             Bruno Márquez Puig     - A00834415
 * Fecha: 26 de enero del 2025
 */

#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max();

/**
 * Funcion algoritmo de Dijkstra para encontrar las distancias más cortas desde un nodo inicial.
 * Complejidad: O((n + a) log n), donde n es el número de nodos y a es el número de aristas.
 */
vector<int> dijkstra(int start, const vector<vector<int>>& graph) {
    int nodeCount = graph.size();
    vector<int> distances(nodeCount, INF);
    distances[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> priorityQueue;
    priorityQueue.push({0, start});

    while (!priorityQueue.empty()) {
        auto [currentDistance, currentNode] = priorityQueue.top();
        priorityQueue.pop();

        // Ignorar nodos que ya tienen una distancia menor conocida
        if (currentDistance > distances[currentNode]) {
            continue;
        }

        for (int neighbor = 0; neighbor < nodeCount; ++neighbor) {
            if (graph[currentNode][neighbor] != -1) {
                int newDistance = distances[currentNode] + graph[currentNode][neighbor];
                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    priorityQueue.push({newDistance, neighbor});
                }
            }
        }
    }

    return distances;
}

/**
 * Funcion algoritmo de Floyd-Warshall para encontrar las distancias más cortas entre todos los pares de nodos.
 * Complejidad: O(n^3), donde n es el número de nodos.
 */
vector<vector<int>> floydWarshall(const vector<vector<int>>& graph) {
    int nodeCount = graph.size();
    vector<vector<int>> distances = graph;

    for (int intermediate = 0; intermediate < nodeCount; ++intermediate) {
        for (int source = 0; source < nodeCount; ++source) {
            for (int target = 0; target < nodeCount; ++target) {
                if (distances[source][intermediate] != -1 && distances[intermediate][target] != -1) {
                    int newDistance = distances[source][intermediate] + distances[intermediate][target];
                    if (distances[source][target] == -1 || newDistance < distances[source][target]) {
                        distances[source][target] = newDistance;
                    }
                }
            }
        }
    }

    return distances;
}

int main() {
    int nodeCount;
    cin >> nodeCount;

    vector<vector<int>> graph(nodeCount, vector<int>(nodeCount));
    for (int row = 0; row < nodeCount; ++row) {
        for (int col = 0; col < nodeCount; ++col) {
            cin >> graph[row][col];
        }
    }

    // Resultados del algoritmo de Dijkstra
    cout << "Dijkstra :\n";
    for (int startNode = 0; startNode < nodeCount; ++startNode) {
        vector<int> distances = dijkstra(startNode, graph);
        for (int endNode = 0; endNode < nodeCount; ++endNode) {
            if (startNode != endNode && distances[endNode] != INF) {
                cout << "node " << startNode + 1 << " to node " << endNode + 1 << " : " << distances[endNode] << "\n";
            }
        }
    }

    // Resultados del algoritmo de Floyd-Warshall
    cout << "\nFloyd :\n";
    vector<vector<int>> floydResults = floydWarshall(graph);
    for (int row = 0; row < nodeCount; ++row) {
        for (int col = 0; col < nodeCount; ++col) {
            if (floydResults[row][col] == -1) {
                cout << "INF ";
            } else {
                cout << floydResults[row][col] << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}
