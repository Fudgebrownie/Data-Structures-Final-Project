#include <iostream>
#include "forest_BST_template.h"
#include "BinarySearch.h"
using namespace std;


void main (void) {
    int num_bsts = 0;
    int what_you_want = 0;
    cout << "How many BSTs would you like to create?" << endl;
    cin >> num_bsts;

    BinarySearchTree* trees = new BinarySearchTree[num_bsts]
    for(int i = 0; i < num_bsts; i++)
    {
        cout << "Please enter values in array #" << i << ": ";
        while(true) {
            cin >> what_you_want;
            if (what_you_want == -999)
                break;
            trees[i].insert(what_you_want);
        }
    }

}
