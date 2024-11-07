#include "csv1.hpp"
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

CSVHandler::CSVHandler(const string& filename) : filename(filename) {}

void CSVHandler::loadCSV() {
    data.clear();
    cout << ("./branch/data/" + filename) << endl;
    ifstream file("./branch/data/" + filename);

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

    cout << "Loaded successfully.\n";
    file.close();
}

void CSVHandler::displayCSV() const {
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
    if (rowNumber < 0 || rowNumber >= static_cast<int>(data.size())) {
        cerr << "Error: Invalid row number.\n";
        return;
    }
    data[rowNumber] = newRow;
}

void CSVHandler::deleteRow(int rowNumber) {
    if (rowNumber < 0 || rowNumber >= static_cast<int>(data.size())) {
        cerr << "Error: Invalid row number.\n";
        return;
    }
    data.erase(data.begin() + rowNumber);
}

void CSVHandler::saveCSV() const {
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

// Function to show a simple menu and handle user input
void CSVHandler::menu() {
    int choice;
    do {
        cout << "\n--- CSV Handler Menu ---\n";
        cout << "1. Load CSV\n";
        cout << "2. Display CSV\n";
        cout << "3. Add Row\n";
        cout << "4. Update Row\n";
        cout << "5. Delete Row\n";
        cout << "6. Save CSV\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                loadCSV();
                // cout << "CSV loaded successfully.\n";
                break;

            case 2:
                displayCSV();
                break;

            case 3: {
                vector<string> row;
                string cell;
                cout << "Enter values for new row (comma-separated): ";
                cin.ignore();
                getline(cin, cell);
                stringstream ss(cell);
                while (getline(ss, cell, ',')) {
                    row.push_back(cell);
                }
                addRow(row);
                cout << "Row added successfully.\n";
                break;
            }

            case 4: {
                int rowNumber;
                vector<string> newRow;
                string cell;
                cout << "Enter row number to update: ";
                cin >> rowNumber;
                cout << "Enter new values for the row (comma-separated): ";
                cin.ignore();
                getline(cin, cell);
                stringstream ss(cell);
                while (getline(ss, cell, ',')) {
                    newRow.push_back(cell);
                }
                updateRow(rowNumber - 1, newRow);
                cout << "Row updated successfully.\n";
                break;
            }

            case 5: {
                int rowNumber;
                cout << "Enter row number to delete: ";
                cin >> rowNumber;
                deleteRow(rowNumber - 1);
                cout << "Row deleted successfully.\n";
                break;
            }

            case 6:
                saveCSV();
                cout << "CSV saved successfully.\n";
                break;

            case 0:
                cout << "Exiting.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

int main() {
    CSVHandler csv("tab1.csv");
    csv.menu();

    return 0;
}