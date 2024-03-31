#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "headers.h" 


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Retira a cabeça de uma lista de nodes //
// Recebe um ponteiro para a cabeça da lista //
// Devolve um ponteiro para o segundo nó da lista (node*) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
node* pop(node* head) { 
    node* newhead = head->next; // vai buscar o ponteiro para o node seguinte //
    free(head); // liberta o ponteiro original //
    return newhead; // torna o ponteiro seguinte na cabeça //
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Retira a cabeça de uma lista de nodes, e liberta o carro que contém //
// Recebe um ponteiro para a cabeça da lista //
// Revolve um ponteiro para o segundo nó da lista (node*) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
node* pop_ccarro(node* head) { 
    node* newhead = head->next; 
    if (head->carro != NULL)
        free(head->carro); // liberta o ponteiro do carro //
    free(head); // liberta o ponteiro original //
    return newhead; // torna o ponteiro seguinte na cabeça //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Retira o node a seguir ao node dado numa lista de nodes //
// Recebe um ponteiro para o node anterior ao node a retirar //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Adiciona um elemento no início de uma lista de nodes //
// Recebe um ponteiro para a cabeça da lista e um ponteiro para um carro //
// Devolve um ponteiro para a nova cabeça da lista (node*) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
node* push(node* head, Carro * newcarro) { 
    node* newhead; 
    newhead = (node*) malloc(sizeof(node)); 
    newhead-> next = head; 
    newhead-> carro = newcarro; // adiciona a informação no novo node //
    return newhead; // devolve a nova cabeça //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Põe um node no final da lista de nodes //
// Recebe a tail da lista e um carro //
// Devolve a nova tail (node*) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
node * put(node * tail, Carro *newcarro) { // adiciona um elemento no fim //
    node * nexnode; 
    nexnode = (node*) malloc(sizeof(node)); // aloca espaço para um novo node //

    if (tail != NULL) // se a lista não estiver vazia //
        tail-> next = nexnode; // a cauda aponta para o novo node //
    nexnode-> next = NULL; 
    nexnode-> carro = newcarro;
    return nexnode; // devolve a nova tail //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Destroi uma lista de nodes //
// Recebe a cabeça da lista //
// Devolve NULL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
node* destroy(node* head) {
    if(head->next != NULL) // enquanto a cabeça nâo for null //
        return destroy(pop(head)); // retira a cabeça à lista //
    return NULL;
}