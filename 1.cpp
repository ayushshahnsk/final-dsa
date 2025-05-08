#include <iostream>
#include <string>
using namespace std;

struct Entry {
    long key;
    string name;
};

class Hashfunction {
    Entry h[10]; // Fixed-size hash table
    int count;   // To keep track of entries

public:
    Hashfunction();
    void insert();
    void remove(long);
    int find(long);
    void display();
};

Hashfunction::Hashfunction() {
    count = 0;
    for (int i = 0; i < 10; i++) {
        h[i].key = -1;
        h[i].name = "NULL";
    }
}

void Hashfunction::insert() {
    char ans;
    long k;
    string n;

    do {
        if (count >= 10) {
            cout << "\n\tHash table is FULL" << endl;
            break;
        }

        cout << "\n\tEnter a Telephone Number: ";
        cin >> k;
        cout << "\n\tEnter the Name: ";
        cin >> n;

        if (find(k) != -1) {
            cout << "\n\tKey already exists! Duplicate entry not allowed." << endl;
        } else {
            int hashindex = k % 10;
            for (int i = 0; i < 10; i++) {
                int currentIndex = (hashindex + i) % 10;
                if (h[currentIndex].key == -1) {
                    h[currentIndex].key = k;
                    h[currentIndex].name = n;
                    count++;
                    cout << "\n\tEntry inserted at index " << currentIndex << endl;
                    break;
                }
            }
        }

        cout << "\n\tDo you want to continue inserting (y/n)? ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');
}

int Hashfunction::find(long k) {
    int hashindex = k % 10;
    for (int i = 0; i < 10; i++) {
        int currentIndex = (hashindex + i) % 10;
        if (h[currentIndex].key == k) {
            cout << "\n\t" << k << " is found at index " << currentIndex << " with name " << h[currentIndex].name << endl;
            return currentIndex;
        }
        if (h[currentIndex].key == -1) {
            return -1;
        }
    }
    return -1;
}

void Hashfunction::remove(long key) {
    int index = find(key);
    if (index == -1) {
        cout << "\n\tKey not found!" << endl;
    } else {
        h[index].key = -1;
        h[index].name = "NULL";
        count--;
        cout << "\n\tKey removed successfully!" << endl;
    }
}

void Hashfunction::display() {
    cout << "\n\t\tIndex\tKey\t\tName";
    for (int i = 0; i < 10; i++) {
        cout << "\n\t\th[" << i << "]\t" << h[i].key << "\t\t" << h[i].name;
    }
    cout << endl;
}

int main() {
    Hashfunction hashTable;
    int choice;
    long key;

    do {
        cout << "\n\n==== Hash Table Menu ====";
        cout << "\n1. Insert";
        cout << "\n2. Display";
        cout << "\n3. Find";
        cout << "\n4. Remove";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            hashTable.insert();
            break;
        case 2:
            hashTable.display();
            break;
        case 3:
            cout << "\n\tEnter key to find: ";
            cin >> key;
            if (hashTable.find(key) == -1)
                cout << "\n\tKey not found!" << endl;
            break;
        case 4:
            cout << "\n\tEnter key to remove: ";
            cin >> key;
            hashTable.remove(key);
            break;
        case 5:
            cout << "\n\tExiting..." << endl;
            break;
        default:
            cout << "\n\tInvalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}