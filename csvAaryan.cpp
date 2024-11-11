#include <bits/stdc++.h>
#include <iostream>
#include "csvAaryan.hpp"
#include "BTree.hpp"
#include <fstream>
#include <sstream>

using namespace std;

CSVHandler::CSVHandler(const string& filename, BTree& tree) : filename(filename), bTree(tree) {}

void CSVHandler::loadCSV() {
    data.clear();  // Clear any existing data

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    bool firstRow=true;
    while (getline(file, line)) {
        if (firstRow) {  // Skip the first row
            firstRow = false;
            continue;
        }

        int id, age;
        float sal;
        stringstream ss(line);
        string value;
        vector<string> row;

        while (getline(ss, value, ',')) {
            row.push_back(value);
        }

        stringstream(row[0]) >> id;
        stringstream(row[2]) >> age;
        stringstream(row[3]) >> sal;


        if (row.size() == 4) { // Ensure we only add valid rows
            data.push_back(row);
            bTree.insert(id, row[1], age, sal); 
            // segmentData1.push_back(attribute1); 
            // segmentData2.push_back(attribute2); 
            
        
        } else {
            cerr << "Warning: Row does not have 4 columns and will be skipped: " << line << endl;
        }
    }
    file.close();
    cout << "CSV file loaded successfully!" << endl;
}

void CSVHandler::displayCSV() const {
    for (size_t i = 0; i < data.size(); ++i) {
        cout << i << ": "; // Display row number
        for (const auto& col : data[i]) {
            cout << col << " ";
        }
        cout << endl;
    }
}

void CSVHandler::addRow(const vector<string>& row) {
    if (row.size() == 4) {
        data.push_back(row);
    } else {
        cout << "Invalid row size!" << endl;
    }
}

void CSVHandler::updateRow(int rowNumber, const vector<string>& newRow) {
    if (rowNumber >= 0 && rowNumber < data.size()) {
        if (newRow.size() == 4) {
            data[rowNumber] = newRow;
        } else {
            cout << "Invalid new row size!" << endl;
        }
    } else {
        cout << "Invalid row number!" << endl;
    }
}

void CSVHandler::deleteRow(int rowNumber) {
    if (rowNumber >= 0 && rowNumber < data.size()) {
        data.erase(data.begin() + rowNumber);
    } else {
        cout << "Invalid row number!" << endl;
    }
}

void CSVHandler::saveCSV() const {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not save file " << filename << endl;
        return;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i < row.size() - 1) {
                file << ",";
            }
        }
        file << endl;
    }

    file.close();
    cout << "CSV file saved successfully!" << endl;
}

BTree CSVHandler::loadDataIntoBTree() {
    bool firstRow = true;
    for (const auto& row : data) {
        if (firstRow) {  // Skip the first row
            firstRow = false;
            continue;
        }
        if (row.size() == 4) {
            try {
                int id = stoi(row[0]);
                string name = row[1];
                int age = stoi(row[2]);
                float salary = stof(row[3]);
                bTree.insert(id, name, age, salary);
            } catch (const invalid_argument& e) {
                cerr << "Error converting data: " << e.what() << endl;
            } catch (const out_of_range& e) {
                cerr << "Error: Data out of range: " << e.what() << endl;
            }
        }
    }
    cout << "Data loaded into BTree successfully!" << endl;
    return bTree;
}

// New function to export BTree data to csvAaryan.cpp
// void CSVHandler::exportBTreeToCPP() {
//     ofstream file("csvAaryan.cpp", ios::app); // Append mode to add to file

//     if (!file.is_open()) {
//         cerr << "Error: Could not open csvAaryan.cpp for writing" << endl;
//         return;
//     }

//     bTree.inOrderTraversal([&](int id, const string& name, int age, float salary) {
//         file << "BTree Entry: ID = " << id << ", Name = " << name
//              << ", Age = " << age << ", Salary = " << salary << endl;
//     });

//     file.close();
//     cout << "BTree data exported to csvAaryan.cpp successfully!" << endl;
// }
void CSVHandler::exportBTreeToCPP() {
    // Use the BTree's extractData function to get a list of records
    std::vector<std::tuple<int, std::string, int, float>> data = bTree.extractData();

    // Open the CSV file for writing (or overwriting)
    std::ofstream csvFile(filename);  // We are using the same filename as the CSV file to save data
    if (!csvFile.is_open()) {
        std::cerr << "Failed to open CSV file for writing." << std::endl;
        return;
    }

    // Write the header to the CSV file (optional)
    csvFile << "ID,Name,Age,Salary\n";

    // Write each record from the BTree to the CSV file
    for (const auto& record : data) {
        int id;
        std::string name;
        int age;
        float salary;
        std::tie(id, name, age, salary) = record;
        
        csvFile << id << "," << name << "," << age << "," << salary << "\n";
    }

    csvFile.close();
    std::cout << "BTree data exported to CSV file successfully!" << std::endl;
}

bool CSVHandler::filexistchk(string filename){
	ifstream bob(filename);

	if (bob.is_open()) {
		//cerr << "Error: File " << filename << "exists. Choose another name." << endl;
		return true;
	}	

	bob.close();
	return false;
	
}


void CSVHandler::menu() {
    int choice;
    do {
        cout << "\\nMenu:\\n";
        cout << "1. Load CSV\\n";
        cout << "2. Display CSV\\n";
        cout << "3. Add Row\\n";
        cout << "4. Update Row\\n";
        cout << "5. Delete Row\\n";
        cout << "6. Save CSV\\n";
        cout << "7. Load Data into BTree\\n";
        cout << "8. Export BTree to cpp\\n";
        cout << "9. Exit\\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter CSV file name: ";
                cin >> filename;
                loadCSV();
                break;
            case 2:
                displayCSV();
                break;
            case 3: {
                vector<string> newRow(4);
                cout << "Enter ID: ";
                cin >> newRow[0];
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, newRow[1]);
                cout << "Enter Age: ";
                cin >> newRow[2];
                cout << "Enter Salary: ";
                cin >> newRow[3];
                addRow(newRow);
                break;
            }
            case 4: {
                int rowNum;
                vector<string> newRow(4);
                cout << "Enter row number to update: ";
                cin >> rowNum;
                cout << "Enter new ID: ";
                cin >> newRow[0];
                cout << "Enter new Name: ";
                cin.ignore();
                getline(cin, newRow[1]);
                cout << "Enter new Age: ";
                cin >> newRow[2];
                cout << "Enter new Salary: ";
                cin >> newRow[3];
                updateRow(rowNum, newRow);
                break;
            }
            case 5: {
                int rowNum;
                cout << "Enter row number to delete: ";
                cin >> rowNum;
                deleteRow(rowNum);
                break;
            }
            case 6:
                saveCSV();
                break;
            case 7:
                loadDataIntoBTree();
                break;
            case 8:
                exportBTreeToCPP();
                break;
            case 9:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, try again!" << endl;
        }
    } while (choice != 9);
}

/*int main(){
    BTree b(4);

    string name="bhargav.csv";
    CSVHandler c(name, b);
    c.menu();

    return 0;
}*/