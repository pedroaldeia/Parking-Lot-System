#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "headers.h"
#include "datas.h"
#include "hash.h"
#include "entrada_e_saida.h"
#include "veiculo.h"

#define IN 0
#define OUT 1
#define FALSE 0
#define TRUE 1

Matricula cria_matricula(char * matricula) { // cria uma matricula a partir de uma string //
    Matricula mat;
    sscanf(matricula, "%s-%s-%s", mat.par1, mat.par2, mat.par3); // lê a string e guarda os valores nas variáveis //
    mat.par1[2] = '\0'; // coloca o caracter nulo no fim de cada string //
    mat.par2[2] = '\0';
    mat.par3[2] = '\0';
    return mat; // devolve a matricula //
}

void sort_entradas_by_park_name(Hash_node **entradas, int tamanho) {
    int i, j;
    Hash_node *key;

    for (i = 1; i < tamanho; i++) {
        key = entradas[i];
        j = i - 1;

        while (j >= 0 && strcmp(entradas[j]->parque->nome, key->parque->nome) > 0) {
            entradas[j + 1] = entradas[j];
            j = j - 1;
        }
        entradas[j + 1] = key;
    }
}

void sort_entradas_by_park_name_and_date(Hash_node **entradas, int tamanho) {
    sort_entradas_by_park_name(entradas, tamanho); // Sort by park name

    int i, j;
    Hash_node *key;

    for (i = 1; i < tamanho; i++) {
        key = entradas[i];
        j = i - 1;

        while (j >= 0 && strcmp(entradas[j]->parque->nome, key->parque->nome) == 0 && compara_datas(entradas[j]->carro->D_entrada, entradas[j]->carro->H_entrada, key->carro->D_entrada, key->carro->H_entrada) == FALSE) {
            entradas[j + 1] = entradas[j];
            j = j - 1;
        }
        entradas[j + 1] = key;
    }
}

Hash_node ** busca_entradas(Hash_list * hashtable, Matricula matricula) { // procura as entradas de um veículo //
    int index = hash_index(matricula), tamanho = hashtable[index].size, i;
    Hash_node ** entradas;
    Hash_node * node = hashtable[index].head; // aponta para o primeiro node da lista de faturações //

    entradas = (Hash_node**) malloc(sizeof(Hash_node) * tamanho);  // aloca espaço para um array de nodes //

    for (i = 0; node != NULL && i < tamanho;) { // para cada node da lista de faturações //
        if (mesma_matricula(node->carro->matricula, matricula)) { // se a matricula do carro for igual à matricula procurada //
            entradas[i] = node; // adiciona o node ao array //
            i++;
        }
        node = node->next; // passa para o próximo node //
    }
    if (i == 0) { // se não houver entradas //
        printf("%s-%s-%s: no entries found in any parking.\n", matricula.par1, matricula.par2, matricula.par3);
        // devolve uma mensagem de erro //
        return NULL; // e devolve NULL //
    }

    entradas = (Hash_node**) realloc(entradas, sizeof(Hash_node) * i); 
    // realoca o espaço para o array de nodes (para o espaço total utilizado pelo array) //
    entradas[i] = NULL; // coloca um NULL no fim do array //
    sort_entradas_by_park_name_and_date(entradas, i); // organiza o array de nodes //

    return entradas; // devolve o array de nodes //
}



void print_carro(Hash_node * node) { // imprime um carro //
    Carro * carro = node->carro; // aponta para o carro do node //
    printf("%s ", node->parque->nome); // imprime o nome do parque //
    print_data_hora(carro->D_entrada, carro->H_entrada); // imprime a data e a hora de entrada //
    if (carro->dentro == OUT) { // se o carro já tiver saído //
        printf(" ");
        print_data_hora(carro->D_saida, carro->H_saida); // imprime a data e a hora de saída //
    }    
    printf("\n");
}

void veiculo(Hash_list * hashtable, Matricula matricula) { // imprime as entradas de um veículo //
    Hash_node ** entradas = busca_entradas(hashtable, matricula); // procura as entradas do veículo //

    if (entradas == NULL) // se não houver entradas //
        return; // retorna //

    for (int i = 0; entradas[i] != NULL; i++) { // para cada entrada do veículo //
        print_carro(entradas[i]); // imprime o carro //
    }
    free(entradas); // liberta o espaço alocado para o array de nodes //
}



void v(Hash_list * hashtable, char ** palavras) { // faz tudo //
    Matricula matricula = cria_matricula(palavras[1]); // cria a matricula a partir da string //

    if (verifica_matriculas(matricula) == FALSE) { // se a matricula for inválida //
        printf("%s-%s-%s: invalid licence plate.\n", matricula.par1, matricula.par2, matricula.par3);
        // imprime uma mensagem de erro //
        return; // e retorna //
    }

    veiculo(hashtable, matricula); // imprime as entradas do veículo //
}



