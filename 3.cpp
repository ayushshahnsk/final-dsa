#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    string label;
    vector<Node*> children;
};

class GT {
    Node* root;

public:
    GT() : root(nullptr) {}

    void create_tree() {
        root = new Node;
        int tchapter;
        cout << "Enter name of book: ";
        cin >> root->label;
        cout << "Enter number of chapters in book: ";
        cin >> tchapter;

        for (int i = 0; i < tchapter; ++i) {
            Node* chapter = new Node;
            cout << "Enter chapter name: ";
            cin >> chapter->label;
            int sections;
            cout << "Enter number of sections in Chapter " << chapter->label << ": ";
            cin >> sections;

            for (int j = 0; j < sections; ++j) {
                Node* section = new Node;
                cout << "Enter section " << j + 1 << " name: ";
                cin >> section->label;
                chapter->children.push_back(section);
            }

            root->children.push_back(chapter);
        }
    }

    void display() {
        if (!root) {
            cout << "Tree is empty.\n";
            return;
        }

        cout << "\n...Book Hierarchy>>>>";
        cout << "\nBook title: " << root->label;

        for (size_t i = 0; i < root->children.size(); ++i) {
            Node* chapter = root->children[i];
            cout << "\nChapter " << i + 1 << ": " << chapter->label;
            cout << "\nSections:";
            for (size_t j = 0; j < chapter->children.size(); ++j) {
                cout << "\n  " << chapter->children[j]->label;
            }
        }
    }

    ~GT() {
        clear(root);
    }

private:
    void clear(Node* node) {
        if (!node) return;
        for (Node* child : node->children) {
            clear(child);
        }
        delete node;
    }
};

int main() {
    int choice;
    GT gt;

    while (true) {
        cout << "\n..........................\n";
        cout << "Book Tree Creation\n1. Create\n2. Display\n3. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                gt.create_tree();
                break;
            case 2:
                gt.display();
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Wrong choice\n";
        }
    }
}
