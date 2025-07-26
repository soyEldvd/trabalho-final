#ifndef FUNCOES_H
#define FUNCOES_H

struct Jogos{
    int id;
    char nome[100];
    char genero[50];
    int max;
    int conquistas;
    float progresso;
};
typedef struct Jogos Jogos;

int comparaString(char *s1, char *s2);
void inicializar();
void ordenaAlfabetica(Jogos *lista, int tamanho);
void ordenaID(Jogos *lista, int tamanho);
Jogos *adicionar_jogo(Jogos *v, int *tamanho, Jogos novo);
void listar_jogo(Jogos *v, int tamanho);
Jogos *remover_jogo(Jogos *v, int *tamanho);

#endif
