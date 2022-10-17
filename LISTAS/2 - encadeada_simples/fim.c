#include<stdio.h>
#include<stdlib.h>

/*-------------------------------- STRUCTS -------------------------------------------------*/

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
    tcelula *pprimeiro, *pultimo;
} tlista;


/*-------------------------------- CRIAR LISTA -------------------------------------------------*/

// CRIAR LISTA
void criaLista (tlista *plista)
{
    plista->pprimeiro = NULL;
    plista->pultimo = NULL;
}


/*--------------------------------- LISTA ESTÁ VAZIA? ------------------------------------------------*/

// verificar se lista esta vazia
int listavazia (tlista *plista)
{
    return plista->pprimeiro == NULL;
}


/*---------------------------------- INSERÇÕES -----------------------------------------------*/

// insere no fim
int insereFIM(tlista *plista, titem x)
{
    tcelula *novo = (tcelula*) malloc(sizeof(tcelula)); // cria um novo nó e aloca espaço pra ele
    novo->item = x;
    novo->pprox = NULL;

    if(listavazia(plista))
        plista->pprimeiro = novo;
    else
        plista->pultimo->pprox = novo;

    plista->pultimo = novo;

    return 1;
}


/*-------------------------------- REMOÇÕES -------------------------------------------------*/

// REMOVER NO FIM
int removerFIM (tlista *plista, titem *px)
{
    if(listavazia(plista))
    {
        printf("LISTA VAZIA!!!");
        return 0;
    }


    tcelula *paux = plista->pprimeiro;
    tcelula *panterior;

    if(tamanho(plista) == 1)
    {
         plista->pprimeiro = NULL;
    }
    else
    {
        while(paux != plista->pultimo)
        {
            panterior = paux;
            paux = paux->pprox;
        }


        panterior->pprox = NULL;
        plista->pultimo = panterior;
    }

    *px = paux->item;

    free(paux);

    return 1;
}


/*-------------------------------- OBTER POSIÇÃO DE ELEMENTO -------------------------------------------------*/

// obter elemento de uma posição "p"
int getposicao(tlista *plista, int p, titem *px)
{
    if (listavazia(plista))
        return 0;

    tcelula *paux;
    int cont = 0;

    for(paux = plista->pprimeiro; paux != NULL; paux = paux->pprox)
    {
        if(cont == p)
       {
           *px = paux->item;
           break;
       }

       cont++;
    }

    return 1;

}


/*-------------------------------- TAMANHO DA LISTA -------------------------------------------------*/

// obter quantos elementos há na lista
int tamanho(tlista *plista)
{
    tcelula *paux;
    int cont = 0;

    for(paux = plista->pprimeiro; paux != NULL; paux = paux->pprox)
    {
        cont++;
    }

    return cont;
}


/*-------------------------------- IMPRIMIR LISTA -------------------------------------------------*/

// imprimir lista
void imprimir (tlista *plista)
{
    tcelula *paux;

    for(paux = plista->pprimeiro; paux != NULL; paux = paux->pprox)
    {
        printf("%d  ",paux->item.chave);
    }

    printf("\n");
}


/*-------------------------------- FUNÇÃO MAIN -------------------------------------------------*/

int main()
{
    tlista lista;
    criaLista(&lista);

    titem item1, item2, item3;
    item1.chave = 24;
    item2.chave = 99;
    item3.chave = 1;

    insereFIM(&lista, item1);
    imprimir(&lista);

    insereFIM(&lista, item2);
    imprimir(&lista);

    insereFIM(&lista, item3);
    imprimir(&lista);

    titem itemRemovido;
    if(removerFIM (&lista, &itemRemovido))
        printf("Item removido: %d\n", itemRemovido.chave);

    item3.chave = 7777;

    insereFIM(&lista, item3);
    imprimir(&lista);

     if(removerFIM (&lista, &itemRemovido)) {
        printf("Item removido: %d\n", itemRemovido.chave);
        imprimir(&lista);
     }

      if(removerFIM (&lista, &itemRemovido)) {
        printf("Item removido: %d\n", itemRemovido.chave);
        imprimir(&lista);
     }

      if(removerFIM (&lista, &itemRemovido)) {
        printf("Item removido: %d\n", itemRemovido.chave);
        imprimir(&lista);
     }

     if(removerFIM (&lista, &itemRemovido)) {
        printf("Item removido: %d\n", itemRemovido.chave);
        imprimir(&lista);
     }
}
