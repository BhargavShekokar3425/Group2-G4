#include<bits/stdc++.h>
#include"BST.hpp"

using namespace std;

class BSTNode{
    public:
    string dbName;
    BSTNode* left;
    BSTNode* right;

    BSTNode(string name){
        name=dbName;
        left=right=nullptr;
    }
};

class BST{
    public:
    BSTNode* root;
    BST(): root(nullptr) {}

    BSTNode* insert(BSTNode* node, const string& name){
        if(node==nullptr) return new BSTNode(name);

        if(name<node->dbName){
            node->left=insert(node->left, name);
        }
        else if(name>node->dbName){
            node->right=insert(node->right, name);
        }
        return node;
    }

    void insert(string name){
        root=insert(root, name);
    }

    bool search(const string& name){
        return search(root, name);
    }

    bool search(BSTNode* node, const string& name){
        if(node==nullptr) return false;

        if(node->dbName==name) return true;

        else if(name<node->dbName){
            return search(node->left, name);
        }
        else{
            return search(node->right, name);
        }
    }
    
};