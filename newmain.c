#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "leitura.h"
#include "headers.h"
#include "parque.h"
#include "entrada_e_saida.h"
#include "remove.h"
#include "hash.h"
#include "veiculo.h"
#include "faturacao.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Função que inicializa argumentos e chama a função p //
// Recebe um array de parques e a linha de input //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void pmain(Parque ** vec_parques, char * linha) {
    char ** palavras;
    int n_args = 6;
    if(strlen(linha) == 1) { // se o input for só 'p' //
        p_menor(vec_parques);
        free(linha); 
    }
    else {
        palavras = wordArray(linha); // divide o input em palavras //
        p_maior(vec_parques, palavras); 
        free_input(palavras, n_args); // liberta a memória alocada para as palavras //
    }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Função que inicializa argumentos e chama a função e //
// Recebe um array de parques, a hora atual, a data atual, a linha de input e a hashtable //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void emain(Parque ** vec_parques, Horas * hora_actual, Data * data_actual, char * linha, Hash_list * hashtable) {
    char ** palavras = wordArray(linha);
    int n_args = 5;
    e(vec_parques, hora_actual, data_actual, palavras, hashtable);
    free_input(palavras, n_args); // liberta a memória alocada para as palavras //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Função que inicializa argumentos e chama a função s //
// Recebe um array de parques, a hora atual, a data atual, a linha de input e a hashtable //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void smain(Parque ** vec_parques, Horas * hora_actual, Data * data_actual, char * linha, Hash_list * hashtable) {
    char ** palavras = wordArray(linha);
    int n_args = 5;
    s(vec_parques, hora_actual, data_actual, palavras, hashtable); 
    free_input(palavras, n_args);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Função que inicializa argumentos e chama a função v //
// Recebe a hashtable e a linha de input //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void vmain(Hash_list * hashtable, char * linha) {
    char ** palavras = wordArray(linha);
    int n_args = 2; 
    v(hashtable, palavras); 
    free_input(palavras, n_args);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Função que inicializa argumentos e chama a função f //
// Recebe um array de parques, a linha de input e a data atual //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void fmain(Parque ** vec_parques, char * linha, Data * data_actual) {
    char ** palavras = wordArray(linha);
    int n_args = conta_palavras(palavras);
    f(vec_parques, palavras, n_args, data_actual);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Função que inicializa argumentos e chama a função r //
// Recebe um array de parques, a linha de input e a hashtable //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void rmain(Parque ** vec_parques, char * linha, Hash_list * hashtable) {
    char ** palavras = wordArray(linha);
    int n_args = 2;
    r(vec_parques, palavras, hashtable);
    free_input(palavras, n_args);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// MAIN: Recebe o input e chama as funções correspondentes //
// Não recebe argumentos //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int main () {
    Parque * vec_parques[PRKMAX] = {NULL}; 
    char  * linha = lineinput(); 
    Hash_list * hashtable = cria_hash();

    Data * data_actual = malloc(sizeof(Data)); 
    Horas * hora_actual = malloc(sizeof(Horas));
    data_actual-> ano = 0; 
    data_actual-> mes = 0;
    data_actual-> dia = 0; 
    hora_actual-> hora = 0;
    hora_actual-> minuto = -1;

    while (linha[0] != 'q') { // enquanto o input não for 'q' //
        switch(linha[0]){ // verifica o primeiro caracter do input //
            case 'p': 
                pmain(vec_parques, linha);
                break;
            case 'e':
                emain(vec_parques, hora_actual, data_actual, linha, hashtable);
                break;
            case 's':
                smain(vec_parques, hora_actual, data_actual, linha, hashtable);
                break;
            case 'v':
                vmain(hashtable, linha);
                break;
            case 'f':
                fmain(vec_parques, linha, data_actual);
                break;
            case 'r':
                rmain(vec_parques, linha, hashtable);
                break;
        }
        linha = lineinput(); // recebe o próximo input //
    }
    free(linha);
    q(vec_parques, data_actual, hora_actual, hashtable);
    return 0;
}

