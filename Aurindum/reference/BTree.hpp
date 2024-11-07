//BTree.hpp

#ifndef BTREE_HPP
#define BTREE_HPP

#include<bits/stdc++.h>
using namespace std;

class BTreeNode {
public:
    vector<int> keys;  // IDs
    vector<string> names; // Names
    vector<int> ages; // Ages
    vector<BTreeNode*> children;
    bool leaf;
    int t; // Minimum degree

    BTreeNode(int _t, bool _leaf);

    void insertNonFull(int key, const string& name, int age);
    void splitChild(int i, BTreeNode *y);
    BTreeNode *search(int key);
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

    void printAll();  // Print all records

    friend class BTree;
};

class BTree {
    BTreeNode *root;
    int t;
public:
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void insert(int key, const string& name, int age);
    void remove(int key);
    BTreeNode* search(int key);
    void printAllRecords();
};

#endif