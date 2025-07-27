#include <stdio.h>
#include "funcoes.h"
#include <stdlib.h>
#include <unistd.h>

int main(){
    inicializar();
    
    Jogos *V = NULL;
    int tam = 0;

    while(1){
        printf("\n");
        printf("Escolha sua ação!\n");
        printf("#############################\n");
        printf("## [L]istar jogos          ##\n");
        printf("## [C]adastrar novo jogo   ##\n");
        printf("## [R]emover um jogo       ##\n");
        printf("## [S]air da PS-POBRE      ##\n");
        printf("#############################\n");        
        char op;
        scanf(" %c", &op);

        switch (op){
            case 'l': case 'L':
                ordenaAlfabetica(V, tam);
                listar_jogo(V, tam);
            break;
            
            case 'c' : case 'C':
                Jogos novo;
                system("clear");
                
                printf("\nQual é o nome do jogo? ");
                scanf(" %[^\n]", novo.nome);
                printf("\nQual é o genero de %s? ", novo.nome);
                scanf(" %[^\n]", novo.genero);
                
                do{
                    printf("\nQuantas conquistas tem em %s? ", novo.nome);
                    scanf("%d", &novo.max);
        
                    if(novo.max <= 0){
                        system("clear");
                        printf("As conquistas devem ser um número positivo!!\n");
                        sleep(2);
                        system("clear");
                    }

                }while(novo.max <= 0);
                
                do{
                    printf("\nQuantas conquistas voce já fez? ");
                    scanf("%d", &novo.conquistas);
        
                    if(novo.conquistas > novo.max){
                        system("clear");
                        printf("\n\nDo a barrel row!!\n");
                        printf("Suas conquistas não podem ser maiores do que o máximo de conquistas do jogo!\n\n");
                        sleep(2);
                        system("clear");
                    }
                }while(novo.conquistas > novo.max);

                V = adicionar_jogo(V, &tam, novo);
                printf("\nJogo adicionado!\n");
                salvar_jogo(V, tam);
                sleep(2);
                system("clear");
            break;

            case 'r' : case 'R':
                V = remover_jogo(V, &tam);
                salvar_jogo(V, tam);
            break;

            case 's' : case 'S':
                free(V);
                return 0;
            break;

            default:
                system("clear");
                printf("ERROR!\n opcao invalida\n");
                sleep(2);
                system("clear");
                inicializar();
            break;
        }
    }

    free(V);
    return 0;
}