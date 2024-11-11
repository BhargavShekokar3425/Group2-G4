#include <bits/stdc++.h>
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
    void updateAddAge(int key, int add);
    void updateAge(int key, int age);
    float querySum();
    void printAllRecords();
    bool isTreeEmpty();
    void printGreater(int attributes);
    void printLess(int attributes);
    void updateSalary(int key, float add);
    void updateAddSalary(int key, float salary);
    void printRange(int attributes);
    void printEqual(int attributes);
    vector<tuple<int, string, int, float>> extractData() const;
};

BTreeNode::BTreeNode(int l, bool _leaf) {
    t = l;
    leaf = _leaf;
}

bool BTree::isTreeEmpty(){
    if(root==nullptr) return true;
    return false;
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

BTree::BTree(int l) {
    root = nullptr;
    t = l;
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

void BTree::updateAddAge(int key, int add) {
    BTreeNode* node = search(key);
    if (node) {
        for (size_t i = 0; i < node->keys.size(); i++) {
            if (node->keys[i] == key) {
                //node->names[i] = name;
                node->ages[i] += add;
                //node->salaries[i] = salary;
                cout << "Record updated successfully!" << endl;
                return;
            }
        }
    }
    cout << "Record not found!" << endl;
}
void BTree::updateAge(int key, int age) {
    BTreeNode* node = search(key);
    if (node) {
        for (size_t i = 0; i < node->keys.size(); i++) {
            if (node->keys[i] == key) {
                //node->names[i] = name;
                node->ages[i] = age;
                //node->salaries[i] = salary;
                cout << "Record updated successfully!" << endl;
                return;
            }
        }
    }
    cout << "Record not found!" << endl;
}


void BTree::updateAddSalary(int key, float add) {
    BTreeNode* node = search(key);
    if (node) {
        for (size_t i = 0; i < node->keys.size(); i++) {
            if (node->keys[i] == key) {
                //node->names[i] = name;
                //node->ages[i] += add;
                node->salaries[i] += add;
                cout << "Record updated successfully!" << endl;
                return;
            }
        }
    }
    cout << "Record not found!" << endl;
}

void BTree::updateSalary(int key, float salary) {
    BTreeNode* node = search(key);
    if (node) {
        for (size_t i = 0; i < node->keys.size(); i++) {
            if (node->keys[i] == key) {
                //node->names[i] = name;
                //node->ages[i] = age;
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

void BTreeNode::collectData(vector<tuple<int, string, int, float>>& data) const {
        for (size_t i = 0; i < keys.size(); i++) {
            // Add the data for each key to the vector as a tuple
            data.emplace_back(keys[i], names[i], ages[i], salaries[i]);
        }
        // Traverse each child node, if not a leaf node
        if (!leaf) {
            for (auto child : children) {
                child->collectData(data);
            }
        }
    }

vector<tuple<int, string, int, float>> BTree::extractData() const {
        vector<tuple<int, string, int, float>> data;
        if (root) {
            root->collectData(data);
        }
        return data;
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




void BTreeNode::printRangeInorder(float lowerLimit, float upperLimit, int attribute) {
    // First recur on left child
    if (!leaf) {
        children[0]->printRangeInorder(lowerLimit, upperLimit, attribute);
    }

    // Process current node's keys
    for (size_t i = 0; i < keys.size(); i++) {
        // Check if we need to recur on child before processing current key
        if (!leaf && i < children.size() - 1) {
            children[i + 1]->printRangeInorder(lowerLimit, upperLimit, attribute);
        }

        // Check if current value is within range based on attribute
        if (attribute == 0) { // Age range
            if (ages[i] >= lowerLimit && ages[i] <= upperLimit) {
                cout << "ID: " << keys[i] 
                     << ", Name: " << names[i] 
                     << ", Age: " << ages[i] 
                     << ", Salary: " << salaries[i] << endl;
            }
        } else if (attribute == 1) { // Salary range
            if (salaries[i] >= lowerLimit && salaries[i] <= upperLimit) {
                cout << "ID: " << keys[i] 
                     << ", Name: " << names[i] 
                     << ", Age: " << ages[i] 
                     << ", Salary: " << salaries[i] << endl;
            }
        }
    }

    // Process last child if it exists
    if (!leaf && !children.empty()) {
        children[children.size() - 1]->printRangeInorder(lowerLimit, upperLimit, attribute);
    }
}

// Modified BTree::printRange implementation:
void BTree::printRange(int attributes) {
    if (!root) {
        cout << "Tree is empty!" << endl;
        return;
    }

    float lowerLimit, upperLimit;
    cout << "Enter the value for range: (lower limit, upper limit)" << endl;
    cout << "lower limit: ";
    cin >> lowerLimit;
    cout << "upper limit: ";
    cin >> upperLimit;

    if (attributes == 0) {
        cout << "\nRecords with Age between " << lowerLimit << " and " << upperLimit << ":\n";
    } else if (attributes == 1) {
        cout << "\nRecords with Salary between " << lowerLimit << " and " << upperLimit << ":\n";
    }

    root->printRangeInorder(lowerLimit, upperLimit, attributes);
}

// In BTreeNode class add these helper functions:
void BTreeNode::printGreaterInorder(float threshold, int attribute) {
    // First recur on left child
    if (!leaf) {
        children[0]->printGreaterInorder(threshold, attribute);
    }

    // Process current node's keys
    for (size_t i = 0; i < keys.size(); i++) {
        // Check child before current key
        if (!leaf && i < children.size() - 1) {
            children[i + 1]->printGreaterInorder(threshold, attribute);
        }

        // Check if current value is greater than threshold
        if (attribute == 0) { // Age
            if (ages[i] > threshold) {
                cout << "ID: " << keys[i] 
                     << ", Name: " << names[i] 
                     << ", Age: " << ages[i] 
                     << ", Salary: " << salaries[i] << endl;
            }
        } else if (attribute == 1) { // Salary
            if (salaries[i] > threshold) {
                cout << "ID: " << keys[i] 
                     << ", Name: " << names[i] 
                     << ", Age: " << ages[i] 
                     << ", Salary: " << salaries[i] << endl;
            }
        }
    }

    // Process last child if it exists
    if (!leaf && !children.empty()) {
        children[children.size() - 1]->printGreaterInorder(threshold, attribute);
    }
}

void BTreeNode::printLessInorder(float threshold, int attribute) {
    // First recur on left child
    if (!leaf) {
        children[0]->printLessInorder(threshold, attribute);
    }

    // Process current node's keys
    for (size_t i = 0; i < keys.size(); i++) {
        // Check child before current key
        if (!leaf && i < children.size() - 1) {
            children[i + 1]->printLessInorder(threshold, attribute);
        }

        // Check if current value is less than threshold
        if (attribute == 0) { // Age
            if (ages[i] < threshold) {
                cout << "ID: " << keys[i] 
                     << ", Name: " << names[i] 
                     << ", Age: " << ages[i] 
                     << ", Salary: " << salaries[i] << endl;
            }
        } else if (attribute == 1) { // Salary
            if (salaries[i] < threshold) {
                cout << "ID: " << keys[i] 
                     << ", Name: " << names[i] 
                     << ", Age: " << ages[i] 
                     << ", Salary: " << salaries[i] << endl;
            }
        }
    }

    // Process last child if it exists
    if (!leaf && !children.empty()) {
        children[children.size() - 1]->printLessInorder(threshold, attribute);
    }
}

void BTreeNode::printEqualInorder(float threshold, int attribute) {
    // First recur on left child
    if (!leaf) {
        children[0]->printEqualInorder(threshold, attribute);
    }

    // Process current node's keys
    for (size_t i = 0; i < keys.size(); i++) {
        // Check child before current key
        if (!leaf && i < children.size() - 1) {
            children[i + 1]->printEqualInorder(threshold, attribute);
        }

        // Check if current value equals threshold
        if (attribute == 0) { // Age
            if (ages[i] == threshold) {
                cout << "ID: " << keys[i] 
                     << ", Name: " << names[i] 
                     << ", Age: " << ages[i] 
                     << ", Salary: " << salaries[i] << endl;
            }
        } else if (attribute == 1) { // Salary
            if (abs(salaries[i] - threshold) < 0.001) { // Using small epsilon for float comparison
                cout << "ID: " << keys[i] 
                     << ", Name: " << names[i] 
                     << ", Age: " << ages[i] 
                     << ", Salary: " << salaries[i] << endl;
            }
        }
    }

    // Process last child if it exists
    if (!leaf && !children.empty()) {
        children[children.size() - 1]->printEqualInorder(threshold, attribute);
    }
}

// In BTree class, implement these methods:
void BTree::printGreater(int attributes) {
    if (!root) {
        cout << "Tree is empty!" << endl;
        return;
    }

    float threshold;
    cout << "Enter the threshold value: ";
    cin >> threshold;

    if (attributes == 0) {
        cout << "\nRecords with Age greater than " << threshold << ":\n";
    } else if (attributes == 1) {
        cout << "\nRecords with Salary greater than " << threshold << ":\n";
    }

    root->printGreaterInorder(threshold, attributes);
}

void BTree::printLess(int attributes) {
    if (!root) {
        cout << "Tree is empty!" << endl;
        return;
    }

    float threshold;
    cout << "Enter the threshold value: ";
    cin >> threshold;

    if (attributes == 0) {
        cout << "\nRecords with Age less than " << threshold << ":\n";
    } else if (attributes == 1) {
        cout << "\nRecords with Salary less than " << threshold << ":\n";
    }

    root->printLessInorder(threshold, attributes);
}

void BTree::printEqual(int attributes) {
    if (!root) {
        cout << "Tree is empty!" << endl;
        return;
    }

    float threshold;
    cout << "Enter the value to match: ";
    cin >> threshold;

    if (attributes == 0) {
        cout << "\nRecords with Age equal to " << threshold << ":\n";
    } else if (attributes == 1) {
        cout << "\nRecords with Salary equal to " << threshold << ":\n";
    }

    root->printEqualInorder(threshold, attributes);
}
/*
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
*/