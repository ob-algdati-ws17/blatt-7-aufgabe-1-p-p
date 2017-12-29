#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <vector>

using namespace std;

class AVLTree {

private:


    struct Node {
        const int key;
        int balance = 0;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(const int key);

        Node(const int key, Node *left, Node *right);

        ~Node();

        vector<int> *preorder() const;  // (Hauptreihenfolge)

        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)

        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    Node *root;

    /**
     * Finds ands returns the parent of child with value.
     *
     * @param cval value of child
     * @return Node* parent, nullptr if cval was not found or has no parent (e.g. is root)
     */
    Node *get_parent(const int child);

    /**
     * Inserts a new child with value into a (sub)tree.
     * @param parent the root of the (sub)tree to insert into
     * @param val the value to insert
     */
    void insert_child(Node *p, const int val);

public:

    ~AVLTree();

    bool search(const int val) const;

    void insert(const int val);

    void remove(const int val);

    vector<int> *preorder() const;

    vector<int> *inorder() const;

    vector<int> *postorder() const;

    friend ostream &operator<<(ostream &, const AVLTree &);

};


#endif //AVLTREE_AVLTREE_H