#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "funcoes.h"
#include "hashscLib.h"
#include "listLib.h"

void tam_med_listas() {
    float cont_colisoes = 0;
    int i;
    for (i = 0; i < M; i++) {
        cont_colisoes += hashTable[i].count;
    }
    float media = cont_colisoes / M;
    printf("\nTamanho medio das listas: %.2f\n", media);
}

void qui_quadrado() {
    double somatorio = 0, dividendo = 0, n = 30228;
    int j;
    for (j = 0; j < M; j++) {
        somatorio += (hashTable[j].count)*(hashTable[j].count + 1);
    }
    somatorio /= 2;
    dividendo = (n / (2 * M)) * (n + (2 * M) -1);

    printf("\n\nTeste qui-quadrado = %lf\n\n\n", somatorio / dividendo);
}

void colisoes() {
    int cont_colisoes = 0;
    int i;
    for (i = 0; i < M; i++) {
        if(hashTable[i].count > 1) {
            cont_colisoes += hashTable[i].count - 1;
        }
    }
    printf("\nNumero de colisoes: %d\n", cont_colisoes);
}

void introduir_dados(int argc, char *argv[], int ref) {

    FILE *arquivo = fopen(argv[ref],"r");
    char aux[150];//usada pra salvar cada linha do txt
    char *ponto_e_virgula;//variavel que vai salvar as frases separadas por ";"
    int cont_topico;//variaveis contadoras

    int id;
    char estado[3];
    char municipio[33];
    char rede[8];
    double media_ciencias_natureza;
    double media_ciencias_humanas;
    double media_linguagem;
    double media_matematica;
    double media_redacao;

    while(fgets(aux,150,arquivo) != NULL) { //lendo cada linha do txt e colocando no aux
        ponto_e_virgula = strtok(aux, ";");//passando aux como argumento pra strtox, e o ";" como elemento para procurar
        cont_topico = 1;
        while(ponto_e_virgula != NULL) {
            switch(cont_topico) {
            case 1: {
                id = atoi(ponto_e_virgula);
                break;
            }
            case 2: {
                strcpy(estado, ponto_e_virgula);
                break;
            }
            case 3: {
                strcpy(municipio, ponto_e_virgula);
                break;
            }
            case 4: {
                strcpy(rede, ponto_e_virgula);
                break;
            }
            case 5: {
                media_ciencias_natureza = atof(ponto_e_virgula);
                break;
            }
            case 6: {
                media_ciencias_humanas = atof(ponto_e_virgula);
                break;
            }
            case 7: {
                media_linguagem = atof(ponto_e_virgula);
                break;
            }
            case 8: {
                media_matematica = atof(ponto_e_virgula);
                break;
            }
            case 9: {
                media_redacao = atof(ponto_e_virgula);
                break;
            }
            default: {
                break;
            }
            }
            cont_topico++;
            ponto_e_virgula = strtok(NULL, ";");//introduzindo o NULL pra sair desse while

        }
        insertToHash(id, estado, municipio, rede, media_ciencias_natureza, media_ciencias_humanas, media_linguagem, media_matematica, media_redacao);
    }
    fclose(arquivo);
}

void inicio(int argc, char* argv[]) {
    clock_t start, end;
    double cpu_time_used;
    if(argc == 1) {
        printf("\nNao foram passados argumentos\n");
    }
    if(argc >= 2) {
        if(strcmp(argv[1], "-b") == 0) {
            if(strcmp(argv[3], "-d") == 0) {
                if(strcmp(argv[5], "-M") == 0) {
                    if(atoi(argv[6]) > 0) {
                        if(strcmp(argv[7], "-mod") == 0) {
                            if(atoi(argv[8]) >= 0 && atoi(argv[8]) <= atoi(argv[6])) {
                                M = atoi(argv[6]);
                                mod = atoi(argv[8]);
                                hashTable = (struct hash *) calloc(M, sizeof(struct hash));
                                start = clock();
                                introduir_dados(argc, argv, 4);
                                end = clock();
                                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                                slots_vazios();
                                tam_med_listas();
                                colisoes();
                                printf("\nTempo para inserir todos os dados: %lf segundos\n", cpu_time_used);
                                FILE *arquivo = fopen(argv[2], "r");
                                char aux[15];
                                while(fgets(aux,15,arquivo) != NULL) {
                                    searchInHash(argc, argv, aux);
                                }
                                if(argc <= 9) {
                                    printf("\nNao foi passado argumento -p para imprimir os dados!\n");
                                }
                                fclose(arquivo);
                            } else {
                                printf("\nDigito mod negativo ou maior do que a tabela hash!\n");
                            }
                        } else {
                            printf("\nNao foi passado o argumento -mod!\n");
                        }
                    } else {
                        printf("\nTamanho de tabela hash negativo!\n");
                    }
                } else {
                    printf("\nNao foi passado o argumento -M para selecao de tamanho da tabela hash!\n");
                }
            } else {
                printf("\nNao foi passado o argumento -d para selecao de arquivo!\n");
            }
        } else {
            if(strcmp(argv[2], "-d") == 0) {
                if(strcmp(argv[4], "-M") == 0) {
                    if(atoi(argv[5]) > 0) {
                        if(strcmp(argv[6], "-mod") == 0) {
                            if(atoi(argv[7]) >= 0 && atoi(argv[7]) <= atoi(argv[5])) {
                                M = atoi(argv[5]);
                                mod = atoi(argv[7]);
                                hashTable = (struct hash *) calloc(M, sizeof(struct hash));
                                start = clock();
                                introduir_dados(argc, argv, 3);
                                end = clock();
                                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                                slots_vazios();
                                tam_med_listas();
                                colisoes();
                                printf("\nTempo para inserir todos os dados: %lf segundos\n", cpu_time_used);
                                searchInHash(argc, argv, 0);
                                if(argc <= 8) {
                                    printf("\nNao foi passado argumento -p para imprimir os dados!\n");
                                }
                            } else {
                                printf("\nDigito mod negativo ou maior do que a tabela hash!\n");
                            }
                        } else {
                            printf("\nNao foi passado o argumento -mod!\n");
                        }
                    } else {
                        printf("\nTamanho de tabela hash negativo!\n");
                    }
                } else {
                    printf("\nNao foi passado o argumento -M para selecao de tamanho da tabela hash!\n");
                }
            } else {
                printf("\nNao foi passado o argumento -d para selecao de arquivo!\n");
            }
        }
    }
}
