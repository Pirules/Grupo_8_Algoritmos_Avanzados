// Programa que ordena N valores de mayor a menor usando Merge Sort.
// Autores: Luis Angel Alba Alfaro - A01640314
//          Fernando García Tejeda - A01642285
//          Bruno Márquez Puig     - A00834415
// Fecha de creación/modificación: 12/01/2025

#include <iostream>
#include <vector>
using namespace std;

// Función para fusionar dos subarreglos en orden descendente
void merge(vector<double>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear subarreglos temporales
    vector<double> leftArr(n1);
    vector<double> rightArr(n2);

    // Copiar los datos a los subarreglos
    for (int i = 0; i < n1; ++i)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        rightArr[j] = arr[mid + 1 + j];

    // Combinar los subarreglos en orden descendente
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] >= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    // Copiar los elementos restantes de leftArr, si es que existen
    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    // Copiar los elementos restantes de rightArr, si es que existen
    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}

// Función recursiva de MergeSort con complejidad O(n log n)
void mergeSort(vector<double>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordenar la primera y segunda mitad
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Fusionar las mitades ordenadas
        merge(arr, left, mid, right);
    }
}

int main() {
    int N;
    cout << "Ingrese el número de valores a ordenar: ";
    cin >> N;

    vector<double> valores(N);
    cout << "\nIngrese " << N << " valores (reales o enteros), uno por línea:" << endl;
    for (int i = 0; i < N; ++i) {
        cin >> valores[i];
    }

    mergeSort(valores, 0, N - 1);

    cout << "\nResultado:" << endl;
    cout << "Valores ordenados de mayor a menor: " << endl;
    for (double valor : valores) {
        cout << valor << " ";
    }
    cout << endl;

    return 0;
}
