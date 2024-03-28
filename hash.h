#include <stdio.h>

#include "headers.h"

Hash_node * hash_put(Hash_node * head, Hash_node * tail, Carro *newcarro, Parque * parque);

Carro * hash_procura_carro_dentro(Hash_list * hashtable, Matricula matricula);

Hash_list * cria_hash();