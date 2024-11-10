#ifndef CSV_HPP
#define CSV_HPP

#include<bits/stdc++.h>
#include "BTree.hpp"  // Include the BTree class

using namespace std;

class CSVHandler {
private:
    string filename;
    vector<vector<string>> data;
    BTree& bTree;  // Reference to BTree object

public:
    CSVHandler(const string& filename, BTree& tree);
    void loadCSV();
    void displayCSV() const;
    void addRow(const vector<string>& row);
    void updateRow(int rowNumber, const vector<string>& newRow);
    void deleteRow(int rowNumber);
    void saveCSV() const;
    void loadDataIntoBTree();  // Load the data from CSV into the BTree
    void exportBTreeToCPP();   // New function to export BTree data to cpp
    void menu();  // Menu function for interactive mode
};

#endif // CSV_HPP