/*
 * License: Educational use only.
 * File: main.cpp
 * Description: programa en C++ que que implemente el algoritmo de backtracking con bitmasking para determinar el número de combinaciones que se puede lograr en el problema: Tipos de gorras en un conjunto de personas.
 * Authors:  Luis Angel Alba Alfaro - A01640314 Fernando García
 * Tejeda - A01642285 Bruno Márquez Puig     - A00834415 Created: February 2, 2025
 */

#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int MAX_GORRAS = 100;
vector<int> gorras[10]; // Máximo 10 personas
int n;

// Backtracking con Bitmasking
// Complejidad: O(2^n * m) donde n es el número de personas (máximo 10) y m el número de gorras únicas.
void backtrack(int person, bitset<MAX_GORRAS> used, vector<int>& selected, int& count, vector<vector<int>>& results) {
    if (person == n) { // Si todas las personas han seleccionado una gorra
        count++;
        results.push_back(selected);
        return;
    }

    for (int gorra : gorras[person]) {
        if (!used[gorra]) { // Si la gorra no ha sido usada
            used[gorra] = 1;
            selected.push_back(gorra);
            backtrack(person + 1, used, selected, count, results);
            selected.pop_back(); // Retrocedemos en el estado
            used[gorra] = 0;
        }
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        int gorra;
        while (cin >> gorra) {
            gorras[i].push_back(gorra);
            if (cin.peek() == '\n') break; // Permite entrada línea por línea
        }
    }

    int count = 0;
    bitset<MAX_GORRAS> used;
    vector<int> selected;
    vector<vector<int>> results;
    backtrack(0, used, selected, count, results);

    cout << count << endl; // Imprime el número total de combinaciones primero
    for (const auto& combination : results) {
        cout << "(";
        for (size_t i = 0; i < combination.size(); i++) {
            cout << combination[i] << (i == combination.size() - 1 ? ")\n" : ", ");
        }
    }

    return 0;
}
