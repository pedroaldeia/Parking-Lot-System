#include <stdio.h>

#include "headers.h"

#define HASHSIZE 907

#ifndef HASH
typedef struct hash_node {
    Carro * carro;
    Parque * parque;
    struct hash_node * next;
} Hash_node;

typedef struct hash_list{
    Hash_node * head;
    Hash_node * tail;
    int size;
} Hash_list;
#define HASH
#endif


#ifndef HASHFUNC

void hash_removenode(Hash_node * head);

int hash_index(Matricula matricula);

void put_hashtable(Hash_list * hashtable, Carro * carro, Parque * parque);

Carro * hash_procura_carro_dentro(Hash_list * hashtable, Matricula matricula);

int hash_carro_dentro(Hash_list * hashtable, Matricula matricula);

Carro * hash_procura_carro_1parque(Hash_list * hashtable, Matricula matricula, Parque  * parque);

Hash_list * cria_hash();
#define HASHFUNC
#endif