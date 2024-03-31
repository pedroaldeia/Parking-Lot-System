#include <stdio.h>


#ifndef LEITURA

// Lê o input do utilizador //
char * lineinput();

// Divide a linha em palavras //
char ** wordArray(char * line);

// Liberta a memória alocada para as palavras //
void free_input(char ** palavras, int n_args);

// Conta o número de palavras numa linha //
int conta_palavras(char ** line);

#define LEITURA
#endif