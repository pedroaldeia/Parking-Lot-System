#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "headers.h" 

node* pop(node* head) { // retira a cabeça de uma lista de nodes //
    node* newhead = head->next; // vai buscar o ponteiro para o node seguinte //
    free(head); // liberta o ponteiro original //
    return newhead; // torna o ponteiro seguinte na cabeça //
}

node* pop_ccarro(node* head) { // retira a cabeça de uma lista de nodes //
    node* newhead = head->next; // vai buscar o ponteiro para o node seguinte //
    if (head->carro != NULL)
        free(head->carro); // liberta o ponteiro do carro //
    free(head); // liberta o ponteiro original //
    return newhead; // torna o ponteiro seguinte na cabeça //
}

void removenode(node * head) {
    if(head == NULL)
        return;
    if(head->next == NULL) {
        head = NULL;
        return;
    }
    head->next = head->next->next;
    head-> next-> next = NULL;
}

node* push(node* head, Carro * newcarro) { // adiciona um elemento numa lista de nodes //
    node* newhead; 
    newhead = (node*) malloc(sizeof(node)); // aloca espaço para um novo node //
    newhead-> next = head; // adiciona o ponteiro para a cabeça no novo node //
    newhead-> carro = newcarro; // adiciona a informação no novo node //
    return newhead; // devolve a nova cabeça //
}

node * put(node * tail, Carro *newcarro) {
    node * nexnode;
    nexnode = (node*) malloc(sizeof(node));

    if (tail != NULL) 
        tail-> next = nexnode;
    nexnode-> next = NULL;
    nexnode-> carro = newcarro;
    return nexnode;
}

node* destroy(node* head) {
    if(head->next != NULL) // enquanto a cabeça nâo for null //
        return destroy(pop(head)); // retira a cabeça à lista //
    return NULL;
}