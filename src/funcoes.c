#include "funcoes.h"
#include <stdio.h>

int comparaString(char *s1, char *s2){
    for(int i = 0; s1[i] != '\0' || s2[i] != '\0'; i++){
        if(s1[i] < s2[i]) return -1; //se s2 for maior bota -1
        if(s1[i] > s2[i]) return  1; //o contrario
    }
   
    return 0;
}

void ordenaAlfabetica(Jogos *lista, int tamanho){
    Jogos temp; 
    int menor_id;

    for(int i = 0; i < tamanho - 1; i++){
        menor_id = i;
        for(int j = i; j < tamanho; j++){
            if(comparaString(lista[j].nome, lista[menor_id].nome) < 0){
                menor_id = j;
            }
        }
        temp = lista[i];
        lista[i] = lista[menor_id];
        lista[menor_id] = temp;
    }
}

void ordenaID(Jogos *lista, int tamanho){
    Jogos temp;
    int menor_id;

    for(int i = 0; i < tamanho - 1; i++){
        menor_id = i;
        for(int j = i; j < tamanho; j++){
            if(lista[j].id < lista[menor_id].id){
                menor_id = j;
            }
        }
        temp = lista[i];
        lista[i] = lista[menor_id];
        lista[menor_id] = temp;
    }
}

void inicializar(){
    printf("Bem-vindo a:\n");
    printf(
        "__________  _________        __________________ _______________________________\n"
        "\\______   \\/   _____/        \\______   \\_____  \\\\______   \\______   \\_   _____/\n"
        " |     ___/\\_____  \\   ______ |     ___//   |   \\|    |  _/|       _/|    __)_ \n"
        " |    |    /        \\ /_____/ |    |   /    |    \\    |   \\|    |   \\|        \\\n"
        " |____|   /_______  /         |____|   \\_______  /______  /|____|_  /_______  /\n"
        "                  \\/                           \\/       \\/        \\/        \\/ \n"
    );
    printf("\n");
    printf("Sua agenda favorita de jogos ;)\n\n");
}