// Code adapted from
// http://see-programming.blogspot.com/2013/05/chain-hashing-separate-chaining-with.html

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listLib.h"
#include "hashscLib.h"

//Vars definitions
struct hash * hashTable; // Hash Table
int M; // default size of hash table with separete chaning
int mod;

/* Returns the hash code for a key */
int hashCode(int id) {
    return id % mod;
}

/* Given some informations (key, name and age),
it inserts a new node on the front of the list of
a hash table index. */
void insertToHash(int id, char * estado, char *municipio, char *rede, double media_ciencias_natureza, double media_ciencias_humanas, double media_linguagem, double media_matematica, double media_redacao) {
    int hashIndex = hashCode(id);


        struct node * newnode = createNode(id, estado, municipio, rede, media_ciencias_natureza, media_ciencias_humanas, media_linguagem, media_matematica, media_redacao);

        /* head of list for the bucket with index "hashIndex" */
        if (!hashTable[hashIndex].head) {
            hashTable[hashIndex].head = newnode;
            hashTable[hashIndex].count = 1;
            return;
        }

        if(testeInHash(id) != 1) {

        /* adding new node to the list */
        newnode -> next = (hashTable[hashIndex].head);
        /*
         * update the head of the list and no of
         * nodes in the current bucket
         */
        hashTable[hashIndex].head = newnode;
        hashTable[hashIndex].count++;
    }
    return;
}

/* Function to delete a node in a hash table with SC.
   key --> to be deleted. */
void deleteFromHash(int key) {
    /* find the bucket using hash index */
    int hashIndex = hashCode(key);

    struct node **head_ref = &hashTable[hashIndex].head;

    if(deleteFromList(head_ref, key) == 1) {
        hashTable[hashIndex].count--;
    } else {
        printf("Search element unavailable in hash table\n");
    }

    return;
}

/* Function to check if a key is in a hash table with SC.
   key --> to be checked. */
void searchInHash(int argc,char *argv[], char aux[]) {
    if(strcmp(argv[1], "-b") != 0) {
        int key = atoi(argv[1]);
        int hashIndex = hashCode(key);
        struct node * myNode;

        myNode = searchInList(hashTable[hashIndex].head, key, argc, argv, 8);

        if(myNode != NULL) {
            if(argc > 8) {
                if(strcmp(argv[8], "-p") == 0) {
                    printf("\n");
                    printNode(myNode);
                } else {
                    printf("\nNao foi passado argumento -p para imprimir os dados!\n");
                }
            }
        }
        return;
    } else {
        int key = atoi(aux);
        int hashIndex = hashCode(key);
        struct node * myNode;

        myNode = searchInList(hashTable[hashIndex].head, key, argc, argv, 0);

        if(myNode != NULL) {
            if(argc > 9) {
                if(strcmp(argv[9], "-p") == 0) {
                    printf("\n");
                    printNode(myNode);
                }
            }
        }
        if(myNode == NULL) {
            if(argc > 9) {
                if(strcmp(argv[9], "-p") == 0) {
                    printf("\nSearch element unavailable in hash table\n");
                }
            }
            return;
        }
    }
}

int testeInHash(int key) {
    int hashIndex = hashCode(key);
    struct node * myNode;

    myNode = testeSearchInList(hashTable[hashIndex].head, key);

    if(myNode != NULL)
        return 1;
    else
        return -1;
}

// This function prints contents of hash table with SC
void display() {
    struct node * myNode;
    int i;
    for (i = 0; i < M; i++) {
        if (hashTable[i].count == 0)
            continue;
        myNode = hashTable[i].head;
        if (!myNode)
            continue;
        printf("\nData at index %d in Hash Table:\n", i);
        printf("-----------------------------------------------------\n");
        while (myNode != NULL) {
            printNode(myNode);
            myNode = myNode -> next;
        }
    }
    return;
}

// This function prints occupied and empyt slots in the hash table with SC
void slots_vazios() {
    int i, contador = 0;
    for(i = 0; i < M; i++) {
        if(hashTable[i].count == 0)
            contador ++;
    }
    printf("\nNumeros de slots vazios: %d\n",contador);
}
