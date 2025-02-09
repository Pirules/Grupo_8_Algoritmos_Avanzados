/*
 * License: Educational use only.
 * File: main.cpp
 * Description: programa en C++ que que implemente el algoritmo de backtracking con poda pesada .
 * Authors:  Luis Angel Alba Alfaro - A01640314 Fernando García
 * Tejeda - A01642285 Bruno Márquez Puig     - A00834415 Created: February 2, 2025
 */

#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<int>> board;
vector<bool> col, diag1, diag2; 

// Complejidad: O(N!) en el peor caso, pero con poda pesada mejora significativamente.
bool solve(int row) {
    if (row == N) return true; 

    for (int c = 0; c < N; c++) {
        if (!col[c] && !diag1[row - c + N - 1] && !diag2[row + c]) {
            board[row][c] = 1;
            col[c] = diag1[row - c + N - 1] = diag2[row + c] = true;

            if (solve(row + 1)) return true;

            // Backtrack
            board[row][c] = 0;
            col[c] = diag1[row - c + N - 1] = diag2[row + c] = false;
        }
    }
    return false;
}

int main() {
    cin >> N;
    if (N != 4 && N != 8) {
        cout << "N debe ser 4 u 8" << endl;
        return 0;
    }

    board.assign(N, vector<int>(N, 0));
    col.assign(N, false);
    diag1.assign(2 * N - 1, false);
    diag2.assign(2 * N - 1, false);

    if (solve(0)) {
        for (const auto& row : board) {
            cout << "{ ";
            for (size_t i = 0; i < row.size(); i++) {
                cout << row[i] << (i == row.size() - 1 ? " }" : ", ");
            }
            cout << endl;
        }
    } else {
        cout << "No hay solución" << endl;
    }

    return 0;
}