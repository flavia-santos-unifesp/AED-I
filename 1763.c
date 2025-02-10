/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê o nome de um país e retorna a frase "Feliz natal!" no idioma dessa país.
* Caso o país não esteja na lista, retorna "--- NOT FOUND ---".*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para armazenar um país e sua frase de Natal
typedef struct Pais {
    char nome[50]; // Nome do país
    char frase[50]; // Frase de Natal no idioma do país
    struct Pais *prox; // Ponteiro para o próximo país na lista
} Pais;

// Função para criar um novo nó (país) na lista
Pais* criarPais(const char *nome, const char *frase) {
    Pais *novo = (Pais *)malloc(sizeof(Pais));
    strcpy(novo->nome, nome);
    strcpy(novo->frase, frase);
    novo->prox = NULL;
    return novo;
}

// Função para inserir um país na lista
void inserirPais(Pais **inicio, const char *nome, const char *frase) {
    Pais *novo = criarPais(nome, frase);
    if (*inicio == NULL) {
        *inicio = novo;
    } else {
        Pais *atual = *inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
}

// Função para buscar a frase de Natal de um país na lista
const char* buscarFrase(Pais *inicio, const char *nome) {
    Pais *atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual->frase;
        }
        atual = atual->prox;
    }
    return NULL; // Retorna NULL se o país não for encontrado
}

int main() {
    Pais *inicio = NULL;

    // Inserindo os países e suas frases na lista
    inserirPais(&inicio, "brasil", "Feliz Natal!");
    inserirPais(&inicio, "alemanha", "Frohliche Weihnachten!");
    inserirPais(&inicio, "austria", "Frohe Weihnacht!");
    inserirPais(&inicio, "coreia", "Chuk Sung Tan!");
    inserirPais(&inicio, "espanha", "Feliz Navidad!");
    inserirPais(&inicio, "grecia", "Kala Christougena!");
    inserirPais(&inicio, "estados-unidos", "Merry Christmas!");
    inserirPais(&inicio, "inglaterra", "Merry Christmas!");
    inserirPais(&inicio, "australia", "Merry Christmas!");
    inserirPais(&inicio, "portugal", "Feliz Natal!");
    inserirPais(&inicio, "suecia", "God Jul!");
    inserirPais(&inicio, "turquia", "Mutlu Noeller");
    inserirPais(&inicio, "argentina", "Feliz Navidad!");
    inserirPais(&inicio, "chile", "Feliz Navidad!");
    inserirPais(&inicio, "mexico", "Feliz Navidad!");
    inserirPais(&inicio, "antardida", "Merry Christmas!");
    inserirPais(&inicio, "canada", "Merry Christmas!");
    inserirPais(&inicio, "irlanda", "Nollaig Shona Dhuit!");
    inserirPais(&inicio, "belgica", "Zalig Kerstfeest!");
    inserirPais(&inicio, "italia", "Buon Natale!");
    inserirPais(&inicio, "libia", "Buon Natale!");
    inserirPais(&inicio, "siria", "Milad Mubarak!");
    inserirPais(&inicio, "marrocos", "Milad Mubarak!");
    inserirPais(&inicio, "japao", "Merii Kurisumasu!");

    char pais[50];
    while (scanf("%s", pais) != EOF) { // Lê os países até o fim da entrada
        const char *frase = buscarFrase(inicio, pais);
        if (frase != NULL) {
            printf("%s\n", frase);
        } else {
            printf("--- NOT FOUND ---\n");
        }
    }

    // Liberação da memória alocada para a lista encadeada
    Pais *atual = inicio;
    while (atual != NULL) {
        Pais *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    return 0;
}