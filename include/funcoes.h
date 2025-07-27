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

void inicializar();
void ordenaAlfabetica(Jogos *v, int tamanho);
void ordenaID(Jogos *lista, int tamanho);
void listar_jogo(Jogos *v, int tamanho);
void salvar_jogo(Jogos *v, int tamanho);
int comparaString(char *s1, char *s2);
Jogos *adicionar_jogo(Jogos *v, int *tamanho, Jogos novo);
Jogos *remover_jogo(Jogos *v, int *tamanho);
Jogos *carregar_jogo(int *tamanho);
Jogos *editar_jogo(Jogos *v, int *tamanho);

#endif
