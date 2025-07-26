#include <stdio.h>
#include "funcoes.h"
#include <stdlib.h>
#include <unistd.h>

void listar_jogo(Jogos *v, int tamanho){
    system("clear");
    if(tamanho == 0){
        printf("Aqui não há nenhum easter-egg então vá embora!!\n");
        sleep(2);
        system("clear");
        inicializar();
        return;
    }

    printf("\nLISTA DE JOGOS \(^___^)/\n");
    printf("%-10s %-30s %-20s %-15s %s\n", "ID", "NOME", "GÊNERO", "CONQUISTAS", "PROGRESSO");
    printf("------------------------------------------------------------\n");
        for(int i = 0; i < tamanho; i++){
            printf("%-10d %-30s %-20s %d/%-15d %.1f%%\n",
            v[i].id,
            v[i].nome,
            v[i].genero,
            v[i].conquistas,
            v[i].max,
            v[i].progresso);
        }

}

Jogos *remover_jogo(Jogos *v, int *tamanho){
    if(*tamanho <= 0){
        system("clear");
        printf("\nNão há nenhum jogo adicionado!\n");
        sleep(2);
        system("clear");
        inicializar();
        return v;
    }
    int op;
    system("clear");
    printf("Digite a maneira como deseja remover o jogo\n");
    printf("1. Quero remover pelo ID\n");
    printf("2. Quero remover pelo nome\n");
    scanf("%d", &op);

    int index = -1;

    if(op == 1){
        int id;
        printf("Digite o id do jogo: ");
        scanf("%d", &id);
        for(int i = 0; i < *tamanho; i++){
            if(v[i].id == id){
                index = i;
                break;
            }
        }
    }

    if(op == 2){
        char nome[50];
        printf("Digite o nome do jogo: ");
        scanf(" %[^\n]", nome);
        for(int i = 0; i < *tamanho; i++){
            if(comparaString(v[i].nome, nome) == 0){
                index = i;
                break;
            }
        }
    }

    if(index == -1){
        printf("O jogo não foi encontrado!!\n");
        sleep(2);
        return v;
    }

    int conf;
    printf("\nO jogo que esta prestes a ser removido:\n");
    printf("ID: %d\n", v[index].id);
    printf("Nome: %s\n", v[index].nome);
    printf("Realmente deseja removê-lo?\n1 = sim\t0 = nao: ");
    scanf("%d", &conf);

    if(conf != 1){
        printf("Remoção cancelada\n");
        return v;
    }
    
    for(int i = index; i < *tamanho; i++){
        v[i] = v[i + 1];
    }
    *tamanho = *tamanho - 1;

    Jogos *temp = realloc(v, (*tamanho) * sizeof(Jogos));
    
    if(temp == NULL && *tamanho != 0){
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA\n");
        free(v);
        exit(EXIT_FAILURE);
    }

    v = temp;
    printf("\nRemoção feita com sucesso!\n");
    sleep(1.5);
    system("clear");
    inicializar();
    return v;
}

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
                sleep(2);
                system("clear");
            break;

            case 'r' : case 'R':
                V = remover_jogo(V, &tam);
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