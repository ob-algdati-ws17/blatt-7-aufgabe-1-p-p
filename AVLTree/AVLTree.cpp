#include "AVLTree.h"

bool AVLTree::search(const int val) const {
    return false;
}

void AVLTree::insert(const int val) {

}

void AVLTree::remove(const int val) {

}

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
