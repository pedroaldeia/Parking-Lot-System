#include <stdio.h>

#include "headers.h"

#define HASHSIZE 61

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

// Remove o primeiro node de uma lista de uma hashtable //
void hash_removenode(Hash_node * head);

// Devolve o index de uma matricula na hashtable //
int hash_index(Matricula matricula);

// Põe um carro na hashtable //
void put_hashtable(Hash_list * hashtable, Carro * carro, Parque * parque);

// Procura um carro na hashtable //
Carro * hash_procura_carro_dentro(Hash_list * hashtable, Matricula matricula);

// Verifica se um carro está dentro de algum parque //
int hash_carro_dentro(Hash_list * hashtable, Matricula matricula);

// Procura um carro num parque específico na hashtable //
Carro * hash_procura_carro_1parque(Hash_list * hashtable, Matricula matricula, Parque  * parque);

// Cria uma hashtable //
Hash_list * cria_hash();

#define HASHFUNC
#endif