/*
 * Descripción breve del programa:
 * implementacion de algoritmos de geometria computacional para encontrar la distancia mas corta entre dos puntos en un conjunto de puntos 
 * de plano cartesiano.
 * 
 *    Autores: Luis Angel Alba Alfaro - A01640314
 *             Fernando García Tejeda - A01642285
 *             Bruno Márquez Puig     - A00834415
 * Fecha: 2 de febrero del 2025
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

/**
 * Estructura para representar un punto en un plano cartesiano.
 */
struct Punto {
    double x, y;
};

/**
 * Calcula la distancia euclidiana entre dos puntos.
 * 
 * Complejidad: O(1)
 * 
 * p1 Primer punto.
 * p2 Segundo punto.
 * Distancia entre los dos puntos.
 */
double calcularDistancia(const Punto& p1, const Punto& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

/**
 * Ordena los puntos por coordenada X.
 */
bool compararX(const Punto& p1, const Punto& p2) {
    return p1.x < p2.x;
}

/**
 * Ordena los puntos por coordenada Y.
 */
bool compararY(const Punto& p1, const Punto& p2) {
    return p1.y < p2.y;
}

/**
 * Calcula la distancia mínima entre un grupo pequeño de puntos mediante fuerza bruta.
 * 
 * Complejidad: O(n^2)
 * 
 * puntos Vector de puntos.
 * izquierda Índice izquierdo del rango.
 * derecha Índice derecho del rango.
 * Distancia mínima encontrada.
 */
double fuerzaBruta(vector<Punto>& puntos, int izquierda, int derecha) {
    double minDistancia = numeric_limits<double>::max();
    for (int i = izquierda; i < derecha; ++i) {
        for (int j = i + 1; j <= derecha; ++j) {
            double d = calcularDistancia(puntos[i], puntos[j]);
            minDistancia = min(minDistancia, d);
        }
    }
    return minDistancia;
}

/**
 * Encuentra la menor distancia en una franja central.
 * 
 * Complejidad: O(n log n) debido al ordenamiento por Y.
 * 
 * franja Vector de puntos dentro de la franja.
 * distanciaMin Distancia mínima actual.
 * @Distancia mínima en la franja.
 */
double encontrarEnFranja(vector<Punto>& franja, double distanciaMin) {
    sort(franja.begin(), franja.end(), compararY);
    int tamano = franja.size();
    for (int i = 0; i < tamano; ++i) {
        for (int j = i + 1; j < tamano && (franja[j].y - franja[i].y) < distanciaMin; ++j) {
            distanciaMin = min(distanciaMin, calcularDistancia(franja[i], franja[j]));
        }
    }
    return distanciaMin;
}

/**
 * Implementa el algoritmo de "Divide y Vencerás" para encontrar la distancia más corta.
 * 
 * Complejidad: O(n log n)
 * 
 *  puntos Vector de puntos ordenados por X.
 *  izquierda Índice izquierdo del rango.
 *  derecha Índice derecho del rango.
 *  Distancia mínima encontrada.
 */
double encontrarParMasCercanoRecursivo(vector<Punto>& puntos, int izquierda, int derecha) {
    if (derecha - izquierda <= 3) {
        return fuerzaBruta(puntos, izquierda, derecha);
    }

    int medio = izquierda + (derecha - izquierda) / 2;
    double distanciaIzq = encontrarParMasCercanoRecursivo(puntos, izquierda, medio);
    double distanciaDer = encontrarParMasCercanoRecursivo(puntos, medio + 1, derecha);
    double distanciaMin = min(distanciaIzq, distanciaDer);

    vector<Punto> franja;
    for (int i = izquierda; i <= derecha; i++) {
        if (abs(puntos[i].x - puntos[medio].x) < distanciaMin) {
            franja.push_back(puntos[i]);
        }
    }

    return min(distanciaMin, encontrarEnFranja(franja, distanciaMin));
}

/**
 * @brief Encuentra la distancia más corta entre dos puntos en un conjunto de puntos.
 * 
 * Complejidad: O(n log n)
 * 
 * @param puntos Vector de puntos.
 * @return Distancia mínima encontrada.
 */
double encontrarParMasCercano(vector<Punto>& puntos) {
    sort(puntos.begin(), puntos.end(), compararX);
    return encontrarParMasCercanoRecursivo(puntos, 0, puntos.size() - 1);
}

int main() {
    int n;
    cin >> n;
    vector<Punto> puntos(n);
    for (int i = 0; i < n; ++i) {
        char coma;
        cin >> puntos[i].x >> coma >> puntos[i].y;
    }

    double distanciaMinima = encontrarParMasCercano(puntos);
    cout << "La distancia mas corta es: " << fixed << distanciaMinima << endl;
    return 0;
}
