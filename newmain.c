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

#define PRKMAX 20
#define BUFSIZ 8192
#define IN 0
#define OUT 1


int main () {
    Parque * vec_parques[PRKMAX] = {NULL}; // inicializar o vetor de parques //
    char  * linha = lineinput(); // recebe o primeiro input //
    int n_args = 0;
    char ** palavras;
    Hash_list * hashtable = cria_hash(); // cria a hashtable //

    Data * data_actual = malloc(sizeof(Data)); // aloca espaço para a data atual //
    Horas * hora_actual = malloc(sizeof(Horas));
    data_actual-> ano = 0; // inicializa a data atual a 0 //
    data_actual-> mes = 0;
    data_actual-> dia = 0; 
    hora_actual-> hora = 0;
    hora_actual-> minuto = -1;

    while (linha[0] != 'q') { // enquanto o input não for 'q' //
        switch(linha[0]){ // verifica o primeiro caracter do input //
            case 'p': // caso seja 'p' //
                if(strlen(linha) == 1) { // se o input for só 'p' //
                    p_menor(vec_parques); // chama a função p_menor //
                }
                else { // se não //
                    palavras = wordArray(linha); // divide o input em palavras //
                    p_maior(vec_parques, palavras); // chama a função p_maior //
                    n_args = 6;
                    free_input(palavras, n_args); // liberta a memória alocada para as palavras //
                }
                break;
            case 'e':
                palavras = wordArray(linha); // divide o input em palavras //
                e(vec_parques, hora_actual, data_actual, palavras, hashtable); // chama a função e //
                n_args = 5;
                free_input(palavras, n_args); // liberta a memória alocada para as palavras //
                break;
            case 's':
                palavras = wordArray(linha); // divide o input em palavras //
                s(vec_parques, hora_actual, data_actual, palavras, hashtable); // chama a função s //
                n_args = 5;
                free_input(palavras, n_args); // liberta a memória alocada para as palavras //
                break;
            case 'v':
                palavras = wordArray(linha); // divide o input em palavras //
                v(hashtable, palavras); // chama a função v //
                n_args = 2;
                free_input(palavras, n_args); // liberta a memória alocada para as palavras //
                break;
            case 'f':
                palavras = wordArray(linha); // divide o input em palavras //
                n_args = conta_palavras(palavras); // conta o número de palavras //
                f(vec_parques, palavras, n_args, data_actual); // chama a função f //
                break;
            case 'r':
                palavras = wordArray(linha); // divide o input em palavras //
                r(vec_parques, palavras); // chama a função r //
                n_args = 2;
                free_input(palavras, n_args); // liberta a memória alocada para as palavras //
                break;
        }
        linha = lineinput(); // recebe o próximo input //
    }
    free(linha); // liberta a memória alocada para a linha //
    q(vec_parques, data_actual, hora_actual); // chama a função q //
    return 0;
}