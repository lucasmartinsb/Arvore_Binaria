// C++ program to implement Tree Sort
#include<bits/stdc++.h>
  
using namespace std;
  
struct Node
{
    string key;
    struct Node *left, *right;
};
  
// A utility function to create a new BST Node
struct Node *newNode(string item)
{
    struct Node *temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
  
// Stores inorder traversal of the BST
// in arr[]
void storeSorted(Node *root, string arr[], int &i)
{
    if (root != NULL)
    {
        storeSorted(root->left, arr, i);
        arr[i++] = root->key;
        storeSorted(root->right, arr, i);
    }
}
  
/* A utility function to insert a new
   Node with given key in BST */
Node* insert(Node* node, string key)
{
    /* If the tree is empty, return a new Node */
    if (node == NULL) return newNode(key);
  
    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
  
    /* return the (unchanged) Node pointer */
    return node;
}
  
// This function sorts arr[0..n-1] using Tree Sort
void treeSort(string arr[], int n)
{
    struct Node *root = NULL;
  
    // Construct the BST
    root = insert(root, arr[0]);
    for (int i=1; i<n; i++)
        root = insert(root, arr[i]);
  
    // Store inorder traversal of the BST
    // in arr[]
    int i = 0;
    storeSorted(root, arr, i);
}
  
// Driver Program to test above functions
int main()
{
    //create input array
    string arr[] = {"bola", "abelha", "caralho", "dado", "acre"};
    int n = sizeof(arr)/sizeof(arr[0]);
  
    treeSort(arr, n);
  
        for (int i=0; i<n; i++)
       cout << arr[i] << " ";
  
    return 0;
}