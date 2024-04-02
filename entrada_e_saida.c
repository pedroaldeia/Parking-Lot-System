#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"
#include "entrada_e_saida.h"
#include "parque.h"
#include "datas.h"
#include "nodes.h"
#include "hash.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se a matricula é válida //
// Recebe uma matricula //
// Devolve TRUE (1) se for válida e FALSE (0) se não for //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
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
                return FALSE; 
        }
        else {
            if(v[i][0] <= 'Z' && v[i][0] >= 'A') { //verifica se o primeiro elemento é uma letra maiúscula //
                if(v[i][1] <= 'Z' && v[i][1] >= 'A')
                    letras++; // e se o segundo também for, passa //
                else
                    return FALSE; 
            }
            else 
                return FALSE; 
        }
    }
    if(numeros == 3 || letras == 3) // se todos os pares forem compostos por letras ou numeros, devolve FALSE (0) //
        return FALSE;

    return TRUE; 
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se as matriculas são iguais //
// Recebe duas matriculas //
// Devolve TRUE (1) se forem iguais e FALSE (0) se não forem //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int mesma_matricula(Matricula matricula1, Matricula matricula2) {
    if(!strcmp(matricula1.par1, matricula2.par1) && // verifica se os pares das matriculas são iguais //
        !strcmp(matricula1.par2, matricula2.par2) &&
        !strcmp(matricula1.par3, matricula2.par3))
        return TRUE; 
    return FALSE; 
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se o carro está dentro de um parque //
// Recebe uma matricula e um parque //
// Devolve TRUE (1) se estiver e FALSE (0) se não estiver //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int verifica_carro_dentro_1parque(Matricula matricula1, Parque * parque) {
    node * vetor_node;
    vetor_node = parque->carros_dentro;

    while(vetor_node != NULL) { // enquanto a cabeça não for nula //
        if(mesma_matricula(matricula1, vetor_node->carro->matricula) && vetor_node->carro->dentro == IN)
            // verifica se os pares das duas matriculas são iguais, para cada carro no parque //
                return TRUE; // se alguma for, devolve TRUE (1) //
        vetor_node = vetor_node->next;
    }
    return FALSE; 
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se o carro está dentro de algum parque //
// Recebe uma matricula e um vetor de parques //
// Devolve TRUE (1) se estiver e FALSE (0) se não estiver //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int verifica_carro_parques(Matricula matricula1, Parque ** vetor_parques) {
    int i;
    for(i = 0; i<PRKMAX; i++) { // para cada parque no vetor //
        if(vetor_parques[i] != NULL && verifica_carro_dentro_1parque(matricula1, vetor_parques[i])) 
        // verifica se o carro está no parque //
            return TRUE; // se estiver, devolve TRUE //
    }
    return FALSE; // se não estiver, devolve FALSE //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Dá entrada a um carro num parque //
// Recebe uma matricula, uma data, uma hora, um parque e uma hashtable //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void entrada(Matricula matricula, Data data, Horas hora, Parque * parque, Hash_list * hashtable) {
    Carro * carro;
    carro = (Carro*) malloc(sizeof(Carro));

    carro->D_entrada.dia = data.dia; // põe os valores de data e hora na estrutura carro //
    carro->D_entrada.mes = data.mes;
    carro->D_entrada.ano = data.ano;
    carro->H_entrada.hora = hora.hora;
    carro->H_entrada.minuto = hora.minuto;
    carro->preco = 0; 
    carro->dentro = IN; // quer dizer que o carro está dentro de um parque //
    // copia os valores da matricula para a estrutura carro //
    strcpy(carro->matricula.par1, matricula.par1); 
    strcpy(carro->matricula.par2, matricula.par2);
    strcpy(carro->matricula.par3, matricula.par3);

    parque->carros_dentro = push(parque->carros_dentro, carro); 
    // adiciona o novo carro à lista de carros do parque //
    parque->lugares_disponiveis -= 1; // retira um lugar disponível do parque //

    if(parque->head_cd == NULL) // se a cabeça da lista de carros dentro do parque for NULL //
            parque->head_cd = parque->carros_dentro; // adiciona a primeira cabeça //

    put_hashtable(hashtable, carro, parque); // adiciona o carro à hashtable //
} 


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Dá saída a um carro de um parque //
// Recebe um carro, uma data, uma hora e um parque //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void saida(Carro * carro, Data data, Horas hora, Parque * parque) {
    carro->D_saida.ano = data.ano; // põe os valores de data e hora de saida na estrutura carro //
    carro->D_saida.mes = data.mes;
    carro->D_saida.dia = data.dia;
    carro->H_saida.hora = hora.hora;
    carro->H_saida.minuto = hora.minuto;
    carro->preco = preco_total(carro->D_entrada, carro->H_entrada, carro->D_saida, carro->H_saida, parque); 
    // calcula o preço total a pagar //
    carro->dentro = OUT; 

    parque->carros_fora = put(parque->carros_fora, carro); 
    // adiciona o carro ao final lista de carros fora do parque //
    if (parque->head_cf == NULL) // se a cabeça da lista de carros fora do parque for NULL //
        parque->head_cf = parque->carros_fora; // adiciona a primeira cabeça //
    parque->lugares_disponiveis += 1; // adiciona um lugar disponível ao parque //
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se os argumentos são válidos para a entrada de um carro num parque //
// Recebe uma hashtable, a data atual, a hora atual, um parque, uma matricula, uma data e uma hora //
// Devolve TRUE (1) se forem válidos e FALSE (0) se não forem //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int verifica_e(Hash_list * hashtable, Data * data_actual, Horas * hora_actual, Parque * parque, Matricula matricula, Data data, Horas hora){
    if (parque->lugares_disponiveis == 0) { // se o parque estiver cheio //
        printf("%s: parking is full.\n", parque->nome); 
        return FALSE;
    }
    
    if (verifica_matriculas(matricula) == FALSE) { // se a matricula for inválida //
        printf("%s-%s-%s: invalid licence plate.\n", matricula.par1, matricula.par2, matricula.par3);
        return FALSE;
    }
    
    if (verifica_datas(data) == FALSE || verifica_horas(hora) == FALSE ||
        compara_datas(*data_actual, *hora_actual, data, hora) == FALSE) {
        // se a data ou a hora forem inválidas ou se a data e a hora forem anteriores à data e hora atuais //
        printf("invalid date.\n");
        return FALSE;
    }

    if(hash_carro_dentro(hashtable, matricula) == TRUE){ // se o carro já estiver dentro de algum parque //
        printf("%s-%s-%s: invalid vehicle entry.\n", matricula.par1, matricula.par2, matricula.par3);
        return FALSE;
    }

    return TRUE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se os argumentos são válidos e dá entrada a um carro num parque //
// Recebe um vetor de parques, a hora atual, a data atual, um vetor de palavras e uma hashtable //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void e(Parque ** parques, Horas * hora_actual, Data * data_actual, char ** palavras, Hash_list * hashtable) {
    Data data;
    Horas hora;
    Matricula matricula;
    Parque * parque = vec_parque(parques, palavras[1]); // procura o parque no vetor de parques //

    sscanf(palavras[2], "%s-%s-%s", matricula.par1, matricula.par2, matricula.par3);
    matricula.par1[2] = '\0'; // guarda a matricula //
    matricula.par2[2] = '\0';
    matricula.par3[2] = '\0';

    sscanf(palavras[3], "%d-%d-%d", &data.dia, &data.mes, &data.ano); // guarda a data e a hora //
    sscanf(palavras[4], "%d:%d", &hora.hora, &hora.minuto);

    if (parque == NULL){  // se o parque não existir //
        printf("%s: no such parking.\n", palavras[1]); 
        return;
    }

    if (verifica_e(hashtable, data_actual, hora_actual, parque, matricula, data, hora) == FALSE) 
        return; // verifica se os argumentos são válidos //

    entrada(matricula, data, hora, parque, hashtable); // dá entrada ao carro //
    data_actual->dia = data.dia; // atualiza a data e a hora atuais //
    data_actual->mes = data.mes;
    data_actual->ano = data.ano;
    hora_actual->hora = hora.hora;
    hora_actual->minuto = hora.minuto;
    // imprime a matricula e o parque //
    printf("%s %d\n", parque->nome, parque->lugares_disponiveis); 
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Verifica se os argumentos são válidos e dá saída a um carro de um parque //
// Recebe um vetor de parques, a hora atual, a data atual, um vetor de palavras e uma hashtable //
// Não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void s(Parque ** parques, Horas * hora_actual, Data * data_actual, char ** palavras, Hash_list * hashtable) {
    Data data;
    Horas hora;
    Matricula matricula;
    Parque * parque = vec_parque(parques, palavras[1]);
    Carro * carro;

    if (parque == NULL){ // se o parque não existir //
        printf("%s: no such parking.\n", palavras[1]); 
        return;
    }
    // guarda a matricula //
    sscanf(palavras[2], "%s-%s-%s", matricula.par1, matricula.par2, matricula.par3);
    matricula.par1[2] = '\0';
    matricula.par2[2] = '\0';
    matricula.par3[2] = '\0';
    if (verifica_matriculas(matricula) == FALSE) { // se a matricula for inválida //
        printf("%s-%s-%s: invalid licence plate.\n", matricula.par1, matricula.par2, matricula.par3);
        return;
    }
    // guarda a data e a hora //
    sscanf(palavras[3], "%d-%d-%d", &data.dia, &data.mes, &data.ano);
    sscanf(palavras[4], "%d:%d", &hora.hora, &hora.minuto);
    if (verifica_datas(data) == FALSE || verifica_horas(hora) == FALSE || 
        compara_datas(*data_actual, *hora_actual, data, hora) == FALSE) {
        // se a data ou a hora forem inválidas ou se a data e a hora forem anteriores à data e hora atuais //
        printf("invalid date.\n"); 
        return;
    }

    carro = hash_procura_carro_1parque(hashtable, matricula, parque); // procura o carro no parque //
    if(carro == NULL){ // se o carro não estiver no parque //
        printf("%s-%s-%s: invalid vehicle exit.\n", matricula.par1, matricula.par2, matricula.par3);
        return;
    }

    saida(carro, data, hora, parque); // dá saída ao carro //
    data_actual->dia = data.dia; // atualiza a data e a hora atuais //
    data_actual->mes = data.mes;
    data_actual->ano = data.ano;
    hora_actual->hora = hora.hora;
    hora_actual->minuto = hora.minuto;

    printf("%s-%s-%s ", matricula.par1, matricula.par2, matricula.par3); // imprime a matricula //
    print_data_hora(carro->D_entrada, carro->H_entrada); // imprime a data e a hora de entrada //
    printf(" ");
    print_data_hora(data, hora); // imprime a data e a hora de saída //
    printf(" %.2f\n", carro->preco); // imprime o preço total a pagar //
}