//BST.hpp

#ifndef BST_HPP
#define BST_HPP

#include<bits/stdc++.h>

class BSTNode{
    public:
    string dbName;
    BSTNode* left;
    BSTNode* right;

    BSTNode(string name);
};

class BST{
    public:
    BSTNode* root;
    BST();

    void insert(string name);
    BSTNode* insert(BSTNode* node, const string& name);
    bool search(BSTNode* node, const string& name);
    bool search(const string& name);
};
#endif