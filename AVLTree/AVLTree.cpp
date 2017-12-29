#include <functional>
#include <iostream>
#include "AVLTree.h"

using namespace std;

/*
 * Helper (private methods)
 */

AVLTree::Node* AVLTree::get_parent(const int cval) {
    Node* p;
    Node* tmp = root;

    while (tmp) {
        if (cval < tmp->key) {
            p = tmp;
            tmp = tmp->left;
        } else if (cval > tmp->key) {
            p = tmp;
            tmp = tmp->right;
        } else {
            return p;
        }
    }

    return nullptr;
}

/*
 * Implementation of class interface
 */

bool AVLTree::search(const int val) const {
    auto vec = inorder();

    if (!vec) {
        return false;
    }

    for (int &it : *vec) {
        if (it == val) {
            return true;
        }
    }

    return false;
}


void AVLTree::insert(const int val) {
    if (!root) {
        root = new Node(val);
    } else {
        insert_child(root, val);
    }
}

void AVLTree::remove(const int val) {

}

/*
 * Node
 */

void AVLTree::insert_child(Node *p, const int val) {
    if (val < p->key) {
        p->balance--;
        if (p->left) {
            insert_child(p->left, val);
        } else {
            p->left = new Node(val);
            return;
        }
    } else if (val > p->key) {
        p->balance++;
        if (p->right) {
            insert_child(p->right, val);
        } else {
            p->right = new Node(val);
            return;
        }
    }

    if (p->balance == -2) {
        // rotate right
    } else if (p->balance == 2) {
        // rotate left
    }
}


/*
 * Traversing
 */

vector<int>* AVLTree::preorder() const {
    if (!root) {
        return nullptr;
    }

    return root->preorder();
}

vector<int>* AVLTree::Node::preorder() const {
    auto vec = new vector<int>();
    vec->push_back(key);

    if (left) {
        auto left_vec = left->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }

    if (right) {
        auto right_vec = right->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }

    return vec;
}

vector<int>* AVLTree::inorder() const {
    if (!root) {
        return nullptr;
    }

    return root->inorder();
}

vector<int>* AVLTree::Node::inorder() const {
    auto vec = new vector<int>();

    if (left) {
        auto left_vec = left->inorder();
        vec->insert(vec->begin(), left_vec->begin(), left_vec->end());
    }

    vec->push_back(key);

    if (right) {
        auto right_vec = right->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }

    return vec;
}

vector<int>* AVLTree::postorder() const {
    if (!root) {
        return nullptr;
    }

    return root->postorder();
}

vector<int>* AVLTree::Node::postorder() const {
    auto vec = new vector<int>();

    if (left) {
        auto left_vec = left->postorder();
        vec->insert(vec->begin(), left_vec->begin(), left_vec->end());
    }

    if (right) {
        auto right_vec = right->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }

    vec->push_back(key);
    return vec;
}

std::ostream &operator<<(std::ostream &os, const AVLTree &tree) {
    function<void(std::ostream &, const int, const AVLTree::Node *, const string)> printToOs
            = [&](std::ostream &os, const int value, const AVLTree::Node *node, const string l) {

                static int nullcount = 0;

                if (node == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << value << " -> " << node->key
                       << " [label=\"" << l << "\"];" << endl;

                    printToOs(os, node->key, node->left, "l");
                    printToOs(os, node->key, node->right, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->left, "l");
        printToOs(os, tree.root->key, tree.root->right, "r");
    }
    os << "}" << endl;
    return os;
}
