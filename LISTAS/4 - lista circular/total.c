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
    struct celula *pant;
}tcelula;

typedef struct
{
    tcelula *pprimeiro;
} tlista;


/*-------------------------------- CRIAR LISTA -------------------------------------------------*/

// CRIAR LISTA
void criaLista (tlista *plista)
{
    plista->pprimeiro = NULL;
}


/*--------------------------------- LISTA ESTÁ VAZIA? ------------------------------------------------*/

// verificar se lista esta vazia
int listavazia (tlista *plista)
{
    return plista->pprimeiro == NULL;
}


/*---------------------------------- INSERÇÃO -----------------------------------------------*/

int insere (tlista *plista, titem x)
{
    tcelula *novo = (tcelula*) malloc(sizeof(tcelula)); // cria um novo nó e aloca espaço pra ele
    novo->item = x;
    novo->pprox = NULL;
    novo->pant = NULL;

    if(listavazia(plista))
    {
        plista->pprimeiro = novo;
        novo->pant = novo;
        novo->pprox = novo;
    }
    else
    {
        novo->pprox = plista->pprimeiro;
        novo->pant = plista->pprimeiro->pant;

        plista->pprimeiro->pant->pprox = novo;
        plista->pprimeiro->pant = novo;
        plista->pprimeiro = novo;
    }


     return 1;
}


/*-------------------------------- REMOÇÕES -------------------------------------------------*/

int removerPRIMEIRO (tlista *plista, titem *px)
{
    if(listavazia(plista))
    {
        printf("LISTA VAZIA!\n");
        return 0;
    }


    tcelula *paux; // o nó auxiliar impede que voce perca a referência entre o anterior e o próximo do nó que será excluído

    paux = plista->pprimeiro;
    *px = paux->item;

    if (tamanho(plista) == 1)
    {
        plista->pprimeiro = NULL;
    }

    else
    {
        paux->pant->pprox = paux->pprox;

        plista->pprimeiro = paux->pprox;
        plista->pprimeiro->pant = paux->pant;
    }


    free(paux);

    return 1;
}


/*Implemente uma função para remover qualquer elemento da lista,
independente de sua posição, na lista circular
 Os elementos a serem removidos devem conter a chave passada por
parâmetro
 Retorna quantos elementos foram removidos
*/
int removerQUALQUER (tlista *plista, int chave)
{
    if(listavazia(plista))
    {
        printf("LISTA VAZIA!\n");
        return 0;
    }

    int cont = 0;


    tcelula *paux = plista->pprimeiro;

    do
    {
        if(paux->item.chave == chave)
        {
            if(paux == plista->pprimeiro)
                plista->pprimeiro = paux->pprox;


            if (tamanho(plista) == 1)
            {
                plista->pprimeiro = NULL;
                free(paux);
                cont++;

                break;
            }
            else
            {
                paux->pant->pprox = paux->pprox;
                paux->pprox->pant = paux->pant;

                tcelula *noParaRemover = paux;
                paux = paux->pprox;

                free(noParaRemover);

                cont++;
            }


        }
        else paux = paux->pprox;

    } while(paux != plista->pprimeiro);


    return cont;
}



/*-------------------------------- TAMANHO DA LISTA -------------------------------------------------*/

// obter quantos elementos há na lista
int tamanho(tlista *plista)
{
    tcelula *paux = plista->pprimeiro;
    int cont = 0;

    do
    {
        cont++;
        paux = paux->pprox;

    } while (paux != plista->pprimeiro);

    return cont;
}


/*-------------------------------- IMPRIMIR LISTA -------------------------------------------------*/

// imprimir lista
void imprimir(tlista *plista)
{
    tcelula *celula = plista->pprimeiro;

    printf("Itens da lista: ");

    if(celula != NULL)
    {
        do
        {
            printf("%d  ", celula->item.chave);
            celula = celula->pprox;

        } while(celula != plista->pprimeiro);
    }

    printf("\n");
}


// ------------------------------------------- MAIN ----------------------------------------------------

int main()
{
    tlista lista;
    criaLista(&lista);

    titem item1, item2, item3;
    item1.chave = 24;
    item2.chave = 24;
    item3.chave = 24;

    titem especial;
    especial.chave = 777;

    insere(&lista,item1);
    imprimir(&lista);

    titem itemRemovido;
    if(removerPRIMEIRO (&lista, &itemRemovido))
        printf("Item removido: %d\n", itemRemovido.chave);

    insere(&lista,item2);
    imprimir(&lista);

    insere(&lista,item3);
    imprimir(&lista);

    insere(&lista,especial);
    imprimir(&lista);

    int quantidade = removerQUALQUER (&lista, 24);

    if(quantidade)
        printf("Quantidades de itens removido: %d\n", quantidade);

    imprimir(&lista);

    if(removerPRIMEIRO (&lista, &itemRemovido)) {
        printf("Item removido: %d\n", itemRemovido.chave);
        imprimir(&lista);
    }

    if(removerPRIMEIRO (&lista, &itemRemovido)) {
        printf("Item removido: %d\n", itemRemovido.chave);
        imprimir(&lista);
    }
}

