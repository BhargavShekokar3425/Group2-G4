#include "BTree.hpp"
#include <iostream>
#include <vector>

using namespace std;

// Constructor for BTreeNode
BTreeNode::BTreeNode(int degree, bool isLeaf) {
    this->degree = degree;  // Store degree in each node
    this->isLeaf = isLeaf;
    keys.reserve(2 * degree - 1);
    names.reserve(2 * degree - 1);
    attribute1.reserve(2 * degree - 1);
    attribute2.reserve(2 * degree - 1);
    children.reserve(2 * degree);
}

// Function to traverse the tree
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!isLeaf)
            children[i]->traverse();
        cout << "Key: " << keys[i] << ", Name: " << names[i] << ", Attr1: " << attribute1[i]
             << ", Attr2: " << attribute2[i] << endl;
    }
    if (!isLeaf)
        children[i]->traverse();
}

// Search function
BTreeNode* BTreeNode::search(int key) {
    int i = 0;
    while (i < keys.size() && key > keys[i])
        i++;

    if (i < keys.size() && keys[i] == key)
        return this;

    if (isLeaf)
        return nullptr;

    return children[i]->search(key);
}

// Insert non-full node
void BTreeNode::insertNonFull(int key, const string& name, int attr1, float attr2) {
    int i = keys.size() - 1;

    if (isLeaf) {
        keys.push_back(0);
        names.push_back("");
        attribute1.push_back(0);
        attribute2.push_back(0.0);

        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            names[i + 1] = names[i];
            attribute1[i + 1] = attribute1[i];
            attribute2[i + 1] = attribute2[i];
            i--;
        }

        keys[i + 1] = key;
        names[i + 1] = name;
        attribute1[i + 1] = attr1;
        attribute2[i + 1] = attr2;

        cout << "Inserted key " << key << " with attributes." << endl;
    } else {
        while (i >= 0 && keys[i] > key)
            i--;

        if (children[i + 1]->keys.size() == 2 * degree - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < key)
                i++;
        }
        children[i + 1]->insertNonFull(key, name, attr1, attr2);
    }
}

// Split child function
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(degree, y->isLeaf);
    z->keys.resize(degree - 1);
    z->names.resize(degree - 1);
    z->attribute1.resize(degree - 1);
    z->attribute2.resize(degree - 1);

    for (int j = 0; j < degree - 1; j++) {
        z->keys[j] = y->keys[j + degree];
        z->names[j] = y->names[j + degree];
        z->attribute1[j] = y->attribute1[j + degree];
        z->attribute2[j] = y->attribute2[j + degree];
    }

    if (!y->isLeaf) {
        z->children.resize(degree);
        for (int j = 0; j < degree; j++)
            z->children[j] = y->children[j + degree];
    }

    y->keys.resize(degree - 1);
    y->names.resize(degree - 1);
    y->attribute1.resize(degree - 1);
    y->attribute2.resize(degree - 1);

    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[degree - 1]);
    names.insert(names.begin() + i, y->names[degree - 1]);
    attribute1.insert(attribute1.begin() + i, y->attribute1[degree - 1]);
    attribute2.insert(attribute2.begin() + i, y->attribute2[degree - 1]);
}

// BTree constructor
BTree::BTree(int degree) {
    root = nullptr;
    this->degree = degree;
}

// Insert function for BTree
void BTree::insert(int key, const string& name, int attr1, float attr2) {
    if (root == nullptr) {
        root = new BTreeNode(degree, true);
        root->keys.push_back(key);
        root->names.push_back(name);
        root->attribute1.push_back(attr1);
        root->attribute2.push_back(attr2);
    } else {
        if (root->keys.size() == 2 * degree - 1) {
            BTreeNode* s = new BTreeNode(degree, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < key)
                i++;
            s->children[i]->insertNonFull(key, name, attr1, attr2);
            root = s;
        } else {
            root->insertNonFull(key, name, attr1, attr2);
        }
    }
}

// Traverse function for BTree
void BTree::traverse() {
    if (root)
        root->traverse();
}

// Search function for BTree
BTreeNode* BTree::search(int key) {
    return root ? root->search(key) : nullptr;
}

// Remove function for BTree
void BTree::remove(int key) {
    if (!root) {
        cout << "The tree is empty.\n";
        return;
    }

    root->remove(key);

    if (root->keys.empty()) {
        BTreeNode* temp = root;
        root = root->isLeaf ? nullptr : root->children[0];
        delete temp;
    }
}
