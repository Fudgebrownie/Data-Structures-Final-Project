#ifndef FOREST_H
#define FOREST_H

#include "Tree.h"

class Forest : public Tree
{
    private:
		void insertRecursive(Node* source, Node* destination);

    public:
        void addTree(Tree& tree);
};

#endif
