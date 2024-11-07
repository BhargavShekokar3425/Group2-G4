#include "csv.hpp"

CSVReader::CSVReader(const string& filename) : filename(filename) {}

vector<vector<string>> CSVReader::readCSV() {
    vector<vector<string>> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return data;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        vector<string> row;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    file.close();
    return data;
}

BTree CSVToBTreeConverter::convertToBTree(const string& filename, int degree) {
    CSVReader reader(filename);
    vector<vector<string>> data = reader.readCSV();
    BTree btree(degree);

    if (data.empty()) {
        cerr << "Error: No data found in file " << filename << endl;
        return btree;
    }

    // Assuming the first row is the header
    for (size_t i = 1; i < data.size(); ++i) {
        int key = stoi(data[i][0]);
        string name = data[i][1];
        int attribute1 = stoi(data[i][2]);
        float attribute2 = stof(data[i][3]);

        // Insert data into the BTree
        btree.insert(key, name, attribute1, attribute2);
    }

    return btree;
}
