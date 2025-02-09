/**
 * Descripción breve del programa:
 *  Este programa resuelve el problema del recorrido del caballo en un tablero de ajedrez de N x N
 *  utilizando un algoritmo de backtracking recursivo, y imprime el tablero con el número de movimiento en cada casilla.
 * 
 * Autores: Luis Angel Alba Alfaro - A01640314
 *          Fernando García Tejeda - A01642285
 *          Bruno Márquez Puig     - A00834415
 * Fecha: 9 de febrero del 2025
 */

#include <iostream>
#include <vector>
using namespace std;

// Arreglo que contiene los posibles movimientos en el eje X para un caballo en un tablero de ajedrez.
const int movimientosX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int movimientosY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

/**
 * Verifica si una posición es válida en el tablero.
 * 
 * Complejidad: O(1)
 * entradas:
 * 
 * x: Coordenada X.
 * y: Coordenada Y.
 * tablero: Matriz de seguimiento.
 * N Tamaño: del tablero.
 * regresa: Verdadero si la posición es válida, falso en caso contrario.
 */
bool esValido(int x, int y, vector<vector<int>>& tablero, int N) {
    return (x >= 0 && x < N && y >= 0 && y < N && tablero[x][y] == -1);
}

/**
 * Función recursiva para resolver el problema del recorrido del caballo.
 * 
 * Complejidad: O(8^(N^2)) en el peor caso.
 * entradas:
 * 
 * x: Coordenada X actual.
 * y: Coordenada Y actual.
 * movimiento: Número de movimiento actual.
 * tablero: Matriz de seguimiento.
 * N: Tamaño del tablero.
 * regresa: Verdadero si se encuentra una solución, falso en caso contrario.
 */
bool resolverRecorrido(int x, int y, int movimiento, vector<vector<int>>& tablero, int N) {
    if (movimiento == N * N) {
        return true;
    }
    
    for (int i = 0; i < 8; ++i) {
        int nuevoX = x + movimientosX[i];
        int nuevoY = y + movimientosY[i];
        
        if (esValido(nuevoX, nuevoY, tablero, N)) {
            tablero[nuevoX][nuevoY] = movimiento;
            if (resolverRecorrido(nuevoX, nuevoY, movimiento + 1, tablero, N)) {
                return true;
            }
            tablero[nuevoX][nuevoY] = -1; // Backtracking
        }
    }
    return false;
}

/**
 * Inicia y resuelve el problema del recorrido del caballo.
 * 
 * Complejidad: O(8^(N^2)) en el peor caso.
 * entradas:
 * 
 * N: Tamaño del tablero.
 */
void resolverProblemaCaballo(int N) {
    vector<vector<int>> tablero(N, vector<int>(N, -1));
    tablero[0][0] = 0;
    
    if (resolverRecorrido(0, 0, 1, tablero, N)) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << tablero[i][j] << "\t";
            }
            cout << endl;
        }
    } else {
        cout << "No se encontró una solución." << endl;
    }
}

int main() {
    int N;
    cin >> N;
    resolverProblemaCaballo(N);
    return 0;
}
