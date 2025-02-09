/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê um dicionário com palavras x valores e calcula o salário dos funcionários.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar uma palavra e seu valor associado
typedef struct Palavra {
    char palavra[17];  // Palavra (máximo de 16 caracteres)
    double valor;      // Valor associado à palavra
    struct Palavra *proximo;
} Palavra;

// Função para criar um novo nó de palavra
Palavra* criarPalavra(char *palavra, double valor) {
    Palavra *novaPalavra = (Palavra*)malloc(sizeof(Palavra));
    strcpy(novaPalavra->palavra, palavra);
    novaPalavra->valor = valor;
    novaPalavra->proximo = NULL;
    return novaPalavra;
}

// Função para inserir uma palavra no dicionário (lista encadeada)
void inserirPalavra(Palavra **dicionario, char *palavra, double valor) {
    Palavra *novaPalavra = criarPalavra(palavra, valor);
    novaPalavra->proximo = *dicionario;
    *dicionario = novaPalavra;
}

// Função para buscar o valor de uma palavra no dicionário
double buscarValor(Palavra *dicionario, char *palavra) {
    Palavra *temp = dicionario;
    while (temp != NULL) {
        if (strcmp(temp->palavra, palavra) == 0) {
            return temp->valor;
        }
        temp = temp->proximo;
    }
    return 0.0;  // Se a palavra não estiver no dicionário, retorna 0
}

// Função para processar as descrições de cargo
void processarDescricao(Palavra *dicionario) {
    char descricao[1000];  // Buffer para armazenar uma linha da descrição
    int salario = 0;       // Salário calculado para a descrição (sem casas decimais)
    while (1) {
        fgets(descricao, sizeof(descricao), stdin);
        descricao[strcspn(descricao, "\n")] = '\0';  // Remover o '\n' da string
        if (strcmp(descricao, ".") == 0) {
            break;  // Fim da descrição
        }

        // Dividir a linha em palavras e calcular o salário
        char *palavra = strtok(descricao, " ");
        while (palavra != NULL) {
            salario += (int)buscarValor(dicionario, palavra);  // Converter para inteiro
            palavra = strtok(NULL, " ");
        }
    }

    // Exibir o salário calculado sem casas decimais
    printf("%d\n", salario);
}

// Função principal
int main() {
    int M, N;
    scanf("%d %d", &M, &N);

    Palavra *dicionario = NULL;  // Lista encadeada para o dicionário

    // Leitura do dicionário
    for (int i = 0; i < M; i++) {
        char palavra[17];
        double valor;
        scanf("%s %lf", palavra, &valor);
        inserirPalavra(&dicionario, palavra, valor);
    }

    // Processamento das descrições de cargos
    for (int i = 0; i < N; i++) {
        processarDescricao(dicionario);
    }

    // Liberar a memória alocada para o dicionário
    Palavra *temp;
    while (dicionario != NULL) {
        temp = dicionario;
        dicionario = dicionario->proximo;
        free(temp);
    }

    return 0;
}