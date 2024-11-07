#include "csv.hpp"
#include <iomanip>
#include <filesystem>
#include <sstream>

using namespace std;

CSVHandler::CSVHandler(const string& filename) : filename(filename) {}

void CSVHandler::loadCSV() {
    data.clear();
    ifstream file("data/" + filename);

    if (!file.is_open()) {
        cerr << "Error: File " << filename << " does not exist in the data folder.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    file.close();
}

void CSVHandler::displayCSV() {
    if (data.empty()) {
        cout << "No data to display.\n";
        return;
    }

    cout << "\nCSV Data:\n";
    for (const auto& row : data) {
        for (const auto& cell : row) {
            cout << setw(15) << cell;
        }
        cout << "\n";
    }
}

void CSVHandler::addRow(const vector<string>& row) {
    data.push_back(row);
}

void CSVHandler::updateRow(int rowNumber, const vector<string>& newRow) {
    if (rowNumber < 0 || rowNumber >= data.size()) {
        cerr << "Error: Invalid row number.\n";
        return;
    }
    data[rowNumber] = newRow;
}

void CSVHandler::deleteRow(int rowNumber) {
    if (rowNumber < 0 || rowNumber >= data.size()) {
        cerr << "Error: Invalid row number.\n";
        return;
    }
    data.erase(data.begin() + rowNumber);
}

void CSVHandler::saveCSV() {
    ofstream file("data/" + filename);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file for writing.\n";
        return;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
}
