#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <vector>

using namespace std;

class AVLTree {

private:


    struct Node {
        int balance;
        const int key;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(const int key) : key(key) { };
        Node(const int key, Node *left, Node *right) :
                key(key),
                left(left),
                right(right) { };
        ~Node();
        vector<int> *preorder() const;  // (Hauptreihenfolge)
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    Node *root;

public:


    ~AVLTree();

    bool search(const int val) const;

    void insert(const int val);

    void remove(const int val);

    vector<int> *preorder() const;
    vector<int> *inorder() const;
    vector<int> *postorder() const;
};


#endif //AVLTREE_AVLTREE_H
