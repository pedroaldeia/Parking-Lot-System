#include <stdio.h>

#ifndef FATURACAO_STRUCT

typedef struct node_preco{
    float preco;
    Data data;
    struct node_preco * next;
} node_preco;

typedef struct list_preco{
    node_preco * head;
    node_preco * tail;
    Data data;
    int size;
} List_preco;

#define FATURACAO_STRUCT
#endif

#ifndef _FATURACAO_H

// Imprime a faturação de um parque, por dia e carro ou geral diário //
void f(Parque ** parques, char ** palavras, int n_palavras, Data * data_actual);

#define _FATURACAO_H
#endif