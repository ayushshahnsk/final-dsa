#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int val)
    {
        data = val;
        left = right = nullptr;
    }
};

class BST
{
private:
    Node *root;
    int count;

    Node *insert(Node *node, int val)
    {
        if (node == nullptr)
        {
            count++;
            return new Node(val);
        }
        if (val < node->data)
            node->left = insert(node->left, val);
        else
            node->right = insert(node->right, val);
        return node;
    }

    void inorder(Node *node)
    {
        if (node != nullptr)
        {
            inorder(node->left);
            cout << node->data << "\t";
            inorder(node->right);
        }
    }

    void preorder(Node *node)
    {
        if (node != nullptr)
        {
            cout << node->data << "\t";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node *node)
    {
        if (node != nullptr)
        {
            postorder(node->left);
            postorder(node->right);
            cout << node->data << "\t";
        }
    }

    int height(Node *node)
    {
        if (node == nullptr)
            return 0;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    int findMin(Node *node)
    {
        if (node == nullptr)
            return -1;
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node->data;
    }

    void mirror(Node *node)
    {
        if (node == nullptr)
            return;
        mirror(node->left);
        mirror(node->right);
        swap(node->left, node->right);
    }

    bool search(Node *node, int key)
    {
        if (node == nullptr)
            return false;
        if (node->data == key)
            return true;
        else if (key < node->data)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

public:
    BST()
    {
        root = nullptr;
        count = 0;
    }

    void insertInteractive()
    {
        char cont;
        do
        {
            int val;
            cout << "Enter value to insert: ";
            cin >> val;
            root = insert(root, val);

            cout << "Do you want to insert another node? (y/n): ";
            cin >> cont;
            cout << endl;
        } while (cont == 'y' || cont == 'Y');
    }

    void displayInorder()
    {
        cout << "\nINORDER TRAVERSAL: ";
        inorder(root);
        cout << endl;
    }

    void displayPreorder()
    {
        cout << "\nPREORDER TRAVERSAL: ";
        preorder(root);
        cout << endl;
    }

    void displayPostorder()
    {
        cout << "\nPOSTORDER TRAVERSAL: ";
        postorder(root);
        cout << endl;
    }

    void getHeight()
    {
        cout << "\nNumber of nodes in longest path (height): " << height(root) << endl;
    }

    void getMin()
    {
        int minVal = findMin(root);
        if (minVal == -1)
            cout << "\nThe tree is empty." << endl;
        else
            cout << "\nMinimum value in the tree: " << minVal << endl;
    }

    void makeMirror()
    {
        mirror(root);
        cout << "\nThe tree has been mirrored." << endl;
    }

    void searchValue()
    {
        int key;
        cout << "Enter value to search: ";
        cin >> key;
        bool found = search(root, key);
        if (found)
            cout << "Key FOUND." << endl;
        else
            cout << "Key NOT found." << endl;
    }
};

// MAIN FUNCTION (must be outside the class)
int main()
{
    BST tree;
    int choice;

    while (true)
    {
        cout << "\nMENU:\n";
        cout << "1) Insert new node(s)\n";
        cout << "2) Find number of nodes in longest path from root\n";
        cout << "3) Find minimum value\n";
        cout << "4) Mirror the tree\n";
        cout << "5) Search a value\n";
        cout << "6) Display Inorder\n";
        cout << "7) Display Preorder\n";
        cout << "8) Display Postorder\n";
        cout << "9) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
            tree.insertInteractive();
            break;
        case 2:
            tree.getHeight();
            break;
        case 3:
            tree.getMin();
            break;
        case 4:
            tree.makeMirror();
            break;
        case 5:
            tree.searchValue();
            break;
        case 6:
            tree.displayInorder();
            break;
        case 7:
            tree.displayPreorder();
            break;
        case 8:
            tree.displayPostorder();
            break;
        case 9:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}