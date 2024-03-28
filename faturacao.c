#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "headers.h"
#include "nodes.h"
#include "datas.h"




typedef struct node_preco{
    float preco;
    Data data;
    struct node_preco * next;
} node_preco;

node_preco * push_preco(node_preco * head, float preco, Data data) {
    node_preco * novo = (node_preco*) malloc(sizeof(node_preco));
    novo->preco = preco;
    novo->data = data;
    novo->next = head;
    head = novo;
}

float devolve_preco_carro(node * nodecarro) {
    if(nodecarro != NULL)
        return nodecarro->carro->preco;
}

node_preco * devolve_preco_dias(node *head_carros) {
    node_preco * head_precos = (node_preco*) malloc(sizeof(node_preco));
    head_precos = NULL;

    while(head_carros != NULL) {
        while(head_carros != NULL && mesma_data(head_carros->carro->D_saida, head_precos->data)) {
            head_precos->preco += devolve_preco_carro(head_carros);
            head_carros = head_carros->next;
        }
        if (head_carros != NULL) {
            push_preco(head_precos, devolve_preco_carro(head_carros), head_carros->carro->D_saida);
            head_carros = head_carros->next;
        }
    }
    return head_precos;
}

void print_precos(node_preco * head_precos) {
    while(head_precos != NULL) {
        printf("%d/%d/%d: %.2f\n", head_precos->data.dia, head_precos->data.mes, head_precos->data.ano, head_precos->preco);
        head_precos = head_precos->next;
    }
}

void free_precos(node_preco * head_precos) {
    node_preco * temp;
    while(head_precos != NULL) {
        temp = head_precos;
        head_precos = head_precos->next;
        free(temp);
    }
}

void faturacao(Parque * parque) {
    node * head_carros = parque->carros_dentro;
    node_preco * head_precos = devolve_preco_dias(head_carros);
    print_precos(head_precos);
    free_precos(head_precos);
}

void print_fatcarro(node * head_carros, Data data) {
    while(head_carros != NULL && !mesma_data(head_carros->carro->D_saida, data)) {
        head_carros = head_carros->next;
    }
    while(head_carros != NULL && mesma_data(head_carros->carro->D_saida, data)){
        printf("%s ", head_carros->carro->matricula);
        print_data_hora(head_carros->carro->D_saida, head_carros->carro->H_saida);
        printf(" %.2f\n", head_carros->carro->preco);
        head_carros = head_carros->next;
    }
}

void f_menor(Parque ** parques, char ** palavras, Data * data_actual, Horas * hora_actual) {
    char * nome = palavras[1];
    Parque * parque = vec_parque(parques, nome);
    Data data;
    Horas hora;

    if(parque == NULL) {
        printf("%s: no such park.\n", nome);
        return;
    }

    sscanf(palavras[2], "%d/%d/%d", &data.dia, &data.mes, &data.ano);
    sscanf(palavras[3], "%d:%d", hora.hora, hora.minuto);

    if(!verifica_datas(data) || !compara_datas(data, hora, *(data_actual),  *(hora_actual))) {
        printf("invalid date.\n");
        return;
    }

    print_fatcarro(parque->head_cf, data);
}

void f_maior(Parque ** parques, char ** palavras) {
    char * nome = palavras[1];
    Parque * parque = vec_parque(parques, nome);

    if(parque == NULL) {
        printf("%s: no such park.\n", nome);
        return;
    }

    faturacao(parque);
}

