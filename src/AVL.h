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
        int height;    // for balancing and keeping track of height
        Node* left;
        Node* right;

        Node(const string& name, const string& ufid) : name(name), UFID(ufid), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // the functions, but private

    Node* insert(Node* node, const string& name, const string& ufid, bool& success);

    Node* remove(Node* node, const string& ufid, bool& success);

    Node* searchByID(Node* node, const string& ufid);
    void searchByName(Node* node, const string& name, vector<string>& matches);

    void gettingIDsInorder(Node* node, vector<string>& ids); //needed this for a cleaner removeInorder
    void inorder(Node* node, vector<string>& result);
    void preorder(Node* node, vector<string>& result);
    void postorder(Node* node, vector<string>& result);
    int levelCount(Node* node);

    // helpers
    int getBalance(Node* node);
    int getHeight(Node* node);
    int max(int a, int b);         // basic useful function

    // gets the node with the smallest UFID (needed it for deletion)
    Node* minValueNode(Node* node);

    // Rotations for balancing
    Node* leftRotate(Node* y);     // left rotation
    Node* rightRotate(Node* x);    // right rotation

    // the destructor
    void destroy(Node* node);

public:
    AVL();

    ~AVL();
    // All them important commands but in public

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
