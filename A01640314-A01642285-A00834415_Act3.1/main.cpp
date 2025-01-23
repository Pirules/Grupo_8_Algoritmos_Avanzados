/*
 * License: Educational use only.
 * File: main.cpp
 * Description: Implementacion de Tries donde se inserta un numero de palabras,
 * despues se busca una palabra y se imprime la cantidad de palabras que hay en
 * el trie. 
 * Authors:  Luis Angel Alba Alfaro - A01640314 
 * Fernando García Tejeda - A01642285 
 * Bruno Márquez Puig - A00834415 
 * Created: January 23, 2025
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TrieNode {
  bool isEndOfWord;
  TrieNode *children[26];

  TrieNode() {
    isEndOfWord = false;
    for (int i = 0; i < 26; i++)
      children[i] = nullptr;
  }
};

class Trie {
private:
  TrieNode *root;

  void dfs(TrieNode *node, string currentWord, vector<string> &result) {
    if (!node)
      return;
    if (node->isEndOfWord)
      result.push_back(currentWord);
    for (int i = 0; i < 26; i++) {
      if (node->children[i]) {
        char nextChar = 'a' + i;
        dfs(node->children[i], currentWord + nextChar, result);
      }
    }
  }

public:
  Trie() { root = new TrieNode(); }

  // Complejidad: O(L), donde L es la longitud de la palabra
  void insert(const string &word) {
    TrieNode *node = root;
    for (char c : word) {
      int index = c - 'a';
      if (!node->children[index])
        node->children[index] = new TrieNode();
      node = node->children[index];
    }
    node->isEndOfWord = true;
  }

  // Complejidad: O(L), donde L es la longitud de la palabra
  bool search(const string &word) {
    TrieNode *node = root;
    for (char c : word) {
      int index = c - 'a';
      if (!node->children[index])
        return false;
      node = node->children[index];
    }
    return node->isEndOfWord;
  }

  // Complejidad: O(N), donde N es el número total de nodos en el Trie
  vector<string> getWords() {
    vector<string> result;
    dfs(root, "", result);
    return result;
  }
};

int main() {
  int N, M;
  cin >> N;

  Trie trie;
  vector<string> words(N);

  // Leer e insertar palabras en el Trie
  for (int i = 0; i < N; i++) {
    cin >> words[i];
    trie.insert(words[i]);
  }

  cin >> M;
  vector<string> searchWords(M);

  // Leer palabras a buscar
  for (int i = 0; i < M; i++) {
    cin >> searchWords[i];
  }

  // Obtener palabras del Trie en DFS
  vector<string> dfsWords = trie.getWords();
  sort(dfsWords.begin(), dfsWords.end());

  // Imprimir palabras en DFS
  for (const string &word : dfsWords)
    cout << word << endl;

  // Buscar las palabras y mostrar resultados
  for (const string &word : searchWords)
    cout << trie.search(word) << endl;

  return 0;
}
