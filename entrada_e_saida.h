#include <stdio.h>

#include "headers.h"
#include "hash.h"

#ifndef ENTRADA_E_SAIDA

// verifica se a matricula é válida //
int verifica_matriculas(Matricula matricula); 

// verifica se as matriculas são iguais //
int mesma_matricula(Matricula matricula1, Matricula matricula2);

// dá entrada a um carro //
void e(Parque ** parques, Horas * hora_actual, Data * data_actual, char ** palavras, Hash_list * hashtable);

// dá saída a um carro //
void s(Parque ** parques, Horas * hora_actual, Data * data_actual, char ** palavras, Hash_list * hashtable);

#define ENTRADA_E_SAIDA
#endif