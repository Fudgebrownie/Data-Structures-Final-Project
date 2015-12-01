#ifndef TREE_H
#define TREE_H

class Tree
{
	friend class Forest;

    protected:
		struct Node
		{
			int data;
			Node* left;
      Node* right;
		};
		Node* root;
		void deleteRecursive(Node* node);
		void displayRecursive(int spaces, Node* node);
		bool checkBstPropertiesRecursive(Node* node);
    bool avlCheckBalanceRecursive(Node* node);
    void avlBalanceRecursive(Node* node, Node* parent, char side);
    int avlGetSubtreeHeight(Node* node);

	public:
		Tree();
    ~Tree();
    bool empty();
    bool search(int value);
    void insert(int value);
    void remove(int value);
    void display();
		bool checkBstProperties();
    bool avlCheckBalance();
    void avlBalance();
};

#endif
