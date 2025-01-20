/*
 * License: Educational use only.
 * File: main.cpp
 * Description: Implementacion de sufix array que dado un string, calcula el
 * arreglo de substrings y lo muestre ordenado alfabeticamente. Authors:  Luis
 * Angel Alba Alfaro - A01640314 Fernando García Tejeda - A01642285 Bruno
 * Márquez Puig     - A00834415 Created: January 19, 2025
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// complejidad O(n log n), donde n es la longitud del string, debido al
// ordenamiento.

std::vector<std::pair<std::string, int>>
construirSuffixArray(const std::string &inputString) {
  std::vector<std::pair<std::string, int>> suffixArray;
  size_t n = inputString.length();

  for (size_t i = 0; i < n; ++i) {
    suffixArray.emplace_back(inputString.substr(i), i);
  }

  std::sort(suffixArray.begin(), suffixArray.end());

  return suffixArray;
}

int main() {
  std::string entrada;
  std::cout << "Introduce un string: ";
  std::getline(std::cin, entrada);

  // Construir y ordenar el suffix array
  std::vector<std::pair<std::string, int>> suffixArray =
      construirSuffixArray(entrada);

  ;
  for (const auto &sufijo : suffixArray) {
    std::cout << sufijo.second + 1 << std::endl;
  }

  return 0;
}
