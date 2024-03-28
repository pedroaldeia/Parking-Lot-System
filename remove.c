#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"
#include "nodes.h"

#define TRUE 1
#define FALSE 0

#define BUFFER 8192
#define VECMAX 20


void print_parques(Parque ** parques) {
    for(int i = 0; i < VECMAX; i++) {
        if(parques[i] != NULL) {
            printf("%s ", parques[i]->nome);
        }
    }
}

Parque* vec_parque_cnull(Parque **vetor_parques, char v[]) { 
    // devolve o ponteiro para o parque que tem o nome em questão //

    int i; 
    Parque * parque;

    for(i = 0; i<VECMAX; i++) { // para cada parque no vetor //
        if(vetor_parques[i] != NULL && !strcmp((vetor_parques[i])->nome, v)){
            parque = vetor_parques[i];
            vetor_parques[i] = NULL; // compara o nome do parque com o dado, se for igual //
            return parque; // devolve o ponteiro para o parque com o nome dado //
        }
    }
    return NULL; // se não devolve vetor nulo //
}

void removeprk(Parque * parque) {
    node * head;

    head = parque->head_cf; // vai buscar a cabeça da lista de carros //
    while(head != NULL) // enquanto o ponteiro não for NULL //
        head = pop(head); // remove a cabeça recomeça com o node seguinte //

    head = parque->carros_dentro; // vai buscar a cabeça da lista de carros //
    while(head != NULL) // enquanto o ponteiro não for NULL //
        head = pop_ccarro(head); // remove a cabeça recomeça com o node seguinte //
        
    free(parque); // liberta o espaço do parque //
    
}

void q(Parque ** parques, Data * data_actual, Horas * hora_actual) {
    for(int i = 0; i < VECMAX; i++) {
        if(parques[i] != NULL) {
            removeprk(parques[i]);
            parques[i] = NULL;
        }
    }
    free(data_actual);
    free(hora_actual);
}

void r(Parque ** parques, char ** palavras) {
    char * nome = palavras[1];

    removeprk(vec_parque_cnull(parques, nome));
    print_parques(parques);
}


