#include <stdio.h>

#ifndef NODE_FUNC

// Retira o primeiro nó da lista //
node* pop(node* head);

// Retira o primeiro nó da lista, e inclusivamente liberta o espaço do carro que contém //
node * pop_ccarro(node* head);

// Retira o nó da lista posterior ao nó dado //
void removenode(node * head);

// Adiciona um nó no início da lista //
node* push(node* head, Carro * newcarro);

// Adiciona um nó no final da lista //
node * put(node * tail, Carro *newcarro);
 
// Destroi uma lista //
node* destroy(node* head);

#define NODE_FUNC
#endif