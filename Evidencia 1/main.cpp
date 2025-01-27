/*
 * License: Educational use only.
 * File: main.cpp
 * Description: E1. Actividad Integradora 1
 * Authors:  
 Luis Angel Alba Alfaro - A01640314 
 Fernando García Tejeda - A01642285 
 Bruno Márquez Puig - A00834415 
 *Created: January 19, 2025
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>

using namespace std;

// Función para leer el contenido de un archivo
string readFile(const string& fileName) {
    ifstream file(fileName);
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

// Función para encontrar si una secuencia está contenida en otra
pair<bool, size_t> contains(const string& text, const string& pattern) {
    size_t pos = text.find(pattern);
    return { pos != string::npos, pos != string::npos ? pos + 1 : 0 };
}

// Función para encontrar el palíndromo más largo en un texto
pair<size_t, string> findLongestPalindrome(const string& s) {
	//Verificamos si el string esta vacio
    if (s.empty()) return { 0, "" };

    int n = s.size();
    int maxLen = 1;
    int start = 0;

    // Palíndromos de longitud 2
    for (int i = 0; i < n; i++) {
        int l = i, r = i;
        while (l >= 0 && r < n && s[l] == s[r]) {
            if (r - l + 1 > maxLen) {
                maxLen = r - l + 1;
                start = l;
            }
            l--;
            r++;
        }
    }

    // Palíndromos de longitud > 2
    for (int i = 0; i < n; i++) {
        int l = i, r = i + 1;
        while (l >= 0 && r < n && s[l] == s[r]) {
            if (r - l + 1 > maxLen) {
                maxLen = r - l + 1;
                start = l;
            }
            l--;
            r++;
        }
    }

    return { start + 1, s.substr(start, maxLen) };  // Ajustar posiciones a base 1
}

// Función para encontrar el substring común más largo entre dos textos
pair<size_t, string> longestCommonSubstring(const string& s1, const string& s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int max_len = 0, end_pos = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max_len) {
                    max_len = dp[i][j];
                    end_pos = i - 1;
                }
            }
        }
    }

    if (max_len == 0) return { 0, "" };
    return { end_pos - max_len + 2, s1.substr(end_pos - max_len + 1, max_len) };
}

int main() {

	// Cambiar directorio de trabajo
    filesystem::current_path("C:/VS/PROJECTS/EXAMENES/Examenes/Examenes/Evidencia 1");
    
	// Leer archivos
    string t1 = readFile("archivos/transmission1.txt");
    string t2 = readFile("archivos/transmission2.txt");

    vector<string> mcodes = {
        readFile("archivos/mcode1.txt"),
        readFile("archivos/mcode2.txt"),
        readFile("archivos/mcode3.txt")
    };

    // Parte 1: Verificar si los códigos maliciosos están contenidos en las transmisiones
    cout << "Parte 1:\n";
    for (auto& code : mcodes) {
        auto [found1, pos1] = contains(t1, code);
        auto [found2, pos2] = contains(t2, code);
        cout << (found1 ? "true " + to_string(pos1) : "false") << "\n"
            << (found2 ? "true " + to_string(pos2) : "false") << "\n";
    }

    // Parte 2: Encontrar el palíndromo más largo en cada transmisión
    cout << "\nParte 2:\n";
    auto [s1, p1] = findLongestPalindrome(t1);
    cout << s1 << " " << s1 + p1.length() - 1 << " " << p1 << endl;
    auto [s2, p2] = findLongestPalindrome(t2);
    cout << s2 << " " << s2 + p2.length() - 1 << " " << p2 << endl;

	// Parte 3 Encontrar el substring común más largo entre las transmisiones
    cout << "\nParte 3:\n";
    auto [cs, comm] = longestCommonSubstring(t1, t2);
    cout << cs << " " << cs + comm.length() - 1 << " " << comm << endl;

    return 0;
}