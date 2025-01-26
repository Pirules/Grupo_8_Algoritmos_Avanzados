// Programa que resuelve el problema de la mochila usando backtracking
// Autores: Luis Angel Alba Alfaro - A01640314
//          Fernando García Tejeda - A01642285
//          Bruno Márquez Puig     - A00834415
// Fecha de creación/modificación: 27/01/2025

#include <iostream>
#include <vector>

using namespace std;

int maxGanancia = 0; // Variable global para almacenar la ganancia

void mochila(vector<int> &val, vector<int> &wt, int W, int i, int ganancia) {
	// Condicion if para parar el backtracking si se llega al final del vector o si la capacidad restante es 0
    if (i == val.size() || W == 0) {
        maxGanancia = max(maxGanancia, ganancia);
        return;
    }

    if (wt[i] <= W) {
        mochila(val, wt, W - wt[i], i + 1, ganancia + val[i]);
    }

    mochila(val, wt, W, i + 1, ganancia);
}

int main() {
	//Inicializamos las variables N y W
    int N, W;
    cout << "Numero de elementos posibles disponibles: ";
    cin >> N;
	//Creamos vectores para almacenar los valores y pesos de los elementos
    vector<int> val(N), wt(N);

	//Ciclo for para agregar los valores de los elementos
    for (int i = 0; i < N; ++i) {
		cout << "valor del elemento " << i + 1 << ":" << endl;
        cin >> val[i];
    }

	//Ciclo for para agregar los pesos de los elementos
    for (int i = 0; i < N; ++i) {
		cout << "peso del elemento " << i + 1 << ":" << endl;
        cin >> wt[i];
    }
    cout << "Capacidad maxima de la mochila: ";
    cin >> W;

	//LLamamos a la función mochila
    mochila(val, wt, W, 0, 0);

    //Imprimimos resultado
    cout << "Ganancia: ";
    cout << maxGanancia << endl;

    return 0;
}