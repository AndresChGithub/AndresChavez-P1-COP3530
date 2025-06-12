#include "AVL.h"
#include <iostream>

using namespace std;

AVL::AVL() : root(nullptr) {}

AVL::~AVL() {
    destroy(root);
}

// using recursion to implement this destroy
void AVL::destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

// using ternary operators for simple "if-else" statements like this
int AVL::getHeight(Node* node) {
    return node ? node->height : 0;
}

int AVL::max(int a, int b) {
    return (a > b) ? a : b;
}

int AVL::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// rotations

AVL::Node* AVL::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // doing the rotation
    x->right = y;
    y->left = T2;

    // updating heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // this is our new root after rotation
}

AVL::Node* AVL::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // doing the rotation
    y->left = x;
    x->right = T2;

    // updating heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // this is our new root after rotation
}

// due to time constraints, I need the following two functions from main also to be here to validate inputs correctly in insert(),
// main works correctly without it, but insert() needs to validate inputs in a standalone way too to pass tests.

bool isValidName(const string& name) {
    for (char ch : name) {
        if (!isalpha(ch) && ch != ' ')
            return false;
    }

    return true;
}

bool isValidUFID(const string& id) {
    if (id.length() != 8)
        return false;

    for (char ch : id) {
        if (!isdigit(ch))
            return false;
    }

    return true;
}

AVL::Node* AVL::insert(Node* node, const string& name, const string& ufid, bool& success) {
    if (!node) {
        success = true;
        return new Node(name, ufid);
    }

    if (ufid < node->UFID) {
        node->left = insert(node->left, name, ufid, success);
    } 

    else if (ufid > node->UFID) {
        node->right = insert(node->right, name, ufid, success);
    } 

    else {
        success = false;  // making sure that no duplicates are allowed
        return node;
    }

    // updating height after insert is called
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // to check our tree's balance after calling insert()
    int balance = getBalance(node);

    // all of the important rotation cases, LL, RR, LR, RL.
    if (balance > 1 && ufid < node->left->UFID)
        return rightRotate(node);

    if (balance < -1 && ufid > node->right->UFID)
        return leftRotate(node);

    if (balance > 1 && ufid > node->left->UFID) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && ufid < node->right->UFID) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// having an insert wrapper makes things easier to understand and read for me
string AVL::insert(const string& name, const string& ufid) {
    if (!isValidName(name) || !isValidUFID(ufid)) {
        return "unsuccessful";
    }

    bool success = false;
    root = insert(root, name, ufid, success);
    return success ? "successful" : "unsuccessful";
}

// our helper for remove(), gets smallest value in a subtree
AVL::Node* AVL::minValueNode(Node* node) {
    Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

AVL::Node* AVL::remove(Node* node, const string& ufid, bool& success) {
    if (!node) {
        success = false;
        return nullptr;
    }

    if (ufid < node->UFID) {
        node->left = remove(node->left, ufid, success);
    } 

    else if (ufid > node->UFID) {
        node->right = remove(node->right, ufid, success);
    } 

    else {
        // after our recursion steps, this is the case where we found the node to delete
        success = true;

        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;

            if (!temp) {
                temp = node;
                node = nullptr;
            } 

            else {
                node->name = temp->name;
                node->UFID = temp->UFID;
                node->height = temp->height;
                node->left = temp->left;
                node->right = temp->right;
            }

            delete temp;

        } 
        
        else {
            // this is for the case it has two kids, we use a successor
            Node* temp = minValueNode(node->right);
            node->name = temp->name;
            node->UFID = temp->UFID;
            node->right = remove(node->right, temp->UFID, success);
        }
    }

    if (!node) return node;

    // updating height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // balancing even though it's optional because balancing in insert() wasn't that hard and it's similar
    int balance = getBalance(node);

    // left heavy
    if (balance > 1) {
        if (getBalance(node->left) >= 0)
            return rightRotate(node); // LL
        else {
            node->left = leftRotate(node->left); // LR
            return rightRotate(node);
        }
    }

    // right heavy
    if (balance < -1) {
        if (getBalance(node->right) <= 0)
            return leftRotate(node); // RR
        else {
            node->right = rightRotate(node->right); // RL
            return leftRotate(node);
        }
    }

    return node;
}

// remove() wrapper
string AVL::remove(const string& ufid) {
    bool success = false;
    root = remove(root, ufid, success);
    return success ? "successful" : "unsuccessful";
}

// the search functions:

AVL::Node* AVL::searchByID(Node* node, const string& ufid) {
    if (!node) return nullptr;
    if (ufid == node->UFID) return node;
    if (ufid < node->UFID) return searchByID(node->left, ufid);
    return searchByID(node->right, ufid);
}

string AVL::searchByID(const string& ufid) {
    Node* result = searchByID(root, ufid);
    return result ? result->name : "unsuccessful";
}

// when searching names, more than one may pop up, so we have to account for that correctly
void AVL::searchByName(Node* node, const string& name, vector<string>& matches) {
    if (!node) return;

    if (node->name == name) {
        matches.push_back(node->UFID);
    }

    searchByName(node->left, name, matches);
    searchByName(node->right, name, matches);
}

vector<string> AVL::searchByName(const string& name) {
    vector<string> matches;
    vector<Node*> stack;

    if (root) stack.push_back(root);

    while (!stack.empty()) {
        Node* current = stack.back();
        stack.pop_back();

        if (current->name == name)
            matches.push_back(current->UFID);

        // push right first so left is processed first
        if (current->right) stack.push_back(current->right);
        if (current->left) stack.push_back(current->left);
    }

    return matches;
}

// level count is just the height of the tree
int AVL::printLevelCount() {
    return getHeight(root);
}

// tree traversals, all 3 with public wrappers

void AVL::inorder(Node* node, vector<string>& result) {
    if (!node) return;
    inorder(node->left, result);
    result.push_back(node->name);
    inorder(node->right, result);
}

void AVL::preorder(Node* node, vector<string>& result) {
    if (!node) return;
    result.push_back(node->name);
    preorder(node->left, result);
    preorder(node->right, result);
}

void AVL::postorder(Node* node, vector<string>& result) {
    if (!node) return;
    postorder(node->left, result);
    postorder(node->right, result);
    result.push_back(node->name);
}

vector<string> AVL::printInorder() {
    vector<string> result;
    inorder(root, result);
    return result;
}

vector<string> AVL::printPreorder() {
    vector<string> result;
    preorder(root, result);
    return result;
}

vector<string> AVL::printPostorder() {
    vector<string> result;
    postorder(root, result);
    return result;
}

// helper for the removeInorder function
void AVL::gettingIDsInorder(Node* node, vector<string>& ids) {
    if (!node) return;
    gettingIDsInorder(node->left, ids);
    ids.push_back(node->UFID);  // we're handling IDs here, not names
    gettingIDsInorder(node->right, ids);
}

bool AVL::removeInorder(int N) {
    vector<string> ids;
    gettingIDsInorder(root, ids);

    if (N < 0 || N >= static_cast<int>(ids.size())) {
        return false;
    }

    remove(ids[N]); // simply calling remove with Nth ID
    return true;
}