#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "headers.h"
#include "parque.h"
 
#define TRUE 1
#define FALSE 0

#define NAMEMAX 100
#define VECMAX 20



int verifica_capacidade(Parque* parque) {
    if(parque -> lugares_disponiveis <= 0) // verifica se a capacidade do parque é menor ou igual a 0 // 
        return FALSE; // se for devolve FALSE (0) //
    return TRUE; // se não devolve TRUE (1) //
}

int qnt_parques(Parque ** parques) {
    int i = 0;
    for(; i < VECMAX && parques[i] != NULL; i++); // percorre o vetor de parques até encontrar um parque que seja NULL //
    return i; // devolve o número de parques //
}

int verifica_qntparques(Parque ** parques) {
    int i = qnt_parques(parques); // vai buscar o número de parques //
    if(i == VECMAX) // se o i for igual a VECMAX (20) //
        return FALSE; // devolve FALSE (0) //
    return TRUE; // se não devolve TRUE (1) //
}

int verifica_parque(Parque ** vetor_parques, char * nome) {
    int i = 0;
    for(; i < VECMAX; i++) { // percorre o vetor de parques até encontrar um parque que seja NULL //
        if(vetor_parques[i] != NULL && !strcmp(vetor_parques[i] -> nome, nome)) // se o nome do parque for igual ao nome dado //
            return FALSE; // devolve FALSE (0) //
    }
    return TRUE; // se não devolve TRUE (1) //
}

Parque* vec_parque(Parque **vetor_parques, char v[]) { 
    // devolve o ponteiro para o parque que tem o nome em questão //

    int i; 
    for(i = 0; i<VECMAX; i++) { // para cada parque no vetor //
        if(vetor_parques[i] != NULL && !strcmp((vetor_parques[i])->nome, v)) // compara o nome do parque com o dado, se for igual //
            return vetor_parques[i]; // devolve o ponteiro para o parque com o nome dado //
    }
    return NULL; // se não devolve vetor nulo //
}

int indice_parque(Parque ** vetor_parques, char v[]) {
    int i;
    for(i = 0; i < VECMAX; i++) { // para cada parque no vetor //
        if(vetor_parques[i] != NULL && !strcmp((vetor_parques[i])->nome, v)) // compara o nome do parque com o dado, se for igual //
            return i; // devolve o índice do parque com o nome dado //
    }
    return -1; // se não devolve -1 //
}

int verifica_precos(int menos1h, int mais1h, int maxdia) {
    if(menos1h < 0 || mais1h < 0 || maxdia < 0) // se algum dos preços for menor que 0 //
        return FALSE; // devolve FALSE (0) //
    if(menos1h > mais1h || mais1h > maxdia) // se o preço de menos de 1h for maior que o preço de mais de 1h ou o preço de mais de 1h for maior que o preço de um dia //
        return FALSE; // devolve FALSE (0) //
    return TRUE; // se não devolve TRUE (1) //
}

void cria_parque(Parque ** parques, char* nome, int capacidade, float menos1h, float mais1h, float maxdia) {
    // cria um parque com o nome, capacidade e preços dados //
    int i = 0;
    Parque * parque = (Parque *) malloc(sizeof(Parque)); // aloca espaço para um parque //
    parque -> nome = (char *) malloc((strlen(nome)+1) * sizeof(char)); // aloca espaço para o nome do parque //
    strcpy(parque -> nome, nome); // copia o nome dado para o nome do parque //
    parque-> capacidade = capacidade; // a capacidade do parque é a capacidade dada //
    parque-> lugares_disponiveis = capacidade; // os lugares disponíveis são a capacidade do parque //
    parque-> menos1h = menos1h; // o preço de menos de 1h é o preço dado //
    parque-> mais1h = mais1h; // o preço de mais de 1h é o preço dado //
    parque-> maxdia = maxdia; // o preço de um dia é o preço dado //
    parque-> carros_dentro = NULL; // a lista de carros dentro é NULL //
    parque-> carros_fora = NULL; // a lista de carros fora é NULL //
    parque-> head_cd = NULL; // a cabeça da lista de carros dentro é NULL //
    parque-> head_cf = NULL; // a cabeça da lista de carros fora é NULL //

    for(; i < VECMAX && parques[i] != NULL; i++); 
    // percorre o vetor de parques até encontrar um parque que seja NULL //
    parques[i] = parque; // 3! // // o parque é adicionado ao vetor de parques //
}

void p_maior(Parque ** parques, char ** palavras) { // cria um parque  //
    char * nome;
    int capacidade = atoi(palavras[2]); // vai buscar a capacidade dada //
    float menos1h = atof(palavras[3]); // vai buscar o preço de menos de 1h dado //
    float mais1h = atof(palavras[4]); // vai buscar o preço de mais de 1h dado //
    float maxdia = atof(palavras[5]); // vai buscar o preço máximo de um dia dado //

    nome = (char*) malloc((strlen(palavras[1]) + 1) * sizeof(char));  // aloca espaço para o nome do parque //
    strcpy(nome, palavras[1]);  // copia o nome dado para o nome do parque //

    if(!verifica_qntparques(parques)) { // se o número de parques for maior que 20 //
        printf("too many parks.\n"); // imprime que há demasiados parques //
        return; // e sai da função //
    }

    if(verifica_parque(parques, nome) == FALSE) { // se o parque já existir //
        printf("%s: parking already exists.\n", nome); // imprime que o parque já existe //
        return; // e sai da função //
    }
    if(capacidade <= 0) { // se a capacidade for menor ou igual a 0 //
        printf("%d: invalid capacity.\n", capacidade); // imprime que a capacidade é inválida //
        return; // e sai da função //
    }
    if(verifica_precos(menos1h, mais1h, maxdia) == FALSE) { // se os preços forem inválidos //
        printf("invalid cost.\n"); // imprime que os preços são inválidos //
        return; // e sai da função //
    }

    cria_parque(parques, nome, capacidade, menos1h, mais1h, maxdia); // cria o parque //
}

void p_menor(Parque ** parques) { // imprime os parques no vetor parques //
    int i; 
    for(i = 0; i < VECMAX; i++) { // para cada parque no vetor de parques //
        if(parques[i] != NULL) // se o parque não for NULL //
            printf("%s %d %d\n", parques[i] -> nome, parques[i] -> capacidade, parques[i] -> lugares_disponiveis);
            // imprime o nome, a capacidade e os lugares disponíveis do parque //
    }
}
