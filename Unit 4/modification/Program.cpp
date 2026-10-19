#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

int getHeight(Node* n) {
    if (n == NULL) return 0;
    return n->height;
}

int getBalanceFactor(Node* n) {
    if (n == NULL) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Traverses tree to print rows inside the table format
void printTableRows(Node* root) {
    if (root == NULL) return;
    
    printTableRows(root->left);
    printTableRows(root->right);
    
    int bf = getBalanceFactor(root);
    
    // Custom slim layout spacing for easy vertical mobile view
    cout << " " << setw(5) << root->data 
         << " | " << setw(6) << root->height 
         << " | " << setw(6) << bf << " | ";
         
    if (bf > 1 || bf < -1) {
        cout << "!! HIGHLIGHTED: CRITICAL !!" << endl;
    } else {
        cout << "BALANCED" << endl;
    }
}

// Renders diagnostic table header
void displayTable(Node* root) {
    cout << "-----------------------------------------------" << endl;
    cout << " Node  | Height |  B.F.  | Status              " << endl;
    cout << "-----------------------------------------------" << endl;
    if (root == NULL) {
        cout << "               Tree is Empty                   " << endl;
    } else {
        printTableRows(root);
    }
    cout << "-----------------------------------------------" << endl;
}

// BST Insertion that triggers an audit immediately after update completes
Node* insertNode(Node* node, int data) {
    if (node == NULL) return createNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return node;
}

Node* findMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL) current = current->left;
    return current;
}

// BST Deletion that triggers an audit immediately after structural removal completes
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = findMinValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL) return root;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    return root;
}

int main() {
    Node* root = NULL;

    cout << "\n=== STEP 1: INSERTING INITIAL NODES (40, 20, 50) ===" << endl;
    root = insertNode(root, 40);
    root = insertNode(root, 20);
    root = insertNode(root, 50);
    displayTable(root);

    cout << "\n=== STEP 2: INSERTING 10 (TRIGGERS IMBALANCE AT NODE 40) ===" << endl;
    root = insertNode(root, 10);
    displayTable(root);

    cout << "\n=== STEP 3: DELETING NODE 50 (INCREASES IMBALANCE EXTENT) ===" << endl;
    root = deleteNode(root, 50);
    displayTable(root);

    return 0;
}
