#include <iostream>
#include "Tree.h"
#include "Forest.h"
using namespace std;

int main()
{
	const char LINE[] = "---------------------------------------------------";
	int number, value, choice;
    char another;

    // Prompt for how many trees to create
    cout << "How many BSTs do you want to create?";
    cin >> number;
	while (number < 1)
	{
		cout << "You can't have zero trees." << endl;
		cout << endl << "How many BSTs do you want to create?";
		cin >> number;
	}
        
    //Create tree object array
    Tree* trees = new Tree[number];
    
    // Loop through trees
    for (int i = 0; i < number; i++)
    {
        // Allow insertion into trees
		cout << endl << LINE << endl;
        do
        {
            // Prompt for the item to insert
            cout << endl << "Enter an integer to insert into tree " << i + 1 << ": ";
            cin >> value;
        
            // Insert the item into the tree
            trees[i].insert(value);
        
            // Ask the user if they would like to insert again
            cout << "Would you like to insert another item in tree " << i + 1 << "? (Y/N) ";
            cin >> another;
        } while (another == 'Y' || another == 'y');
        
        // Display the tree
		cout << endl << LINE << endl;
        cout << endl << "Tree " << i + 1 << " will now be displayed." << endl << endl;
        trees[i].display();
    }
    
    // Create a forest and display it
	Forest forest;
	for (int i = 0; i < number; i++)
		forest.addTree(trees[i]);
	cout << endl << LINE << endl;
	cout << endl << "A forest created from the trees will now be displayed." << endl << endl;
	forest.display();

	// Ask the user if they would like to remove an item from the tree
	cout << endl << LINE << endl;
	cout << endl << "Would you like to remove an item from a tree? (Y/N) ";
	cin >> another;

	// Prompt user to remove another item
	while (another == 'Y' || another == 'y')
	{
		// Prompt for the tree
		cout << "Which tree would you like to remove an item from? ";
		cin >> choice;

		// Make sure choice is valid
		if (choice >= 1 && choice <= number)
		{
			// Prompt for the item to remove
			cout << "Enter an integer to remove from tree " << choice << ": ";
			cin >> value;

			// Remove the item from the tree
			trees[choice - 1].remove(value);
			if (trees[choice - 1].checkBstProperties())
				cout << "The BST properties still hold." << endl;
			else
				cout << "Error: BST properties do not hold." << endl;

			// Display tree after removal
			cout << endl << LINE << endl;
			cout << endl << "Tree " << choice << " will now be displayed." << endl << endl;
			trees[choice - 1].display();
		}
		else
			cout << "You must enter a number between 1 and " << number << "." << endl;

		// Ask the user if they would like to remove again
		cout << endl << LINE << endl;
		cout << endl << "Would you like to remove another item from a tree? (Y/N) ";
		cin >> another;
	}

	// Allow the user to check for AVL trees
	cout << endl << LINE << endl << endl;
	do
	{
		// Prompt for tree
		cout << "Which tree would you want to check for AVL characteristics? ";
		cin >> choice;

		// Make sure the user entered a valid tree number
		if (choice >= 1 && choice <= number)
		{
			// Don't do anything if it is an AVL tree
			if (trees[choice - 1].avlCheckBalance())
				cout << "Tree " << choice << " is a valid AVL tree with no balancing needed." << endl;

			// Balance the tree if it isnt
			else
			{
				cout << "Tree " << choice << " is not a valid AVL tree, so it will be balanced." << endl;
				trees[choice - 1].avlBalance();
				cout << endl << LINE << endl;
				cout << endl << "Tree " << choice << " will now be displayed." << endl << endl;
				trees[choice - 1].display();
			}
		}
		else
			cout << "You must enter a number between 1 and " << number << "." << endl;

		// Ask the user if they would like to check another tree
		cout << endl << LINE << endl;
		cout << endl << "Would you like to check AVL for another tree? (Y/N) ";
		cin >> another;
	} while (another == 'Y' || another == 'y');

    // Deallocation
    delete[] trees;
	cout << endl << LINE << endl;
	cout << endl << "The tree objects have been deallocated from memory." << endl;
}
