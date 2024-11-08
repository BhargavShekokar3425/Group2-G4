#ifndef CSV1_HPP
#define CSV1_HPP

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class CSVHandler {
private:
    string filename;
    vector<vector<string>> data;

    // Private helper functions
    bool isValidRow(const vector<string>& row) const;
    bool isUniqueID(const string& id) const;

public:
    CSVHandler(const string& filename);
    void loadCSV();
    void displayCSV() const;

    void addRow(const vector<string>& row);
    void updateRow(int rowNumber, const vector<string>& newRow);
    void deleteRow(int rowNumber);
    void saveCSV() const;
    void menu();  // New menu function for interactive mode
};

#endif // CSV1_HPP
