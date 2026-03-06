#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"


struct AVLNode* loadAnimals(char *fileName);
struct AVLNode* insertAnimal(struct AVLNode* t, char *name, char *type, char cage, char gender, char *date, int age, int donation);
void infoAnimal(struct AVLNode* t, char *name);
void displayAnimals(struct AVLNode* t);
struct Animal* findPopularDonation(struct AVLNode* t);
void popularAnimal(struct AVLNode* t, struct Animal* highestDonationAnimal);

int main (int argc, char **argv){

    struct AVLNode* myTree;
    int menuOption, flag = 1;

    if(argc == 1){
        printf("Please provide a file name: ");
        return 0;
    }

    myTree = loadAnimals(argv[1]);

    printf("Welcome to data analysis @ Animal Shelter\n");

    while (flag){
        printf("\n-------Menu-------\n"
               "(1)Insert animal\n"
               "(2)Display the full index of animals\n"
               "(3)Display the details of the animals\n"
               "(4)Display the popular animal\n"
               "(5)Exit\n"
               "Enter your option:");
        scanf("%d", &menuOption);

        switch (menuOption) {

            case 1:{
                char name[50], type[50], cage, gender, date[11];
                int age, donation;

                printf("Please enter animal details:\n");
                printf("Name:");
                scanf(" %s", name);
                printf("Type:");
                scanf(" %s", type);
                printf("Cage:");
                scanf(" %c", &cage);
                printf("Gender:");
                scanf(" %c",&gender);
                printf("Date:");
                scanf(" %s",date);
                printf("Age:");
                scanf("%d",&age);
                printf("Donation:");
                scanf("%d",&donation);
                myTree = insertAnimal(myTree, name, type, cage, gender, date, age, donation);
                printf("%s %s has been added successfully.\n", type, name);
                break;
            }
            case 2:{
                displayAnimals(myTree);
                break;
            }
            case 3:{
                char name[30];
                printf("Name: ");
                scanf(" %s", name);
                infoAnimal(myTree,name);
                break;
            }
            case 4:{
                printf("Detailed information of the most popular animal: \n");
                popularAnimal(myTree, findPopularDonation(myTree));
                break;
            }
            case 5: {
                flag = 0;
                break;
            }
            default:{
                printf("Option %d can't be recognized.", menuOption);
            }
        }
    }

    myTree= MakeEmptyTree(myTree);
    return 0;
}

struct AVLNode* insertAnimal(struct AVLNode* t, char *name, char *type, char cage, char gender, char *date, int age, int donation) {

    struct Animal *curr = NULL;
    //Creating a new animal and adding the details
    struct Animal *newAnimal = malloc(sizeof(struct Animal));

    if (newAnimal == NULL) {
        printf("Memory allocation failed.\n");
        return t;
    }

    strcpy(newAnimal->name, name);
    strcpy(newAnimal->type, type);
    newAnimal->cage = cage;
    newAnimal->gender = gender;
    strcpy(newAnimal->date, date);
    newAnimal->age = age;
    newAnimal->donation = donation;
    newAnimal->next = NULL;

    // Adding to a Avl Tree

    t = InsertAnimal(t, newAnimal);

    if (strcmp(newAnimal->name, t->data->name) == 0) // If we have a data that have the same name add it to the node
    {

            struct Animal* curr = t->data;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = newAnimal;
            return t;
        }


    return t;
}





struct AVLNode* loadAnimals(char *fileName){

        char text[300];
        char name[50], type[50], cage, gender, date[11];
        int age,donation;
        struct AVLNode* tree = NULL;

        FILE* inFile = fopen(fileName, "r");
        if (inFile == NULL) {
            printf("Error opening file: %s\n", fileName);
            return NULL;
        }

        fgets(text, sizeof(text), inFile);


        while (fgets(text, sizeof(text), inFile)) {



            sscanf(text, "%[^;];%[^;];%c;%d;%c;%[^;];%d", name,type,gender,age,cage,date,donation);
            tree = insertAnimal(tree,name,type,cage, gender, date,age,donation);
        }

        fclose(inFile);
        return tree;
    }



void displayAnimals(struct AVLNode* t) {

    if (t == NULL) return;

    // Traverse left subtree
    displayAnimals(t->left);

    // Print all animals with the same name
    struct Animal *current = t->data;
    while (current != NULL) {
        PrintDataDetails(current);
        printf("----------------------\n");
        current = current->next;
    }

    // Traverse right subtree
    displayAnimals(t->right);
}


void infoAnimal(struct AVLNode* t, char *name){

    struct AVLNode *tree = t;
    struct Animal* found = FindNode(t, name);

        if (found == NULL) {
            printf("No animal with the name '%s' found in the shelter.\n", name);
            return;
        }

        // Print all animals with the same name using linked list
        while (found != NULL) {
            PrintDataDetails(found);
            printf("----------------------\n");
            found = found->next;
        }
    }

/*
 * For Time Complexity :
 *
 * The worst-case time complexity is :  O(log n) ( where n is the number of unique animal names in the tree).
 * After finding the matching name, we have a linked list of animals with the same name. Let m be the number of animals with that  specific name. Printing them takes O(m) time.
 * => Total Time Complexity: O(log n + m)
 *
 * Potential Improvement:

 * -   We could store the duplicates in another balanced tree (BST or AVL) or a dynamic array for faster access.
 */



struct Animal* findPopularDonation(struct AVLNode* t) {

        if (t == NULL) return NULL;

        struct Animal* leftMax = findPopularDonation(t->left);
        struct Animal* rightMax = findPopularDonation(t->right);

        struct Animal* curr = t->data;
        struct Animal* maxAnimal = NULL;
        int maxDonation = 0;

        // Finding the maximum

        while (curr != NULL) {
            if (curr->donation > maxDonation) {
                maxDonation = curr->donation;
                maxAnimal = curr;
            }
            curr = curr->next;
        }

        // Checking the left subtree
        if (leftMax != NULL && leftMax->donation > maxDonation) {
            maxDonation = Max(maxDonation, leftMax->donation);
            maxAnimal = leftMax;
        }

        // Checking the right subtree
        if (rightMax != NULL && rightMax->donation > maxDonation) {
            maxDonation = Max(maxDonation, rightMax->donation);
            maxAnimal = rightMax;
        }



        return maxAnimal;
    }


void popularAnimal(struct AVLNode* t, struct Animal* highestDonationAnimal) {

        if (t == NULL || highestDonationAnimal == NULL)
            return;

        int sameDonation = highestDonationAnimal->donation;

        // Checking for the same amount of donation

        struct Animal* curr = t->data;

        while (curr != NULL) {
            if (curr->donation == sameDonation) {
                PrintDataDetails(curr);
                printf("------------------------\n");
            }
            curr = curr->next;
        }

        // Checking for the left and right subtree
        popularAnimal(t->left, highestDonationAnimal);
        popularAnimal(t->right, highestDonationAnimal);
    }

/*
 * Time Complexity will be O(n^2) because algorithm will  traverse through
 * list and tree. So if we have n nodes and n elements in a tree n*n = n^2
 *--------------------------
 *
 *Potential Improvement: We could store a balanced BST that maps donation amounts
 *   to lists of animals. This way access to the wanted donation would be easier. Alternatively, we could store a hash map (or balanced BST) that maps donation amounts
 *   to lists of animals. This would allow O(1) or O(log d) access to animals with a given donation,
 *   where d is the number of distinct donation values.
 *
 */




