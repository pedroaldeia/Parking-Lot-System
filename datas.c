#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int v_meses[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// verifica se a data é válida //
// recebe uma data //
// devolve 1 se a data for válida e 0 se não for (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int verifica_datas(Data data) {
    if(data.mes < 13 && data.mes > 0) { // se o mês for de 1 a 12 //
        if(data.dia > 0 && data.dia <= v_meses[data.mes]) { 
            // e se o dia for de 1 ao último dia do mês respectivo //
            return TRUE; // devolve TRUE (1) //
        }
    }
    return FALSE; // se não devolve FALSE (0) //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// verifica se as horas são válidas //
// recebe as horas //
// devolve 1 se as horas forem válidas e 0 se não forem (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int verifica_horas(Horas horas) {
    if(horas.minuto >= 0 && horas.minuto < 60) { // se o minuto for de 0 a 60 //
        if(horas.hora >= 0 && horas.hora < 24) // e se a hora for de 0 a 23 //
            return TRUE; // devolve TRUE (1) //
    }
    return FALSE; // se não devolve FALSE (0) //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// verifica se as datas são iguais //
// recebe duas datas //
// devolve 1 se as datas forem iguais e 0 se não forem (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int mesma_data(Data data1, Data data2) {
    if(data1.dia == data2.dia && data1.mes == data2.mes && data1.ano == data2.ano) 
    // se os dias, meses e anos forem iguais //
        return TRUE; // devolve TRUE (1) //
    return FALSE; // se não devolve FALSE (0) //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// verifica se a data e hora 1 é menor que a data e hora 2 //
// recebe duas datas //
// devolve 1 se a data e hora 1 for menor que a data e hora 2 e 0 se não for, e devolve 1 se forem iguais //
// (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int compara_datas(Data data1, Horas hora1, Data data2, Horas hora2) {
    if(data1.ano > data2.ano) // compara cada elemento das datas e das horas //
        return FALSE; // se o elemento da data 1 for maior do que o da data 2, devolve FALSE //
    if(data2.ano > data1.ano) // se o elemento da data 2 for maior, devolve TRUE //
        return TRUE; 
        // se forem iguais, continua a comparar os valores por ordem decrescente de importância //

    if(data1.mes > data2.mes)
        return FALSE;
    if(data2.mes > data1.mes)
        return TRUE;
    
    if(data1.dia > data2.dia)
        return FALSE;
    if(data2.dia > data1.dia)
        return TRUE;

    if(hora1.hora > hora2.hora)
        return FALSE;
    if(hora2.hora > hora1.hora)
        return TRUE;

    if(hora1.minuto > hora2.minuto)
        return FALSE;
    if(hora2.minuto > hora1.minuto)
        return TRUE;
    return TRUE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// verifica se a data 1 é menor que a data 2 //
// recebe duas datas //
// devolve 1 se a data 1 for menor que a data 2 e 0 se não for, e devolve 0 se forem iguais (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int compara_so_datas(Data data1, Data data2) {
    if(data1.ano > data2.ano) // compara cada elemento das datas e das horas //
        return FALSE; // se o elemento da data 1 for maior do que o da data 2, devolve FALSE //
    if(data2.ano > data1.ano) // se o elemento da data 2 for maior, devolve TRUE //
        return TRUE; 
        // se forem iguais, continua a comparar os valores por ordem decrescente de importância //

    if(data1.mes > data2.mes)
        return FALSE;
    if(data2.mes > data1.mes)
        return TRUE;
    
    if(data1.dia > data2.dia)
        return FALSE;
    if(data2.dia > data1.dia)
        return TRUE;
    return FALSE;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// calcula a diferença de minutos entre duas horas //
// recebe duas horas //
// devolve a diferença de minutos entre as duas horas (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int diferenca_horas(Horas horas1, Horas horas2) {
    int minHoras1, minHoras2;

    minHoras1 = horas1.hora * 60 + horas1.minuto; // converte as horas e minutos para apenas minutos //
    minHoras2 = horas2.hora * 60 + horas2.minuto;

    if(minHoras1 > minHoras2) { // se as horas iniciais forem maiores do que as finais //
        return minHoras2 + 60*24 - minHoras1; 
        // devolve a diferença entre os minutos mais um dia em minutos //
    }
    return (minHoras2 - minHoras1); // se não devolve apenas a diferença entre os minutos //
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Calcula a diferença de dias entre duas datas //
// recebe duas datas //
// devolve a diferença de dias entre as duas datas (int) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
int diferenca_datas(Data data1, Data data2) {
    int dias = 0, i;

    if(data1.mes == data2.mes) // se os meses forem iguais //
        dias += (data2.dia - data1.dia); // adiciona-se a diferença de dias à qnt de dias //

    dias += ((data2.ano - data1.ano)*365); // por cada ano de diferença adiciona-se 365 dias //

    if(data1.mes < data2.mes) { // se o primeiro ano tiver mês maior //
        dias += (v_meses[data1.mes] - data1.dia); // adiciona-se os dias restantes do mês //
        if(data1.mes + 1 != data2.mes) {
            i = data1.mes + 1;
            while(i < data2.mes) {// por cada mês antes da ultima data //
                dias += v_meses[i];// adiciona-se os dias respetivos //
                i++;
            }
        }
        dias += data2.dia; // adiciona-se os dias do mês da ultima data
    }
    if(data1.mes > data2.mes) { // se o mês da primeira data for maior //
        dias += (- v_meses[data1.mes] + data1.dia); // retira-se os dias restantes do mês //
        if(data1.mes - 1 != data2.mes) {
            i = data1.mes - 1;
            while(i > data2.mes) {// por cada mês antes da ultima data //
                dias -= v_meses[i];// adiciona-se os dias respetivos //
                i--;
            }
        }
        dias += data1.dia; // e adiciona-se os dias da segunda data //
    }
    return dias;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Calcula o preço a pagar por um determinado periodo de tempo //
// recebe o número de dias e minutos e os preços por periodo de tempo //
// devolve o preço a pagar  (float) //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
float preco(int dias, int minutos, float menos1h, float mais1h, float maxdia) {
    float preco = 0;

    if(minutos >= 60) {
        minutos -= 60;
        preco += (4*menos1h); // adiciona-se o preço da primeira hora //
        if((minutos % 15) == 0) // se os minutos forem divisíveis por 15 //
            minutos = (minutos/15);  // faz-se apenas a divisão inteira por 15 //
        else
            minutos = (minutos/15)+1; // se não adiciona-se mais 1 //
        if((minutos * mais1h + preco) < maxdia) // se o preco total for menor do que o maximo por dia //
            preco += (minutos * mais1h); // adiciona-se o preço do resto das horas //
        else{
            preco -= (4*menos1h); // se não, retira-se o preço da primeira hora //
            preco += maxdia; // e adiciona-se o maximo por dia //
        }
    }

    else {// se os minutos forem menores do que 60 //
        if((minutos % 15) == 0) // se os minutos forem divisíveis por 15 //
            minutos = (minutos/15); // divide-se apenas por 15 //
        else
            minutos = (minutos/15)+1; // se não, adiciona-se mais 1 //
        
        preco += (minutos*menos1h); // e adiciona-se o preço do tempo correspondente //
    }
    if(maxdia < (menos1h*4 + mais1h*4*23))
        preco += (dias*maxdia); // adiciona-se o preço por cada dia que o carro esteve no parque //
    else 
        preco += (dias*(menos1h*4 + mais1h*4*23)); 
        // se o maximo por dia for menor do que o preço total por dia, adiciona-se o preço total por dia //
    

    return preco; // devolve o preço //
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Calcula o preço total a pagar para um carro //
// recebe a data e hora de entrada e de saída, e o parque onde o carro esteve //
// devolve o preço total a pagar (float) //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
float preco_total(Data data1, Horas hora1, Data data2, Horas hora2, Parque * parque) {
    int dias, minutos;
    float preco_total = 0;

    dias = diferenca_datas(data1, data2); // calcula a diferença de dias //
    minutos = diferenca_horas(hora1, hora2); // calcula a diferença de minutos //
    if(hora1.hora > hora2.hora || (hora1.hora == hora2.hora && hora1.minuto > hora2.minuto)) 
    // se a hora inicial for menor do que a final //
        dias -= 1; // retira se um dia //
    preco_total = preco(dias, minutos, parque->menos1h, parque->mais1h, parque->maxdia); 
    // calcula o preço total //

    return preco_total; // devolve o preço total //
} 


// ~~~~~~~~~~~~~~~~~~~~~~~~//
// Imprime apenas uma hora //
// recebe uma hora //
// não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~//
void print_so_hora(Horas hora) {
    if(hora.hora < 10)
        printf("0%d:", hora.hora); // imprime a hora com um 0 à frente se for menor que 10 //
    else
        printf("%d:", hora.hora); 
    if(hora.minuto < 10)
        printf("0%d", hora.minuto); 
    else
        printf("%d", hora.minuto); 
}


// ~~~~~~~~~~~~~~~~~~~~~~~~//
// Imprime apenas uma data //
// recebe uma data //
// não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~//
void print_so_data(Data data) {
    if(data.dia < 10) // se o dia e mês forem menores que 10, imprime com um 0 à frente //
        printf("0%d-", data.dia); 
    else
        printf("%d-", data.dia); 
    if(data.mes < 10) 
        printf("0%d-", data.mes); 
    else
        printf("%d-", data.mes);
    printf("%d", data.ano); 
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Imprime uma data e uma hora //
// recebe uma data e uma hora //
// não devolve nada //
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void print_data_hora(Data data, Horas hora) {
    print_so_data(data); // imprime a data //
    printf(" ");
    print_so_hora(hora); // imprime a hora //
}