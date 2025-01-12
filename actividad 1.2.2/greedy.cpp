#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Leer el número de denominaciones
    int N;
    cout << "Ingrese el número de denominaciones de monedas: ";
    cin >> N;

    vector<int> denominaciones(N);

    // Leer las denominaciones
    cout << "Ingrese las denominaciones de las monedas, una por línea:\n";
    for (int i = 0; i < N; ++i) {
        cin >> denominaciones[i];
    }

    // Ordenar las denominaciones en orden descendente
    // El método rbegin() retorna un iterador al último elemento del vector (comenzando desde el final),
    // y rend() retorna un iterador al elemento antes del primero (conceptualmente, al 'nulo'). Estos se
    // utilizan para ordenar las denominaciones en orden descendente.
    sort(denominaciones.rbegin(), denominaciones.rend());

    // Leer el precio del producto y la cantidad pagada
    // Podrian ser mas descriptivos los nombres de las variables
    int P, Q;
    cout << "Ingrese el precio del producto: ";
    cin >> P;
    cout << "Ingrese la cantidad pagada: ";
    cin >> Q;

    // Calcular el cambio
    int cambio = Q - P;

    if (cambio < 0) {
        cout << "Falta dinero para pagar ese producto\n";
        return 0;
    } else if (cambio == 0) {
        cout << "No hay cambio por dar\n";
        return 0;
    }

    // Vector para almacenar la cantidad de monedas de cada denominación
    vector<int> monedas(N, 0);

    // Algoritmo avaro para calcular el cambio 
    for (int i = 0; i < N; ++i) {
        if (denominaciones[i] <= cambio) {
            monedas[i] = cambio / denominaciones[i];
            cambio %= denominaciones[i];
        }
    }

    // Mostrar el resultado
    for (int i = 0; i < N; ++i) {
        cout << monedas[i] << " moneda(s) de " << denominaciones[i] << "\n";
    }

    return 0;
}
