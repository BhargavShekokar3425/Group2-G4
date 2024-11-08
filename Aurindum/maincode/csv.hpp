#ifndef CSV_HPP
#define CSV_HPP

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class CSVHandler {
private:
    string filename;
    vector<vector<string>> data;

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

#endif // CSV_HPP
