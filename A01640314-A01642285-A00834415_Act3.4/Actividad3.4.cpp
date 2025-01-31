// Programa que ordena N valores de mayor a menor usando Merge Sort.
// Autores: Luis Angel Alba Alfaro - A01640314
//          Fernando García Tejeda - A01642285
//          Bruno Márquez Puig     - A00834415
// Fecha de creación/modificación: 30/01/2025

#include <iostream>
#include <vector>

using namespace std;
//Creamos funcion para verificar que se puede asignar un color a un nodo
bool esSeguro(int nodo, vector<vector<int>>& grafo, vector<int>& colores, int color) {
    for (int i = 0; i < grafo.size(); i++) {
        if (grafo[nodo][i] && colores[i] == color) {
            return false;
        }
    }
    return true;
}

//Creamos funcion para colorear el grafo
bool colorearGrafo(vector<vector<int>>& grafo, vector<int>& colores, int nodo, int numColores) {
    if (nodo == grafo.size()) {
        return true;
    }
    for (int color = 0; color < numColores; color++) {
        if (esSeguro(nodo, grafo, colores, color)) {
            colores[nodo] = color;
            if (colorearGrafo(grafo, colores, nodo + 1, numColores)) {
                return true;
            }
            colores[nodo] = -1;
        }
    }
    return false;
}

int main() {
    cout << "Ejemplo de Entrada" << endl;
    //Inicializamos variable n
    int n;
    cin >> n;
    vector<vector<int>> grafo(n, vector<int>(n));
	//Creamos matriz para almacenar los nodos
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grafo[i][j];
        }
    }

    vector<int> colores(n, -1);
    int numColores = n;
	//Imprimimos resultado
    cout << "Ejemplo de Salida"<<endl;
    if (colorearGrafo(grafo, colores, 0, numColores)) {
        for (int i = 0; i < n; i++) {
            cout << "Node: " << i << ", Assigned Color: " << colores[i] << endl;
        }
    }
    return 0;
}
