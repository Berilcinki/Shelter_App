//
// Created by Beril on 6.03.2026.
//

#ifndef UNTITLED_AVLTREE_H
#define UNTITLED_AVLTREE_H
//data structure definition
struct Animal{
    char name[50], type[50], cage, gender, date[11];
    int age,donation;
    struct Animal* next;
};

struct AVLNode {
    struct Animal* data;
    struct AVLNode *left, *right;
    int height;
};

//avl tree functionalities
struct AVLNode* CreateTree(void);//Creates an empty tree
struct AVLNode* MakeEmptyTree(struct AVLNode* t);//Iterates over all the nodes inside avl tree and frees the nodes to empty the tree.
struct AVLNode* InsertAnimal(struct AVLNode* t, struct Animal* animal);//Inserts new animal by name.
struct AVLNode* SingleRotateWithRight(struct AVLNode* t);
struct AVLNode* DoubleRotateWithRight(struct AVLNode* t);
struct AVLNode* SingleRotateWithLeft(struct AVLNode* t);
struct AVLNode* DoubleRotateWithLeft(struct AVLNode* t);
struct Animal* FindNode(struct AVLNode *t, char *name);//Searches to find an animal with provided name, function returns the address of animal structure.
void DisplayTree(struct AVLNode* t);//Traverses the tree to print animals by alphabetical order.
void PrintDataDetails(struct Animal* animal);//Gets an animal structure and prints its data.
int Max(int x, int y);//Compares two integer and returns greater value.
int AVLTreeHeight(struct AVLNode* t);//Returns the height of the current node.



#endif //UNTITLED_AVLTREE_H
