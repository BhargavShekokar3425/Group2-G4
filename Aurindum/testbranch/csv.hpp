#ifndef CSV1_HPP
#define CSV1_HPP

#include <vector>
#include <string>
#include <iostream>

class CSVHandler {
private:
    std::string filename;
    std::vector<std::vector<std::string>> data;

public:
    CSVHandler(const std::string& filename);
    void loadCSV();
    void displayCSV() const;
    
    void addRow(const std::vector<std::string>& row);
    void updateRow(int rowNumber, const std::vector<std::string>& newRow);
    void deleteRow(int rowNumber);
    void saveCSV() const;
    void menu();  // New menu function for interactive mode
};

#endif // CSV1_HPP
