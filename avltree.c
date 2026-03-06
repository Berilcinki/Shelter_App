#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"


struct AVLNode* CreateTree(void){
    return NULL;
}

struct AVLNode* MakeEmptyTree(struct AVLNode* t)
{
    if (t != NULL)
    {
        MakeEmptyTree(t->left);
        MakeEmptyTree(t->right);
        free(t);
    }
    return NULL;
}

struct AVLNode* InsertAnimal(struct AVLNode* t, struct Animal* animal) {
    if (t == NULL) {

        /*Create and return a one-node tree */

        t = malloc(sizeof(struct AVLNode));
        if (t == NULL) {
            printf("Out of memory space!!!\n");
            return NULL;
        }
        t->data = animal;
        t->height = 0;
        t->left = t->right = NULL;
    }
    else if (strcmp(animal->name, t->data->name) < 0) {
        //Left subtree
        t->left = InsertAnimal(t->left, animal);
        if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2) {
            if (strcmp(animal->name, t->left->data->name) < 0)
                t = SingleRotateWithRight(t);
            else
                t = DoubleRotateWithLeft(t);
        }
    }
    else if (strcmp(animal->name, t->data->name) > 0) {
        // Right subtree
        t->right = InsertAnimal(t->right, animal);
        if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2) {
            if (strcmp(animal->name, t->right->data->name) > 0)
                t = SingleRotateWithLeft(t);
            else
                t = DoubleRotateWithRight(t);
        }
    }
    /* else val is in the tree already ... do nothing */
    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;

    return t;
}


//right rotation
struct AVLNode*  SingleRotateWithRight(struct AVLNode*  k2)
{
    struct AVLNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) + 1;
    k1->height = Max(AVLTreeHeight(k1->left), k2->height) + 1;
    return k1;
}

//left rotation
struct AVLNode*  SingleRotateWithLeft(struct AVLNode*  k1)
{
    struct AVLNode* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) + 1;
    k2->height = Max(AVLTreeHeight(k2->right), k1->height) + 1;
    return k2;
}

//left and right rotation
struct AVLNode*  DoubleRotateWithLeft(struct AVLNode*  k3)
{
    k3->left = SingleRotateWithLeft(k3->left);
    return SingleRotateWithRight(k3);
}

// right and left rotation
struct AVLNode*  DoubleRotateWithRight(struct AVLNode* k3)
{
    k3->right = SingleRotateWithRight(k3->right);
    return SingleRotateWithLeft(k3);
}

int Max(int x, int y)
{
    if (x >= y)
        return x;
    else
        return y;

}

int AVLTreeHeight(struct AVLNode* t)
{
    if (t == NULL)
        return -1;
    else
        return t->height;

}

void DisplayTree(struct AVLNode* t)
{

    if (t != NULL)
    {
        DisplayTree(t->left);
        printf("%d\n", t->data);
        DisplayTree(t->right);
    }

}

void PrintDataDetails(struct Animal* animal){
    if (animal == NULL) return;
    printf("Name: %s\n", animal->name);
    printf("Type: %s\n", animal->type);
    printf("Gender: %c\n", animal->gender);
    printf("Cage: %c\n", animal->cage);
    printf("Date: %s\n", animal->date);
    printf("Age: %d\n", animal->age);
    printf("Donation: %d\n", animal->donation);
}

struct Animal* FindNode(struct AVLNode *t, char *name){

    if (t == NULL)
        return NULL;
    int value = strcmp(name, t->data->name);
    if (value == 0)
        return t->data;
    else if (value < 0)
        return FindNode(t->left, name);
    else
        return FindNode(t->right, name);
}