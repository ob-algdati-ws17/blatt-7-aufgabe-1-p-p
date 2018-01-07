#include "testAVLTree.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool isEqual(const vector<int> &v1, const vector<int> v2);
AVLTree *insertNodes(AVLTree &tree, const vector<int> &nodes);
bool searchNodes(const AVLTree &tree, const vector<int> &nodes);
void treeToPng(AVLTree *tree);

// Empty tree
TEST(AVLTreeTest, Empty_Tree) {
    AVLTree *tree = new AVLTree();
    EXPECT_EQ(nullptr, tree->inorder());
    EXPECT_EQ(nullptr, tree->postorder());
    EXPECT_EQ(nullptr, tree->preorder());
}

// insert and search without rotation
TEST(AVLTreeTest, One_Node) {
    AVLTree *tree = new AVLTree();
    tree->insert(1);
    EXPECT_TRUE(tree->search(1));
    EXPECT_FALSE(tree->search(10));
    EXPECT_FALSE(tree->search(-1));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(1));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(1));
}

TEST(AVLTreeTest, Root_With_Child_Left) {
    AVLTree *tree = new AVLTree();
    tree->insert(2);
    tree->insert(1);
    EXPECT_TRUE(tree->search(1));
    EXPECT_TRUE(tree->search(2));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(2, 1));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(1, 2));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(1, 2));
}

TEST(AVLTreeTest, Root_With_Child_Right) {
    AVLTree *tree = new AVLTree();
    tree->insert(2);
    tree->insert(3);
    EXPECT_TRUE(tree->search(2));
    EXPECT_TRUE(tree->search(3));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(2, 3));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 3));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(3, 2));
}

TEST(AVLTreeTest, Root_With_two_Childs) {
    AVLTree *tree = new AVLTree();
    tree->insert(2);
    tree->insert(3);
    tree->insert(1);
    EXPECT_TRUE(tree->search(2));
    EXPECT_TRUE(tree->search(3));
    EXPECT_TRUE(tree->search(1));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(2, 1, 3));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(1, 2 ,3));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(1, 3, 2));
}

//Insert and search with root rotation
TEST(AVLTreeTest, Rotate_Root_Left_Three_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {4, 6, 8});
    EXPECT_TRUE(searchNodes(*tree, {4, 6, 8}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 8));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 6, 8));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 8, 6));
}

TEST(AVLTreeTest, Rotate_Root_Right_Three_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {4, 8, 6});
    EXPECT_TRUE(searchNodes(*tree, {4, 8, 6}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 8));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 6, 8));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 8, 6));
}

TEST(AVLTreeTest, Rotate_Root_Left_Right_Three_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {8, 4, 6});
    EXPECT_TRUE(searchNodes(*tree, {8, 4, 6}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 8));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 6, 8));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 8, 6));
}

TEST(AVLTreeTest, Rotate_Root_Right_Left_Three_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {4, 8, 6});
    EXPECT_TRUE(searchNodes(*tree, {4, 8, 6}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 8));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 6, 8));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 8, 6));
}

TEST(AVLTreeTest, Rotate_Root_Left_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {4, 2, 8, 6, 10, 12});
    EXPECT_TRUE(searchNodes(*tree, {4, 2, 8, 6, 10, 12}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(8, 4, 2, 6, 10, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 6, 8, 10, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 6, 4, 12, 10, 8));
}

TEST(AVLTreeTest, Rotate_Root_Right_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {10, 6, 4, 8, 2, 12});
    EXPECT_TRUE(searchNodes(*tree, {10, 6, 4, 8, 2, 12}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 2, 10, 8, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 6, 8, 10, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 4, 8, 12, 10, 6));
}

TEST(AVLTreeTest, Rotate_Root_Left_Right_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {8, 4, 2, 6, 12, 7});
    EXPECT_TRUE(searchNodes(*tree, {8, 4, 2, 6, 12, 7}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 2, 8, 7, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 6, 7, 8, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 4, 7, 12, 8, 6));
}

TEST(AVLTreeTest, Rotate_Root_Right_Left_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {4, 2, 8, 6, 12, 5});
    EXPECT_TRUE(searchNodes(*tree, {4, 2, 8, 6, 12, 5}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(6, 4, 2, 5, 8, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 5, 6, 8, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 5, 4, 12, 8, 6));
}

// Insert and search with inner node rotation
TEST(AVLTreeTest, Rotate_Inner_Node_Left_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {8, 4, 6, 7, 10, 12});
    EXPECT_TRUE(searchNodes(*tree, {8, 4, 6, 7, 10, 12}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(8, 6, 4, 7, 10, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 6, 7, 8, 10, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 7, 6, 12, 10, 8));
}

TEST(AVLTreeTest, Rotate_Inner_Node_Right_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {8, 6, 10, 4, 12, 2});
    EXPECT_TRUE(searchNodes(*tree, {8, 6, 4, 2, 10, 12}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(8, 4, 2, 6, 10, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 6, 8, 10, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 6, 4, 12, 10, 8));
}

TEST(AVLTreeTest, Rotate_Inner_Node_Left_Right_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {8, 6, 10, 4, 12, 5});
    EXPECT_TRUE(searchNodes(*tree, {8, 6, 10, 4, 12, 5}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(8, 5, 4, 6, 10, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(4, 5, 6, 8, 10, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(4, 6, 5, 12, 10, 8));
}

TEST(AVLTreeTest, Rotate_Inner_Node_Right_Left_Six_Nodes) {
    AVLTree *tree = new AVLTree();
    tree = insertNodes(*tree, {8, 4, 10, 2, 12, 11});
    EXPECT_TRUE(searchNodes(*tree, {8, 11, 10, 4, 12, 2}));
    EXPECT_THAT(*tree->preorder(), testing::ElementsAre(8, 4, 2, 11, 10, 12));
    EXPECT_THAT(*tree->inorder(), testing::ElementsAre(2, 4, 8, 10, 11, 12));
    EXPECT_THAT(*tree->postorder(), testing::ElementsAre(2, 4, 10, 12, 11, 8));
}

/*
 * Helper method, that compares element wise two vectors.
 * Gives true, if vectors are equal, false, if not.
*/
bool isEqual(const vector<int> &v1, const vector<int> v2) {
    if (v1.size() != v2.size())
        return false;
    return equal(v1.begin(), v1.end(), v2.begin());
}

/*
 * Adds nodes from vector to a tree.
 * Returns this tree.
 */
AVLTree *insertNodes(AVLTree &tree, const vector<int> &nodes) {
    for(auto it = nodes.begin(); it < nodes.end(); it++)
        tree.insert(*it);
    return &tree;
}

/*
 * Searches for nodes from vector in a tree.
 * Gives true, if all nodes were found. False, if not.
 */
bool searchNodes(const AVLTree &tree, const vector<int> &nodes) {
    for(auto it = nodes.begin(); it < nodes.end(); it++) {
        if(!tree.search(*it))
            return false;
    }
    return true;
}
 void treeToPng (AVLTree *tree) {
    ofstream myfile;
    myfile.open("tree.dot");
    myfile << *tree;
    myfile.close();
    system("dot -Tpng tree.dot -o tree.png");
}
