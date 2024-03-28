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

int verifica_qntparques(Parque ** parques) {
    int i = 0;
    for(; i < VECMAX && parques[i] != NULL; i++); // percorre o vetor de parques até encontrar um parque que seja NULL //
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

int verifica_precos(int menos1h, int mais1h, int maxdia) {
    if(menos1h < 0 || mais1h < 0 || maxdia < 0) // se algum dos preços for menor que 0 //
        return FALSE; // devolve FALSE (0) //
    if(menos1h > mais1h || mais1h > maxdia) // se o preço de menos de 1h for maior que o preço de mais de 1h ou o preço de mais de 1h for maior que o preço de um dia //
        return FALSE; // devolve FALSE (0) //
    return TRUE; // se não devolve TRUE (1) //
}

void cria_parque(Parque ** parques, char* nome, int capacidade, float menos1h, float mais1h, float maxdia) {
    int i = 0;
    Parque * parque = (Parque *) malloc(sizeof(Parque));
    parque -> nome = (char *) malloc((strlen(nome)+1) * sizeof(char));
    strcpy(parque -> nome, nome);
    parque-> capacidade = capacidade;
    parque-> lugares_disponiveis = capacidade;
    parque-> menos1h = menos1h;
    parque-> mais1h = mais1h;
    parque-> maxdia = maxdia;
    parque-> carros_dentro = NULL;
    parque-> carros_fora = NULL;
    parque-> head_cd = NULL;
    parque-> head_cf = NULL;

    for(; i < VECMAX && parques[i] != NULL; i++);
    parques[i] = parque; // 3! //
}

void p_maior(Parque ** parques, char ** palavras) {
    char * nome;
    int capacidade = atoi(palavras[2]);
    float menos1h = atof(palavras[3]);
    float mais1h = atof(palavras[4]);
    float maxdia = atof(palavras[5]);

    nome = (char*) malloc((strlen(palavras[1]) + 1) * sizeof(char));
    strcpy(nome, palavras[1]);  

    if(!verifica_qntparques(parques)) {
        printf("too many parks.\n");
        return;
    }

    if(!verifica_parque(parques, nome)) {
        printf("%s: parking already exists.\n", nome);
        return;
    }
    if(capacidade <= 0) {
        printf("%d: invalid capacity.\n", capacidade);
        return;
    }
    if(!verifica_precos(menos1h, mais1h, maxdia)) {
        printf("invalid cost.\n");
        return;
    }

    cria_parque(parques, nome, capacidade, menos1h, mais1h, maxdia);
}

void p_menor(Parque ** parques) {
    int i;
    for(i = 0; i < VECMAX; i++) {
        if(parques[i] != NULL) 
            printf("%s %d %d\n", parques[i] -> nome, parques[i] -> capacidade, parques[i] -> lugares_disponiveis);
    }
}
