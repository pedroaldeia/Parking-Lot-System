
#include <stdio.h>

#ifndef DATA
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;
#define DATA
#endif

#ifndef HORAS
typedef struct {
    int minuto;
    int hora;
} Horas;
#define HORAS
#endif

#ifndef MATRICULA
typedef struct {
    char par1[3];
    char par2[3];
    char par3[3];
} Matricula;
#define MATRICULA
#endif

#ifndef CARRO
typedef struct {
    Matricula matricula;
    Data D_entrada;
    Horas H_entrada;
    Data D_saida;
    Horas H_saida;
    float preco;
    int dentro;
} Carro;
#define CARRO
#endif

#ifndef NODE
typedef struct node {
    Carro * carro;
    struct node * next;
} node;
#define NODE
#endif

#ifndef PARQUE
typedef struct {
    char * nome;
    int capacidade;
    int lugares_disponiveis;
    float menos1h;
    float mais1h;
    float maxdia;
    node * carros_dentro;
    node * head_cd;
    node * carros_fora;
    node * head_cf;
} Parque;
#define PARQUE
#endif