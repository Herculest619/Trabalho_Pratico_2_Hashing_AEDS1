#ifndef HASHSC_H   // guardas de cabeçalho, impedem inclusões cíclicas
#define HASHSC_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "listLib.h"

extern int M;
extern int mod;
extern struct hash * hashTable;

struct hash {
    struct node * head;
    int count;
};

int hashCode(int key);

void insertToHash(int id, char * estado, char *municipio, char *rede, double media_ciencias_natureza, double media_ciencias_humanas, double media_linguagem, double media_matematica, double media_redacao);

void deleteFromHash(int key);

void searchInHash(int argc, char *argv[], char aux[]);

int testeInHash(int key);

struct node* testeSearchInList(struct node* head, int id);

void display();

void slots_vazios();

#endif
