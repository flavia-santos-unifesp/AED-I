/* Flavia Fernandes dos Santos, RA 170563
* Este programa lê uma lista com n nomes, classifica os nomes em ordem alfabética e imprime o nome da posição k.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Estrutura para armazenar os nomes*/
typedef struct list
{
    char nome[21];
    struct list* prox;
} LNomes;

/*Estrutura para a cabeça da lista*/
typedef struct head
{
    int qnt;
    LNomes *ini;
} HNomes;

/*Função que inicializa a estrutura da cabeça.*/
void init (HNomes* p) {
    p->ini = NULL;
    p->qnt = 0;
}

/*Função que insere os nós na lista em ordem alfabética*/
void push (HNomes* p, char* n) {
       LNomes *new = (LNomes*) malloc (sizeof(LNomes));
    LNomes *auxI, *auxII;
    auxI = NULL;
    auxII = p->ini;
    strcpy(new->nome,n);
    new->prox = NULL;

    while (auxII != NULL){ 
        if (strcmp(new->nome,auxII->nome) == 0){
            free (new);
            return;
        } else if (strcmp(new->nome,auxII->nome) > 0){
            auxI = auxII;
            auxII = auxII->prox;
        } else if (strcmp(new->nome,auxII->nome) < 0){
            new->prox = auxII;
            if (auxI == NULL){
                new->prox = p->ini;
                p->ini = new;
            } else {
                auxI->prox = new;
            }
            p->qnt++;
            return;
        }
    } 
    
    if (auxI == NULL){
        p->ini = new;
    } else if (auxII == NULL){
        auxI->prox = new;
    }
    p->qnt++;
}


/*Função que imprime o nome da posição k*/
void print (HNomes* p, int k){
    LNomes *auxI;
    auxI = p->ini;
    int i;
    char *sorteado;
    for (i = 0; i < k-1; i++){
        auxI = auxI->prox;
    }
    printf ("%s\n", auxI->nome);
}

/*Função que libera a memória após a utilização da lista*/
void clear (HNomes* p){
    LNomes *aux;
     do {
        aux = p->ini;
        p->ini = aux->prox;
        free(aux);
    } while (p->ini != NULL);

    p->ini = NULL;
    p->qnt = 0;

}

int main () {

    int n, k, i, j;
    char nome[21];
    HNomes Lista_Chamada;

    /*Recebe o número de alunos que serão inseridas.*/
    scanf("%d\n", &n);
    if (1 > n || n > 100) {
        //printf ("Valor invalido. Insira um valor entre 1 e 100:\n");
        scanf("%d", &n);
    }

    /*Recebe a posição sorteada.*/
    scanf("%d\n", &k);
    if (1 > k || k > n) {
        //printf ("Valor invalido. Insira um valor entre 1 e 100:\n");
        scanf("%d", &k);
    }

    init(&Lista_Chamada);

    /*Recebe os nomes dos alunos*/
    for (i=0; i < n; i++) {
        scanf("%s", nome);
        push(&Lista_Chamada,nome);
    }
    
    print (&Lista_Chamada, k);
    clear (&Lista_Chamada);

    return 0;
}