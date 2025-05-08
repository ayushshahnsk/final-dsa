#include <iostream>
#include <cstring>
using namespace std;

class HashFunction {
    typedef struct hash {
        long key;
        char name[10];
    } hash;

    hash h[10];

public:
    HashFunction();
    void insert();
    void Display();
    int find(long);
    void Delete(long);
};

HashFunction::HashFunction() {
    for (int i = 0; i < 10; i++) {
        h[i].key = -1;
        strcpy(h[i].name, "NULL");
    }
}

void HashFunction::Delete(long k) {
    int index = find(k);
    if (index == -1) {
        cout << "\n\tKey Not Found";
    } else {
        h[index].key = -1;
        strcpy(h[index].name, "NULL");
        cout << "\n\tKey is Deleted";
    }
}

int HashFunction::find(long k) {
    for (int i = 0; i < 10; i++) {
        if (h[i].key == k) {
            cout << "\n\t" << h[i].key << " is Found at Location " << i << " with Name " << h[i].name;
            return i;
        }
    }
    return -1;  // Key not found
}

void HashFunction::Display() {
    cout << "\n\tIndex\tKey\t\tName";
    for (int i = 0; i < 10; i++) {
        cout << "\n\th[" << i << "]\t" << h[i].key << "\t\t" << h[i].name;
    }
}

void HashFunction::insert() {
    char ans, n[10], ntemp[10];
    long k, temp;
    int hi, cnt = 0, flag = 0;

    do {
        if (cnt >= 10) {
            cout << "\n\tHash Table is FULL";
            break;
        }

        cout << "\n\tEnter a Telephone No: ";
        cin >> k;
        cout << "\n\tEnter a Client Name: ";
        cin >> n;
        hi = k % 10;

        // If home slot is empty
        if (h[hi].key == -1) {
            h[hi].key = k;
            strcpy(h[hi].name, n);
        }
        else {
            // If current key is not at its own home (replacement case)
            if (h[hi].key % 10 != hi) {
                temp = h[hi].key;
                strcpy(ntemp, h[hi].name);

                h[hi].key = k;
                strcpy(h[hi].name, n);

                flag = 0;
                for (int i = hi + 1; i < 10; i++) {
                    if (h[i].key == -1) {
                        h[i].key = temp;
                        strcpy(h[i].name, ntemp);
                        flag = 1;
                        break;
                    }
                }
                if (!flag) {
                    for (int i = 0; i < hi; i++) {
                        if (h[i].key == -1) {
                            h[i].key = temp;
                            strcpy(h[i].name, ntemp);
                            break;
                        }
                    }
                }
            }
            else {
                // Linear probing without replacement
                flag = 0;
                for (int i = hi + 1; i < 10; i++) {
                    if (h[i].key == -1) {
                        h[i].key = k;
                        strcpy(h[i].name, n);
                        flag = 1;
                        break;
                    }
                }
                if (!flag) {
                    for (int i = 0; i < hi; i++) {
                        if (h[i].key == -1) {
                            h[i].key = k;
                            strcpy(h[i].name, n);
                            break;
                        }
                    }
                }
            }
        }

        cnt++;
        cout << "\n\t....Do You Want to Insert More Keys (y/n)? ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
}

int main() {
    long k;
    int ch, index;
    char ans;
    HashFunction obj;

    do {
        cout << "\n\t**** Telephone Directory (ADT) ****";
        cout << "\n\t1. Insert\n\t2. Display\n\t3. Find\n\t4. Delete\n\t5. Exit";
        cout << "\n\tEnter Your Choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                obj.insert();
                break;

            case 2:
                obj.Display();
                break;

            case 3:
                cout << "\n\tEnter a Key to Search: ";
                cin >> k;
                index = obj.find(k);
                if (index == -1) {
                    cout << "\n\tKey Not Found";
                }
                break;

            case 4:
                cout << "\n\tEnter a Key to Delete: ";
                cin >> k;
                obj.Delete(k);
                break;

            case 5:
                cout << "\n\tExiting the Program.";
                return 0;

            default:
                cout << "\n\tInvalid Choice!";
        }

        cout << "\n\tDo You Want To Continue In Main Menu (y/n)? ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');

    return 0;
}
