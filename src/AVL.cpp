#include "AVL.h"
#include <iostream>

using namespace std;

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

AVL::Node* AVL::insert(Node* node, const string& name, const string& ufid, bool& success) {
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

string AVL::insert(const string& name, const string& ufid) {
    bool success = false;
    root = insert(root, name, ufid, success);
    return success ? "successful" : "unsuccessful";
}

AVL::Node* AVL::minValueNode(Node* node) {
    Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

AVL::Node* AVL::remove(Node* node, const std::string& ufid, bool& success) {
    if (!node) {
        success = false;
        return nullptr;
    }

    if (ufid < node->UFID) {
        node->left = remove(node->left, ufid, success);
    } else if (ufid > node->UFID) {
        node->right = remove(node->right, ufid, success);
    } else {
        // Node to be deleted found
        success = true;

        // Node with one child or no child
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            // Node with two children: Get inorder successor
            Node* temp = minValueNode(node->right);
            node->name = temp->name;
            node->UFID = temp->UFID;
            node->right = remove(node->right, temp->UFID, success);
        }
    }

    if (!node) return node;

    // Update height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Balance
    int balance = getBalance(node);

    // Left Heavy
    if (balance > 1) {
        if (getBalance(node->left) >= 0)
            return rotateRight(node); // LL
        else {
            node->left = rotateLeft(node->left); // LR
            return rotateRight(node);
        }
    }

    // Right Heavy
    if (balance < -1) {
        if (getBalance(node->right) <= 0)
            return rotateLeft(node); // RR
        else {
            node->right = rotateRight(node->right); // RL
            return rotateLeft(node);
        }
    }

    return node;
}

std::string AVL::remove(const std::string& ufid) {
    bool success = false;
    root = remove(root, ufid, success);
    return success ? "successful" : "unsuccessful";
}

// === Search by ID (single result) ===
AVL::Node* AVL::searchByID(Node* node, const std::string& ufid) {
    if (!node) return nullptr;
    if (ufid == node->UFID) return node;
    if (ufid < node->UFID) return searchByID(node->left, ufid);
    return searchByID(node->right, ufid);
}

std::string AVL::searchByID(const std::string& ufid) {
    Node* result = searchByID(root, ufid);
    return result ? result->name : "unsuccessful";
}

// === Search by Name (may be multiple matches) ===
void AVL::searchByName(Node* node, const std::string& name, std::vector<std::string>& matches) {
    if (!node) return;

    if (node->name == name) {
        matches.push_back(node->UFID);
    }

    searchByName(node->left, name, matches);
    searchByName(node->right, name, matches);
}

std::vector<std::string> AVL::searchByName(const std::string& name) {
    std::vector<std::string> matches;
    // Traverse in pre-order (for required output order)
    std::vector<Node*> stack;
    if (root) stack.push_back(root);

    while (!stack.empty()) {
        Node* current = stack.back();
        stack.pop_back();

        if (current->name == name)
            matches.push_back(current->UFID);

        // Push right first so left is processed first
        if (current->right) stack.push_back(current->right);
        if (current->left) stack.push_back(current->left);
    }

    return matches;
}