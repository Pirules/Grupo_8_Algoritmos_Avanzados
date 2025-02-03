
/*
 * Descripción breve del programa:
 * implementacion de algrotimo de busqueda binaria aleatorizada para encontrar un elemento en un arreglo de enteros.
 * 
 *    Autores: Luis Angel Alba Alfaro - A01640314
 *             Fernando García Tejeda - A01642285
 *             Bruno Márquez Puig     - A00834415
 * Fecha: 2 de febrero del 2025
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

/**
 * Implementa el algoritmo de búsqueda binaria aleatorizada.
 * 
 * Complejidad: O(log n) en promedio.
 * 
 * arreglo Vector de números enteros ordenados.
 * izquierda Índice izquierdo del rango de búsqueda.
 * derecha Índice derecho del rango de búsqueda.
 * objetivo Número a buscar.
 * Índice del elemento si se encuentra, -1 en caso contrario.
 */
int busquedaBinariaAleatoria(vector<int>& arreglo, int izquierda, int derecha, int objetivo) {
    while (izquierda <= derecha) {
        int indiceAleatorio = izquierda + rand() % (derecha - izquierda + 1);
        
        if (arreglo[indiceAleatorio] == objetivo) {
            return indiceAleatorio;
        }
        else if (arreglo[indiceAleatorio] > objetivo) {
            derecha = indiceAleatorio - 1;
        }
        else {
            izquierda = indiceAleatorio + 1;
        }
    }
    return -1;
}

int main() {
    srand(time(0)); // Inicializa la semilla para la aleatorización
    
    int objetivo;
    cin >> objetivo;
    
    string linea;
    cin.ignore();
    getline(cin, linea);
    
    vector<int> arreglo;
    stringstream flujo(linea);
    int numero;
    char coma;
    
    while (flujo >> numero) {
        arreglo.push_back(numero);
        flujo >> coma;
    }
    
    int indice = busquedaBinariaAleatoria(arreglo, 0, arreglo.size() - 1, objetivo);
    
    if (indice != -1) {
        cout << "El elemento esta presente en el indice: " << indice << endl;
    } else {
        cout << "El elemento no esta presente en el arreglo" << endl;
    }
    
    return 0;
}
