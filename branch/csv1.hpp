#ifndef CSV1_HPP
#define CSV1_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class CSVHandler {
public:
    CSVHandler(const string& filename);
    void loadCSV();
    void displayCSV();
    void addRow(const vector<string>& row);
    void updateRow(int rowNumber, const vector<string>& newRow);
    void deleteRow(int rowNumber);
    void saveCSV();

private:
    string filename;
    vector<vector<string>> data;
};

#endif // CSV_HPP
