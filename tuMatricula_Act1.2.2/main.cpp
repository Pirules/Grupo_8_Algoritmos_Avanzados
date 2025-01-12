// Programa que calcula el cambio óptimo de monedas utilizando un algoritmo avaro.
// Autores: Luis Angel Alba Alfaro - A01640314
//          Fernando García Tejeda - A01642285
//          Bruno Márquez Puig     - A00834415
// Fecha de creación/modificación: 12/01/2025

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Leer el número de denominaciones
    int numDenominaciones;
    cout << "Ingrese el número de denominaciones de monedas: ";
    cin >> numDenominaciones;

    vector<int> denominaciones(numDenominaciones);

    // Leer las denominaciones
    cout << "Ingrese las denominaciones de las monedas, una por línea:\n";
    for (int i = 0; i < numDenominaciones; ++i) {
        cin >> denominaciones[i];
    }

    // Ordenar las denominaciones en orden descendente
    // Complejidad: O(N log N), donde N es el número de denominaciones.
    sort(denominaciones.rbegin(), denominaciones.rend());

    // Leer el precio del producto y la cantidad pagada
    int precioProducto, cantidadPagada;
    cout << "Ingrese el precio del producto: ";
    cin >> precioProducto;
    cout << "Ingrese la cantidad pagada: ";
    cin >> cantidadPagada;

    // Calcular el cambio
    int cambio = cantidadPagada - precioProducto;

    if (cambio < 0) {
        cout << "Falta dinero para pagar ese producto\n";
        return 0;
    } else if (cambio == 0) {
        cout << "No hay cambio por dar\n";
        return 0;
    }

    // Vector para almacenar la cantidad de monedas de cada denominación
    vector<int> monedasPorDenominacion(numDenominaciones, 0);

    // Algoritmo avaro para calcular el cambio
    // Complejidad: O(N), donde N es el número de denominaciones.
    for (int i = 0; i < numDenominaciones; ++i) {
        if (denominaciones[i] <= cambio) {
            monedasPorDenominacion[i] = cambio / denominaciones[i];
            cambio %= denominaciones[i];
        }
    }

    // Mostrar el resultado
    for (int i = 0; i < numDenominaciones; ++i) {
        cout << monedasPorDenominacion[i] << " moneda(s) de " << denominaciones[i] << "\n";
    }

    return 0;
}