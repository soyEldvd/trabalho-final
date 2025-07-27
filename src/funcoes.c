#include "funcoes.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int comparaString(char *s1, char *s2){
    for(int i = 0; s1[i] != '\0' || s2[i] != '\0'; i++){
        if(s1[i] < s2[i]) return -1; //se s2 for maior bota -1
        if(s1[i] > s2[i]) return  1; //o contrario
    }
   
    return 0;
}

void ordenaAlfabetica(Jogos *v, int tamanho){
    Jogos temp; 
    int menor_id;

    for(int i = 0; i < tamanho - 1; i++){
        menor_id = i;
        for(int j = i; j < tamanho; j++){
            if(comparaString(v[j].nome, v[menor_id].nome) < 0){
                menor_id = j;
            }
        }
        temp = v[i];
        v[i] = v[menor_id];
        v[menor_id] = temp;
    }
}

void ordenaID(Jogos *v, int tamanho){
    Jogos temp;
    int menor_id;

    for(int i = 0; i < tamanho - 1; i++){
        menor_id = i;
        for(int j = i; j < tamanho; j++){
            if(v[j].id < v[menor_id].id){
                menor_id = j;
            }
        }
        temp = v[i];
        v[i] = v[menor_id];
        v[menor_id] = temp;
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

Jogos *adicionar_jogo(Jogos *v, int *tamanho, Jogos novo){
    novo.progresso = 100 * ((float)novo.conquistas/novo.max);
    
    FILE *arquivo = fopen("dados.txt", "r");
    if(arquivo == NULL){
        printf("Falha ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }
    int aux;
    fscanf(arquivo, "%d", &aux);
    novo.id = aux;

    Jogos *temp = realloc(v, (*tamanho + 1) * sizeof(Jogos));

    if(temp == NULL){
        printf("\nERRO NA ALOCAÇÃO DE MEMORIA\n");
        free(v);
        exit(EXIT_FAILURE);
    }

    v = temp;

    v[*tamanho] = novo;
    *tamanho = *tamanho + 1;

    return v;
}

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

void salvar_jogo(Jogos *v, int tamanho){
    FILE *arquivo = fopen("dados.txt", "w");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo para escrita\n");
        exit(EXIT_FAILURE);
    }

    fprintf(arquivo, "%d\n", tamanho);

    for(int i = 0; i < tamanho; i++){
        fprintf(arquivo, "%d\n", v[i].id);
        fprintf(arquivo, "%s\n", v[i].nome);
        fprintf(arquivo, "%s\n", v[i].genero);
        fprintf(arquivo, "%d\n", v[i].max);
        fprintf(arquivo, "%d\n", v[i].conquistas);
        fprintf(arquivo, "%f\n", v[i].progresso);
    }

    fclose(arquivo);
}

Jogos *carregar_jogo(int *tamanho){
    FILE *arquivo = fopen("dados.txt", "r");
    if(arquivo == NULL){
        *tamanho = 0;
        return malloc(*tamanho * sizeof(Jogos));
    }
    
    int n;
    fscanf(arquivo, "%d", &n);
    *tamanho = n;

    Jogos* lista = malloc(n * sizeof(Jogos));

    for(int i = 0; i < n; i++){
        fscanf(arquivo, "%d", &lista[i].id);
        fscanf(arquivo, " %[^\n]", lista[i].nome);
        fscanf(arquivo, " %[^\n]", lista[i].genero);
        fscanf(arquivo, "%d", &lista[i].max);
        fscanf(arquivo, "%d", &lista[i].conquistas);
        fscanf(arquivo, "%f", &lista[i].progresso);
    }

    fclose(arquivo);
    return lista;
}

Jogos *editar_jogo(Jogos *v, int *tamanho){
    if(*tamanho <= 0){
        system("clear");
        printf("Não há nenhum jogo na lista para ser editado\n");
        sleep(1);
        system("clear");
        inicializar();
        return v;
    }

    listar_jogo(v, *tamanho);
    int index = -1;
    int aux;
    printf("Digite o id do jogo que voce pretende editar\n");
    scanf("%d", &aux);

    for(int i = 0; i < *tamanho; i++){
        if(aux == v[i].id){
            index = i;
            break;
        }
    }
    if(index == -1){
        system("clear");
        printf(":(\n");
        printf("Esse jogo não tá na lista!\n");
        sleep(1);
        return v;
    }

    printf("\n#################################\n");
    printf("#  O QUE DESEJA EDITAR?         #\n");
    printf("#################################\n");
    printf("# 1. Nome                       #\n");
    printf("# 2. Gênero                     #\n");
    printf("# 3. Conquistas                 #\n");
    printf("# 0. Cancelar                   #\n");
    printf("#################################\n");
    printf("▸ Escolha uma opção: ");

    int op;
    scanf("%d", &op);

    switch (op){
    case 1:
        printf("Digite o novo nome [atual %s]: ", v[index].nome);
        scanf(" %[^\n]", v[index].nome);
        system("clear");
        printf("NOME ATUALIZADO COM SUCESSO\n");
        break;
    
    case 2:
        printf("Digite o novo gênero [atual %s]: ", v[index].genero);
        scanf(" %[^\n]", v[index].genero);
        system("clear");
        printf("NOME ATUALIZADO COM SUCESSO\n");
        break;

    case 3:
            int temp = v[index].conquistas;
        do{
            printf("Digite as suas novas conquistas: ");
            scanf("%d", &v[index].conquistas);

            if(v[index].conquistas > v[index].max){
                printf("Suas conquistas não podem ser maior que %d!\n", v[index].max);
            }
            if(v[index].conquistas < temp){
                printf("Não é possível perde conquistas\n Digite um valor acima de %d\n", temp);
            }
        }while(v[index].conquistas > v[index].max || v[index].conquistas < temp);

        system("clear");
        printf("CONQUISTAS ADICIONADAS COM SUCESSO!\n");
        v[index].progresso = 100 * ((float)v[index].conquistas / v[index].max);
        
    break;


    default:
        printf("Opção INválida\n");
        return v;
        break;
    }

    return v;
}