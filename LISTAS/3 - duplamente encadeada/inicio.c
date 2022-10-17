#include<stdio.h>
#include<stdlib.h>

/*-------------------------------- STRUCTS -------------------------------------------------*/

typedef struct
{
    int chave;
} titem;

typedef struct celula
{
    struct celula *pant;
    struct celula *pprox;
    titem item;
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

// insere no inicio
int insereINICIO (tlista *plista, titem x)
{
    tcelula *novo = (tcelula*) malloc(sizeof(tcelula)); // cria um novo nó e aloca espaço pra ele
    novo->item = x;
    novo->pprox = NULL;
    novo->pant = NULL;

    if(listavazia(plista))
    {
        plista->pprimeiro = novo;
        plista->pultimo = novo;
    }
    else
    {
        novo->pprox = plista->pprimeiro;
        plista->pprimeiro->pant = novo;
        plista->pprimeiro = novo;
    }

     return 1;
}


/*-------------------------------- REMOÇÕES -------------------------------------------------*/

// REMOVER NO INICIO
int removerINICIO (tlista *plista, titem *px)
{
    if(listavazia(plista))
    {
        printf("LISTA VAZIA!!!\n");
        return 0;
    }


    tcelula *paux; // o nó auxiliar impede que voce perca a referência entre o anterior e o próximo do nó que será excluído

    paux = plista->pprimeiro;
    *px = paux->item;

    if(tamanho(plista) == 1)
    {
        plista->pprimeiro = NULL;
    }
    else {
        plista->pprimeiro = paux->pprox;
        plista->pprimeiro->pant = NULL;
    }
    free(paux);

    return 1;
}


/*-------------------------------- OBTER POSIÇÃO DE ELEMENTO -------------------------------------------------*/

// obter elemento de uma posição "p"
int getposicao(tlista *plista, int p, titem *px)
{
    if (listavazia(plista))
    {
        printf("Impossivel obter posicao %d! ",p);
        printf("A lista esta vazia!\n");
        return 0;
    }


    if(p> tamanho(plista) - 1)
    {
        printf("Impossivel obter posicao %d! ",p);
        printf("A lista vai de 0 a %d", tamanho(plista) - 1);

        return 0;
    }


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
void imprimir (tlista *plista, int inverso)
{
    tcelula *paux;

    if(listavazia(plista))
    {
        printf("LISTA VAZIA\n");
        return 0;
    }

    if(inverso)
    {
        printf("Itens da lista na ordem inversa:\n");
        paux = plista->pultimo;

        while(paux != NULL)
        {
            printf("%d  ",paux->item.chave);
            paux = paux->pant;
        }

    }
    else
    {
        printf("Itens da lista na ordem normal:\n");
        paux = plista->pprimeiro;

        while(paux != NULL)
        {
            printf("%d  ",paux->item.chave);
            paux = paux->pprox;
        }
    }

    printf("\n");
}

/*-------------------------------- BUSCA NA LISTA -------------------------------------------------*/
/*Implemente uma função de busca na lista duplamente encadeada
 pLista: lista a ser pesquisada
 chave: informação a ser encontrada dentro de uma célula
 Retorna o ponteiro de uma célula que contém a chave pesquisada ou
NULL caso a chave não exista na lista*/

tcelula* busca (tlista *plista, int chave)
{
    tcelula *paux;

    for(paux = plista->pprimeiro; paux != NULL; paux = paux->pprox)
    {
        if(paux->item.chave == chave)
            return paux;
    }

    return NULL;
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

    titem posi;
    if(getposicao(&lista,2,&posi))
        printf("valor %d nessa posicao",posi.chave);

    insereINICIO(&lista, item1);
    imprimir(&lista,0);

    insereINICIO(&lista, item2);
    imprimir(&lista,0);

    insereINICIO(&lista, item3);
    imprimir(&lista,0);
    imprimir(&lista,1);


    if(getposicao(&lista,2,&posi))
        printf("\nvalor %d nessa posicao\n",posi.chave);


    titem itemRemovido;
    if(removerINICIO (&lista, &itemRemovido))
        printf("Item removido: %d\n", itemRemovido.chave);

    item3.chave = 7777;

    insereINICIO(&lista, item3);
    imprimir(&lista,0);

    tcelula *teste;
    teste = busca(&lista,1);

    if(teste == NULL)
        printf("\nNao esta presente!");
    else
        printf("\nEsta presente!");


    teste = busca(&lista,24);

    if(teste == NULL)
        printf("\nNao esta presente!");
    else
        printf("\nEsta presente!\n");

    int i;

    for( i = 0; i<3; i++)
    {
        if(removerINICIO (&lista, &itemRemovido)) {
            printf("Item removido: %d\n", itemRemovido.chave);
            imprimir(&lista,0);
        }
    }

    if(removerINICIO (&lista, &itemRemovido))
    {
        printf("Item removido: %d\n", itemRemovido.chave);
        imprimir(&lista,0);
    }

}
