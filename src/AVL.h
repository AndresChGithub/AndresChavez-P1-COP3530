#ifndef AVL_H
#define AVL_H

#include <string>
#include <vector>

class AVL {
private:
    struct Node {
        std::string name;
        std::string UFID;
        int height;
        Node* left;
        Node* right;

        Node(const std::string& name, const std::string& ufid)
            : name(name), UFID(ufid), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // ========== Private Helper Methods (To Be Implemented) ==========
    Node* insert(Node* node, const std::string& name, const std::string& ufid, bool& success);
    Node* remove(Node* node, const std::string& ufid, bool& success);
    Node* removeInorder(Node* node, int& count, int target, bool& success);
    Node* searchByID(Node* node, const std::string& ufid);
    void searchByName(Node* node, const std::string& name, std::vector<std::string>& matches);

    void inorder(Node* node, std::vector<std::string>& result);
    void preorder(Node* node, std::vector<std::string>& result);
    void postorder(Node* node, std::vector<std::string>& result);
    int levelCount(Node* node);

    int getBalance(Node* node);
    int getHeight(Node* node);
    int max(int a, int b);

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
    std::string insert(const std::string& name, const std::string& ufid);
    std::string remove(const std::string& ufid);
    std::string removeInorder(int n);
    std::string searchByID(const std::string& ufid);
    std::vector<std::string> searchByName(const std::string& name);
    std::vector<std::string> printInorder();
    std::vector<std::string> printPreorder();
    std::vector<std::string> printPostorder();
    int printLevelCount();
};

// separator cause, well, yknow

template <typename T>
struct Node {
	typedef T value_type;

	Node(value_type value, Node<T> *left = nullptr, Node<T> *right = nullptr)
	: value(value), left(left), right(right), height(0) {}

	value_type value;
	Node<T> *left;
	Node<T> *right;
	size_t height;
};

#endif // AVL_H