#include <stdio.h>

// Cria um parque //
void p_maior(Parque ** parques, char ** palavras);

// Imprime os parques criados //
void p_menor(Parque ** parques);

// Devolve o vetor que aponta para o parque com o nome v //
Parque* vec_parque(Parque **vetor_parques, char v[]);

// Devolve a quantidade de parques no vetor //
int qnt_parques(Parque ** parques);

// Devolve o índice do parque com o nome v //
int indice_parque(Parque ** vetor_parques, char v[]);

