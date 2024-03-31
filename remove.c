#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"
#include "nodes.h"
#include "hash.h"
#include "parque.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Remove as listas de carros de dentro e fora do parque //
// Recebe um ponteiro para o parque //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void removelista_dentro_e_fora(Parque * parque) {
    node * head;
    if(parque != NULL){
        head = parque->head_cf; // vai buscar a cabeça da lista de carros //
        while(head != NULL) 
            head = pop(head); // remove a cabeça recomeça com o node seguinte //

        head = parque->carros_dentro; // vai buscar a cabeça da lista de carros //
        while(head != NULL)
            head = pop_ccarro(head); // remove a cabeça recomeça com o node seguinte //
    }
    
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Remove as entradas pertencentes a um parque na hashtable //
// Recebe um ponteiro para a hashtable e um ponteiro para o parque //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void remove_entradas_hash(Hash_list * hashtable, Parque * parque){
    for (int i = 0; i < HASHSIZE; i++) {
        Hash_node *atual = hashtable[i].head;
        Hash_node *anterior = NULL;
        while (atual != NULL) {
            if (atual->parque == parque) {
                Hash_node *temp = atual; // guarda o nó a ser removido //
                if (anterior == NULL) { // se o nó a ser removido for o primeiro da lista //
                    hashtable[i].head = atual->next; // a novo head é o próximo nó //
                    atual = atual->next; 
                } else {
                    anterior->next = atual->next; // o nó anterior passa a apontar para o próximo nó //
                    atual = atual->next; 
                }
                free(temp); // liberta o nó removido //
            } else {
                anterior = atual;
                atual = atual->next; 
            }
        }
    }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Cria uma cópia do vetor de parques //
// Recebe um vetor de parques //
// Devolve um vetor de parques //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Parque ** cria_copia_vec_parques(Parque ** parques){
    int i;
    Parque ** parques_novo = (Parque**) malloc(sizeof(Parque*) * PRKMAX);
    for(i = 0; i < PRKMAX; i++) 
        parques_novo[i] = parques[i];
    return parques_novo;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Organiza o vetor de parques por ordem alfabética //
// Recebe um vetor de parques e o seu tamanho //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void parques_sort(Parque ** parques, int tamanho) {
    int i, j;
    Parque * key;

    for (i = 1; i < tamanho; i++) {
        key = parques[i];
        j = i - 1;

        while (j >= 0 && strcmp(parques[j]->nome, key->nome) > 0) {
        // se o nome do parque na posição j vier depois do nome do parque na posição i na ordem alfabética //
            parques[j + 1] = parques[j]; // o parque na posição j passa para a posição j+1 //
            j = j - 1;
        }
        parques[j + 1] = key; // o parque na posição i passa para a posição j+1 //
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Imprime os parques por ordem alfabética //
// Recebe um vetor de parques //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void print_parques(Parque ** parques) {
    Parque ** parques_novo = cria_copia_vec_parques(parques); // cria uma cópia do vetor de parques //
    int qntparques = qnt_parques(parques); // vai buscar o número de parques //
    parques_sort(parques_novo, qntparques); // organiza o vetor de parques por ordem alfabética //
    for(int i = 0; i < PRKMAX; i++) {
        if(parques_novo[i] != NULL) {
            printf("%s\n", parques_novo[i]->nome); // imprime os nomes dos parques //
        }
    }
    free(parques_novo);
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Muda os parques de indice maior do que o dado uma posição para trás //
// Recebe um vetor de parques, um índice e o número de parques //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void muda_parques_lugar(Parque ** parques, int indice, int qntparques) {
    for(int i = indice; i < qntparques; i++) {
        parques[i] = parques[i+1];
    }
    parques[qntparques] = NULL;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Remove um parque //
// Recebe um vetor de parques, um índice e a hashtable //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void removeprk(Parque ** parques, int indice, Hash_list * hashtable) {
    Parque * parque = parques[indice]; // aponta para o parque com o índice dado //
    int qntparques = qnt_parques(parques); // vai buscar o número de parques //
    
    removelista_dentro_e_fora(parque); // remove as listas de carros //
    remove_entradas_hash(hashtable, parque); // remove as entradas na hashtable //

    free(parque->nome); // liberta o espaço do nome //
    free(parque); // liberta o espaço do parque //

    muda_parques_lugar(parques, indice, qntparques); // muda os parques de lugar //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Liberta toda a memória alocada e termina o programa //
// Recebe um vetor de parques, a data atual, a hora atual e a hashtable //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void q(Parque ** parques, Data * data_actual, Horas * hora_actual, Hash_list * hashtable) {
    for(int i = 0; i < PRKMAX; i++) {
        if(parques[i] != NULL)
            removeprk(parques, i, hashtable); // remove os parques e registos //
    }
    free(data_actual); // liberta o resto da memória alocada //
    free(hora_actual);
    free(hashtable);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica os argumentos dados e remove o parque pedido //
// Recebe um vetor de parques, um vetor de palavras e a hashtable //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void r(Parque ** parques, char ** palavras, Hash_list * hashtable){
    char * nome = palavras[1];
    int indice = indice_parque(parques, nome);

    if(indice == -1) { // se o parque não existir //
        printf("%s: no such parking.\n", nome);
        return;
    }

    removeprk(parques, indice, hashtable); // remove o parque //
    print_parques(parques); // imprime os parques restantes //
}


