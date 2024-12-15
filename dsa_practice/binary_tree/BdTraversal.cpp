#include <iostream>
using namespace std;


struct Node {
    int data;
    struct Node *left, *right;
};

Node* newNode(int data)
{
    Node* temp = new Node;
    temp->data = data;
    temp->left = temp->right = nullptr;
    return temp;
}

void printLeaves(Node* root)
{
    if (root == nullptr)
        return;

    printLeaves(root->left);

    // Print it if it is a leaf node
    if (!(root->left) && !(root->right))
        cout << root->data << " ";

    printLeaves(root->right);
}


void printBoundaryLeft(Node* root)
{
    if (root == nullptr)
        return;

    if (root->left) {

        // to ensure top down order, print the node
        // before calling itself for left subtree
        cout << root->data << " ";
        printBoundaryLeft(root->left);
    }
    else if (root->right) {
        cout << root->data << " ";
        printBoundaryLeft(root->right);
    }
    // do nothing if it is a leaf node, this way we avoid
    // duplicates in output
}


void printBoundaryRight(Node* root)
{
    if (root == nullptr)
        return;

    if (root->right) {
        // to ensure bottom up order, first call for right
        // subtree, then print this node
        printBoundaryRight(root->right);
        cout << root->data << " ";
    }
    else if (root->left) {
        printBoundaryRight(root->left);
        cout << root->data << " ";
    }
    // do nothing if it is a leaf node, this way we avoid
    // duplicates in output
}

void printBoundary(Node* root)
{
    if (root == nullptr)
        return;

    cout << root->data << " ";

    // Print the left boundary in top-down manner.
    printBoundaryLeft(root->left);

    // Print all leaf nodes
    printLeaves(root->left);
    printLeaves(root->right);

    // Print the right boundary in bottom-up manner
    printBoundaryRight(root->right);
}

int main()
{
    // Let us construct the tree given in the above diagram
    Node* root = newNode(20);
    root->left = newNode(8);
    root->left->left = newNode(4);
    root->left->right = newNode(12);
    root->left->right->left = newNode(10);
    root->left->right->right = newNode(14);
    root->right = newNode(22);
    root->right->right = newNode(25);

    printBoundary(root);

    return 0;
}


