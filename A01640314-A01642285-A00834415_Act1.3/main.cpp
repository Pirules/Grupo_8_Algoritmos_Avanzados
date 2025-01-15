/*
 * Descripción breve del programa:
 * Este programa resuelve un laberinto utilizando dos técnicas: backtracking y ramificación y poda.
 * Se reciben las dimensiones del laberinto y el laberinto en sí desde la entrada estándar.
 * Luego, se imprimen dos soluciones, una para cada técnica.
 * 
 *    Autores: Luis Angel Alba Alfaro - A01640314
 *             Fernando García Tejeda - A01642285
 *             Bruno Márquez Puig     - A00834415
 * Fecha: 15 de enero del 2025
 */

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int> > Maze;
typedef vector<vector<bool> > Path;



// Función para imprimir una matriz de valores booleanos
void printMatrix(const Path& matrix) {
    for (const auto& row : matrix) {
        for (bool cell : row) {
            cout << (cell ? 1 : 0) << ' ';
        }
        cout << endl;
    }
}

// Resuelve el laberinto utilizando la técnica de backtracking
bool solveMazeBacktracking(const Maze& maze, Path& solution, int x, int y) {
    int M = maze.size();
    int N = maze[0].size();

    // Caso base: Si (x, y) es el destino, se ha encontrado el camino
    if (x == M - 1 && y == N - 1) {
        solution[x][y] = true;
        return true;
    }

    // Verificar si la posición actual es válida
    if (x >= 0 && x < M && y >= 0 && y < N && maze[x][y] == 1 && !solution[x][y]) {
        // Marca la casilla como parte de la solución
        solution[x][y] = true;

        // Mover hacia abajo
        if (solveMazeBacktracking(maze, solution, x + 1, y)) {
            return true;
        }

        // Mover hacia la derecha
        if (solveMazeBacktracking(maze, solution, x, y + 1)) {
            return true;
        }

        // Mover hacia arriba
        if (solveMazeBacktracking(maze, solution, x - 1, y)) {
            return true;
        }

        // Mover hacia la izquierda
        if (solveMazeBacktracking(maze, solution, x, y - 1)) {
            return true;
        }

        // Si ninguno de los movimientos funciona, desmarca la casilla y retrocede
        solution[x][y] = false;
        return false;
    }

    return false;
}

// Resuelve el laberinto utilizando la técnica de ramificación y poda
bool solveMazeBranchAndBound(const Maze& maze, Path& solution, int x, int y, vector<vector<bool> >& visited) {
    int M = maze.size();
    int N = maze[0].size();

    // Caso base: Si (x, y) es el destino, se ha encontrado el camino
    if (x == M - 1 && y == N - 1) {
        solution[x][y] = true;
        return true;
    }

    // Verificar si la posición actual es válida
    if (x >= 0 && x < M && y >= 0 && y < N && maze[x][y] == 1 && !visited[x][y]) {
        // Marca la casilla como parte de la solución y como visitada
        visited[x][y] = true;
        solution[x][y] = true;

        // Mover hacia abajo
        if (solveMazeBranchAndBound(maze, solution, x + 1, y, visited)) {
            return true;
        }

        // Mover hacia la derecha
        if (solveMazeBranchAndBound(maze, solution, x, y + 1, visited)) {
            return true;
        }

        // Mover hacia arriba
        if (solveMazeBranchAndBound(maze, solution, x - 1, y, visited)) {
            return true;
        }

        // Mover hacia la izquierda
        if (solveMazeBranchAndBound(maze, solution, x, y - 1, visited)) {
            return true;
        }

        // Si ninguno de los movimientos funciona, desmarca la casilla y retrocede
        solution[x][y] = false;
        visited[x][y] = false;
        return false;
    }

    return false;
}

int main() {
    int M, N;
    cin >> M >> N;

    Maze maze(M, vector<int>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> maze[i][j];
        }
    }

    // Resolver el laberinto usando backtracking
    Path solutionBacktracking(M, vector<bool>(N, false));
    if (solveMazeBacktracking(maze, solutionBacktracking, 0, 0)) {
        cout << "Camino encontrado usando backtracking" << endl;
        printMatrix(solutionBacktracking);
    } else {
        cout << "No se encontró camino usando backtracking" << endl;
    }

    cout << endl; // Separador entre soluciones

    // Resolver el laberinto usando ramificación y poda
    Path solutionBranchAndBound(M, vector<bool>(N, false));
    vector<vector<bool> > visited(M, vector<bool>(N, false));
    if (solveMazeBranchAndBound(maze, solutionBranchAndBound, 0, 0, visited)) {
        cout << "Camino encontrado usando ramificación y poda" << endl;
        printMatrix(solutionBranchAndBound);
    } else {
        cout << "No se encontró camino usando ramificación y poda" << endl;
    }

    return 0;
}
