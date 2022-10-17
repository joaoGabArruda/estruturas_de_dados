#include<stdio.h>
#include<stdlib.h>

// ----------------------------------- STRUCT ------------------------------------------
typedef struct
{
    int chave;
} titem;

typedef struct celula
{
    titem item;
    struct celula *pprox;
} tcelula;

typedef struct
{
    tcelula *pinicio, *pfim;
    int tamanho;
} tfila;


// ----------------------------------- INICIAR FILA ------------------------------------------
void iniciarFila (tfila *fila)
{
    fila->pinicio = NULL;
    fila->pfim = NULL;
    fila->tamanho = 0;
}


// ----------------------------------- ESTÁ VAZIA? ------------------------------------------
int isVazia (tfila *fila)
{
    return fila->pinicio == NULL;
}


// ----------------------------------- INSERÇÃO NO FIM ------------------------------------------
int enqueue (tfila *fila, titem x)
{
    tcelula *novo = (tcelula*) malloc(sizeof(tcelula));
    novo->item = x;
    novo->pprox = NULL;

    if(isVazia(fila))
        fila->pinicio = novo;
    else
        fila->pfim->pprox = novo;

    fila->pfim = novo;
    fila->tamanho++;

    return 1;
}


// ----------------------------------- REMOÇÃO NO INICIO ------------------------------------------
int dequeue (tfila *fila, titem *pX)
{
    if(isVazia(fila))
    {
        printf("LISTA VAZIA!!!\n");
        return 0;
    }

    tcelula *paux = fila->pinicio;

    if(fila->tamanho == 1)
    {
        fila->pinicio = NULL;
        fila->pfim = NULL;
    }
    else
    {
        fila->pinicio = fila->pinicio->pprox;
    }

    fila->tamanho--;
    *pX = paux->item;
    free(paux);

    return 1;
}


// ----------------------------------- STRUCT ------------------------------------------
int peek (tfila *fila, titem *px)
{
    if(isVazia(fila))
    {
        printf("LISTA VAZIAAA!!!\n");
        return 0;
    }

    *px = fila->pinicio->item;

    return 1;
}


// ----------------------------------- STRUCT ------------------------------------------
int tamanho (tfila *fila)
{
    return fila->tamanho;
}


// ----------------------------------- STRUCT ------------------------------------------
int limpar (tfila *fila)
{
    tcelula *paux = fila->pinicio;
    tcelula *pant = paux;

    do
    {
        paux = paux->pprox;
        free(pant);
        pant = paux;
    } while(paux != NULL);

    fila->pinicio = NULL;
    fila->pfim = NULL;

    return 1;
}


// ----------------------------------- STRUCT ------------------------------------------

// imprimir lista
void imprimir (tfila *plista)
{
    if(isVazia(plista))
    {
        printf("LISTA VAva!!!\n");
        return 0;
    }


    tcelula *paux;

    for(paux = plista->pinicio; paux != NULL; paux = paux->pprox)
    {
        printf("%d  ",paux->item.chave);
    }

    printf("\n");
}


// ----------------------------------- STRUCT ------------------------------------------
int main()
{
    tfila fila;
    iniciarFila (&fila);

    printf("Vazia: %s\n", isVazia(&fila) == 1 ? "SIM":"NAO");

    titem item1, item2, item3;
    item1.chave = 10;
    item2.chave = -5;
    item3.chave = 20;

    enqueue (&fila, item1);
    enqueue (&fila, item2);
    enqueue (&fila, item3);
    imprimir(&fila);

    printf("Vazia: %s\n", isVazia(&fila) == 1 ? "SIM":"NAO");

    titem itemTeste; int i;
    for(i = 0; i < 4; i++)
    if(dequeue (&fila, &itemTeste))
    {
        printf("Elemento removido: %d\n", itemTeste.chave);
        imprimir(&fila);
    }

    enqueue (&fila, item1);
    enqueue (&fila, item2);
    enqueue (&fila, item3);
    imprimir(&fila);

    printf("Elementos existentes: %d\n", tamanho(&fila));
    peek (&fila, &itemTeste);
    printf("Elemento no inicio: %d\n", itemTeste.chave);

    limpar(&fila);
    imprimir(&fila);

    return 0;
}
