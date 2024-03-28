#include <stdio.h>

#ifndef NODE_FUNC

node* pop(node* head);

node * pop_ccarro(node* head);

void removenode(node * head);

node* push(node* head, Carro * newcarro);

node * put(node * tail, Carro *newcarro);

node* destroy(node* head);

#define NODE_FUNC
#endif