#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"
#include "nodes.h"
#include "hash.h"
#include "parque.h"

#define TRUE 1
#define FALSE 0

#define BUFFER 8192
#define VECMAX 20
#define HASHSIZE 191


void print_parques(Parque ** parques) {
    for(int i = 0; i < VECMAX; i++) {
        if(parques[i] != NULL) {
            printf("%s\n", parques[i]->nome);
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

void removelista_dentro_e_fora(Parque * parque) {
    node * head;
    if(parque != NULL){
        head = parque->head_cf; // vai buscar a cabeça da lista de carros //
        while(head != NULL) // enquanto o ponteiro não for NULL //
            head = pop(head); // remove a cabeça recomeça com o node seguinte //

        head = parque->carros_dentro; // vai buscar a cabeça da lista de carros //
        while(head != NULL) // enquanto o ponteiro não for NULL //
            head = pop_ccarro(head); // remove a cabeça recomeça com o node seguinte //
    }
    
}

void remove_entradas_hash(Hash_list * hashtable, Parque * parque){
    Hash_node * head;
    for (int i = 0; i < HASHSIZE; i++) {
        if (hashtable[i].head != NULL) {
            head = hashtable[i].head;
            for(; head != NULL; head = head->next) {
                if(head->next->parque == parque) 
                    hash_removenode(head);
            }
        }
        if (hashtable[i].head != NULL && hashtable[i].head->parque == parque) {
            free(hashtable[i].head);
        }
    }
}

void muda_parques_lugar(Parque ** parques, int indice, int qntparques) {
    for(int i = indice; i < qntparques; i++) {
        parques[i] = parques[i+1];
    }
    parques[qntparques] = NULL;
}

void removeprk(Parque ** parques, int indice) {
    Parque * parque = parques[indice]; // aponta para o parque com o índice dado //
    int qntparques = qnt_parques(parques); // vai buscar o número de parques //
    
    removelista_dentro_e_fora(parque); // remove as listas de carros //

    free(parque->nome); // liberta o espaço do nome //
    free(parque); // liberta o espaço do parque //

    muda_parques_lugar(parques, indice, qntparques); // muda os parques de lugar //
}

void q(Parque ** parques, Data * data_actual, Horas * hora_actual) {
    for(int i = 0; i < VECMAX; i++) {
        if(parques[i] != NULL)
            removeprk(parques, i);
    }
    free(data_actual);
    free(hora_actual);
}

void r(Parque ** parques, char ** palavras) {
    char * nome = palavras[1];
    int indice = indice_parque(parques, nome);

    if(indice == -1) {
        printf("%s: no such park.\n", nome);
        return;
    }

    removeprk(parques, indice);
    print_parques(parques);
}


