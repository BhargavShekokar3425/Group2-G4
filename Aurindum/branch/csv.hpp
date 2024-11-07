#ifndef CSV_HPP
#define CSV_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "BTree.hpp"

using namespace std;

class CSVReader {
public:
    CSVReader(const string& filename);
    vector<vector<string>> readCSV();

private:
    string filename;
};

class CSVToBTreeConverter {
public:
    BTree convertToBTree(const string& filename, int degree);
};

#endif
