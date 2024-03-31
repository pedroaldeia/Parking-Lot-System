#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "headers.h"
#include "datas.h"
#include "hash.h"
#include "entrada_e_saida.h"
#include "veiculo.h"


Matricula cria_matricula(char * matricula) { // cria uma matricula a partir de uma string //
    Matricula mat;
    sscanf(matricula, "%s-%s-%s", mat.par1, mat.par2, mat.par3); // lê a string e guarda os valores nas variáveis //
    mat.par1[2] = '\0'; // coloca o caracter nulo no fim de cada string //
    mat.par2[2] = '\0';
    mat.par3[2] = '\0';
    return mat; // devolve a matricula //
}

void sort_entradas_nome(Hash_node **entradas, int tamanho) { // ordena as entradas por nome do parque //
    int i, j;
    Hash_node *key;

    for (i = 1; i < tamanho; i++) { // para cada entrada //
        key = entradas[i]; // guarda a entrada //
        j = i - 1; // guarda o índice anterior //

        while (j >= 0 && strcmp(entradas[j]->parque->nome, key->parque->nome) > 0) { // enquanto o nome do parque for maior //
            entradas[j + 1] = entradas[j]; // troca as entradas //
            j = j - 1; // passa para a entrada anterior //
        }
        entradas[j + 1] = key; // coloca a entrada na posição correta //
    }
}

void sort_entradas_nome_data(Hash_node **entradas, int tamanho) {
    sort_entradas_nome(entradas, tamanho); // ordena as entradas por nome do parque //

    int i, j;
    Hash_node *key;

    for (i = 1; i < tamanho; i++) { // para cada entrada //
        key = entradas[i]; // guarda a entrada //
        j = i - 1; // guarda o índice anterior //

        while (j >= 0 && strcmp(entradas[j]->parque->nome, key->parque->nome) == 0 
            && compara_datas(entradas[j]->carro->D_entrada, entradas[j]->carro->H_entrada, 
            key->carro->D_entrada, key->carro->H_entrada) == FALSE) {
            // enquanto o nome do parque for igual e a data de entrada for menor //
            entradas[j + 1] = entradas[j]; // troca as entradas //
            j = j - 1; // passa para a entrada anterior //
        }
        entradas[j + 1] = key; // coloca a entrada na posição correta //
    }
}

Hash_node ** busca_entradas(Hash_list * hashtable, Matricula matricula) { // procura as entradas de um veículo //
    int index = hash_index(matricula), tamanho = hashtable[index].size + 1, i;
    Hash_node ** entradas = NULL;
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
        free(entradas); // liberta o espaço alocado para o array de nodes //
        return NULL; // e devolve NULL //
    }
    entradas[i] = NULL; // coloca um NULL no fim do array //

    entradas = (Hash_node**) realloc(entradas, sizeof(Hash_node) * i); 
    // realoca o espaço para o array de nodes (para o espaço total utilizado pelo array) //
    entradas[i] = NULL; // coloca um NULL no fim do array //
    sort_entradas_nome_data(entradas, i); // organiza o array de nodes //

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



