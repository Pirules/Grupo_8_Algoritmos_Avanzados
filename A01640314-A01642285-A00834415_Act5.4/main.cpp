/*
 * License: Educational use only.
 * File: main.cpp
 * Description: programa en C++ que que implemente el algoritmo encontrarse en el medio (meet in the middle).
 * Authors:  Luis Angel Alba Alfaro - A01640314 Fernando García
 * Tejeda - A01642285 Bruno Márquez Puig     - A00834415 Created: February 2, 2025
 */

 #include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Genera todos los subconjuntos posibles de un conjunto dado y devuelve sus sumas
// Complejidad: O(2^(n/2)) donde n es el tamaño del conjunto.
void generateSubsets(const vector<long long>& arr, vector<long long>& subsets) {
    int size = arr.size();
    int total = 1 << size; // 2^size
    for (int mask = 0; mask < total; mask++) {
        long long sum = 0;
        for (int i = 0; i < size; i++) {
            if (mask & (1 << i)) sum += arr[i];
        }
        subsets.push_back(sum);
    }
}

// Algoritmo Meet in the Middle para encontrar la suma máxima menor o igual a S
// Complejidad: O(2^(n/2) log(2^(n/2))) debido a la generación de subconjuntos y la búsqueda binaria.
long long meetInTheMiddle(const vector<long long>& arr, long long S) {
    int n = arr.size();
    vector<long long> leftSubsets, rightSubsets;
    generateSubsets(vector<long long>(arr.begin(), arr.begin() + n / 2), leftSubsets);
    generateSubsets(vector<long long>(arr.begin() + n / 2, arr.end()), rightSubsets);

    sort(rightSubsets.begin(), rightSubsets.end()); // Ordenamos para búsqueda binaria

    long long maxSum = 0;
    vector<long long> bestSubset;
    for (long long sumLeft : leftSubsets) {
        if (sumLeft > S) continue;
        auto it = upper_bound(rightSubsets.begin(), rightSubsets.end(), S - sumLeft);
        if (it != rightSubsets.begin()) {
            long long sumRight = *(--it);
            if (sumLeft + sumRight > maxSum) {
                maxSum = sumLeft + sumRight;
            }
        }
    }

    cout << "La suma máxima del subconjunto es: " << maxSum;
    cout << ", el cual se obtiene de la suma de ";

    long long remaining = maxSum;
    bool first = true;
    for (long long num : arr) {
        if (remaining >= num && find(rightSubsets.begin(), rightSubsets.end(), remaining - num) != rightSubsets.end()) {
            if (!first) cout << ", ";
            cout << num;
            remaining -= num;
            first = false;
        }
    }
    cout << "." << endl;

    return maxSum;
}

int main() {
    string inputLine;
    cout << "Ingrese los elementos del conjunto:\n";
    getline(cin, inputLine);

    vector<long long> arr;
    stringstream ss(inputLine);
    long long num;
    while (ss >> num) {
        arr.push_back(num);
    }

    long long S;
    cout << "Ingrese el valor de S:\n";
    cin >> S;

    meetInTheMiddle(arr, S);

    return 0;
}
