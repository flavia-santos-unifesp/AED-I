/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê a quantidade de caixas disponíveis e de clientes na fila, bem como o tempo de atendimento em cada caixa
* e quantidade de itens pra cada cliente, e calcula em quanto tempo todos os clientes serão atendidos.*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um funcionário do caixa
typedef struct Caixa {
    int id;         // Identificação do funcionário
    int tempo_livre; // Tempo em que estará livre
    int tempo_por_item; // Tempo para processar um item
    struct Caixa *prox;
} Caixa;

// Função para inserir um funcionário na lista ordenada por tempo_livre e id
void inserir_caixa(Caixa **lista, int id, int tempo_livre, int tempo_por_item) {
    Caixa *novo = (Caixa *)malloc(sizeof(Caixa));
    novo->id = id;
    novo->tempo_livre = tempo_livre;
    novo->tempo_por_item = tempo_por_item;
    novo->prox = NULL;
    
    if (*lista == NULL || (*lista)->tempo_livre > tempo_livre || 
        ((*lista)->tempo_livre == tempo_livre && (*lista)->id > id)) {
        novo->prox = *lista;
        *lista = novo;
        return;
    }
    
    Caixa *atual = *lista;
    while (atual->prox != NULL && 
           (atual->prox->tempo_livre < tempo_livre ||
            (atual->prox->tempo_livre == tempo_livre && atual->prox->id < id))) {
        atual = atual->prox;
    }
    
    novo->prox = atual->prox;
    atual->prox = novo;
}

// Função para remover o primeiro funcionário da lista
Caixa *remover_caixa(Caixa **lista) {
    if (*lista == NULL) return NULL;
    Caixa *removido = *lista;
    *lista = (*lista)->prox;
    return removido;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int tempos[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &tempos[i]);
    }
    
    int clientes[M];
    for (int i = 0; i < M; i++) {
        scanf("%d", &clientes[i]);
    }
    
    // Criando a lista de funcionários
    Caixa *lista = NULL;
    for (int i = 0; i < N; i++) {
        inserir_caixa(&lista, i + 1, 0, tempos[i]);
    }
    
    int tempo_total = 0;
    for (int i = 0; i < M; i++) {
        Caixa *atendente = remover_caixa(&lista);
        
        int tempo_atendimento = atendente->tempo_por_item * clientes[i];
        atendente->tempo_livre += tempo_atendimento;
        tempo_total = atendente->tempo_livre > tempo_total ? atendente->tempo_livre : tempo_total;
        
        inserir_caixa(&lista, atendente->id, atendente->tempo_livre, atendente->tempo_por_item);
        free(atendente);
    }
    
    printf("%d\n", tempo_total);
    
    // Liberar memória da lista
    while (lista != NULL) {
        Caixa *temp = lista;
        lista = lista->prox;
        free(temp);
    }
    
    return 0;
}
