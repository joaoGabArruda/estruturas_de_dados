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
        if( (p == 0 || p==1) && (plista->pprimeiro == NULL) ) // caso a lista esteja vazia e a pessoa dejesa inserir na primeira posição
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

// REMOVER NO MEIO
int removerQUALQUER (tlista *plista, int p, titem *px)
{
    if(listavazia(plista))
    {
        printf("Impossivel remover! A lista esta vazia.\n");
        return 0;
    }


    if(p > tamanho(plista) - 1) // se a posição for maior que o tamanho da lista - 1 (como a lista começa em 0, é necessário colocar o -1)
    {
        printf("Impossivel remover pois o Tamanho da lista vai ate: %d e a posicao dada foi: %d\n",tamanho(plista)-1, p);

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
        else if (cont == p && paux == plista->pprimeiro) //se quiser remover no inicio
        {
            plista->pprimeiro = paux->pprox;

            break;
        }
        else if(cont == p) // se quiser remover no meio
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

    insereQUALQUER(&lista,1, item1);
    imprimir(&lista);

    insereQUALQUER(&lista,0, item2);
    imprimir(&lista);

    insereQUALQUER(&lista,1, item3);
    imprimir(&lista);

    titem posi;
    if(getposicao(&lista,2,&posi))
        printf("valor %d nessa posicao\n",posi.chave);

    titem itemRemovido;
    if(removerQUALQUER (&lista,1, &itemRemovido)) {
        printf("Item removido: %d\n", itemRemovido.chave);
        imprimir(&lista);
    }

    item3.chave = 7777;

    insereQUALQUER(&lista,2, item3);
    imprimir(&lista);

     if(removerQUALQUER (&lista,0, &itemRemovido)) {
        printf("Item removido: %d\n", itemRemovido.chave);
        imprimir(&lista);
     }

      if(removerQUALQUER (&lista,1, &itemRemovido)) {
        printf("Item removido: %d\n", itemRemovido.chave);
        imprimir(&lista);
     }

     if(removerQUALQUER (&lista,0, &itemRemovido)) {
        printf("Item removido: %d\n", itemRemovido.chave);
        imprimir(&lista);
     }

     if(removerQUALQUER (&lista,0, &itemRemovido)) {
        printf("Item removido: %d\n", itemRemovido.chave);
        imprimir(&lista);
     }
}
