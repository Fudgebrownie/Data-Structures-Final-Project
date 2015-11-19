/******	I tried to change as much as I could to fit our need for 2-3-4 tree,
though there's probably a lot we need to change here.				*****/

/*JV: Okay, I've got the code working so that the node data is stored in an
array, so I figured I'd upload what I've got. I know it's not much, but
blame the Physics homework I almost forgot to do.   */

#include <iostream>

#ifndef TWO_THREE_FOUR_TREE
#define TWO_THREE_FOUR_TREE

template <typename DataType>
class tree
{
public:
  /***** Function Members *****/
  tree();


  bool empty() const;


  bool search(const DataType & item) const;


  void insert(const DataType & item);


  void remove(const DataType & item);


  void inorder(ostream & out) const;
  /*------------------------------------------------------------------------
  Inorder traversal of BST.
  ------------------------------------------------------------------------*/

  void graph(ostream & out) const;
  /*------------------------------------------------------------------------
  Graphic output of BST.

  Precondition:  ostream out is open.
  Postcondition: Graphical representation of BST has been output to out.
  Note: graph() uses private auxiliary function graphAux().
  ------------------------------------------------------------------------*/

private:
  /***** Node class *****/
  class Node234
  {
  public:
    DataType data[3];
    Node234 * left;
    Node234 * right;
    Node234 * lmiddle;
    Node234 * rmiddle;

    Node234()
    {
      data[0] = 0;
	  data[1] = 0;
	  data[2] = 0;
      left = 0;
      right = 0;
      lmiddle = 0;
      rmiddle = 0;
    }

    Node234(DataType item, int position)
    {
	  data[0] = 0;
	  data[1] = 0;
	  data[2] = 0;
      data[position] = item;
      left = 0;
      right = 0;
      lmiddle = 0;
      rmiddle = 0;
    }
  };

  typedef Node234 * Pointer234;

  /***** Private Function Members *****/		//Not Sure if we need all of these or not
  void search2(const DataType & item, bool & found,
    Pointer234 & locptr, Pointer234 & parent) const;
  /*------------------------------------------------------------------------
  Locate a node containing item and its parent.

  Precondition:  None.
  Postcondition: locptr points to node containing item or is null if
  not found, and parent points to its parent.#include <iostream>
  ------------------------------------------------------------------------*/

  void inorderAux(ostream & out,
    Pointer234 subtreePtr) const;
  /*------------------------------------------------------------------------
  Inorder traversal auxiliary function.

  Precondition:  ostream out is open; subtreePtr points to a subtree
  of this BST.
  Postcondition: Subtree with root pointed to by subtreePtr has been
  output to out.
  ------------------------------------------------------------------------*/

  void graphAux(ostream & out, int indent,
    Pointer234 subtreeRoot) const;
  /*------------------------------------------------------------------------
  Graph auxiliary function.

  Precondition:  ostream out is open; subtreePtr points to a subtree
  of this BST.
  Postcondition: Graphical representation of subtree with root pointed
  to by subtreePtr has been output to out, indented indent spaces.
  ------------------------------------------------------------------------*/

  /***************	All of these pertain to the BST example from chptr 12 source code
  Should contain all of the data members we need, though definitions
  must be rewritten to fit 2-3-4 tree.								***************/



  /***** Data Members *****/
  Pointer234 myRoot;

}; // end of class template declaration

//--- Definition of constructor
template <typename DataType>
inline tree<DataType>::tree()
  : myRoot(0)
{}

//--- Definition of empty()
template <typename DataType>
inline bool tree<DataType>::empty() const
{
  return myRoot == 0;
}

//--- Definition of search()
template <typename DataType>
bool tree<DataType>::search(const DataType & item) const
{
  Pointer234 locptr = myRoot;
  bool found = false;
  while (!found && locptr != 0)
  {
    if (item < locptr->data[0])       // descend left
      locptr = locptr->left;
    else if (locptr->data[0] < item)  // descend right
      locptr = locptr->right;
    else                           // item found
      found = true;
  }
  return found;
}

//--- Definition of insert()
template <typename DataType>
inline void tree<DataType>::insert(const DataType & item)
{
  Pointer234
    locptr = myRoot,   // search pointer
    parent = 0,        // pointer to parent of current node
    grandparent = 0,   // pointer to grandparent of the current node
	  child = 0,
	  newNode = 0;
  int numItems = 0;
  bool found = false;     // indicates if item already in BST
  while (!found && locptr != 0)
  {
	  grandparent = parent;
    parent = locptr;
	  child = locptr;
    for (int i = 0; i < 3; i++)         //Search the node for the data, as well as find the number of items in the node
    {
      if (item == locptr->data[i])
      {
        found = true;                   // item found
      }
      else if (locptr->data[i] != 0)
      {
        numItems++;
      }
    }
	  if (numItems == 3)                  //Upon encountering  a full node, split it
	  {
      newNode = new Node234(locptr->data[2], 0);
  	  locptr->data[2] = 0;
	    if (grandparent == 0)             //If the current node is the root
	    {
        grandparent = new Node234(locptr->data[1], 0);
		    myRoot = grandparent;
        grandparent->left = locptr;
        locptr->data[1] = 0;
	    }
	    else
	    {
        grandparent->data[1] = locptr->data[1];
		    locptr->data[1] = 0;
	    }
	    grandparent->lmiddle = newNode;
	    newNode->left = locptr->rmiddle;
	    newNode->lmiddle = locptr->right;
	    locptr->rmiddle = 0;
	    locptr->right = 0;
	    child = newNode->left;
	    if(item < locptr->data[0])
	    {
        locptr = locptr->left;
	    }
	    else if (item > newNode->data[0])
	    {
        parent = newNode;
        locptr = newNode->lmiddle;
	    }
	    else if (item > grandparent->data[0])
	    {
        parent = newNode;
        locptr = newNode->left;
	    }
	    else
	    {
        locptr = locptr->lmiddle;
	    }
	  }
    else if (numItems == 1)
    {
      if (item < locptr->data[0])       // descend left
      {
        locptr = locptr->left;
      }
      else                              // descend left-middle
      {
        locptr = locptr->lmiddle;
      }
    }
    else if (numItems == 2)
    {
      if (item < locptr->data[0])       // descend left
      {
        locptr = locptr->left;
      }
      else if (item < locptr->data[1])  // descend left-middle
      {
        locptr = locptr->lmiddle;
      }
      else                              // descend right-middle
      {
        locptr = locptr->rmiddle;
      }
    }
  }
  if (!found)
  {                                   // Add item to tree
    if (numItems == 0)                //If no nodes exist
    {
      locptr = new Node234(item, 0);
      myRoot = locptr;
    }
    else
    {
      numItems = 0;
      for (int i = 0; i < 3; i++)     //Count the number of items in the current node
      {
        if (parent->data[i] != 0)
        {
          numItems++;
        }
      }
      if (numItems == 2)              //If 2
      {
        if (item < parent->data[0])
        {
          parent->data[2] = parent->data[1];
          parent->data[1] = parent->data[0];
          parent->data[0] = item;
        }
        else if (item < parent->data[1])
        {
          parent->data[2] = parent->data[1];
          parent->data[1] = item;
        }
        else
        {
          parent->data[2] = item;
        }
      }
      else                            //If 1
      {
        if (item < parent->data[0])
        {
          parent->data[1] = parent->data[0];
          parent->data[0] = item;
        }
        else
        {
          parent->data[1] = item;
        }
      }
    }
  }
  else
  {
    cout << "Item already in the tree\n";
  }
}

//--- Definition of remove()
template <typename DataType>
void tree<DataType>::remove(const DataType & item)
{
  bool found;                      // signals if item is found
  Pointer234
    x,                            // points to node to be deleted
    parent;                       //    "    " parent of x and xSucc
  search2(item, found, x, parent);

  if (!found)
  {
    cout << "Item not in the BST\n";
    return;
  }
  //else
  if (x->left != 0 && x->right != 0)
  {                                // node has 2 children
    // Find x's inorder successor and its parent
    Pointer234 xSucc = x->right;
    parent = x;
    while (xSucc->left != 0)       // descend left
    {
      parent = xSucc;
      xSucc = xSucc->left;
    }

    // Move contents of xSucc to x and change x 
    // to point to successor, which will be removed.
    x->data[0] = xSucc->data[0];
    x = xSucc;
  } // end if node has 2 children

  // Now proceed with case where node has 0 or 2 child
  Pointer234
    subtree = x->left;             // pointer to a subtree of x
  if (subtree == 0)
    subtree = x->right;
  if (parent == 0)                  // root being removed
    myRoot = subtree;
  else if (parent->left == x)       // left child of parent
    parent->left = subtree;
  else                              // right child of parent
    parent->right = subtree;
  delete x;
}

//--- Definition of inorder()
template <typename DataType>
inline void tree<DataType>::inorder(ostream & out) const
{
  inorderAux(out, myRoot);
}

//--- Definition of graph()
template <typename DataType>
inline void tree<DataType>::graph(ostream & out) const
{
  graphAux(out, 0, myRoot);
}

//--- Definition of search2()
template <typename DataType>
void tree<DataType>::search2(const DataType & item, bool & found,
  Pointer234 & locptr,
  Pointer234 & parent) const
{
  locptr = myRoot;
  parent = 0;
  found = false;
  while (!found && locptr != 0)
  {
    if (item < locptr->data[0])       // descend left
    {
      parent = locptr;
      locptr = locptr->left;
    }
    else if (locptr->data[0] < item)  // descend right
    {
      parent = locptr;
      locptr = locptr->right;
    }
    else                           // item found
      found = true;
  }
}

//--- Definition of inorderAux()
template <typename DataType>
void tree<DataType>::inorderAux(ostream & out,
  Pointer234 subtreeRoot) const
{
  if (subtreeRoot != 0)
  {
    inorderAux(out, subtreeRoot->left);    // L operation
    out << subtreeRoot->data[0] << "  ";      // V operation
    inorderAux(out, subtreeRoot->right);   // R operation
  }
}

//--- Definition of graphAux()
#include <iomanip>

template <typename DataType>
void tree<DataType>::graphAux(ostream & out, int indent,
  Pointer234 subtreeRoot) const
{
  if (subtreeRoot != 0)
  {
    graphAux(out, indent + 8, subtreeRoot->right);
    out << setw(indent) << " " << subtreeRoot->data[0] << " " << subtreeRoot->data[1] << " " << subtreeRoot->data[2] << endl;
    graphAux(out, indent + 8, subtreeRoot->left);
  }
}

#endif
