/**********	Overall flow should be here, though function calls and variable
names will need to be changed for 2-3-4 tree.					**********/

/*JV: No changes here, aside from variable name changes.*/

#include <iostream>
using namespace std;

#include "234tree.h"

int main()
{
  //Construct tree/ test empty
  tree<int> inttree;            // test the class constructor
  cout << "Constructing empty 234 tree\n";
  cout << "234 tree " << (inttree.empty() ? "is" : "is not") << " empty\n";


  //Ask user for items to insert
  //Inser items
  //Display tree
  cout << "\nNow insert a bunch of integers into the 234 tree."
    "\nTry items not in the 234 tree and some that are in it:\n";
  int number;
  for (;;)
  {
    cout << "Item to insert (-999 to stop): ";
    cin >> number;
    if (number == -999) break;
    inttree.insert(number);
  }
  inttree.graph(cout);
  //inttree.inorder(cout);

  cout << endl;

  //Ask user for an item to delete
  //Delete item
  //Display new tree
  /*cout << "\nNow testing the remove() operation."
    "\nTry both items in the 234 tree and some not in it:\n";
  for (;;)
  {
    cout << "Item to remove (-999 to stop): ";
    cin >> number;
    if (number == -999) break;
    inttree.remove(number);
    inttree.graph(cout);
  }
  cout << "\nInorder Traversal of 234 tree: \n";
  inttree.inorder(cout);
  cout << endl;
  */
}
