#ifndef AVL_H
#define AVL_H

#include <string>
#include <vector>

using namespace std;

class AVL {
private:
    struct Node {
        string name;
        string UFID;
        int height;
        Node* left;
        Node* right;

        Node(const string& name, const string& ufid)
            : name(name), UFID(ufid), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // ========== Private Helper Methods (To Be Implemented) ==========
    Node* insert(Node* node, const string& name, const string& ufid, bool& success);
    Node* remove(Node* node, const string& ufid, bool& success);
    Node* searchByID(Node* node, const string& ufid);
    void searchByName(Node* node, const string& name, vector<string>& matches);
    void inorderCollect(Node* node, vector<string>& ids);

    void inorder(Node* node, vector<string>& result);
    void preorder(Node* node, vector<string>& result);
    void postorder(Node* node, vector<string>& result);
    int levelCount(Node* node);

    int getBalance(Node* node);
    int getHeight(Node* node);
    int max(int a, int b);
    Node* minValueNode(Node* node);

    // Rotations
    Node* rotateLeft(Node* y);
    Node* rotateRight(Node* x);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);

    void destroy(Node* node);

public:
    AVL();
    ~AVL();

    // ========== Public Interface for Testing ==========
    string insert(const string& name, const string& ufid);
    string remove(const string& ufid);
    void removeInorder(int n);
    string searchByID(const string& ufid);
    vector<string> searchByName(const string& name);
    vector<string> printInorder();
    vector<string> printPreorder();
    vector<string> printPostorder();
    int printLevelCount();
};

#endif // AVL_H