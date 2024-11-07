#include <bits/stdc++.h>
#include <iostream>
#include "BTree.hpp"
#include "BST.hpp"  
#include "SegmentTree.hpp"
#include "CSV.hpp"
#include <queue>

using namespace std;

int main() {
    cout << "1.CREATE\n2.READ\n3.UPDATE\n4.DELETE\n";
    int crud_choice;
    cin >> crud_choice;

    // Initialize BST for database names
    BST dbNames;  // Assume this stores names as strings and includes insert/search functionality

    // CREATE operation
    if (crud_choice == 1) {
        string dbname;
        cout << "Enter Database Name: ";
        cin >> dbname;

        if (dbNames.search(dbname)) {
            cout << "Database Already Exists\n";
            return 0;
        }

        dbNames.insert(dbname);

        int degree;
        cout << "Enter Number of Attributes (3 or 4): ";
        cin >> degree;
        if (degree != 3 && degree != 4) {
            cout << "Please choose 3 or 4 attributes.\n";
            return 0;
        }

        BTree btree(degree);  // Initialize BTree with user-specified degree
        vector<string> attributes(degree);
        cout << "Enter Attribute Names:\n";
        for (int i = 0; i < degree; i++) {
            cin >> attributes[i];
        }

        vector<int> segmentData;
        while (true) {
            if (degree == 3) {
                int key, attribute1;
                string name;
                cout << "Enter Key, Name, Attribute1: ";
                cin >> key >> name >> attribute1;
                btree.insert(key, name, attribute1);
                segmentData.push_back(attribute1);
            } else if (degree == 4) {
                int key, attribute1;
                float attribute2;
                string name;
                cout << "Enter Key, Name, Attribute1, Attribute2: ";
                cin >> key >> name >> attribute1 >> attribute2;
                btree.insert(key, name, attribute1, attribute2);
                segmentData.push_back(static_cast<int>(attribute2));  // For SegmentTree integer compatibility
            }

            int choice;
            cout << "Enter 1 to add more, 0 to exit: ";
            cin >> choice;
            if (choice == 0) break;
        }

        SegmentTree segTree(segmentData);

        // Save data to CSV
        CSVToBTreeConverter converter;
        converter.saveBTreeToCSV(btree, dbname + ".csv", degree);
    }

    // READ operation
    else if (crud_choice == 2) {
        string dbname;
        cout << "Enter Database Name: ";
        cin >> dbname;

        if (!dbNames.search(dbname)) {
            cout << "Database does not exist\n";
            return 0;
        }

        CSVToBTreeConverter converter;
        BTree btree = converter.convertToBTree(dbname + ".csv", 4); // Default to degree 4
        btree.display();  // Display function to show the tree contents
    }

    // UPDATE operation
    else if (crud_choice == 3) {
        string dbname;
        cout << "Enter Database Name: ";
        cin >> dbname;

        if (!dbNames.search(dbname)) {
            cout << "Database does not exist\n";
            return 0;
        }

        CSVToBTreeConverter converter;
        BTree btree = converter.convertToBTree(dbname + ".csv", 4);

        while (true) {
            cout << "1. Name \n2. Age \n3. Salary\n";
            cout << "Enter the attribute number to update: ";
            int updateNo, key, newValue;
            cin >> updateNo;
            cout << "Enter Key: ";
            cin >> key;

            BTreeNode* node = btree.search(key);
            if (!node) {
                cout << "No such node found\n";
                return 0;
            }

            cout << "Enter new value: ";
            cin >> newValue;

            if (updateNo == 1) {
                node->name = to_string(newValue);
            } else if (updateNo == 2) {
                node->attribute1 = newValue;
            } else if (updateNo == 3) {
                node->attribute2 = static_cast<float>(newValue);
            }

            int choice;
            cout << "Update more? 1. Yes 0. No: ";
            cin >> choice;
            if (choice == 0) break;
        }

        converter.saveBTreeToCSV(btree, dbname + ".csv", 4);
    }

    // DELETE operation
    else if (crud_choice == 4) {
        string dbname;
        cout << "Enter Database Name: ";
        cin >> dbname;

        if (!dbNames.search(dbname)) {
            cout << "Database does not exist\n";
            return 0;
        }

        CSVToBTreeConverter converter;
        BTree btree = converter.convertToBTree(dbname + ".csv", 4);

        while (true) {
            cout << "Enter Key to delete: ";
            int key;
            cin >> key;

            if (!btree.search(key)) {
                cout << "Node not found\n";
                return 0;
            }

            btree.remove(key);

            int choice;
            cout << "Delete more? 1. Yes 0. No: ";
            cin >> choice;
            if (choice == 0) break;
        }

        converter.saveBTreeToCSV(btree, dbname + ".csv", 4);
    }

    return 0;
}
