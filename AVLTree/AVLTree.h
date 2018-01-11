#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <vector>

using namespace std;

class AVLTree {

private:

    /**
     * Representation of a Node in the tree, this can either
     * be a 'full' node, a 'leaf' or a 'half-leaf'.
     */
    struct Node {
        const int key;
        short balance = 0;
        Node* left = nullptr;
        Node* right = nullptr;

        /**
         * Constructs a new Node.
         *
         * @param key of the new Node
         */
        Node(const int key);

        /**
         * Constructs a new Node.
         *
         * @param key of the new Node
         * @param left child of the new Node
         * @param right child of the new Node
         */
        Node(const int key, Node *left, Node *right);

        /**
         * Frees the memory used by this node and that of all children.
         */
        ~Node();

        bool search(const int val) const;

        int height() const;

        vector<int> *preorder() const;  // (Hauptreihenfolge)

        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)

        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    /**
     * The root of the tree.
     */
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
     *
     * @param parent the root of the (sub)tree to insert into
     * @param val the value to insert
     */
    void insert_child(Node *p, const int val);

    /**
     * Performs the 'left-rotation' on a given node to rebalance the tree.
     *
     * @param center the node to rotate
     */
    void rotate_left(Node *center);

    /**
     * Performs the 'right-rotation' on a given node to rebalance the tree.
     *
     * @param center the node to rotate
     */
    void rotate_right(Node *center);

    /**
     * Called after every insertion, recursively goes back from the point of insertion
     * back to the root (or until a rotation happens) and checks if rebalancing is required.
     *
     * @param p the parent of the newly inserted node
     */
    void upin(Node *p);

    /**
     * Called after removal, if needed. Ensures that the tree is rebalanced by doing
     * appropriate rotations when necessary.
     *
     * @param p the parent of the removed node or the root of a subtree
     */
    void upout(Node *p);

    /**
     * Retrieves the symmetric successor of a node.
     *
     * @param p the node whose symmetric successor is searched for
     * @return the symmetric successor or nullptr if no such node exists
     */
    Node* find_sym_succ(Node* p) const;

public:

    /**
     * Deconstructs the tree and all Nodes contained by the tree.
     */
    ~AVLTree();

    /**
     * Searches a value in the tree, complexity is O(log n)
     *
     * @param val the value to search for
     * @return true if the value was found, false if not
     */
    bool search(const int val) const;

    /**
     * Inserts a value into the tree. Worst-case complexity is O(log n), best case is O(1) (empty tree).
     *
     * @param val the value to insert
     */
    void insert(const int val);

    /**
     * Removes the node with val from the tree.
     *
     * @param val the val to remove
     * @return true if a node was removed, false if not
     */
    bool remove(const int val);

    vector<int> *preorder() const;

    vector<int> *inorder() const;

    vector<int> *postorder() const;

    friend ostream &operator<<(ostream &, const AVLTree &);

};


#endif //AVLTREE_AVLTREE_H
