#include <iostream>
#include <iomanip>
#include "Tree.h"
using namespace std;


Tree::Tree()
{
    root = NULL;
}

Tree::~Tree()
{
    deleteRecursive(root);
}

void Tree::deleteRecursive(Node* node)
{
    if (node != NULL)
    {
	deleteRecursive(node->left);
	deleteRecursive(node->right);
        delete node;
    }
}


bool Tree::empty()
{
    return (root == NULL);
}

bool Tree::search(int value)
{
    // Traverse the tree starting at the root
    Node* current = root;
    while (current != NULL)
    {
	if (current->data == value)
		return true;

        if (value < current->data)
            current = current->left;
        else if (value > current->data)
            current = current->right;
    }
    
    return false;
}

void Tree::insert(int value)
{
    Node* current = root;
    Node* parent = NULL;
    while (current != NULL)
    {
	if (current->data == value)
        {
			cout << "Error: Unable to insert " << value << " because it is already in the tree." << endl;
			return;
        }   

        parent = current;
        if (value < current->data)
            current = current->left;
        else if (value > current->data)
            current = current->right;
    }

	current = new Node;
	current->data = value;
	current->left = NULL;
	current->right = NULL;

    if (parent == NULL)
        root = current;
    
    else if (value < parent->data)
          parent->left = current;
    else if (value > parent->data)
          parent->right = current;
	cout << value << " has been inserted into the tree." << endl;
}

void Tree::remove(int value)
{
	if (empty())
	{
		cout << "Error: Unable to remove " << value << " because the tree is empty." << endl;
		return;
	}

    Node* current = root;
    Node* parent = NULL;
    bool found = false;
    while (current != NULL)
    {
		if (current->data == value)
		{
			found = true;
			break;
		}
        
        parent = current;
        if (value < current->data)
            current = current->left;
        else if (value > current->data)
            current = current->right;
    }

    if (!found)
    {
		cout << "Error: Unable to remove " << value << " because it was not found in the tree." << endl;
        return;
    }
    
    if (current->left != NULL && current->right != NULL)
    {

        Node* successor = current->right;
        parent = current;
        while (successor->left != NULL)
        {
           parent = successor;
           successor = successor->left;
        }
        current->data = successor->data;
        
        current = successor;
    }
    Node* child = current->left;
    if (child == NULL)
        child = current->right;

    if (parent == NULL)
        root = child;
    
    else if (parent->left == current)
        parent->left = child;
    else
        parent->right = child;
    
    delete current;
	cout << value << " has been removed from the tree." << endl;
}

void Tree::display()
{
    if (!empty())
        displayRecursive(0, root);
    else
        cout << "The tree is currently empty." << endl;
}

void Tree::displayRecursive(int spaces, Node* node)
{
    if (node != NULL)
    {
        displayRecursive(spaces + 6, node->right);
        cout << setw(spaces) << " " << node->data << endl;
        displayRecursive(spaces + 6, node->left);
    }
}

bool Tree::checkBstProperties()
{
	return checkBstPropertiesRecursive(root);
}

bool Tree::checkBstPropertiesRecursive(Node* node)
{
	if (node == NULL || (node->left == NULL && node->right == NULL))
		return true;

	if (!checkBstPropertiesRecursive(node->left))
		return false;

	if (!checkBstPropertiesRecursive(node->right))
		return false;

	if (node->left != NULL && node->left->data > node->data)
		return false;
	if (node->right != NULL && node->right->data < node->data)
		return false;
	return true;
}

bool Tree::avlCheckBalance()
{
    return avlCheckBalanceRecursive(root);
}

void Tree::avlBalance()
{
	while (!avlCheckBalanceRecursive(root))
		avlBalanceRecursive(root, NULL, NULL);
}

bool Tree::avlCheckBalanceRecursive(Node* node)
{
    if (node == NULL)
        return true;
    
    if (!avlCheckBalanceRecursive(node->left))
        return false;
    if (!avlCheckBalanceRecursive(node->right))
        return false;
    
    int balanceFactor = avlGetSubtreeHeight(node->left) - avlGetSubtreeHeight(node->right);
    if (balanceFactor < -1 || balanceFactor > 1)
        return false;
    
    return true;
}

void Tree::avlBalanceRecursive(Node* node, Node* parent, char side)
{
    if (node == NULL)
        return;
    
    avlBalanceRecursive(node->left, node, 'L');
    avlBalanceRecursive(node->right, node, 'R');
    
    int nodeBalanceFactor = avlGetSubtreeHeight(node->left) - avlGetSubtreeHeight(node->right);
	int leftBalanceFactor, rightBalanceFactor;
	if (node->left != NULL)
		leftBalanceFactor = avlGetSubtreeHeight(node->left->left) - avlGetSubtreeHeight(node->left->right);
	else
		leftBalanceFactor = 0;
	if (node->right != NULL)
		rightBalanceFactor = avlGetSubtreeHeight(node->right->left) - avlGetSubtreeHeight(node->right->right);
	else
		rightBalanceFactor = 0;

    if (nodeBalanceFactor > 1 && leftBalanceFactor > 0)
    {
        Node* child = node->left;
        if (parent == NULL)
            root = child;
        else if (side == 'L')
            parent->left = child;
        else if (side == 'R')
            parent->right = child;
        
        node->left = child->right;
        child->right = node;
    }
    
    else if (nodeBalanceFactor < -1 && rightBalanceFactor < 0)
    {

        Node* child = node->right;
        if (parent == NULL)
            root = child;
        else if (side == 'L')
            parent->left = child;
        else if (side == 'R')
            parent->right = child;
        
        node->right = child->left;
        child->left = node;
    }
    
    else if (nodeBalanceFactor > 1)
    {

        Node* child = node->left;
        Node* grandchild = child->right;
        node->left = grandchild;
        child->right = grandchild->left;
        grandchild->left = child;
        
        if (parent == NULL)
            root = grandchild;
        else if (side == 'L')
            parent->left = grandchild;
        else if (side == 'R')
            parent->right = grandchild;
        node->left = grandchild->right;
        grandchild->right = node;
    }
    
    else if (nodeBalanceFactor < -1)
    {

        Node* child = node->right;
		Node* grandchild =child->left;
        node->right = grandchild;
        child->left = grandchild->right;
        grandchild->right = child;
        
        if (parent == NULL)
            root = grandchild;
        else if (side == 'L')
            parent->left = grandchild;
        else if (side == 'R')
            parent->right = grandchild;
        node->right = grandchild->left;
        grandchild->left = node;
    }
}

int Tree::avlGetSubtreeHeight(Node* node)
{
    int height = 0;
    if (node != NULL)
    {
        int heightL = avlGetSubtreeHeight(node->left);
        int heightR = avlGetSubtreeHeight(node->right);
        if (heightL > heightR)
            height = heightL + 1;
        else
            height = heightR + 1;
    }
    return height;
}
