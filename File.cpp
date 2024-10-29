#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Employee {
    int id;
    int salary;
    string name;
    string position;
    string department;
};

// CSV Handler class for reading, writing, and saving data
class CSVHandler {
private:
    string filename;

public:
    CSVHandler(const string& fname) : filename(fname) {}

    // Function to read data from the CSV file
    vector<Employee> readData() {
        vector<Employee> data;
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return data;
        }

        string line;
        getline(file, line); // Skip header line

        while (getline(file, line)) {
            stringstream ss(line);
            string item;
            Employee emp;

            getline(ss, item, ','); emp.id = stoi(item);
            getline(ss, item, ','); emp.salary = stoi(item);
            getline(ss, item, ','); emp.name = item;
            getline(ss, item, ','); emp.position = item;
            getline(ss, item, ','); emp.department = item;

            data.push_back(emp);
        }
        file.close();
        return data;
    }

    // Function to save data to the CSV file
    void saveData(const vector<Employee>& data) {
        ofstream file(filename);

        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        // Write header
        file << "ID,Salary,Name,Position,Department\n";

        // Write employee data
        for (const auto& emp : data) {
            file << emp.id << ',' << emp.salary << ',' << emp.name << ','
                 << emp.position << ',' << emp.department << '\n';
        }
        file.close();
    }

    // Function to add a new employee record to the CSV file
    void addRecord(const Employee& emp) {
        ofstream file(filename, ios::app);

        if (!file.is_open()) {
            cerr << "Error: Could not open file " << filename << endl;
            return;
        }

        file << emp.id << ',' << emp.salary << ',' << emp.name << ','
             << emp.position << ',' << emp.department << '\n';
        file.close();
    }
};

int main() {
    string filename = "employees.csv";
    CSVHandler csvHandler(filename);

    // Read data from CSV
    vector<Employee> employees = csvHandler.readData();

    // Example: Display employee data
    for (const auto& emp : employees) {
        cout << "ID: " << emp.id << ", Salary: " << emp.salary
             << ", Name: " << emp.name << ", Position: " << emp.position
             << ", Department: " << emp.department << endl;
    }

    // Example: Adding a new employee
    Employee newEmployee = {101, 70000, "Alice Smith", "Engineer", "IT"};
    csvHandler.addRecord(newEmployee);

    // Example: Saving data back to CSV after modifying
    employees.push_back(newEmployee);
    csvHandler.saveData(employees);

    return 0;
}
