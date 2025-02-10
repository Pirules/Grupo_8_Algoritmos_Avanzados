/*
 * License: Educational use only.
 * File: main.cpp
 * Description: programa en C++ que que implemente el algoritmo de A*.
 * Authors:  Luis Angel Alba Alfaro - A01640314 Fernando García
 * Tejeda - A01642285 Bruno Márquez Puig     - A00834415 Created: February 2, 2025
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
using namespace std;

struct Node {
    int x, y, cost, heuristic;
    string path;
    Node(int _x, int _y, int _cost, int _heuristic, string _path)
        : x(_x), y(_y), cost(_cost), heuristic(_heuristic), path(_path) {}
};

struct Compare {
    bool operator()(const Node &a, const Node &b) {
        return (a.cost + a.heuristic) > (b.cost + b.heuristic);
    }
};

int heuristic(int x, int y, int destX, int destY) {
    return abs(destX - x) + abs(destY - y);
}

vector<string> aStar(vector<vector<int>> &maze, int N) {
    if (maze[0][0] == 0 || maze[N - 1][N - 1] == 0)
        return {"No path"};

    priority_queue<Node, vector<Node>, Compare> pq;
    pq.push(Node(0, 0, 0, heuristic(0, 0, N - 1, N - 1), ""));
    vector<vector<int>> visited(N, vector<int>(N, 0));
    vector<string> solutions;
    int min_cost = numeric_limits<int>::max();

    int dx[] = {1, 0, 0, -1};
    int dy[] = {0, -1, 1, 0};
    char dir[] = {'D', 'L', 'R', 'U'};

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.x == N - 1 && current.y == N - 1) {
            if (current.cost < min_cost) {
                min_cost = current.cost;
                solutions.clear();
                solutions.push_back(current.path);
            } else if (current.cost == min_cost) {
                solutions.push_back(current.path);
            }
            continue;
        }

        if (visited[current.x][current.y] && current.cost > min_cost)
            continue;

        visited[current.x][current.y] = 1;

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[i], ny = current.y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < N && ny < N && maze[nx][ny] == 1) {
                pq.push(Node(nx, ny, current.cost + 1, heuristic(nx, ny, N - 1, N - 1), current.path + dir[i]));
            }
        }
    }
    return solutions;
}

int main() {
    int N;
    cout << "N: ";
    cin >> N;
    vector<vector<int>> maze(N, vector<int>(N));

    cout << "Ingrese la matriz del laberinto línea por línea:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> maze[i][j];
        }
    }

    vector<string> results = aStar(maze, N);
    for (const string &path : results) {
        cout << "Camino encontrado: " << path << endl;
    }
    return 0;
}
