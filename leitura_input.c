#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define BUFSIZ 8192



int main(){
    char * lista_palavras[6] = {NULL};
    char input[BUFSIZ];
    int i = 0, j = 0;
    int prox_espaco = 0;
    char c = getchar();
    
    while(c != '\n' && i < BUFSIZ){
        input[i++] = c;
        c = getchar();
    }
    
    for(i = 0, c = input[i]; c != '\0' && c != '\n'; c = input[i]){

        if (c == '"') {
            i++;
            for(; input[i + prox_espaco] != '"'; prox_espaco++);
            char * palavra_n = (char*) malloc((prox_espaco + 1) * sizeof(char));
            strncpy(palavra_n, input + i, prox_espaco);
            lista_palavras[j++] = palavra_n;
            i++;
        }   
        else{
            for(; input[i + prox_espaco] != ' ' && input[i + prox_espaco] != '\0'; prox_espaco++);
            char * palavra_n = (char*) malloc((prox_espaco + 1) * sizeof(char));
            strncpy(palavra_n, input + i, prox_espaco);
            lista_palavras[j++] = palavra_n;
            i++;
        }
        i += prox_espaco;
        prox_espaco = 0;
    }

    printf("%s %s %s", lista_palavras[0], lista_palavras[1], lista_palavras[2]);
    return 0;
}



