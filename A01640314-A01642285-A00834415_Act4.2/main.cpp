/*
 * License: Educational use only.
 * File: main.cpp
 * Description: programa en C++ que implementa el algoritmo para determinar el polígono convexo más pequeño en un conjunto de puntos aplicando el algoritmo de Graham's Scan.. 
 * Authors:  Luis Angel Alba Alfaro - A01640314 Fernando García
 * Tejeda - A01642285 Bruno Márquez Puig     - A00834415 Created: February 2, 2025
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

bool compare(Point p1, Point p2) {
    return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

int crossProduct(Point p, Point q, Point r) {
    return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

vector<Point> grahamScan(vector<Point>& points) {
    if (points.size() < 3) return points;

    //Ordenar los puntos por coordenadas
    sort(points.begin(), points.end(), compare);

    vector<Point> hull;

    //Construir la mitad inferior del polígono
    for (Point p : points) {
        while (hull.size() >= 2 && crossProduct(hull[hull.size() - 2], hull[hull.size() - 1], p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    //Construir la mitad superior del polígono
    int lowerSize = hull.size();
    for (int i = points.size() - 1; i >= 0; i--) {
        Point p = points[i];
        while (hull.size() > lowerSize && crossProduct(hull[hull.size() - 2], hull[hull.size() - 1], p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    hull.pop_back(); // El último punto es igual al primero, por lo que lo eliminamos
    return hull;
}

int main() {
    int n;
    cin >> n;  // Número de puntos
    vector<Point> points;

    // ciclo for que lee los puntos
    for (int i = 0; i < n; i++) {
        Point p;
        cin >> p.x >> p.y;
        points.push_back(p);
    }

    vector<Point> convexHull = grahamScan(points);

    for (Point p : convexHull) {
        cout << p.x << " " << p.y << endl;
    }

    return 0;
}
