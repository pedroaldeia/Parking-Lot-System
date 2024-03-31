#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "headers.h"
#include "nodes.h"
#include "datas.h"
#include "parque.h"
#include "leitura.h"
#include "faturacao.h"

// Funções de faturação //


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Põe um preço no final da lista de preços //
// Recebe a lista de preços, o preço e a data //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void put_preco(List_preco * lista_precos, float preco, Data data) { // adiciona um elemento no fim //
    node_preco * novo = (node_preco*) malloc(sizeof(node_preco));
    novo->preco = preco;
    novo->data = data;
    novo->next = NULL;

    if(lista_precos->head == NULL) { // se a lista estiver vazia //
        lista_precos->head = novo; // a cabeça é o novo node //
        lista_precos->tail = novo; // e a cauda também //
    } else {
        lista_precos->tail->next = novo; // se não, a cauda aponta para o novo node //
        lista_precos->tail = novo; // e a cauda passa a ser o novo node //
    }
    lista_precos->size++; // aumenta o tamanho da lista //
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Devolve o preço pago por um carro //
// Recebe um node //
// Devolve o preço (float) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
float devolve_preco_carro(node * nodecarro) { // devolve o preço pago por um carro //
    return nodecarro->carro->preco; 
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Devolve a faturação por dia do parque //
// Recebe a cabeça da lista de carros //
// Devolve a lista de nodes preço //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
List_preco * devolve_preco_dias(node *head_carros) { 
    List_preco * list_precos = (List_preco*) malloc(sizeof(List_preco));
    list_precos->head = NULL; 
    list_precos->tail = NULL;
    list_precos->size = 0;

    while(head_carros != NULL) { 
        while(head_carros != NULL && list_precos->head != NULL && 
        mesma_data(head_carros->carro->D_saida, list_precos->tail->data)) { 
            // se a lista não for NULL e a data do carro for igual à data da cauda //
            list_precos->tail->preco += devolve_preco_carro(head_carros); 
            // soma o preço do carro à cauda //
            head_carros = head_carros->next;
        }
        if (head_carros != NULL) { // se a data passar a ser diferente //
            // adiciona um novo node à lista //
            put_preco(list_precos, devolve_preco_carro(head_carros), head_carros->carro->D_saida);
            head_carros = head_carros->next;
        }
    }
    return list_precos;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Imprime a faturação por dia //
// Recebe a lista de preços //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void print_precos(List_preco * list_precos) { 
    node_preco * head_precos = list_precos->head; 
    while(head_precos != NULL) { // enquanto a cabeça não for null //
        print_so_data(head_precos->data);
        printf(" %.2f\n", head_precos->preco);
        // imprime a data e o preço //
        head_precos = head_precos->next; 
    }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Liberta a memória alocada para a lista de preços //
// Recebe a lista de preços //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void free_precos(List_preco * list_precos) { 
    node_preco * head_precos = list_precos->head; 
    node_preco * temp;
    while(head_precos != NULL) { // enquanto a cabeça não for null //
        temp = head_precos; 
        head_precos = head_precos->next; // guarda o ponteiro do próximo node //
        free(temp); // liberta a memória alocada para o node //
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Faz as operações necessárias para imprimir a faturação de um parque por dia //
// Recebe o parque //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void faturacao(Parque * parque) { // imprime a faturação do parque //
    node * head_carros = parque->head_cf; // aponta para a cabeça da lista de carros //
    List_preco * lista_precos = devolve_preco_dias(head_carros); 
    // aponta para a cabeça da lista de preços //
    print_precos(lista_precos); // imprime a faturação por dia //
    free_precos(lista_precos); // liberta a memória dos nodes da lista de preços //
    free(lista_precos); // liberta a memória alocada para a lista de preços //
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Imprime a faturação de um parque por carro num determinado dia //
// Recebe a cabeça da lista de carros e a data //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void print_fatcarro(node * head_carros, Data data) { 
    while(head_carros != NULL && !mesma_data(head_carros->carro->D_saida, data)) { 
        // enquanto a cabeça não for null e a data da fatura for diferente da data //
        head_carros = head_carros->next; // passa para o próximo carro //
    }
    while(head_carros != NULL && mesma_data(head_carros->carro->D_saida, data)){ 
        // enquanto a data de fatura do carro for igual à data //
        printf("%s-%s-%s ", head_carros->carro->matricula.par1, head_carros->carro->matricula.par2,
            head_carros->carro->matricula.par3); // imprime a matrícula //
        print_so_hora(head_carros->carro->H_saida); // imprime a data e a hora de saída //
        printf(" %.2f\n", head_carros->carro->preco); // imprime o preço pago pelo carro //
        head_carros = head_carros->next;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se os argumentos são válidos e faz imprimir a faturação de um parque num determinado dia //
// Recebe o vetor de parques, as palavras e a data atual //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void f_menor(Parque ** parques, char ** palavras, Data * data_actual) {
    char * nome = palavras[1];
    Parque * parque = vec_parque(parques, nome); // aponta para o parque com o nome dado //
    Data data;

    if(parque == NULL) { // se o parque não existir //
        printf("%s: no such park.\n", nome); 
        return;
    }

    sscanf(palavras[2], "%d-%d-%d", &data.dia, &data.mes, &data.ano); // vai buscar a data dada //

    if(verifica_datas(data) == FALSE || (compara_so_datas(data, *(data_actual))  == FALSE
        && mesma_data(data, *data_actual) == FALSE)){
        // se a data for inválida ou se a data for posterior à data atual //
        printf("invalid date.\n"); 
        return;
    }

    print_fatcarro(parque->head_cf, data); // imprime a faturação de um carro no dia dado //
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se os argumentos são válidos e faz imprimir a faturação de um parque por dia //
// Recebe o vetor de parques e as palavras //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void f_maior(Parque ** parques, char ** palavras) { // imprime a faturação de um parque por dias //
    char * nome = palavras[1];
    Parque * parque = vec_parque(parques, nome); // aponta para o parque com o nome dado //

    if(parque == NULL) { // se o parque não existir //
        printf("%s: no such park.\n", nome);
        return;
    }

    faturacao(parque); // imprime a faturação do parque por dias //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Decide qual das funções f chamar //
// Recebe o vetor de parques, as palavras, o número de palavras e a data atual //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void f(Parque ** parques, char ** palavras, int n_palavras, Data * data_actual) { 
    if (n_palavras < 3) { // se o input tiver menos de 3 palavras //
        f_maior(parques, palavras);
    }
    else {
        f_menor(parques, palavras, data_actual);
    }
}
