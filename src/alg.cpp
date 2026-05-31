// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

#include "bst.h"

struct WordFreq {
  std::string word;
  int count;
};

void collect(BST<std::string>::Node* node, std::vector<WordFreq>& list) {
  if (node == nullptr) {
    return;
  }
  collect(node->left, list);
  list.push_back({node->value, node->count});
  collect(node->right, list);
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string word = "";
  int ch;
  while ((ch = file.get()) != EOF) {
    if (ch >= 'A' && ch <= 'Z') {
      word += static_cast<char>(ch - 'A' + 'a');
    } else if (ch >= 'a' && ch <= 'z') {
      word += static_cast<char>(ch);
    } else {
      if (!word.empty()) {
        tree.add(word);
        word.clear();
      }
    }
  }
  if (!word.empty()) {
    tree.add(word);
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<WordFreq> list;
  collect(tree.getRoot(), list);

  std::sort(list.begin(), list.end(), [](const WordFreq& a, const WordFreq& b) {
    if (a.count != b.count) {
      return a.count > b.count;
    }
    return a.word < b.word;
  });

  std::ofstream outFile("result/freq.txt");

  for (const auto& item : list) {
    std::cout << item.word << " " << item.count << std::endl;
    if (outFile.is_open()) {
      outFile << item.word << " " << item.count << "\n";
    }
  }

  if (outFile.is_open()) {
    outFile.close();
  }
}
