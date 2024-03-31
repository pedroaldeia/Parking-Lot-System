#include <stdio.h>

#ifndef REMOVE

// Liberta toda a memória alocada para os parques, registos e hashtable //
void q(Parque ** parques, Data * data_atual, Horas * hora_atual, Hash_list * hashtable);

// Remove um parque e todos os registos referentes ao parque //
void r(Parque ** parques, char ** palavras, Hash_list * hashtable);

#define REMOVE
#endif

