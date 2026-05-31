// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

template <typename T>
class BST {
 public:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;

    explicit Node(T val) : value(val), count(1), left(nullptr), right(nullptr) {}
  };

 private:
  Node* root;

  Node* insert(Node* node, const T& value) {
    if (node == nullptr) {
      return new Node(value);
    }
    if (value < node->value) {
      node->left = insert(node->left, value);
    } else if (value > node->value) {
      node->right = insert(node->right, value);
    } else {
      node->count++;
    }
    return node;
  }

  int getDepth(Node* node) const {
    if (node == nullptr) {
      return 0;
    }
    int leftDepth = getDepth(node->left);
    int rightDepth = getDepth(node->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
  }

  Node* searchNode(Node* node, T value) const {
    if (node == nullptr || node->value == value) {
      return node;
    }
    if (value < node->value) {
      return searchNode(node->left, value);
    }
    return searchNode(node->right, value);
  }

  void clear(Node* node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

 public:
  BST() : root(nullptr) {}

  ~BST() {
    clear(root);
  }

  void add(const T& value) {
    root = insert(root, value);
  }

  int depth() const {
    int d = getDepth(root);
    return d > 0 ? d - 1 : 0;
  }

  int search(T value) const {
    Node* node = searchNode(root, value);
    if (node != nullptr) {
      return node->count;
    }
    return 0;
  }

  Node* getRoot() const {
    return root;
  }
};

#endif  // INCLUDE_BST_H_
