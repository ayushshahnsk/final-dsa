#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cctype> // for isspace
using namespace std;

// Trim whitespace from left and right of a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

// Function to add an employee record
void addEmployee() {
    ofstream f("employee.txt", ios::app);
    if (!f.is_open()) {
        cerr << "Error opening database file!" << endl;
        return;
    }

    string id, name, designation;
    float salary;

    cout << "Enter Employee ID: ";
    getline(cin >> ws, id); // ws consumes any leading whitespace

    cout << "Enter Employee Name: ";
    getline(cin, name);

    cout << "Enter Employee Designation: ";
    getline(cin >> ws, designation);

    cout << "Enter Employee Salary: ";
    cin >> salary;

    // Validate input
    if (id.empty() || name.empty() || designation.empty()) {
        cout << "All fields are required!\n";
        return;
    }

    f << left << setw(20) << id
      << setw(30) << name
      << setw(30) << designation
      << setw(10) << salary << endl;

    f.close();
    cout << "Employee Added Successfully.\n";
}

// Function to delete an employee record by ID
void deleteEmployee() {
    ifstream f("employee.txt");
    if (!f.is_open()) {
        cerr << "Error opening database file!" << endl;
        return;
    }

    string line, id;
    cout << "Enter Employee ID to Delete: ";
    cin >> id;

    string fileData;
    bool found = false;
    bool isHeader = true;

    while (getline(f, line)) {
        if (isHeader) {
            // Always keep the header
            fileData += line + "\n";
            isHeader = false;
            continue;
        }

        stringstream ss(line);
        string currentId;
        ss >> currentId;
        currentId = trim(currentId);

        if (currentId == id) {
            found = true;
        } else {
            fileData += line + "\n";
        }
    }

    f.close();

    ofstream f1("employee.txt", ios::out);
    if (!f1.is_open()) {
        cerr << "Error opening database file for writing!" << endl;
        return;
    }
    f1 << fileData;
    f1.close();

    if (found)
        cout << "Employee Deleted Successfully.\n";
    else
        cout << "Employee Not Found.\n";
}

// Function to search for an employee by ID
void searchEmployee() {
    ifstream f("employee.txt");
    if (!f.is_open()) {
        cerr << "Error opening database file!" << endl;
        return;
    }

    string line, id;
    cout << "Enter Employee ID to Search: ";
    cin >> id;

    bool found = false;
    bool isHeader = true;

    while (getline(f, line)) {
        if (isHeader) {
            isHeader = false;
            continue; // Skip header
        }

        stringstream ss(line);
        string currentId;
        ss >> currentId;
        currentId = trim(currentId);

        if (currentId == id) {
            cout << "Employee Details:\n" << line << endl;
            found = true;
            break;
        }
    }

    f.close();
    if (!found) {
        cout << "Employee Doesn't Exist!\n";
    }
}

// Function to print all employee records
void printEmployees() {
    ifstream f("employee.txt");
    if (!f.is_open()) {
        cerr << "Error opening database file!" << endl;
        return;
    }

    string line;
    cout << "\nPrinting File Data...\n";
    while (getline(f, line)) {
        cout << line << endl;
    }
    cout << "Printing Complete!\n";
    f.close();
}

// Main function
int main() {
    // Only add headers if file doesn't exist or is empty
    ifstream check("employee.txt");
    if (!check.is_open() || check.peek() == ifstream::traits_type::eof()) {
        check.close();
        ofstream f("employee.txt", ios::out);
        if (f.is_open()) {
            f << left << setw(20) << "Employee ID"
              << setw(30) << "Name"
              << setw(30) << "Designation"
              << setw(10) << "Salary"
              << endl;
            f.close();
        } else {
            cerr << "Error creating database file!" << endl;
            return 1;
        }
    } else {
        check.close();
    }

    int ip = 0;

    while (ip != 5) {
        cout << "\nEnter your choice : \n" << endl
             << "1. Add Employee\n"
             << "2. Delete Employee\n"
             << "3. Search Employee\n"
             << "4. Print All Employees\n" 
             << "5. Exit\n---> " ;
        cin >> ip;
        cin.ignore(); // Clear the newline character from the buffer

        switch (ip) {
            case 1:
                addEmployee();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                printEmployees();
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Please Re-Enter Your Choice.\n";
                break;
        }
    }

    return 0;
}