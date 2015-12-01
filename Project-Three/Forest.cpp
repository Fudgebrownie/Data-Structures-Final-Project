#include <iostream>
#include "Forest.h"
#include "Tree.h"
using namespace std;

void Forest::addTree(Tree& tree)
{
    if (tree.root == NULL)
        return;
    Node* node = new Node;
    node->data = tree.root->data;
    node->left = NULL;
    node->right = NULL;
    
    if (this->root == NULL)
        this->root = node;
    else
    {
        Node* current = this->root;
        while (current->right != NULL)
            current = current->right;
        current->right = node;
    }
    
    insertRecursive(tree.root, node);
}


void Forest::insertRecursive(Node* source, Node* destination)
{
	if (source->left != NULL && source->right != NULL)
	{
		// Create right item node
		Node* nodeR = new Node;
		nodeR->data = source->right->data;
		nodeR->left = NULL;
		nodeR->right = NULL;

		// Create left item node
		Node* nodeL = new Node;
		nodeL->data = source->left->data;
		nodeL->left = NULL;
		nodeL->right = nodeR;
		destination->left = nodeL;

		// Process children
		insertRecursive(source->left, nodeL);
		insertRecursive(source->right, nodeR);
	}

	else if (source->left != NULL)
	{
		Node* node = new Node;
		node->data = source->left->data;
		node->left = NULL;
		node->right = NULL;
		destination->left = node;
		insertRecursive(source->left, node);
	}

	else if (source->right != NULL)
	{
		Node* node = new Node;
		node->data = source->right->data;
		node->left = NULL;
		node->right = NULL;
		destination->left = node;
		insertRecursive(source->right, node);
	}
}
