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
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void insert(int key, const string& name, int age, float salary);
    void remove(int key);
    BTreeNode* search(int key);
    void update(int key, const string& name, int age, float salary);
    float querySum();
    void printAllRecords();
};

BTreeNode::BTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;
}

void BTree::insert(int key, const string& name, int age, float salary) {
    if (root == nullptr) {
        root = new BTreeNode(t, true);
        root->keys.push_back(key);
        root->names.push_back(name);
        root->ages.push_back(age);
        root->salaries.push_back(salary);
    } else {
        if (static_cast<int>(root->keys.size()) == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < key) i++;
            s->children[i]->insertNonFull(key, name, age, salary);
            root = s;
        } else {
            root->insertNonFull(key, name, age, salary);
        }
    }
}

void BTreeNode::insertNonFull(int key, const string& name, int age, float salary) {
    int i = static_cast<int>(keys.size()) - 1;

    if (leaf) {
        keys.push_back(0);
        names.push_back("");
        ages.push_back(0);
        salaries.push_back(0.0);

        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            names[i + 1] = names[i];
            ages[i + 1] = ages[i];
            salaries[i + 1] = salaries[i];
            i--;
        }
        keys[i + 1] = key;
        names[i + 1] = name;
        ages[i + 1] = age;
        salaries[i + 1] = salary;
    } else {
        while (i >= 0 && keys[i] > key) i--;
        if (static_cast<int>(children[i + 1]->keys.size()) == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < key) i++;
        }
        children[i + 1]->insertNonFull(key, name, age, salary);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->keys.assign(y->keys.begin() + t, y->keys.end());
    z->names.assign(y->names.begin() + t, y->names.end());
    z->ages.assign(y->ages.begin() + t, y->ages.end());
    z->salaries.assign(y->salaries.begin() + t, y->salaries.end());

    y->keys.resize(t - 1);
    y->names.resize(t - 1);
    y->ages.resize(t - 1);
    y->salaries.resize(t - 1);

    if (!y->leaf) {
        z->children.assign(y->children.begin() + t, y->children.end());
        y->children.resize(t);
    }

    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
    names.insert(names.begin() + i, y->names[t - 1]);
    ages.insert(ages.begin() + i, y->ages[t - 1]);
    salaries.insert(salaries.begin() + i, y->salaries[t - 1]);
}

BTreeNode* BTree::search(int key) {
    return (root == nullptr) ? nullptr : root->search(key);
}

BTreeNode* BTreeNode::search(int key) {
    int i = 0;
    while (i < static_cast<int>(keys.size()) && key > keys[i]) i++;
    if (i < static_cast<int>(keys.size()) && keys[i] == key) return this;
    if (leaf) return nullptr;
    return children[i]->search(key);
}

void BTree::update(int key, const string& name, int age, float salary) {
    BTreeNode* node = search(key);
    if (node) {
        for (size_t i = 0; i < node->keys.size(); i++) {
            if (node->keys[i] == key) {
                node->names[i] = name;
                node->ages[i] = age;
                node->salaries[i] = salary;
                cout << "Record updated successfully!" << endl;
                return;
            }
        }
    }
    cout << "Record not found!" << endl;
}

void BTreeNode::printAll() {
    for (size_t i = 0; i < keys.size(); i++) {
        if (!leaf) children[i]->printAll();
        cout << "ID: " << keys[i] << ", Name: " << names[i] << ", Age: " << ages[i] << ", Salary: " << salaries[i] << endl;
    }
    if (!leaf) children[keys.size()]->printAll();
}

void BTree::printAllRecords() {
    if (root) root->printAll();
}

float BTreeNode::querySum() {
    float sum = 0;
    for (size_t i = 0; i < salaries.size(); i++) {
        sum += salaries[i];
    }
    for (auto child : children) {
        sum += child->querySum();
    }
    return sum;
}

float BTree::querySum() {
    return root ? root->querySum() : 0.0f;
}

void BTreeNode::remove(int key) {
    // Find the index of the key to be removed
    int i = 0;
    while (i < keys.size() && keys[i] < key) {
        i++;
    }

    // If the key is found in the current node
    if (i < keys.size() && keys[i] == key) {
        if (leaf) {
            // Remove the key from the leaf node
            keys.erase(keys.begin() + i);
            names.erase(names.begin() + i);
            ages.erase(ages.begin() + i);
            salaries.erase(salaries.begin() + i);
        } else {
            // Handle non-leaf nodes (this is more complex and requires further logic)
            cout << "Removing a key from a non-leaf node is not implemented yet." << endl;
        }
    } else if (!leaf) {
        // Recur to the child node
        children[i]->remove(key);
    }
}

void BTree::remove(int key) {
    if (root != nullptr) {
        root->remove(key);
        if (root->keys.empty()) {
            // If root has no keys, make the first child the new root (if it exists)
            BTreeNode* oldRoot = root;
            if (root->leaf) {
                root = nullptr;
            } else {
                root = root->children[0];
            }
            delete oldRoot;
        }
    }
}

int main() {
    BTree tree(3);
    int choice;
    int id, age;
    string name;
    float salary;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Record\n";
        cout << "2. Delete Record\n";
        cout << "3. Search Record\n";
        cout << "4. Update Record\n";
        cout << "5. Query (Sum)\n";
        cout << "6. View All Records\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Salary: ";
                cin >> salary;
                tree.insert(id, name, age, salary);
                break;
            case 2:
                cout << "Enter ID to delete: ";
                cin >> id;
                tree.remove(id);
                break;
            case 3:
                cout << "Enter ID to search: ";
                cin >> id;
                {
                    BTreeNode* result = tree.search(id);
                    if (result) {
                        cout << "Found record - ID: " << id << endl;
                    } else {
                        cout << "Record not found!" << endl;
                    }
                }
                break;
            case 4:
                cout << "Enter ID to update: ";
                cin >> id;
                cout << "Enter new Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter new Age: ";
                cin >> age;
                cout << "Enter new Salary: ";
                cin >> salary;
                tree.update(id, name, age, salary);
                break;
            case 5:
                cout << "Total Salary Sum: " << tree.querySum() << endl;
                break;
            case 6:
                tree.printAllRecords();
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, try again!" << endl;
        }
    } while (choice != 7);

    return 0;
}
