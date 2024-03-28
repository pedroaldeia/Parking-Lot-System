#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "headers.h"
#include "parque.h"
#include "nodes.h"
#include "entrada_e_saida.h"
#include "hash.h"

#define HASHSIZE 113
#define IN 0
#define OUT 1

typedef struct node {
    Carro * carro;
    Parque * parque;
    struct node * next;
} Hash_node;

typedef struct {
    Hash_node * head;
    Hash_node * tail;
} Hash_list;

Hash_node * hash_pop(Hash_node * head) { // retira a cabeça de uma lista de nodes //
    Hash_node* newhead = head->next; // vai buscar o ponteiro para o node seguinte //

    free(head); // liberta o ponteiro original //
    return newhead; // torna o ponteiro seguinte na cabeça //
}

Hash_node * hash_pop_ccarro(Hash_node * head) { // retira a cabeça de uma lista de nodes //
    Hash_node * newhead = head->next; // vai buscar o ponteiro para o node seguinte //
    if (head->carro != NULL)
        free(head->carro); // liberta o ponteiro do carro //
    free(head); // liberta o ponteiro original //
    return newhead; // torna o ponteiro seguinte na cabeça //
}

void hash_removenode(Hash_node * head) {
    Hash_node * toremove;
    if(head == NULL)
        return;
    if(head->next == NULL) {
        free(head->next);
        head = NULL;
        return;
    }
    head->next = toremove;
    head->next = head->next->next;
    free(toremove);
}

Hash_node * hash_push(Hash_node * head, Carro * newcarro, Parque * parque) { // adiciona um elemento numa lista de nodes //
    Hash_node * newhead; 
    newhead = (Hash_node*) malloc(sizeof(Hash_node)); // aloca espaço para um novo node //
    newhead-> next = head; // adiciona o ponteiro para a cabeça no novo node //
    newhead-> carro = newcarro; // adiciona a informação no novo node //
    newhead-> parque = parque;
    return newhead; // devolve a nova cabeça //
}

Hash_node * hash_put(Hash_node * head, Hash_node * tail, Carro *newcarro, Parque * parque) {
    Hash_node * nexnode;
    nexnode = (Hash_node*) malloc(sizeof(Hash_node));

    if (tail != NULL) 
        tail-> next = nexnode;
    if (head == NULL)
        head = nexnode;
    nexnode-> next = NULL;
    nexnode-> carro = newcarro;
    return nexnode;
}

node* hash_destroy(node* head) {
    if(head != NULL) // enquanto a cabeça não for null //
        return destroy(pop(head)); // retira a cabeça à lista //
    return NULL;
}

int numero_matricula(Matricula matricula){
    return (atoi(matricula.par1[0]) + atoi(matricula.par1[1]) + atoi(matricula.par2[0]) 
        + atoi(matricula.par2[1]) + atoi(matricula.par3[0]) + atoi(matricula.par3[1]));
}

int hash_index(Matricula matricula){
    return numero_matricula(matricula) % HASHSIZE;
}

void put_hashlist(Hash_list * hash_list, Carro * carro, Parque * parque) {
    int index = hash_index(carro->matricula);
    Hash_node * newnode = hash_put(hash_list[index].head, hash_list[index].tail, carro, parque);
}

Carro * hash_procura_carro_dentro(Hash_list * hashtable, Matricula matricula) {
    int index = hash_index(matricula);
    Hash_node * node = hashtable[index].head;
    while(node != NULL) {
        if(mesma_matricula(node->carro->matricula, matricula) && node->carro->dentro == IN) {
            return node->carro;
        }
        node = node->next;
    }
    return NULL;
}

Carro * hash_procura_carro_1parque(Hash_list * hashtable, Matricula matricula, Parque parque){
    int index = hash_index(matricula);
    Hash_node * node = hashtable[index].head;
    while(node != NULL) {
        if(mesma_matricula(node->carro->matricula, matricula) && node->parque == &parque) {
            return node->carro;
        }
        node = node->next;
    }
    return NULL;
}

Hash_list * cria_hash() {
    Hash_list * hashtable = (Hash_list*) malloc(sizeof(Hash_list) * HASHSIZE);
    int i;
    for(i = 0; i < HASHSIZE; i++) {
        hashtable[i].head = NULL;
        hashtable[i].tail = NULL;
    }
    return hashtable;
}