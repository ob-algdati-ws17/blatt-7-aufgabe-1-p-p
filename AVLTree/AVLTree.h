//
// Created by octav on 12/27/17.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <vector>

using namespace std;

class AVLTree {
    struct Node {
        const int key;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(const int key) : key(key) { };
        Node(const int key, Node *left, Node *right) :
                key(key),
                left(left),
                right(right) { };
        ~Node();
        vector<int>* preorder() const;  // (Hauptreihenfolge)
        vector<int>* inorder() const;   // (Symmetrische Reihenfolge)
        vector<int>* postorder() const; // (Nebenreihenfolge)
    };
};


#endif //AVLTREE_AVLTREE_H
