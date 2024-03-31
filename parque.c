#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "headers.h"
#include "parque.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se a capacidade do parque é menor ou igual a 0 //
// Recebe um ponteiro para o parque //
// Devolve TRUE (1) se a capacidade for maior que 0, FALSE (0) se for menor (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int verifica_capacidade(Parque* parque) {
    if(parque -> lugares_disponiveis <= 0) 
        return FALSE; 
    return TRUE; 
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Conta a quantidade de parques no vetor de parques //
// Recebe um vetor de parques //
// Devolve o número de parques (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int qnt_parques(Parque ** parques) {
    int i = 0;
    for(; i < PRKMAX && parques[i] != NULL; i++); // percorre o vetor de parques até encontrar um parque que seja NULL //
    return i; // devolve o número de parques //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se o número de parques é maior que 20 //
// Recebe um vetor de parques //
// Devolve TRUE (1) se o número de parques for menor que 20, FALSE (0) se for maior (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int verifica_qntparques(Parque ** parques) {
    int i = qnt_parques(parques); // vai buscar o número de parques //
    if(i == PRKMAX) // se o i for igual a PRKMAX (20) //
        return FALSE; // devolve FALSE (0) //
    return TRUE; // se não devolve TRUE (1) //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se o parque com o nome dado já existe no vetor de parques //
// Recebe um vetor de parques e um nome //
// Devolve TRUE (1) se o parque não existir, FALSE (0) se existir (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int verifica_parque(Parque ** vetor_parques, char * nome) {
    int i = 0;
    for(; i < PRKMAX; i++) { // percorre o vetor de parques até encontrar um parque que seja NULL //
        if(vetor_parques[i] != NULL && !strcmp(vetor_parques[i] -> nome, nome)) // se o nome do parque for igual ao nome dado //
            return FALSE; // devolve FALSE (0) //
    }
    return TRUE; // se não devolve TRUE (1) //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Devolve o ponteiro para o parque que tem o nome dado //
// Recebe um vetor de parques e um nome //
// Devolve um ponteiro para o parque (Parque*) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
Parque* vec_parque(Parque **vetor_parques, char v[]) { 

    int i; 
    for(i = 0; i < PRKMAX; i++) { // para cada parque no vetor //
        if(vetor_parques[i] != NULL && !strcmp((vetor_parques[i])->nome, v)) 
        // compara o nome do parque com o dado, se for igual //
            return vetor_parques[i];
    }
    return NULL; // se não devolve vetor nulo //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Devolve o índice do parque que tem o nome dado //
// Recebe um vetor de parques e um nome //
// Devolve o índice do parque (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int indice_parque(Parque ** vetor_parques, char v[]) {
    int i;
    for(i = 0; i < PRKMAX; i++) { // para cada parque no vetor //
        if(vetor_parques[i] != NULL && !strcmp((vetor_parques[i])->nome, v)) 
        // compara o nome do parque com o dado, se for igual //
            return i; 
    }
    return -1; // se não devolve -1 //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se os preços dados são válidos //
// Recebe os preços de menos de 1h, mais de 1h e de um dia //
// Devolve TRUE (1) se os preços forem válidos, FALSE (0) se não forem (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int verifica_precos(float menos1h, float mais1h, float maxdia) {
    if(menos1h <= 0 || mais1h <= 0 || maxdia <= 0) // se algum dos preços for menor que 0 //
        return FALSE;
    if(menos1h > mais1h || mais1h > maxdia) 
    // se o preço de menos de 1h for maior que o preço de mais de 1h ou o preço de mais de 1h 
    // for maior que o preço de um dia //
        return FALSE;
    return TRUE; 
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Cria um parque com o nome, capacidade e preços dados //
// Recebe um vetor de parques, um nome, uma capacidade, os preços de menos de 1h, 
// mais de 1h e de um dia //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void cria_parque(Parque ** parques, char* nome, int capacidade, float menos1h, float mais1h, float maxdia) {
    // cria um parque com o nome, capacidade e preços dados //
    int i = 0;
    Parque * parque = (Parque *) malloc(sizeof(Parque)); // aloca espaço para um parque //
    parque -> nome = (char *) malloc((strlen(nome)+1) * sizeof(char)); // aloca espaço para o nome do parque //
    strcpy(parque -> nome, nome); // atribui os valores dados ao parque //
    parque-> capacidade = capacidade; 
    parque-> lugares_disponiveis = capacidade;
    parque-> menos1h = menos1h; 
    parque-> mais1h = mais1h; 
    parque-> maxdia = maxdia; 
    parque-> carros_dentro = NULL; // inicializa as listas a NULL //
    parque-> carros_fora = NULL; 
    parque-> head_cd = NULL; 
    parque-> head_cf = NULL;

    for(; i < PRKMAX && parques[i] != NULL; i++); 
    // percorre o vetor de parques até encontrar um parque que seja NULL //
    parques[i] = parque; // o parque é adicionado ao vetor de parques //
    free(nome); // liberta a memória alocada para o nome //
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica os argumentos e cria um parque //
// Recebe um vetor de parques e um vetor de palavras //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void p_maior(Parque ** parques, char ** palavras) { 
    char * nome;
    int capacidade = atoi(palavras[2]); // vai buscar a capacidade dada //
    float menos1h = atof(palavras[3]); // vai buscar o preço de menos de 1h dado //
    float mais1h = atof(palavras[4]); // vai buscar o preço de mais de 1h dado //
    float maxdia = atof(palavras[5]); // vai buscar o preço máximo de um dia dado //

    nome = (char*) malloc((strlen(palavras[1]) + 1) * sizeof(char)); // aloca espaço para o nome do parque //
    strcpy(nome, palavras[1]);  // copia o nome dado para o nome do parque //

    if(!verifica_qntparques(parques)) { // se o número de parques for maior que 20 //
        printf("too many parks.\n"); 
        return; 
    }

    if(verifica_parque(parques, nome) == FALSE) { // se o parque já existir //
        printf("%s: parking already exists.\n", nome); 
        return; 
    }
    if(capacidade <= 0) { // se a capacidade for menor ou igual a 0 //
        printf("%d: invalid capacity.\n", capacidade); 
        return; 
    }
    if(verifica_precos(menos1h, mais1h, maxdia) == FALSE) { // se os preços forem inválidos //
        printf("invalid cost.\n"); 
        return; 
    }

    cria_parque(parques, nome, capacidade, menos1h, mais1h, maxdia); // cria o parque //
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// imprime os parques no vetor parques //
// Recebe um vetor de parques //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void p_menor(Parque ** parques) { // imprime os parques no vetor parques //
    int i; 
    for(i = 0; i < PRKMAX; i++) { // para cada parque no vetor de parques //
        if(parques[i] != NULL) 
            printf("%s %d %d\n", parques[i]->nome, parques[i] -> capacidade, 
            parques[i] -> lugares_disponiveis);
            // imprime o nome, a capacidade e os lugares disponíveis do parque //
    }
}
