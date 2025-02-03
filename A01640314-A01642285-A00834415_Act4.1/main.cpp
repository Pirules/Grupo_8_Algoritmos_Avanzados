/*
 * License: Educational use only.
 * File: main.cpp
 * Description: Programa en C++ que implementa el algoritmo para determinar si dos segmentos de rectas intersectan. 
 * Authors:  Luis Angel Alba Alfaro - A01640314 Fernando García
 * Tejeda - A01642285 Bruno Márquez Puig     - A00834415 Created: February 2,
 * 2025
 */

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Point {
    int x, y;
};

// Calcula la orientación de tres puntos (p, q, r)
// Complejidad: O(1) ya que solo realiza operaciones aritméticas simples
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

// Verifica si el punto q está sobre el segmento pr
// Complejidad: O(1) porque solo compara las coordenadas de los puntos
bool onSegment(Point p, Point q, Point r) {
    return (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y));
}

// Determina si dos segmentos de recta (p1q1 y p2q2) se intersecan
// Complejidad: O(1) ya que solo realiza cuatro cálculos de orientación y comprobaciones de segmentos
bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

int main() {
    int n;
    cin >> n; 
    cin.ignore();

    vector<bool> results; 

    // Itera a través de los casos de prueba
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line); 

        stringstream ss(line);
        vector<int> coords;
        string value;

        // Separa las coordenadas por coma y las almacena en un vector
        while (getline(ss, value, ',')) {
            coords.push_back(stoi(value));  
        }

        Point p1 = {coords[0], coords[1]};
        Point q1 = {coords[2], coords[3]};
        Point p2 = {coords[4], coords[5]};
        Point q2 = {coords[6], coords[7]};

        results.push_back(doIntersect(p1, q1, p2, q2));
    }

    for (bool res : results) {
        cout << (res ? "True" : "False") << endl;
    }

    return 0;
}
