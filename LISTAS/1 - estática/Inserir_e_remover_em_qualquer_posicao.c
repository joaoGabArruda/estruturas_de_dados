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

// remover de qualquer posição
int removerQUALQUER (tlista *plista,int p, titem *px) //p é uma posição; *px devolve o valor removido para o programa principal;
{
    if (listavazia(plista) || p >= plista -> ultimo)
        return 0;

    *px = plista -> item[p];
    int cont;

    for(cont = p+1; cont < plista -> ultimo; cont ++)
    {
        plista -> item[cont-1] = plista ->item[cont];

    }

    plista -> ultimo--;

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

	titem item1, item2,item3,item4;
	item1.chave = 10;
	insereQUALQUER (&lista,0, item1);
	item2.chave = -5;
	insereQUALQUER (&lista,1, item2);
	item3.chave = 72;
	insereQUALQUER (&lista,0, item3);
	item4.chave = 33;
	insereQUALQUER (&lista,2, item4);
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

	removerQUALQUER (&lista, 2, &itemRemovido);
	printf("Item removido: %d\n", itemRemovido.chave);
	imprimir (&lista);

	removerQUALQUER (&lista, 0, &itemRemovido);
	printf("Item removido: %d\n", itemRemovido.chave);
    imprimir (&lista);

    return 0;
}
