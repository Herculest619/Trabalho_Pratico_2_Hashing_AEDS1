#include <stdio.h>
#include <string.h>
#include "listLib.h"

// This function prints contents of one node
void printNode(struct node * node) {
    printf("ID: %d\n", node->id);
    printf("ESTADO: %s\n", node->estado);
    printf("MUNICIPIO: %s\n", node->municipio);
    printf("REDE: %s\n", node->rede);
    printf("MEDIA CIENCIAS DA NATUREZA: %lf\n", node->media_ciencias_natureza);
    printf("MEDIA CIENCIAS HUMANA: %lf\n", node->media_ciencias_humanas);
    printf("MEDIA LINGUAGEM: %lf\n", node->media_linguagem);
    printf("MEDIA MATEMATICA: %lf\n", node->media_matematica);
    printf("MEDIA REDACAO: %lf\n", node->media_redacao);
    printf("\n");
}

// This fuction creates a new node given some informations
struct node * createNode(int id, char * estado, char *municipio, char *rede, double media_ciencias_natureza, double media_ciencias_humanas, double media_linguagem, double media_matematica, double media_redacao) {

    struct node * newnode;
    newnode = (struct node * ) malloc(sizeof(struct node));

    newnode->id = id;
    strcpy(newnode->estado, estado);
    strcpy(newnode->municipio, municipio);
    strcpy(newnode->rede, rede);
    newnode->media_ciencias_natureza = media_ciencias_natureza;
    newnode->media_ciencias_humanas = media_ciencias_humanas;
    newnode->media_linguagem = media_linguagem;
    newnode->media_matematica = media_matematica;
    newnode->media_redacao = media_redacao;
    newnode->next = NULL;

    return newnode;
}

/* Checks whether the value key is present in linked list */
struct node* searchInList(struct node* head, int id, int argc, char *argv[], int aux) {
    struct node * myNode;
    myNode = head;

    if (!myNode) {
        if(argc > 8) {
            if(strcmp(argv[8], "-p") == 0) {
                printf("\nSearch element unavailable in the list\n");
            }
        }

        return NULL;
    }
    while (myNode != NULL) {
        if (myNode->id == id) {

            //printNode(myNode);
            return myNode;
        }
        myNode = myNode->next;
    }
    if(argc > 8) {
        if(strcmp(argv[8], "-p") == 0) {
            printf("\nSearch element unavailable in the list\n");
        }
    }
    return NULL;
}

struct node* testeSearchInList(struct node* head, int id) {

    struct node * myNode;
    myNode = head;

    if (!myNode) {
        //printf("Search element unavailable in the list 11111\n");
        return NULL;
    }
    while (myNode != NULL) {
        if (myNode->id == id) {

            //printNode(myNode);
            return myNode;
        }
        myNode = myNode->next;
    }

    //printf("Search element unavailable in the list 22222\n");
    return NULL;

}

/* Function to delete a node in a Linked List.


   head_ref --> pointer to head node pointer.
   del  -->  pointer to node to be deleted. */
int deleteFromList(struct node **head_ref, int id) {
    // Store head node
    struct node *temp = *head_ref, *prev;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->id == id) {
        *head_ref = temp->next;   // Changed head
        free(temp);               // free old head
        printf("Data deleted successfully from list\n");
        return 1;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL) {
        printf("Given data is not present in the list\n");
        return 0;
    }

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp);  // Free memory

    return 1;
}
