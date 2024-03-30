#include <stdio.h>


#ifndef FUNC_DATAS

int verifica_datas(Data data);

int verifica_horas(Horas horas);

int mesma_data(Data data1, Data data2);

int compara_datas(Data data1, Horas hora1, Data data2, Horas hora2);

int compara_so_datas(Data data1, Data data2);

float preco_total(Data data1, Horas horas1, Data data2, Horas horas2, Parque * parque);

void print_data_hora(Data data, Horas hora);

void print_so_hora(Horas hora);

void print_so_data(Data data);

#define FUNC_DATAS
#endif



