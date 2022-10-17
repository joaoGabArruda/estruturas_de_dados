#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    int chave;
}titem;

typedef struct celula
{
    titem item;
    struct celula *pprox;
}tcelula;

typedef struct
{
    tcelula *ptopo;
    int tamanho;
} tpilha;


// ------------------------------------ INICIAR PILHA ---------------------------------

void cria_pilha (tpilha *ppilha)
{
    ppilha->ptopo = NULL;
    ppilha->tamanho = 0;
}


// ------------------------------------ PILHA ESTA VAZIA? ---------------------------------
int isVazia (tpilha *ppilha)
{
    return ppilha->ptopo == NULL;
}

// ------------------------------------ INSERÇÃO NO INICIO ---------------------------------

int push (tpilha *ppilha, titem x)
{
    tcelula *novo = (tcelula*) malloc(sizeof(tcelula));
    novo->item = x;
    novo->pprox = NULL;

    if(isVazia(ppilha))
        ppilha->ptopo = novo;
    else
    {
        novo->pprox = ppilha->ptopo;
        ppilha->ptopo = novo;
    }

    ppilha->tamanho++;

    return 1;
}


// ------------------------------------ REMOÇÃO NO INICIO ---------------------------------

int pop(tpilha *ppilha, titem *px)
{
    if(isVazia(ppilha))
    {
        printf("LISTA VAZIA!!!\n");
        return 0;
    }

    tcelula *paux = ppilha->ptopo;

    if(ppilha->tamanho == 1)
    {
        ppilha->ptopo = NULL;
    }
    else
    {
        ppilha->ptopo = ppilha->ptopo->pprox;
    }

    *px = paux->item;

    free(paux);
    ppilha->tamanho--;

    return 1;
}


// ------------------------------------ CONSULTAR ELEMENTO NO TOPO DA PILHA ---------------------------------

int peek(tpilha *ppilha, titem *px)
{
    if(isVazia(ppilha))
    {
        printf("LISTA VAZIA!!!\n");
        return 0;
    }

    *px = ppilha->ptopo->item;

    return 1;
}


// ------------------------------------ CONSULTAR TAMANHO TOPO DA PILHA ---------------------------------

int tamanho(tpilha *ppilha)
{
    return  ppilha->tamanho;
}

// imprimir lista
void imprimir (tpilha *plista)
{
    tcelula *paux;

    for(paux = plista->ptopo; paux != NULL; paux = paux->pprox)
    {
        printf("%d  ",paux->item.chave);
    }

    printf("\n");
}

int main()
{
    tpilha pilha;
    cria_pilha(&pilha);

    printf("Vazia: %s\n", isVazia(&pilha) == 1 ? "SIM":"NAO");

    titem item1, item2, item3;
    item1.chave = 10;
    item2.chave = -5;
    item3.chave = 20;

    push (&pilha, item1);
    push (&pilha, item2);
    push (&pilha, item3);
    imprimir(&pilha);

    printf("Vazia: %s\n", isVazia(&pilha) == 1 ? "SIM":"NAO");

    titem itemTeste; int i;
    for(i = 0; i < 4; i++)
    if(pop (&pilha, &itemTeste))
    {
        printf("Elemento removido: %d\n", itemTeste.chave);
        imprimir(&pilha);
    }

    push (&pilha, item1);
    push (&pilha, item2);
    push (&pilha, item3);


    peek (&pilha, &itemTeste);
    printf("Elemento no topo: %d\n", itemTeste.chave);
    printf("Elementos existentes: %d\n", tamanho(&pilha));
}
