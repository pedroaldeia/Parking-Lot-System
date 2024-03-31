#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "headers.h"
#include "parque.h"
#include "nodes.h"
#include "entrada_e_saida.h"
#include "hash.h" 

// Funções para a hashtable //


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Retira o primeiro nó de uma lista da hashtable //
// Recebe um ponteiro para o primeiro nó da lista //
// Devolve um ponteiro para o segundo nó da lista (Hash_node*) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Hash_node * hash_pop(Hash_node * head) { 
    Hash_node* newhead = head->next; // vai buscar o ponteiro para o node seguinte //

    free(head); // liberta o ponteiro original //
    return newhead; // torna o ponteiro seguinte na cabeça //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Retira o primeiro nó de uma lista da hashtable, e inclusivamente liberta o espaço do carro que contém //
// Recebe um ponteiro para o primeiro nó da lista //
// Devolve um ponteiro para o segundo nó da lista (Hash_node*) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Hash_node * hash_pop_ccarro(Hash_node * head) { 
    Hash_node * newhead = head->next; // vai buscar o ponteiro para o node seguinte //
    if (head->carro != NULL)
        free(head->carro); // liberta o ponteiro do carro //
    free(head); // liberta o ponteiro original //
    return newhead; // torna o ponteiro seguinte na cabeça //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Retira o nó da lista posterior ao nó dado //
// Recebe um ponteiro para o nó anterior ao nó a retirar //
// Devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void hash_removenode(Hash_node * head) { // retira um elemento de uma lista de nodes //
    Hash_node * toremove;
    if(head == NULL || head->next == NULL)
        return;
    toremove = head->next; // aponta para o node a retirar //
    head->next = head->next->next; // retira o node da lista //
    free(toremove); // liberta o node //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Adiciona um nó no início da lista //
// Recebe um ponteiro para o primeiro nó da lista, um ponteiro para um carro e um ponteiro para um parque //
// Devolve um ponteiro para o novo primeiro nó da lista (Hash_node *) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Hash_node * hash_push(Hash_node * head, Carro * newcarro, Parque * parque) {
    Hash_node * newhead; 
    newhead = (Hash_node*) malloc(sizeof(Hash_node)); // aloca espaço para um novo node //
    newhead-> next = head; // adiciona o ponteiro para a cabeça no novo node //
    newhead-> carro = newcarro; // adiciona a informação no novo node //
    newhead-> parque = parque;
    return newhead; // devolve a nova cabeça //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Destroi uma lista de nodes da hashtable //
// Recebe um ponteiro para o primeiro nó da lista //
// Devolve um ponteiro para NULL //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Hash_node* hash_destroy(Hash_node* head) {
    if(head != NULL) // enquanto a cabeça não for null //
        return hash_destroy(hash_pop(head)); // retira a cabeça à lista //
    return NULL;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Devolve o numero correspondente à matricula //
// Recebe uma matricula //
// Devolve o número (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int numero_matricula(Matricula matricula){ 
    return (matricula.par1[0] + matricula.par1[1] + matricula.par2[0] 
        + matricula.par2[1] + matricula.par3[0] + matricula.par3[1]); 
        // soma os valores ASCII dos caracteres //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Devolve o índice da hashtable correspondente à matricula //
// Recebe uma matricula //
// Devolve o índice (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int hash_index(Matricula matricula){ 
    return numero_matricula(matricula) % HASHSIZE;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Põe um carro na hashtable //
// Recebe um ponteiro para a hashtable, um ponteiro para um carro e um ponteiro para um parque //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void put_hashtable(Hash_list * hashtable, Carro * carro, Parque * parque) {
    // põe um node na hashtable //
    int index = hash_index(carro->matricula); // vai buscar o índice da matricula //
    Hash_node * nexnode;
    nexnode = (Hash_node*) malloc(sizeof(Hash_node)); // aloca espaço para um novo node //

    if (hashtable[index].tail != NULL) { // se a cauda não for null //
        hashtable[index].tail-> next = nexnode; // a cauda aponta para o novo node //
        hashtable[index].tail = nexnode; // a cauda passa a ser o novo node //
    }
        
    if (hashtable[index].head == NULL){ // se a cabeça for null //
        hashtable[index].head = nexnode; // a cabeça passa a ser o novo node //
        hashtable[index].tail = nexnode; // e a cauda também //
    }
    nexnode-> next = NULL; // o ponteiro para o node a seguir é null //
    nexnode-> carro = carro; // o node aponta para o carro //
    nexnode-> parque = parque; // o node aponta para o parque //
    hashtable[index].size++; // aumenta o tamanho da lista na hashtable //
}



Carro * hash_procura_carro_dentro(Hash_list * hashtable, Matricula matricula) { 
    // procura um carro dentro da hashtable // 
    int index = hash_index(matricula); // vai buscar o índice da matricula //
    Hash_node * node = hashtable[index].head; // aponta para o primeiro node da lista de faturações //
    while(node != NULL) { // enquanto o node não for null //
        if(mesma_matricula(node->carro->matricula, matricula) && node->carro->dentro == IN) {
            // se a matricula do carro for igual à matricula procurada e o carro estiver dentro //
            return node->carro; // devolve o carro //
        }
        node = node->next; // se não passa para o próximo node //
    }
    return NULL; // se não encontrar devolve null //
}

int hash_carro_dentro(Hash_list * hashtable, Matricula matricula){ 
    // verifica se um carro está dentro da hashtable //
    if (hash_procura_carro_dentro(hashtable, matricula) != NULL) // se o carro estiver dentro //
        return TRUE; // devolve true //
    return FALSE; // se não devolve false //
}

Carro * hash_procura_carro_1parque(Hash_list * hashtable, Matricula matricula, Parque * parque){
    // procura um carro num parque //
    int index = hash_index(matricula); // vai buscar o índice da matricula //
    Hash_node * node = hashtable[index].head; // aponta para o primeiro node da lista de faturações //
    while(node != NULL) { // enquanto o node não for null //
        if(mesma_matricula(node->carro->matricula, matricula) && node->parque == parque 
        && node->carro->dentro == IN) {
        // se a matricula do carro for igual à matricula procurada, o parque for igual ao procurado 
        // e o carro estiver dentro //
            return node->carro; // devolve o carro //
        }
        node = node->next; // se não passa para o próximo node //
    }
    return NULL; // se não encontrar devolve null //
}

Hash_list * cria_hash() { 
    Hash_list * hashtable = (Hash_list*) malloc(sizeof(Hash_list) * HASHSIZE); 
    // aloca espaço para a hashtable //
    int i;
    for(i = 0; i < HASHSIZE; i++) { // para cada índice //
        hashtable[i].head = NULL; // inicializa os componentes da lista a NULL e 0 //
        hashtable[i].tail = NULL;
        hashtable[i].size = 0;
    }
    return hashtable; // devolve a hashtable //
}