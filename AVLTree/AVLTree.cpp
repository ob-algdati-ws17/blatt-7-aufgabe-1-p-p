#include <functional>
#include <iostream>
#include "AVLTree.h"

using namespace std;

AVLTree::Node::Node(const int key) : key(key) {}

AVLTree::Node::Node(const int key, Node *left, Node *right)
        : key(key), left(left), right(right) {}

AVLTree::Node::~Node() { delete left; delete right; }

int AVLTree::Node::height() const {
    int l = 1, r = 1;
    if (left) l = left->height() + 1;
    if (right) r = right->height() + 1;
    return l > r ? l : r;
}

AVLTree::Node* AVLTree::get_parent(const int cval) {
    Node* p = nullptr;
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

void AVLTree::rotate_left(Node *center) {
    Node *a = center;
    Node *b = center->right;

    if (center == root) {
        root = b;
    } else {
        Node *p = get_parent(center->key);
        if (a == p->right) {
            p->right = b;
        } else {
            p->left = b;
        }
    }

    a->right = b->left;
    b->left = a;
}

void AVLTree::rotate_right(Node *center) {
    Node *a = center;
    Node *b = center->left;

    if (center == root) {
        root = b;
    } else {
        Node *p = get_parent(center->key);
        if (a == p->left) {
            p->left = b;
        } else {
            p->right = b;
        }
    }

    a->left = b->right;
    b->right = a;
}

AVLTree::~AVLTree() { delete root; }

bool AVLTree::search(const int val) const {
    if (!root) {
        return false;
    }

    return root->search(val);
}

bool AVLTree::Node::search(const int val) const {
    if (val == key) return true;
    if (val < key && left) return left->search(val);
    if (val > key && right) return right->search(val);
    return false;
}

void AVLTree::insert(const int val) {
    if (root) {
        insert_child(root, val);
    } else {
        root = new Node(val);
    }
}

void AVLTree::insert_child(Node *p, const int val) {
    if (val == p->key) {
        return;
    }

    if (val < p->key) {
        if (p->left) {
            insert_child(p->left, val);
        } else {
            p->left = new Node(val);
            p->balance--;
            upin(p);
        }
    } else {
        if (p->right) {
            insert_child(p->right, val);
        } else {
            p->right = new Node(val);
            p->balance++;
            upin(p);
        }
    }
}

void AVLTree::upin(Node *p) {
    if (p->balance == 0) return;
    if (p == root) {
        return;
    }

    Node *parent = get_parent(p->key);
    if (p == parent->left) {
        switch (parent->balance) {
            case 1:
                parent->balance = 0;
                break;
            case 0:
                parent->balance = -1;
                break;
            case -1:
                if (p->balance == 1) {
                    rotate_left(parent->left);
                    rotate_right(parent);
                    parent->balance = 0;
                } else if (p->balance == -1){
                    rotate_right(parent);
                    parent->balance = 0;
                }
                p->balance = 0;
                return;
            default:
                throw logic_error("parent->balance should be in [-1,1]");
        }
    } else if (p == parent->right) {
        switch (parent->balance) {
            case -1:
                parent->balance = 0;
                break;
            case 0:
                parent->balance = 1;
                break;
            case 1:
                if (p->balance == -1) {
                    rotate_right(parent->right);
                    rotate_left(parent);
                    parent->balance = 0;
                } else if (p->balance == 1){
                    rotate_left(parent);
                    parent->balance = 0;
                }
                p->balance = 0;
                return;
            default:
                throw logic_error("parent->balance should be in [-1,1]");
        }
    }

    upin(parent);
}

bool AVLTree::remove(const int val) {
    auto n = root;

    while (n) {
        if (val < n->key) {
            n = n->left;
        } else if (val > n->key) {
            n = n->right;
        } else {
            break;
        }
    }

    if (!n || n->key != val) return false;

    Node *parent = get_parent(n->key);

    auto two_leafs = [&](){
        if (!parent) {
            root = nullptr;
        } else if (n == parent->left) {
            parent->left = nullptr;
            auto q = parent->right;

            if (!q) {
                parent->balance = 0;
                upout(parent);
            } else if (q->height() == 1) {
                parent->balance = 1;
            } else if (q->height() == 2) {
                switch (q->balance) {
                    case -1:
                        rotate_right(q);
                        rotate_left(parent);
                        upout(q);
                        break;
                    case 1:
                        rotate_left(parent);
                        upout(q);
                        break;
                    case 0:
                        rotate_left(parent);
                        break;
                    default:
                        throw logic_error("parent->balance should be in [-1,1]");
                }
            }
        } else {
            parent->right = nullptr;
            auto q = parent->left;

            if (!q) {
                parent->balance = 0;
                upout(parent);
            } else if (q->height() == 1) {
                parent->balance = -1;
            } else if (q->height() == 2) {
                switch (q->balance) {
                    case 1:
                        rotate_left(q);
                        rotate_right(parent);
                        upout(q);
                        break;
                    case -1:
                        rotate_right(parent);
                        upout(q);
                        break;
                    case 0:
                        rotate_right(parent);
                        break;
                    default:
                        throw logic_error("parent->balance should be in [-1,1]");
                }
            }
        }
    };

    auto one_leaf_one_node = [&](){
        if (n->left) {
            if (!parent) {
                root = n->left;
                return true;
            } else {
                if (n == parent->left) {
                    parent->left = n->left;
                    upout(parent->left);
                } else {
                    parent->right = n->left;
                    upout(parent->right);
                }
            }
        } else {
            if (!parent) {
                root = n->right;
                return true;
            } else {
                if (n == parent->left) {
                    parent->left = n->right;
                    upout(parent->left);
                } else {
                    parent->right = n->right;
                    upout(parent->right);
                }
            }
        }
    };

    auto two_nodes = [&](){
        auto sym = find_sym_succ(n);
        auto sym_p = get_parent(sym->key);

        if (!parent) {
            if (root->right->height() > 1) {
                root = new Node(sym->key, root->left, root->right);
            } else {
                root = new Node(sym->key, root->left, nullptr);
            }
        } else if (n == parent->left) {
            parent->left = new Node(sym->key, n->left, n->right);
            sym_p = parent->left;
        } else {
            parent->right = new Node(sym->key, n->left, n->right);
            sym_p = parent->right;
        }

        // remove the symmetric successor
        n = sym;
        parent = sym_p;
        if (!n->left && !n->right) {
            two_leafs();
        }

        if (!n->left != !n->right) {
            if (n == parent->left) {
                parent->left = n->right;
                parent->balance++;
            } else {
                parent->right = n->right;
                parent->balance--;
            }
        }

        upout(parent);
    };

    if (!n->left && !n->right) {
        // Case 1: Both children are leafs
        two_leafs();
    } else if (!n->left != !n->right) {
        // Case 2: One child is a leaf, one is a node
        one_leaf_one_node();
    } else {
        // Case 3: Both childs are inner nodes
        two_nodes();
    }

    // Finally delete n
    n->left = nullptr;
    n->right = nullptr;
    delete n;

    return true;
}

void AVLTree::upout(Node *p) {
    if (p->balance != 0) return;
    Node *parent = get_parent(p->key);

    if (!parent) return;

    if (p == parent->left) {
        switch (parent->balance) {
            case -1:
                parent->balance = 0;
                upout(parent);
                break;
            case 0:
                parent->balance = 1;
                break;
            case 1: {
                auto q = parent->right;
                switch (q->balance) {
                    case 0:
                        rotate_left(q);
                        break;
                    case 1:
                        rotate_left(parent);
                        upout(q);
                        break;
                    case -1: {
                        auto r = q->left;
                        rotate_right(q);
                        rotate_left(parent);
                        parent->balance = -1;
                        q->balance = 0;
                        r->balance = 0;
                        upout(r);
                        break;
                    }
                    default:
                        throw logic_error("parent->balance should be in [-1,1]");
                }
                break;
            }
            default:
                throw logic_error("parent->balance should be in [-1,1]");
        }
    } else {
        switch (parent->balance) {
            case 1:
                parent->balance = 0;
                upout(parent);
                break;
            case 0:
                parent->balance = -1;
                break;
            case -1: {
                auto q = parent->left;
                switch (q->balance) {
                    case 0:
                        rotate_right(q);
                        break;
                    case -1:
                        rotate_right(parent);
                        upout(q);
                        break;
                    case 1: {
                        auto l = q->right; // 7
                        rotate_left(q);
                        rotate_right(parent);
                        parent->balance = 1;
                        q->balance = 0;
                        l->balance = 0;
                        upout(l);
                        break;
                    }
                    default:
                        throw logic_error("parent->balance should be in [-1,1]");
                }
                break;
            }
            default:
                throw logic_error("parent->balance should be in [-1,1]");
        }
    }
}

AVLTree::Node * AVLTree::find_sym_succ(Node *p) const {
    if (!p->right) {
        return nullptr;
    }

    auto s = p->right;
    while (s->left) {
        s = s->left;
    }

    return s;
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

                    printToOs(os, node->key, node->left, to_string(node->balance));
                    printToOs(os, node->key, node->right, to_string(node->balance));
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->left, to_string(tree.root->balance));
        printToOs(os, tree.root->key, tree.root->right, to_string(tree.root->balance));
    }
    os << "}" << endl;
    return os;
}
