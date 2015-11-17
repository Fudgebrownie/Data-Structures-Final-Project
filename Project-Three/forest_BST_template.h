#ifndef DATA_STRUCTURES_FINAL_PROJECT_FOREST_BST_TEMPLATE_H
#define DATA_STRUCTURES_FINAL_PROJECT_FOREST_BST_TEMPLATE_H

class BinarySearch;

class forest{
private:
    BinarySearch *tree;
    int treeroot[100];
public:
    forest();
    ~forest();
    void insert(BinarySearch *tree);
};

forest(){
    root = NULL;
    int treeroot=0;
}
~forest(){
    root = NULL;
}
void insert(BinarySearch *tree){
    for(int i = 0; i < len(tree); i++)
    {
        treeroot[i] = tree[i].root->getData();
    }

}

#endif //DATA_STRUCTURES_FINAL_PROJECT_FOREST_BST_TEMPLATE_H
