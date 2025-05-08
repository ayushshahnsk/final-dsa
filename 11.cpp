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

// Function to add a student record
void addStudent() {
    ofstream f("db.txt", ios::app);
    if (!f.is_open()) {
        cerr << "Error opening database file!" << endl;
        return;
    }

    string rn, name, div, add;

    cout << "Enter Student Roll No.: ";
    getline(cin >> ws, rn); // ws consumes any leading whitespace

    cout << "Enter Student Name: ";
    getline(cin, name);

    cout << "Enter Student Division: ";
    getline(cin >> ws, div);

    cout << "Enter Student Address: ";
    getline(cin, add);

    // Validate input
    if (rn.empty() || name.empty() || div.empty() || add.empty()) {
        cout << "All fields are required!\n";
        return;
    }

    f << left << setw(20) << rn
      << setw(20) << name
      << setw(20) << div
      << setw(20) << add << endl;

    f.close();
    cout << "Student Added Successfully.\n";
}

// Function to delete a student record by roll number
void deleteStudent() {
    ifstream f("db.txt");
    if (!f.is_open()) {
        cerr << "Error opening database file!" << endl;
        return;
    }

    string line, rn;
    cout << "Enter Student Roll No. To Delete: ";
    cin >> rn;

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
        string currentRn;
        ss >> currentRn;
        currentRn = trim(currentRn);

        if (currentRn == rn) {
            found = true;
        } else {
            fileData += line + "\n";
        }
    }

    f.close();

    ofstream f1("db.txt", ios::out);
    if (!f1.is_open()) {
        cerr << "Error opening database file for writing!" << endl;
        return;
    }
    f1 << fileData;
    f1.close();

    if (found)
        cout << "Student Deleted Successfully.\n";
    else
        cout << "Student Not Found.\n";
}

// Function to search for a student by roll number
void searchStudent() {
    ifstream f("db.txt");
    if (!f.is_open()) {
        cerr << "Error opening database file!" << endl;
        return;
    }

    string line, rn;
    cout << "Enter Student Roll No. To Search: ";
    cin >> rn;

    bool found = false;
    bool isHeader = true;

    while (getline(f, line)) {
        if (isHeader) {
            isHeader = false;
            continue; // Skip header
        }

        stringstream ss(line);
        string currentRn;
        ss >> currentRn;
        currentRn = trim(currentRn);

        if (currentRn == rn) {
            cout << "Student Details:\n" << line << endl;
            found = true;
            break;
        }
    }

    f.close();
    if (!found) {
        cout << "Student Doesn't Exist!\n";
    }
}

// Function to print all student records
void printStudent() {
    ifstream f("db.txt");
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
    ifstream check("db.txt");
    if (!check.is_open() || check.peek() == ifstream::traits_type::eof()) {
        check.close();
        ofstream f("db.txt", ios::out);
        if (f.is_open()) {
            f << left << setw(20) << "Roll No."
              << setw(20) << "Name"
              << setw(20) << "Division"
              << setw(20) << "Address"
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
             << "1. Add Student\n"
             << "2. Delete Student\n"
             << "3. Search Student\n"
             << "4. Print Data\n" 
             << "5. Exit\n---> " ;
        cin >> ip;
        cin.ignore(); // Clear the newline character from the buffer

        switch (ip) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                printStudent();
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