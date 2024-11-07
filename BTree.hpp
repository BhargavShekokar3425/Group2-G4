#ifndef BTREE_HPP
#define BTREE_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BTreeNode {
public:
    vector<int> keys;         // IDs
    vector<string> names;      // Names
    vector<int> ages;          // Ages
    vector<float> salaries;    // Salaries
    vector<BTreeNode*> children;
    bool leaf;
    int t;                     // Minimum degree

    BTreeNode(int _t, bool _leaf);

    void insertNonFull(int key, const string& name, int age, float salary);
    void splitChild(int i, BTreeNode *y);
    BTreeNode *search(int key);
    void remove(int key); // To be implemented fully as needed

    void printAll();
    float querySum(); // Calculates the sum of salaries in this node and children recursively

    friend class BTree;
};

class BTree {
    BTreeNode *root;
    int t;

public:
    BTree(int _t);

    void insert(int key, const string& name, int age, float salary);
    void remove(int key);
    BTreeNode* search(int key);
    void update(int key, const string& name, int age, float salary);
    float querySum();
    void printAllRecords();
};

#endif // BTREE_HPP
