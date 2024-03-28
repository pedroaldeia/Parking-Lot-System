#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "leitura.h"
#include "headers.h"
#include "parque.h"
#include "entrada_e_saida.h"
#include "remove.h"

#define PRKMAX 20
#define BUFSIZ 8192
#define IN 0
#define OUT 1

int main () {
    Parque * vec_parques[PRKMAX] = {NULL}; // inicializar o vetor de parques //
    char  * linha = lineinput(); // recebe o primeiro input //
    int n_args = 0;
    char ** palavras;

    Data * data_actual = malloc(sizeof(Data)); // aloca espaço para a data atual //
    Horas * hora_actual = malloc(sizeof(Horas));
    data_actual-> ano = 0; // inicializa a data atual a 0 //
    data_actual-> mes = 0;
    data_actual-> dia = 0; 
    hora_actual-> hora = 0;
    hora_actual-> minuto = -1;

    while (linha[0] != 'q') {
        switch(linha[0]){
            case 'p':
                if(strlen(linha) == 1) {
                    p_menor(vec_parques);
                }
                else {
                    palavras = wordArray(linha);
                    p_maior(vec_parques, palavras);
                    n_args = 6;
                    free_input(palavras, n_args);
                }
                break;
            case 'e':
                palavras = wordArray(linha);
                e(vec_parques, hora_actual, data_actual, palavras);
                n_args = 5;
                free_input(palavras, n_args);
                break;
            case 's':
                palavras = wordArray(linha);
                s(vec_parques, hora_actual, data_actual, palavras);
                n_args = 5;
                free_input(palavras, n_args);
                break;
            case 'r':
                palavras = wordArray(linha);
                r(vec_parques, palavras);
                n_args = 2;
                free_input(palavras, n_args);
                break;
        }
        linha = lineinput();
    }
    q(vec_parques, data_actual, hora_actual);
    return 0;
}