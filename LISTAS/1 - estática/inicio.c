#include<stdio.h>

#define inicio 0
#define max 500

/*-------------------------------- STRUCTS -------------------------------------------------*/

typedef struct
{
    int chave;
} titem;

typedef struct
{
    titem item[max]; // faz um vetor chamado "item" de tamanho 500; o vetor é do tipo "titem", então ele só pode armazenar a "chave"
    int primeiro, ultimo;
} tlista;

/*-------------------------------- CRIAR LISTA -------------------------------------------------*/

// CRIAR LISTA
void criaLista(tlista *plista)
{
    plista -> primeiro = inicio;
    plista -> ultimo = plista -> primeiro;
}

/*--------------------------------- LISTA ESTÁ VAZIA? ------------------------------------------------*/

// verificar se lista esta vazia
int listavazia (tlista *plista)
{
    return plista -> primeiro == plista -> ultimo;
}

/*---------------------------------- INSERÇÕES -----------------------------------------------*/

// insere no inicio
int insereINICIO (tlista *plista, titem x)
{
    if(plista -> ultimo == max)
    {
        printf("\nLISTA CHEIA!\n");
        return 0;
    }

    int i = plista -> ultimo;

    while(i != 0)
    {
        plista->item[i] = plista->item[i-1];
        i--;
    }
    plista->item[plista->primeiro] = x;
    plista->ultimo++;

    return 1;
}

/*-------------------------------- REMOÇÕES -------------------------------------------------*/

// REMOVER NO INICIO
int removerINICIO (tlista *plista, titem *px)
{
    if (listavazia(plista))
        return 0;

    *px = plista -> item[plista->primeiro];
    int cont = plista->primeiro;

    while(cont != plista->ultimo)
    {
        plista->item[cont] = plista->item[cont+1];
        cont++;
    }

    plista->ultimo--;

    return 1;
}

/*-------------------------------- OBTER POSIÇÃO DE ELEMENTO -------------------------------------------------*/

// obter elemento de uma posição "p"
int getposicao(tlista *plista, int p, titem *px)
{
    if (listavazia(plista))
        return 0;

    *px = plista ->item[p];

    return 1;
}

/*-------------------------------- TAMANHO DA LISTA -------------------------------------------------*/

// obter quantos elementos há na lista
int tamanho(tlista *plista)
{
    return plista -> ultimo;
}

/*-------------------------------- IMPRIMIR LISTA -------------------------------------------------*/

// imprimir lista
void imprimir(tlista *plista)
{
    int i = 0;

    printf("Itens da lista:\n");

    while(i != plista -> ultimo)
    {
        printf("%d   ",plista ->item[i].chave);

        i++;
    }

    printf("\n");
}

/*-------------------------------- FUNÇÃO MAIN -------------------------------------------------*/

int main()
{
    tlista lista;
	criaLista (&lista);
	printf("Tamanho: %d. ", tamanho(&lista));
	printf("Vazia: %s\n", listavazia(&lista) == 1 ? "SIM":"NAO");

	titem item1, item2;
	item1.chave = 10;
	insereINICIO (&lista, item1);
	item2.chave = -5;
	insereINICIO (&lista, item2);
	imprimir (&lista);

	titem itemRetornado;

	getposicao (&lista, 1, &itemRetornado);
	printf("Retorno: %d\n", itemRetornado.chave);

	printf("Tamanho: %d. ", tamanho(&lista));
	printf("Vazia: %s\n", listavazia(&lista) == 1 ? "SIM":"NAO");

	titem itemRemovido;
	removerINICIO (&lista, &itemRemovido);
	printf("Item removido: %d\n", itemRemovido.chave);
	imprimir (&lista);

	removerINICIO (&lista, &itemRemovido);
	printf("Item removido: %d\n", itemRemovido.chave);

    return 0;
}
