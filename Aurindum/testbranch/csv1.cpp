#include "csv1.hpp"
#include <iomanip>
#include <sstream>
#include <fstream>
#include <regex>

using namespace std;

CSVHandler::CSVHandler(const string& filename) : filename(filename) {}

void CSVHandler::loadCSV() {
    data.clear();
    ifstream file("D:\\MyStuff\\College\\S-RAID\\GitHubRepos\\DSAGroup2-G4\\Aurindum\\testbranch\\data\\tab1.csv");

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

void CSVHandler::saveCSV() const {
    ofstream file("D:\\MyStuff\\College\\S-RAID\\GitHubRepos\\DSAGroup2-G4\\Aurindum\\testbranch\\data\\tab1.csv");

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

bool CSVHandler::isValidRow(const vector<string>& row) const {
    if (row.size() != 4) return false;

    // Check if ID is an integer
    if (!regex_match(row[0], regex("\\d+"))) return false;

    // Check if Age is an integer
    if (!regex_match(row[2], regex("\\d+"))) return false;

    // Check if Salary is a float
    if (!regex_match(row[3], regex("^[0-9]*\\.?[0-9]+$"))) return false;

    return true;
}

bool CSVHandler::isUniqueID(const string& id) const {
    for (const auto& row : data) {
        if (!row.empty() && row[0] == id) {
            return false;
        }
    }
    return true;
}

void CSVHandler::addRow(const vector<string>& row) {
    if (!isValidRow(row)) {
        cerr << "Error: Invalid data types in row. Expected format: ID[int], Name[string], Age[int], Salary[float].\n";
        return;
    }
    if (!isUniqueID(row[0])) {
        cerr << "Error: ID " << row[0] << " already exists.\n";
        return;
    }
    data.push_back(row);
    cout << "Row added successfully.\n";
}

void CSVHandler::updateRow(int rowNumber, const vector<string>& newRow) {
    if (rowNumber < 0 || rowNumber >= static_cast<int>(data.size())) {
        cerr << "Error: Invalid row number.\n";
        return;
    }
    if (!isValidRow(newRow)) {
        cerr << "Error: Invalid data types in row. Expected format: ID[int], Name[string], Age[int], Salary[float].\n";
        return;
    }
    if (newRow[0] != data[rowNumber][0] && !isUniqueID(newRow[0])) {
        cerr << "Error: ID " << newRow[0] << " already exists.\n";
        return;
    }
    data[rowNumber] = newRow;
    cout << "Row updated successfully.\n";
}


void CSVHandler::deleteRow(int rowNumber) {
    if (rowNumber < 0 || rowNumber >= static_cast<int>(data.size())) {
        cerr << "Error: Invalid row number.\n";
        return;
    }
    data.erase(data.begin() + rowNumber);
    cout << "Row deleted successfully.\n";
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
