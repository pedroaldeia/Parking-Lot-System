#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitura.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// divide a linha em palavras //
//recebe a linha e um array de strings //
// devolve as palavras da linha num array de strings //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int splitlinha(char *linha, char ***palavras) { 
    int c = 0, tamanho;
    char ** lista_p = malloc(BUFSIZ * sizeof(char*));
    // Inicializa os ponteiros de inicio e fim da linha
    char *inicio = linha;
    char *fim = linha;
    char emAspas = 0;

    while (*fim != '\0') { // Percorre a linha até ao fim
        if (*fim == '"') { // Se encontrar aspas, inverte o estado da variável emAspas
            emAspas = !emAspas;
        } else if (*fim == ' ' && !emAspas) { // Se encontrar um espaço fora de aspas, termina a palavra
            tamanho = fim - inicio;

            if (tamanho > 0) {
                lista_p[c] = malloc((tamanho + 1) * sizeof(char)); // aloca memória para a palavra //
                strncpy(lista_p[c], inicio, tamanho); // copia a palavra //
                lista_p[c][tamanho] = '\0';

                char *quotePtr = strchr(lista_p[c], '"'); // procura as aspas na palavra //
                if (quotePtr != NULL) { // se encontrar aspas //
                    memmove(quotePtr, quotePtr + 1, strlen(quotePtr)); // move todos os caracteres uma posição para a esquerda //
                    lista_p[c][strlen(lista_p[c]) - 1] = '\0'; // e ocupa o ultimo caracter por '\0' //
                }
                c++; // aumenta o contador de palavras //
            }
            inicio = fim + 1; // o inicio da proxima palavra é o caracter a seguir ao fim da palavra anterior //
        }
        fim++; // passa para o próximo caracter //
    }
    // Processa a última palavra
    int length = fim - inicio; // calcula o tamanho da última palavra //
    if (length > 0) { // se o tamanho for maior que 0 //
        lista_p[c] = malloc((length + 2) * sizeof(char)); // aloca memória para a palavra //
        strncpy(lista_p[c], inicio, length); // copia a palavra //
        lista_p[c][length] = '\0'; //adiciona o caracter '\0' no fim da palavra //

        char *quotePtr = strchr(lista_p[c], '"'); // procura as aspas na palavra //
        if (quotePtr != NULL) { // se existirem aspas //
            memmove(quotePtr, quotePtr + 1, strlen(quotePtr)); // move os caracteres uma posição para a esquerda //
            lista_p[c][strlen(lista_p[c]) - 1] = '\0'; // e põe '\0' no fim da palavra //
        }
        c++;
    }
    lista_p[c] = NULL; // Adiciona NULL no fim do array de palavras //
    *palavras = realloc(lista_p, (c+1) * sizeof(char*)); // realoca o array para o tamanho certo //

    return c;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Lê a linha de input //
// Não recebe argumentos //
// Devolve a linha lida //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~//
char * lineinput() {
    char  * linha = (char *) malloc(sizeof(char)* BUFSIZ);
    int i = 0;
    char c;
    for(c = getchar(); c != '\n'; c = getchar()){
        linha[i++] = c;
    }
    linha[i] = '\0';
    return linha;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Liberta a memória alocada para as palavras //
// Recebe um array de strings e o número de palavras //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void free_input(char ** palavras, int n_args) {
    int i;

    for(i = 0; i < n_args; i++) {
        free(palavras[i]);
    }
    free(palavras);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Conta o número de palavras numa linha //
// Recebe um array de strings //
// Devolve o número de palavras //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int conta_palavras(char ** palavras) {
    int i = 0;
    while(palavras[i] != NULL) {
        i++;
    }
    return i;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Divide a linha em palavras
// Recebe a linha
// Devolve um array de strings com as palavras da linha (char **) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
char ** wordArray(char *linha) {
    char **words;

    if (linha[strlen(linha) - 1] == '\n') { // se o último caracter da linha for '\n' //
        linha[strlen(linha) - 1] = '\0'; // substitui por '\0' //
    }
    
    splitlinha(linha, &words); // divide o input em palavras //

    free(linha); // liberta a memória alocada para a linha //

    return words;
}
