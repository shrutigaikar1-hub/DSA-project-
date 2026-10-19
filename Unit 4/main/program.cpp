#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

// Returns the height of a node
int getHeight(Node* n) {
    if (n == NULL) return 0;
    return n->height;
}

// Allocates a new node structure
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; 
    return newNode;
}

// Evaluates the balance factor of a targeted node
int getBalanceFactor(Node* n) {
    if (n == NULL) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// Regular BST Insertion (Without Rotations to show Unbalanced Nodes)
Node* insertNode(Node* node, int data) {
    if (node == NULL) return createNode(data);

    if (data < node->data) {
        node->left = insertNode(node->left, data);
    } else if (data > node->data) {
        node->right = insertNode(node->right, data);
    } else {
        return node;
    }

    // Update parent node height calculation bounds
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return node;
}

// Scans tree infrastructure to calculate balance profiles and expose violations
void checkTreeBalance(Node* root) {
    if (root == NULL) return;

    // Post-order processing pass sequence
    checkTreeBalance(root->left);
    checkTreeBalance(root->right);

    int leftH = getHeight(root->left);
    int rightH = getHeight(root->right);
    int bf = getBalanceFactor(root);

    cout << "Node: " << root->data 
         << " | Height: " << root->height
         << " | Balance Factor: " << bf;

    // Evaluation rule baseline check
    if (bf > 1 || bf < -1) {
        cout << " -> [CRITICAL WARNING: UNBALANCED NODE]";
    } else {
        cout << " -> [BALANCED]";
    }
    cout << endl;
}

int main() {
    Node* root = NULL;

    cout << "--- Inserting Skewed Sequence (30, 20, 10, 40) ---" << endl;
    root = insertNode(root, 30);
    root = insertNode(root, 20);
    root = insertNode(root, 10); // Deliberately creates left imbalance at node 30
    root = insertNode(root, 40);

    cout << "\n--- Full Operational Node Balance Verification ---" << endl;
    checkTreeBalance(root);

    return 0;
}
