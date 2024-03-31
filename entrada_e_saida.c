#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"
#include "entrada_e_saida.h"
#include "parque.h"
#include "datas.h"
#include "nodes.h"
#include "hash.h"

#define TRUE 1
#define FALSE 0

#define IN 0
#define OUT 1

#define BUFFER 8192
#define VECMAX 20

int verifica_matriculas(Matricula matricula){ 
    char v[3][3];
    int i, numeros = 0, letras = 0;
    strcpy(v[0], matricula.par1); // copia os pares da matricula para um vetor //
    strcpy(v[1], matricula.par2);
    strcpy(v[2], matricula.par3);

    for(i = 0; i < 3; i++){ // para cada par //
        if(v[i][0] <= 58 && v[i][0] >= 48) { // verifica se o primeiro elemento é um numero //
            if(v[i][1] <= 58 && v[i][1] >= 48)
                numeros++; // e se o segundo também for, passa //
            
            else
                return FALSE; // se não devolve FALSE //
        }
        else {
            if(v[i][0] <= 'Z' && v[i][0] >= 'A') { //verifica se o primeiro elemento é uma letra maiúscula //
                if(v[i][1] <= 'Z' && v[i][1] >= 'A')
                    letras++; // e se o segundo também for, passa //
                else
                    return FALSE; // se não devolve FALSE (0) //
            }
            else 
                return FALSE; // se não devolve FALSE (0) //
        }
    }
    if(numeros == 3 || letras == 3) // se todos os pares forem compostos por letras ou numeros, devolve FALSE (0) //
        return FALSE;

    return TRUE; // se passar os testes devolve TRUE (1) //
}

int mesma_matricula(Matricula matricula1, Matricula matricula2) {
    if(!strcmp(matricula1.par1, matricula2.par1) && // verifica se os pares das matriculas são iguais //
        !strcmp(matricula1.par2, matricula2.par2) &&
        !strcmp(matricula1.par3, matricula2.par3))
        return TRUE; // se forem iguais, devolve TRUE (1) //
    return FALSE; // se não forem iguais, devolve FALSE (0) //
}

int verifica_carro_dentro_1parque(Matricula matricula1, Parque * parque) {
    node * vetor_node;
    vetor_node = parque->carros_dentro; // é a cabeça para a lista de carros //

    while(vetor_node != NULL) { // enquanto a cabeça não for nula //
        if(mesma_matricula(matricula1, vetor_node->carro->matricula) && vetor_node->carro->dentro == IN)
            // verifica se os pares das duas matriculas são iguais, para cada carro no parque //
                return TRUE; // se alguma for, devolve TRUE (1) //
        vetor_node = vetor_node->next; // Se a atual não for, segue para a seguinte //
    }
    return FALSE; // Se nenhuma for, devolve FALSE (0) //
}

int verifica_carro_parques(Matricula matricula1, Parque ** vetor_parques) {
    int i;
    for(i = 0; i<VECMAX; i++) { // para cada parque no vetor //
        if(vetor_parques[i] != NULL && verifica_carro_dentro_1parque(matricula1, vetor_parques[i])) // verifica se o carro está no parque //
            return TRUE; // se estiver, devolve TRUE //
    }
    return FALSE; // se não estiver, devolve FALSE //
}


node * procura_carro_dentro(Parque * parque, Matricula matricula1) {
    node * head; 
    head = parque->carros_dentro; // é a cabeça da lista de carros do parque //

    while(head != NULL) { // se a cabeça não for NULL //
        if(mesma_matricula(matricula1, head->carro->matricula) && head->carro->dentro == IN)
            // verifica se os pares das matriculas são iguais //
            return head; // se forem iguais, devolve a cabeça //
        head = head->next; // se não forem iguais, segue para a cabeça seguinte//
    }
    return NULL; // se não encontrar, devolve NULL //
}

int carro_dentro(Parque ** parques, Matricula matricula1) {
    int i;
    node * node_carro;
    for(i = 0; i<VECMAX; i++) {
        if(parques[i] != NULL){
            node_carro = procura_carro_dentro(parques[i], matricula1);
            if(node_carro != NULL && node_carro->carro->dentro == IN)
                return TRUE;
        }
        
    }
    return FALSE;
}

Carro * procura_carro_fora(Parque * parque, Matricula matricula1) {
    node * head; 
    head = parque->carros_fora; // é a cabeça da lista de carros do parque //
    Carro * carro = NULL;

    while(head != NULL) { // se a cabeça não for NULL //
        if(mesma_matricula(matricula1, head->carro->matricula))
            // verifica se os pares das matriculas são iguais //
            carro = head->carro; // se forem iguais, devolve a cabeça //
        head = head->next; // se não forem iguais, segue para a cabeça seguinte//
    }
    return carro; // se não encontrar, devolve NULL //
}

int entrada(Matricula matricula, Data data, Horas hora, Parque * parque, Hash_list * hashtable) {
    Carro * carro;
    carro = (Carro*) malloc(sizeof(Carro)); // aloca memoria para um carro //

    carro->D_entrada.dia = data.dia; // põe os valores de data e hora na estrutura carro //
    carro->D_entrada.mes = data.mes;
    carro->D_entrada.ano = data.ano;
    carro->H_entrada.hora = hora.hora;
    carro->H_entrada.minuto = hora.minuto;
    carro->preco = 0; // quer dizer que o carro está dentro de um parque //p
    carro->dentro = IN; // quer dizer que o carro está dentro de um parque //
    strcpy(carro->matricula.par1, matricula.par1); // copia os valores da matricula para a estrutura carro //
    strcpy(carro->matricula.par2, matricula.par2);
    strcpy(carro->matricula.par3, matricula.par3);

    parque->carros_dentro = push(parque->carros_dentro, carro); // adiciona o novo carro à lista de carros do parque //
    parque->lugares_disponiveis -= 1; // retira um lugar disponível do parque //

    if(parque->head_cd == NULL) // se a cabeça da lista de carros dentro do parque for NULL //
            parque->head_cd = parque->carros_dentro; // adiciona a primeira cabeça //

    put_hashtable(hashtable, carro, parque); // adiciona o carro à hashtable //

    return 0;
} 

int saida(Carro * carro, Data data, Horas hora, Parque * parque) {
    carro->D_saida.ano = data.ano; // põe os valores de data e hora de saida na estrutura carro //
    carro->D_saida.mes = data.mes;
    carro->D_saida.dia = data.dia;
    carro->H_saida.hora = hora.hora;
    carro->H_saida.minuto = hora.minuto;
    carro->preco = preco_total(carro->D_entrada, carro->H_entrada, carro->D_saida, carro->H_saida, parque); // calcula o preço total do carro //
    carro->dentro = OUT; // quer dizer que o carro está fora do parque //

    parque->carros_fora = put(parque->carros_fora, carro); // adiciona o carro ao final lista de carros fora do parque //
    if (parque->head_cf == NULL) // se a cabeça da lista de carros fora do parque for NULL //
        parque->head_cf = parque->carros_fora; // adiciona a primeira cabeça //
    parque->lugares_disponiveis += 1; // adiciona um lugar disponível ao parque //

    return 0;
}

void e(Parque ** parques, Horas * hora_actual, Data * data_actual, char ** palavras, Hash_list * hashtable) {
    Data data;
    Horas hora;
    Matricula matricula;
    Parque * parque = vec_parque(parques, palavras[1]);

    if (parque == NULL){
        printf("%s: no such parking.\n", palavras[1]);
        return;
    }
    if (parque->lugares_disponiveis == 0) {
        printf("%s: parking is full.\n", palavras[1]);
        return;
    }
        
    sscanf(palavras[2], "%s-%s-%s", matricula.par1, matricula.par2, matricula.par3);
    matricula.par1[2] = '\0';
    matricula.par2[2] = '\0';
    matricula.par3[2] = '\0';

    if (verifica_matriculas(matricula) == FALSE) {
        printf("%s-%s-%s: invalid licence plate.\n", matricula.par1, matricula.par2, matricula.par3);
        return;
    }

    sscanf(palavras[3], "%d-%d-%d", &data.dia, &data.mes, &data.ano);
    sscanf(palavras[4], "%d:%d", &hora.hora, &hora.minuto);
    if (verifica_datas(data) == FALSE || verifica_horas(hora) == FALSE ||
        compara_datas(*data_actual, *hora_actual, data, hora) == FALSE) {
        printf("invalid date.\n");
        return;
    }

    if(hash_carro_dentro(hashtable, matricula) == TRUE){
        printf("%s-%s-%s: invalid vehicle entry.\n", matricula.par1, matricula.par2, matricula.par3);
        return;
    }

    entrada(matricula, data, hora, parque, hashtable);
    data_actual->dia = data.dia;
    data_actual->mes = data.mes;
    data_actual->ano = data.ano;
    hora_actual->hora = hora.hora;
    hora_actual->minuto = hora.minuto;

    printf("%s %d\n", parque->nome, parque->lugares_disponiveis);
}

void s(Parque ** parques, Horas * hora_actual, Data * data_actual, char ** palavras, Hash_list * hashtable) {
    Data data;
    Horas hora;
    Matricula matricula;
    Parque * parque = vec_parque(parques, palavras[1]);
    Carro * carro;

    if (parque == NULL){
        printf("%s: no such parking.\n", palavras[1]);
        return;
    }

    sscanf(palavras[2], "%s-%s-%s", matricula.par1, matricula.par2, matricula.par3);
    matricula.par1[2] = '\0';
    matricula.par2[2] = '\0';
    matricula.par3[2] = '\0';
    if (verifica_matriculas(matricula) == FALSE) {
        printf("%s-%s-%s: invalid licence plate.\n", matricula.par1, matricula.par2, matricula.par3);
        return;
    }

    sscanf(palavras[3], "%d-%d-%d", &data.dia, &data.mes, &data.ano);
    sscanf(palavras[4], "%d:%d", &hora.hora, &hora.minuto);
    if (verifica_datas(data) == FALSE || verifica_horas(hora) == FALSE ||
        compara_datas(*data_actual, *hora_actual, data, hora) == FALSE) {
        printf("invalid date.\n");
        return;
    }

    carro = hash_procura_carro_1parque(hashtable, matricula, parque);
    if(carro == NULL){
        printf("%s-%s-%s: invalid vehicle exit.\n", matricula.par1, matricula.par2, matricula.par3);
        return;
    }

    saida(carro, data, hora, parque);
    data_actual->dia = data.dia;
    data_actual->mes = data.mes;
    data_actual->ano = data.ano;
    hora_actual->hora = hora.hora;
    hora_actual->minuto = hora.minuto;

    printf("%s-%s-%s ", matricula.par1, matricula.par2, matricula.par3);
    print_data_hora(carro->D_entrada, carro->H_entrada);
    printf(" ");
    print_data_hora(data, hora);
    printf(" %.2f\n", carro->preco);
}