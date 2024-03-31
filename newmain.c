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


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Recebe o input e chama as funções correspondentes //
// Não recebe argumentos //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int main () {
    Parque * vec_parques[PRKMAX] = {NULL}; 
    char  * linha = lineinput(); 
    int n_args = 0;
    char ** palavras;
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
                if(strlen(linha) == 1) { // se o input for só 'p' //
                    p_menor(vec_parques);
                    free(linha); 
                }
                else {
                    palavras = wordArray(linha); // divide o input em palavras //
                    p_maior(vec_parques, palavras); 
                    n_args = 6;
                    free_input(palavras, n_args); // liberta a memória alocada para as palavras //
                }
                break;
            case 'e':
                palavras = wordArray(linha); 
                e(vec_parques, hora_actual, data_actual, palavras, hashtable);
                n_args = 5;
                free_input(palavras, n_args); // liberta a memória alocada para as palavras //
                break;
            case 's':
                palavras = wordArray(linha); 
                s(vec_parques, hora_actual, data_actual, palavras, hashtable); 
                n_args = 5;
                free_input(palavras, n_args);
                break;
            case 'v':
                palavras = wordArray(linha); 
                v(hashtable, palavras); 
                n_args = 2;
                free_input(palavras, n_args);
                break;
            case 'f':
                palavras = wordArray(linha); 
                n_args = conta_palavras(palavras);  // conta o número de palavras //
                f(vec_parques, palavras, n_args, data_actual); 
                break;
            case 'r':
                palavras = wordArray(linha); 
                r(vec_parques, palavras, hashtable); 
                n_args = 2;
                free_input(palavras, n_args);
                break;
        }
        linha = lineinput(); // recebe o próximo input //
    }
    free(linha);
    q(vec_parques, data_actual, hora_actual, hashtable);
    return 0;
}