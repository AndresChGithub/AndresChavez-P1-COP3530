#include "AVL.h"
#include <iostream>

AVL::AVL() : root(nullptr) {}

AVL::~AVL() {
    destroy(root);
}

void AVL::destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

int AVL::getHeight(Node* node) {
    return node ? node->height : 0;
}

int AVL::max(int a, int b) {
    return (a > b) ? a : b;
}

int AVL::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// Rotations
AVL::Node* AVL::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

AVL::Node* AVL::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

AVL::Node* AVL::insert(Node* node, const std::string& name, const std::string& ufid, bool& success) {
    if (!node) {
        success = true;
        return new Node(name, ufid);
    }

    if (ufid < node->UFID) {
        node->left = insert(node->left, name, ufid, success);
    } else if (ufid > node->UFID) {
        node->right = insert(node->right, name, ufid, success);
    } else {
        success = false;  // Duplicate UFID
        return node;
    }

    // Update height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Balance factor
    int balance = getBalance(node);

    // 4 Imbalance Cases
    if (balance > 1 && ufid < node->left->UFID)
        return rotateRight(node);

    if (balance < -1 && ufid > node->right->UFID)
        return rotateLeft(node);

    if (balance > 1 && ufid > node->left->UFID) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && ufid < node->right->UFID) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;  // No rotation needed
}

std::string AVL::insert(const std::string& name, const std::string& ufid) {
    bool success = false;
    root = insert(root, name, ufid, success);
    return success ? "successful" : "unsuccessful";
}
