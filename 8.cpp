#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

const int MAX = 20;
float p[MAX], q[MAX];           // p: success probabilities, q: failure probabilities
float wt[MAX][MAX], cost[MAX][MAX];
int root[MAX][MAX];
int n;

void buildOBST() {
    for (int i = 0; i <= n; i++) {
        wt[i][i] = q[i];
        cost[i][i] = 0;
        root[i][i] = 0;

        wt[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
        cost[i][i + 1] = wt[i][i + 1];
        root[i][i + 1] = i + 1;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len;
            wt[i][j] = wt[i][j - 1] + p[j] + q[j];
            cost[i][j] = INT_MAX;

            for (int rIndex = i + 1; rIndex <= j; rIndex++) {
                float t = cost[i][rIndex - 1] + cost[rIndex][j] + wt[i][j];
                if (t < cost[i][j]) {
                    cost[i][j] = t;
                    root[i][j] = rIndex;
                }
            }
        }
    }

    cout << "\nOptimal BST Cost: " << cost[0][n] << endl;
    cout << "Root of OBST: " << root[0][n] << endl;
}

void printTree(int i, int j, int parent, bool isLeft) {
    if (i >= j) return;

    int r = root[i][j];
    if (parent == -1)
        cout << "Root: k" << r << endl;
    else if (isLeft)
        cout << "Left child of k" << parent << " is k" << r << endl;
    else
        cout << "Right child of k" << parent << " is k" << r << endl;

    printTree(i, r - 1, r, true);
    printTree(r, j, r, false);
}

int main() {
    cout << "**** Optimal Binary Search Tree (OBST) ****\n";
    cout << "Enter number of keys: ";
    cin >> n;

    cout << "\nEnter probabilities of successful search (p1 to p" << n << "):\n";
    for (int i = 1; i <= n; i++) {
        cout << "p[" << i << "]: ";
        cin >> p[i];
    }

    cout << "\nEnter probabilities of unsuccessful search (q0 to q" << n << "):\n";
    for (int i = 0; i <= n; i++) {
        cout << "q[" << i << "]: ";
        cin >> q[i];
    }

    buildOBST();

    cout << "\nBinary Search Tree Structure:\n";
    printTree(0, n, -1, false);

    return 0;
}