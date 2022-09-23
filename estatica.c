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


// insere no fim
int insereFIM (tlista *plista, titem x)
{
    if(plista -> ultimo == max)
        return 0;

    plista -> item[plista -> ultimo++] = x; // ultimo++ significa que ele vai inserir na possição ultimo e depois incrementá-la em +1

    return 1;
}

// INSERE EM QUALQUER POSIÇÃO
int insereQUALQUER (tlista *plista, int p, titem x)
{
    if(plista -> ultimo == max)
    {
        printf("\nLISTA CHEIA!\n");
        return 0;
    }

    if(p > plista->ultimo)
    {
        printf("Impossivel inserir valor: %d pois Tamanho da lista e: %d e posicao dada foi: %d\n", x.chave,tamanho(plista), p);
        return 0;
    }

    int i = plista -> ultimo;

    while(i != p)
    {
        plista->item[i] = plista->item[i-1];
        i--;
    }

    plista->item[p] = x;
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

// REMOVER NO FIM
int removerFIM (tlista *plista, titem *px)
{
    if (listavazia(plista))
        return 0;

    *px = plista -> item[plista->ultimo - 1];

    plista->ultimo--;

    return 1;
}

// remover de qualquer posição
int removerQUALQUER (tlista *plista,int p, titem *px) //p é uma posição; *px devolve o valor removido para o programa principal;
{
    if (listavazia(plista) || p >= plista -> ultimo)
        return 0;

    *px = plista -> item[p];
    int cont;

    for(cont = p+1; cont <= plista -> ultimo; cont ++)
    {
        plista -> item[p] = plista ->item[cont];
        plista -> ultimo--;

        return 1;
    }
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
	insereFIM (&lista, item1);
	item2.chave = -5;
	insereFIM (&lista, item2);
	imprimir (&lista);

	titem itemRetornado;

	getposicao (&lista, 1, &itemRetornado);
	printf("Retorno: %d\n", itemRetornado.chave);

	printf("Tamanho: %d. ", tamanho(&lista));
	printf("Vazia: %s\n", listavazia(&lista) == 1 ? "SIM":"NAO");

	titem itemRemovido;
	removerQUALQUER (&lista, 1, &itemRemovido);
	printf("Item removido: %d\n", itemRemovido.chave);
	imprimir (&lista);

    return 0;
}
