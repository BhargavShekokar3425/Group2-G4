#include <iostream>
#include <vector>
#include <string>
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

BTreeNode::BTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
}

void BTree::insert(int key, const string& name, int age) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys.push_back(key);
        root->names.push_back(name);
        root->ages.push_back(age);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < key)
                i++;
            s->children[i]->insertNonFull(key, name, age);
            root = s;
        } else {
            root->insertNonFull(key, name, age);
        }
    }
}

void BTreeNode::insertNonFull(int key, const string& name, int age) {
    int i = keys.size() - 1;

    if (leaf) {
        keys.push_back(0);
        names.push_back("");
        ages.push_back(0);

        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            names[i + 1] = names[i];
            ages[i + 1] = ages[i];
            i--;
        }
        keys[i + 1] = key;
        names[i + 1] = name;
        ages[i + 1] = age;
    } else {
        while (i >= 0 && keys[i] > key)
            i--;
        if (children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < key)
                i++;
        }
        children[i + 1]->insertNonFull(key, name, age);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->keys.assign(y->keys.begin() + t, y->keys.end());
    z->names.assign(y->names.begin() + t, y->names.end());
    z->ages.assign(y->ages.begin() + t, y->ages.end());

    y->keys.resize(t - 1);
    y->names.resize(t - 1);
    y->ages.resize(t - 1);

    if (!y->leaf) {
        z->children.assign(y->children.begin() + t, y->children.end());
        y->children.resize(t);
    }

    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
    names.insert(names.begin() + i, y->names[t - 1]);
    ages.insert(ages.begin() + i, y->ages[t - 1]);
}

BTreeNode* BTree::search(int key) {
    return (root == nullptr) ? nullptr : root->search(key);
}

BTreeNode* BTreeNode::search(int key) {
    int i = 0;
    while (i < keys.size() && key > keys[i])
        i++;

    if (i < keys.size() && keys[i] == key)
        return this;

    if (leaf)
        return nullptr;

    return children[i]->search(key);
}

void BTree::remove(int key) {
    if (!root)
        return;

    root->remove(key);

    if (root->keys.size() == 0) {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->children[0];
        delete tmp;
    }
}

void BTreeNode::printAll() {
    for (int i = 0; i < keys.size(); i++) {
        if (!leaf)
            children[i]->printAll();
        cout << "ID: " << keys[i] << ", Name: " << names[i] << ", Age: " << ages[i] << endl;
    }
    if (!leaf)
        children[keys.size()]->printAll();
}

void BTree::printAllRecords() {
    if (root != nullptr)
        root->printAll();
    else
        cout << "No records available!" << endl;
}

int BTreeNode::findKey(int key) {
    int idx = 0;
    while (idx < keys.size() && keys[idx] < key)
        idx++;
    return idx;
}

void BTreeNode::remove(int key) {
    int idx = findKey(key);

    if (idx < keys.size() && keys[idx] == key) {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    } else {
        if (leaf) return;

        bool flag = (idx == keys.size());

        if (children[idx]->keys.size() < t)
            fill(idx);

        if (flag && idx > keys.size())
            children[idx - 1]->remove(key);
        else
            children[idx]->remove(key);
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    keys.erase(keys.begin() + idx);
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int key = keys[idx];

    if (children[idx]->keys.size() >= t) {
        int pred = getPred(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    } else if (children[idx + 1]->keys.size() >= t) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    } else {
        merge(idx);
        children[idx]->remove(key);
    }
}

int BTreeNode::getPred(int idx) {
    BTreeNode *cur = children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->keys.size()];
    return cur->keys[cur->keys.size() - 1];
}

int BTreeNode::getSucc(int idx) {
    BTreeNode *cur = children[idx + 1];
    while (!cur->leaf)
        cur = cur->children[0];
    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && children[idx - 1]->keys.size() >= t)
        borrowFromPrev(idx);
    else if (idx != keys.size() && children[idx + 1]->keys.size() >= t)
        borrowFromNext(idx);
    else {
        if (idx != keys.size())
            merge(idx);
        else
            merge(idx - 1);
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode *child = children[idx];
    BTreeNode *sibling = children[idx - 1];

    child->keys.insert(child->keys.begin(), keys[idx - 1]);

    if (!child->leaf)
        child->children.insert(child->children.begin(), sibling->children[sibling->keys.size()]);

    keys[idx - 1] = sibling->keys[sibling->keys.size() - 1];
    sibling->keys.pop_back();
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode *child = children[idx];
    BTreeNode *sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);

    if (!child->leaf)
        child->children.push_back(sibling->children[0]);

    keys[idx] = sibling->keys[0];
    sibling->keys.erase(sibling->keys.begin());
}

void BTreeNode::merge(int idx) {
    BTreeNode *child = children[idx];
    BTreeNode *sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);

    for (int i = 0; i < sibling->keys.size(); ++i)
        child->keys.push_back(sibling->keys[i]);

    if (!child->leaf) {
        for (int i = 0; i <= sibling->keys.size(); ++i)
            child->children.push_back(sibling->children[i]);
    }

    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);

    delete sibling;
}

#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(vector<int>& data) {
        n = data.size();
        tree.resize(2 * n);
        build(data);
    }

    void build(vector<int>& data) {
        for (int i = 0; i < n; ++i)
            tree[n + i] = data[i];
        for (int i = n - 1; i > 0; --i)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }

    void update(int pos, int value) {
        pos += n;
        tree[pos] = value;
        for (pos /= 2; pos > 0; pos /= 2)
            tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
    }

    int query(int l, int r) {
        int sum = 0;
        l += n;
        r += n;
        while (l < r) {
            if (l % 2 == 1) sum += tree[l++];
            if (r % 2 == 1) sum += tree[--r];
            l /= 2;
            r /= 2;
        }
        return sum;
    }
};
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Include the BTree and SegmentTree implementations

int main() {
    BTree btree(3); // BTree of minimum degree 3
    vector<int> segmentData;
    SegmentTree* segTree = nullptr;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert Record\n";
        cout << "2. Delete Record\n";
        cout << "3. Search Record\n";
        cout << "4. Update Record\n";
        cout << "5. Query (Sum)\n";
        cout << "6. View All Records\n";
        cout << "7. Exit\n";
        cout << "\nInput : ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            int key, age;
            string name;
            cout << "Enter ID: ";
            cin >> key;
            cout << "Enter Name: ";
            cin.ignore();  // To ignore any newline characters
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            btree.insert(key, name, age);
            segmentData.push_back(age);
            if (segTree == nullptr) {
                segTree = new SegmentTree(segmentData);
            } else {
                segTree->build(segmentData);
            }
        } else if (choice == 2) {
            int key;
            cout << "Enter ID to delete: ";
            cin >> key;
            btree.remove(key);
        } else if (choice == 3) {
            int key;
            cout << "Enter ID to search: ";
            cin >> key;
            BTreeNode* result = btree.search(key);
            if (result) {
                cout << "Record found.\n";
            } else {
                cout << "Record not found.\n";
            }
        } else if (choice == 4) {
            int key, newAge;
            cout << "Enter ID to update: ";
            cin >> key;
            cout << "Enter new Age: ";
            cin >> newAge;
            btree.remove(key);  // Removing old record and inserting updated one
            btree.insert(key, "Updated Name", newAge);  // This is just an example, modify as needed
        } else if (choice == 5) {
            if (segTree == nullptr) {
                cout << "No records to query.\n";
            } else {
                int l, r;
                cout << "Enter left index for SUM query: ";
                cin >> l;
                cout << "Enter right index for SUM query: ";
                cin >> r;
                int result = segTree->query(l, r);
                cout << "SUM between " << l << " and " << r << " is " << result << "\n";
            }
        } else if (choice == 6) {
            cout << "All records:\n";
            btree.printAllRecords();
        } else if (choice == 7) {
            cout << "Exiting...\n";
            break;
        }
    }

    return 0;
}
