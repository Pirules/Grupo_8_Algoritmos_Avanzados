#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Función para leer el contenido de un archivo
string readFile(const string& fileName) {
    ifstream file(fileName);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return content;
}

// Función para encontrar si una secuencia está contenida en otra
pair<bool, size_t> contains(const string& text, const string& pattern) {
    size_t pos = text.find(pattern);
    return {pos != string::npos, pos + 1}; // Ajustar posición a base 1
}

// Función para encontrar el palíndromo más largo en un texto
pair<size_t, string> findLongestPalindrome(const string& text) {
    size_t n = text.size();
    size_t start = 0, maxLength = 1;

    vector<vector<bool>> dp(n, vector<bool>(n, false));

    // Todas las subcadenas de un solo carácter son palíndromos
    for (size_t i = 0; i < n; ++i) {
        dp[i][i] = true;
    }

    // Palíndromos de longitud 2
    for (size_t i = 0; i < n - 1; ++i) {
        if (text[i] == text[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    // Palíndromos de longitud > 2
    for (size_t len = 3; len <= n; ++len) {
        for (size_t i = 0; i < n - len + 1; ++i) {
            size_t j = i + len - 1;
            if (text[i] == text[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                start = i;
                maxLength = len;
            }
        }
    }

    return {start + 1, text.substr(start, maxLength)}; // Ajustar posiciones a base 1
}

// Función para encontrar el substring común más largo entre dos textos
pair<size_t, string> longestCommonSubstring(const string& text1, const string& text2) {
    size_t n1 = text1.size(), n2 = text2.size();
    vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));

    size_t maxLength = 0, endPos = 0;

    for (size_t i = 1; i <= n1; ++i) {
        for (size_t j = 1; j <= n2; ++j) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endPos = i - 1;
                }
            }
        }
    }

    return {endPos - maxLength + 2, text1.substr(endPos - maxLength + 1, maxLength)}; // Ajustar posiciones a base 1
}

int main() {
    // Leer archivos
    string transmission1 = readFile("transmission1.txt");
    string transmission2 = readFile("transmission2.txt");
    vector<string> mcodes = {readFile("mcode1.txt"), readFile("mcode2.txt"), readFile("mcode3.txt")};

    // Parte 1: Verificar si los códigos maliciosos están contenidos en las transmisiones
    cout << "Parte 1:\n";
    for (size_t i = 0; i < mcodes.size(); ++i) {
        auto [found1, pos1] = contains(transmission1, mcodes[i]);
        auto [found2, pos2] = contains(transmission2, mcodes[i]);

        cout << (found1 ? "true " + to_string(pos1) : "false") << endl;
        cout << (found2 ? "true " + to_string(pos2) : "false") << endl;
    }

    // Parte 2: Encontrar el palíndromo más largo en cada transmisión
    cout << "\nParte 2:\n";
    auto [start1, palindrome1] = findLongestPalindrome(transmission1);
    auto [start2, palindrome2] = findLongestPalindrome(transmission2);

    cout << start1 << " " << start1 + palindrome1.size() - 1 << " " << palindrome1 << endl;
    cout << start2 << " " << start2 + palindrome2.size() - 1 << " " << palindrome2 << endl;

    // Parte 3: Encontrar el substring común más largo entre las dos transmisiones
    cout << "\nParte 3:\n";
    auto [commonStart, commonSubstring] = longestCommonSubstring(transmission1, transmission2);
    cout << commonStart << " " << commonStart + commonSubstring.size() - 1 << " " << commonSubstring << endl;

    return 0;
}
