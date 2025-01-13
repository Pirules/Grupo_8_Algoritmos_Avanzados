// Programa que calcula el cambio óptimo de monedas utilizando un algoritmo avaro.
// Autores: Luis Angel Alba Alfaro - A01640314
//          Fernando García Tejeda - A01642285
//          Bruno Márquez Puig     - A00834415
// Fecha de creación/modificación: 12/01/2025
#include <iostream>
#include <vector>

using namespace std;

vector<int> metodoCambio(int cambio, const vector<int>& valormoneda) {
    // Inicializacion de la variable n para el tamano del vector valormoneda
    int n = valormoneda.size();
	//Vector con limite maximo de enteros
    vector<int> dp(cambio + 1, numeric_limits<int>::max()); 
    vector<int> ultimamoneda(cambio + 1, -1);
    dp[0] = 0;

    // Iteracion para calcular el cambio
    for (int i = 0; i < n; ++i) {
        for (int j = valormoneda[i]; j <= cambio; ++j) {
            if (dp[j - valormoneda[i]] != numeric_limits<int>::max() &&
                dp[j - valormoneda[i]] + 1 < dp[j]) {
                dp[j] = dp[j - valormoneda[i]] + 1;
                ultimamoneda[j] = i;
            }
        }
    }

    // Condicional para verificar si se puede dar el cambio
    if (dp[cambio] == numeric_limits<int>::max()) {
        return {};
    }

    // Vector que almacena el resultado
    vector<int> resultado(n, 0);
    int cambioactual = cambio;
    while (cambioactual > 0) {
        int ID = ultimamoneda[cambioactual];
        //Condicional para verificar si se queda fuera de rango
        if (ID == -1) {
            return {};
        }
        resultado[ID]++;
        cambioactual -= valormoneda[ID];
    }

    return resultado;
}

int main() {
    // Inicializacion de la variable N para el tamano del vector valormoneda
    int N;
    cout << "Ingrese el numero de denominaciones de monedas: ";
    cin >> N;

    // Vector que almacena las denominaciones de las monedas
    vector<int> valormoneda(N);
    cout << "Ingrese las denominaciones de las monedas, una por linea:" << endl;
    for (int i = 0; i < N; ++i) {
        cin >> valormoneda[i];
    }

    // Ordenar de mayor a menor
    for (int i = 0; i < N - 1; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (valormoneda[i] < valormoneda[j]) {
                swap(valormoneda[i], valormoneda[j]);
            }
        }
    }

    // Inicializacion de variables P y Q para el precio del producto y la cantidad pagada
    int P, Q;
    cout << "Ingrese el precio del producto: ";
    cin >> P;
    cout << "Ingrese la cantidad pagada: ";
    cin >> Q;

    int cambio = Q - P;

    // Condicionales para verificar si la cantidad pagada es suficiente o si no hay cambio
    if (cambio < 0) {
        cout << "Falta dinero para pagar ese producto" << endl;
        return 0;
    }
    else if (cambio == 0) {
        cout << "No hay cambio por dar." << endl;
        return 0;
    }

    // Vector que almacena el resultado del metodoCambio
    vector<int> resultado = metodoCambio(cambio, valormoneda);

    // Condicionales para imprimir el resultado
    if (resultado.empty()) {
        cout << "No es posible dar el cambio." << endl;
    }
    else {
        cout << "Cambio a dar:" << endl;
        for (int i = 0; i < N; ++i) {
            if (resultado[i] >= 0) {
                cout << resultado[i] << " moneda(s) de " << valormoneda[i] << endl;
            }
        }
    }

    return 0;
}
