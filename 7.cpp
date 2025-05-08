#include<iostream>
using namespace std;

#define INF 999

class tree {
    int a[20][20], l, u, w, i, j, v, e, visited[20];
public:
    void input();
    void display();
    void minimum();
};

void tree::input() {
    cout << "Enter the no. of branches: ";
    cin >> v;
    for (i = 0; i < v; i++) {
        visited[i] = 0;
        for (j = 0; j < v; j++) {
            a[i][j] = INF;
        }
    }

    cout << "\nEnter the no. of connections: ";
    cin >> e;

    for (i = 0; i < e; i++) {
        cout << "\nEnter the end branches of connection (1-indexed): ";
        cin >> l >> u;
        cout << "Enter the phone company charges for this connection: ";
        cin >> w;
        a[l - 1][u - 1] = a[u - 1][l - 1] = w; // zero-based indexing
    }
}

void tree::display() {
    cout << "\nAdjacency Matrix:\n";
    for (i = 0; i < v; i++) {
        for (j = 0; j < v; j++) {
            if (a[i][j] == INF)
                cout << "- ";
            else
                cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void tree::minimum() {
    int p = 0, q = 0, total = 0, min;
    visited[0] = 1;

    for (int count = 0; count < (v - 1); count++) {
        min = INF;
        for (i = 0; i < v; i++) {
            if (visited[i] == 1) {
                for (j = 0; j < v; j++) {
                    if (visited[j] != 1 && a[i][j] < min && a[i][j] != INF) {
                        min = a[i][j];
                        p = i;
                        q = j;
                    }
                }
            }
        }

        visited[q] = 1;
        total += min;
        cout << "Minimum cost connection is: Branch " << (p + 1) << " -> Branch " << (q + 1)
             << " with charge: " << min << endl;
    }
    cout << "\nThe minimum total cost to connect all branches is: " << total << endl;
}

int main() {
    int ch;
    tree t;
    do {
        cout << "\n-- PRIM'S ALGORITHM MENU --\n";
        cout << "1. INPUT\n2. DISPLAY\n3. MINIMUM\n4. EXIT\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            cout << "\n-- INPUT YOUR VALUES --\n";
            t.input();
            break;
        case 2:
            cout << "\n-- DISPLAY THE CONTENTS --\n";
            t.display();
            break;
        case 3:
            cout << "\n-- MINIMUM SPANNING TREE --\n";
            t.minimum();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (ch != 4);

    return 0;
}