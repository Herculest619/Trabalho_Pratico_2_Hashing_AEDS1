#ifndef LISTLIB_H   // guardas de cabeçalho, impedem inclusões cíclicas
#define LISTLIB_H

#include <stdio.h>
#include <stdlib.h>

struct node {
    int id;
    char estado[3];
    char municipio[33];
    char rede[8];
    double media_ciencias_natureza;
    double media_ciencias_humanas;
    double media_linguagem;
    double media_matematica;
    double media_redacao;
    struct node * next;
};

void printNode(struct node * node);

struct node * createNode(int id, char * estado, char *municipio, char *rede, double media_ciencias_natureza, double media_ciencias_humanas, double media_linguagem, double media_matematica, double media_redacao);

int deleteFromList(struct node **head_ref, int id);

struct node * searchInList(struct node* head, int id, int argc, char *argv[], int aux);

#endif
