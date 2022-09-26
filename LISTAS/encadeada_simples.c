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

// insere no inicio
int insereINICIO (tlista *plista, titem x)
{
    tcelula *novo = (tcelula*) malloc(sizeof(tcelula)); // cria um novo nó e aloca espaço pra ele
    novo->item = x;
    novo->pprox = NULL;

    if(listavazia(plista))
    {
        plista->pprimeiro = novo;
        plista->pultimo = novo;
    }
    else
    {
        novo->pprox = plista->pprimeiro;
        plista->pprimeiro = novo;
    }

    return 1;
}


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


// INSERE EM QUALQUER POSIÇÃO
int insereQUALQUER (tlista *plista, int p, titem x)
{
    if(p > tamanho(plista) + 1) // se a posição for maior que o tamanho da lista no momento + 1 (oq significa que não é pra inserir na ultima posição)
    {
        printf("Impossivel inserir valor: %d pois o Tamanho da lista e: %d e posicao dada foi: %d\n", x.chave,tamanho(plista), p);
        return 0;
    }

    tcelula *novo = (tcelula*) malloc(sizeof(tcelula)); // cria um novo nó e aloca espaço pra ele
    novo->item = x;
    novo->pprox = NULL;

    tcelula *paux = plista->pprimeiro;
    tcelula *panterior = paux;
    int cont = 0;


    do
    {
        if( (p == 0) && (plista->pprimeiro == NULL) ) // caso a lista esteja vazia e a pessoa dejesa inserir na primeira posição
        {
            plista->pprimeiro = novo;
            plista->pultimo = novo;

            break;
        }
        else if ( (p == 0) ) // caso deseje inserir no inicio e a lista nao esteja vazia
        {
            novo->pprox = plista->pprimeiro;
            plista->pprimeiro = novo;

            break;
        }
        else if (cont == p) // se quiser inserir no meio
        {
            novo->pprox = panterior->pprox;
            panterior->pprox = novo;

            break;
        }
        else if ( paux == plista->pultimo ) // caso deseje inserir no final e a lista nao esteja vazia
        {
            plista->pultimo->pprox = novo;
            plista->pultimo = novo;

            break;
        }
        else // se nenhuma das anteriores, vá para a próxima posição
        {
            panterior = paux;
            paux = paux->pprox;
            cont++;
        }

    }while (paux != NULL);

    return 1;
}

/*-------------------------------- REMOÇÕES -------------------------------------------------*/

// REMOVER NO INICIO
int removerINICIO (tlista *plista, titem *px)
{
    if(listavazia(plista))
        return 0;

    tcelula *paux; // o nó auxiliar impede que voce perca a referência entre o anterior e o próximo do nó que será excluído

    paux = plista->pprimeiro;
    *px = paux->item;

    plista->pprimeiro = paux->pprox;
    free(paux);

    return 1;
}


// REMOVER NO FIM
int removerFIM (tlista *plista, titem *px)
{
    if(listavazia(plista))
    {
        printf("LISTA VAZIA!!!     ");
        printf("Ultimo ");
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


// REMOVER NO MEIO
int removerMEIO (tlista *plista, int p, titem *px)
{
    if(p > tamanho(plista) - 1) // se a posição for maior que o tamanho da lista - 1 (como a lista começa em 0, é necessário colocar o -1)
    {
        printf("Impossivel remover pois o Tamanho da lista vai ate: %d e a posicao dada foi: %d\n",tamanho(plista) - 1, p);

        return 0;
    }

    if(listavazia(plista))
    {
        printf("LISTA VAZIA!!!     ");
        printf("Ultimo ");
        return 0;
    }

    tcelula *paux = plista->pprimeiro;
    tcelula *panterior;
    int cont = 0;

    do
    {
        if(tamanho(plista) == 1) // se a lista só tiver uma célula
        {
            plista->pprimeiro = NULL;

            break;
        }
        else if (cont == p && paux == plista->pprimeiro) //se a poicao for no meio da lista
        {
            plista->pprimeiro = paux->pprox;

            break;
        }
        else if(cont == p)
        {
            panterior->pprox = paux->pprox;

            break;
        }
        else if(paux == plista->pultimo) // se a posição dada foi a do ultimo nó
        {
            panterior->pprox = NULL;
            plista->pultimo = panterior;

            break;
        }

        cont++;
        panterior = paux;
        paux = paux->pprox;

    } while(paux != NULL);

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

    insereINICIO(&lista, item2);
    imprimir(&lista);

    printf("Tamanho: %d. ", tamanho(&lista));

    titem itemRemovido;
	removerINICIO (&lista, &itemRemovido);
	printf("Item removido: %d\n", itemRemovido.chave);

    insereQUALQUER(&lista,1, item3);
    imprimir(&lista);

    printf("Tamanho: %d. ", tamanho(&lista));


    removerFIM (&lista, &itemRemovido);
	printf("Item removido: %d\n", itemRemovido.chave);

    imprimir(&lista);
	printf("Tamanho: %d. ", tamanho(&lista));

}
