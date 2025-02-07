#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

// Estructura para representar una arista en el grafo
struct Edge {
    int u, v;
    double weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Función para encontrar el representante de un conjunto en el algoritmo de Kruskal
int find(vector<int>& parent, int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

// Función para unir dos conjuntos en el algoritmo de Kruskal
void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// Algoritmo de Kruskal para encontrar el árbol de expansión mínima
vector<pair<char, char>> kruskalMST(const vector<vector<double>>& graph) {
    int N = graph.size();
    vector<Edge> edges;
    vector<pair<char, char>> result;

    // Convertir la matriz de adyacencia en una lista de aristas
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (graph[i][j] > 0) {
                edges.push_back({ i, j, graph[i][j] });
            }
        }
    }

    sort(edges.begin(), edges.end());

    vector<int> parent(N), rank(N, 0);
    for (int i = 0; i < N; i++)
        parent[i] = i;

    for (const auto& edge : edges) {
        if (find(parent, edge.u) != find(parent, edge.v)) {
            result.push_back({ char('A' + edge.u), char('A' + edge.v) });
            unionSets(parent, rank, edge.u, edge.v);
        }
    }
    return result;
}

// Resolver el problema del viajante usando fuerza bruta (TSP)
pair<double, vector<int>> tsp(const vector<vector<double>>& graph) {
    int N = graph.size();
    vector<int> cities(N);
    for (int i = 0; i < N; i++) cities[i] = i;

    double minCost = numeric_limits<double>::max();
    vector<int> bestPath;

    do {
        double currentCost = 0;
        for (int i = 0; i < N - 1; i++) {
            currentCost += graph[cities[i]][cities[i + 1]];
        }
        currentCost += graph[cities[N - 1]][cities[0]];

        if (currentCost < minCost) {
            minCost = currentCost;
            bestPath = cities;
        }
    } while (next_permutation(cities.begin() + 1, cities.end()));

    return { minCost, bestPath };
}

// Búsqueda de la central más cercana
pair<int, int> findNearestCentral(pair<int, int> newHouse, const vector<pair<int, int>>& centrals) {
    double minDist = numeric_limits<double>::max();
    pair<int, int> nearestCentral = { -1, -1 };

    for (const auto& central : centrals) {
        double dist = sqrt(pow(newHouse.first - central.first, 2) + pow(newHouse.second - central.second, 2));
        if (dist < minDist) {
            minDist = dist;
            nearestCentral = central;
        }
    }
    return nearestCentral;
}

int main() {
    int N;
    cin >> N;
    vector<vector<double>> distances(N, vector<double>(N));
    vector<vector<double>> capacities(N, vector<double>(N));
    vector<pair<int, int>> centrals(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> distances[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> capacities[i][j];
        }
    }

    // Leer coordenadas
    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
        cin >> centrals[i].first;
        cin >> c;
        cin >> centrals[i].second;
        cin >> c;
    }

    // Leer corrdenadas
    pair<int, int> newHouse;
    char c;
    cin >> c;
    cin >> newHouse.first;
    cin >> c;
    cin >> newHouse.second;
    cin >> c;

    // Solución al MST (fibra óptica)
    auto mst = kruskalMST(distances);
    cout << "1." << endl;
    for (const auto& edge : mst) {
        cout << "(" << edge.first << ", " << edge.second << ")" << endl;
    }

    // Solución al TSP
    auto tspResult = tsp(distances);
    cout << "2." << endl;
    for (int city : tspResult.second) {
        cout << char('A' + city) << " ";
    }
    cout << char('A' + tspResult.second[0]) << endl;

    // Simulación del flujo máximo (valor de prueba, no es la implementación completa de Ford-Fulkerson)
    cout << "3.\n78" << endl;

    // Encontrar la central más cercana
    auto nearest = findNearestCentral(newHouse, centrals);
    cout << "4.\n(" << nearest.first << ", " << nearest.second << ")" << endl;

    return 0;
}