/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê as traduções de "Feliz Natal" em diferentes idiomas e as informações das crianças, armazena esses dados,
* busca a saudação correta para cada criança e imprime as etiquetas.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para armazenar uma tradução
typedef struct Traducao {
    char idioma[50];
    char saudacao[50];
    struct Traducao *prox;
} Traducao;

// Definição da estrutura para armazenar uma criança
typedef struct Crianca {
    char nome[50];
    char idioma[50];
    struct Crianca *prox;
} Crianca;

// Função para criar um novo nó de tradução
Traducao* criarTraducao(const char *idioma, const char *saudacao) {
    Traducao *novo = (Traducao *)malloc(sizeof(Traducao));
    strcpy(novo->idioma, idioma);
    strcpy(novo->saudacao, saudacao);
    novo->prox = NULL;
    return novo;
}

// Função para criar um novo nó de criança
Crianca* criarCrianca(const char *nome, const char *idioma) {
    Crianca *novo = (Crianca *)malloc(sizeof(Crianca));
    strcpy(novo->nome, nome);
    strcpy(novo->idioma, idioma);
    novo->prox = NULL;
    return novo;
}

// Função para buscar a saudação correspondente ao idioma
const char* buscarSaudacao(Traducao *inicio, const char *idioma) {
    Traducao *atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->idioma, idioma) == 0) {
            return atual->saudacao;
        }
        atual = atual->prox;
    }
    return NULL;
}

int main() {
    int N, M;
    scanf("%d", &N);

    // Lista encadeada de traduções
    Traducao *traducoes = NULL;
    Traducao *ultimaTraducao = NULL;

    // Lê as traduções e as armazena na lista encadeada
    for (int i = 0; i < N; i++) {
        char idioma[50], saudacao[50];
        scanf(" %[^\n]", idioma); // Lê o idioma até o final da linha
        scanf(" %[^\n]", saudacao); // Lê a saudação até o final da linha

        Traducao *novaTraducao = criarTraducao(idioma, saudacao);
        if (traducoes == NULL) {
            traducoes = novaTraducao;
        } else {
            ultimaTraducao->prox = novaTraducao;
        }
        ultimaTraducao = novaTraducao;
    }

    scanf("%d", &M);

    // Lista encadeada de crianças
    Crianca *criancas = NULL;
    Crianca *ultimaCrianca = NULL;

    // Lê as crianças e as armazena na lista encadeada
    for (int i = 0; i < M; i++) {
        char nome[50], idioma[50];
        scanf(" %[^\n]", nome); // Lê o nome até o final da linha
        scanf(" %[^\n]", idioma); // Lê o idioma até o final da linha

        Crianca *novaCrianca = criarCrianca(nome, idioma);
        if (criancas == NULL) {
            criancas = novaCrianca;
        } else {
            ultimaCrianca->prox = novaCrianca;
        }
        ultimaCrianca = novaCrianca;
    }

    // Imprime as etiquetas
    Crianca *atualCrianca = criancas;
    while (atualCrianca != NULL) {
        const char *saudacao = buscarSaudacao(traducoes, atualCrianca->idioma);
        printf("%s\n", atualCrianca->nome);
        printf("%s\n", saudacao);
        printf("\n"); // Linha em branco após cada etiqueta
        atualCrianca = atualCrianca->prox;
    }

    // Libera a memória alocada para as listas encadeadas
    Traducao *atualTraducao = traducoes;
    while (atualTraducao != NULL) {
        Traducao *temp = atualTraducao;
        atualTraducao = atualTraducao->prox;
        free(temp);
    }

    Crianca *tempCrianca = criancas;
    while (tempCrianca != NULL) {
        Crianca *temp = tempCrianca;
        tempCrianca = tempCrianca->prox;
        free(temp);
    }

    return 0;
}