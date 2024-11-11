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
    void collectData(vector<tuple<int, string, int, float>>& data) const;
    void printRangeInorder(float lowerLimit, float upperLimit, int attribute);
    void printEqualInorder(float threshold, int attribute);
    void printGreaterInorder(float threshold, int attribute);
    void printLessInorder(float threshold, int attribute);
    void printAll();
    float querySum(); // Calculates the sum of salaries in this node and children recursively

    friend class BTree;
};

class BTree {
    public:
    BTreeNode *root;
    int t;

    BTree(int l);

    void insert(int key, const string& name, int age, float salary);
    void remove(int key);
    BTreeNode* search(int key);
    void update(int key, const string& name, int age, float salary);
    float querySum();
    void updateAddAge(int key, int add);
    void updateAge(int key, int age);
    void printGreater(int attributes);
    void printLess(int attributes);
    void updateSalary(int key, float add);
    void updateAddSalary(int key, float salary);
    void printRange(int attributes);
    void printEqual(int attributes);
    void printAllRecords();
    vector<tuple<int, string, int, float>> extractData() const;
    bool isTreeEmpty();
};

#endif // BTREE_HPP
