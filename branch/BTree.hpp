// BTree.hpp

#ifndef BTREE_HPP
#define BTREE_HPP

#include <vector>
#include <string>
#include <iostream>

class BTreeNode {
public:
    bool isLeaf;
    std::vector<int> keys;
    std::vector<std::string> names;  // Assuming a name attribute
    std::vector<int> attribute1;     // First additional attribute (integer)
    std::vector<float> attribute2;   // Second additional attribute (float)
    std::vector<BTreeNode*> children;

    BTreeNode(int degree, bool isLeaf);
    void traverse();
    BTreeNode* search(int key);
    void insertNonFull(int key, const std::string& name, int attr1, float attr2);
    void splitChild(int i, BTreeNode* y);
    void remove(int key);
    int findKey(int key);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPred(int idx);
    int getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    friend class BTree;
};

class BTree {
private:
    BTreeNode* root;
    int degree;

public:
    BTree(int degree);
    void traverse();
    BTreeNode* search(int key);
    void insert(int key, const std::string& name, int attr1, float attr2);
    void remove(int key);
};

#endif // BTREE_HPP
