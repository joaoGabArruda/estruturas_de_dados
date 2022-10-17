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


// insere no fim
int insereFIM(tlista *plista, titem x)
{
    tcelula *novo = (tcelula*) malloc(sizeof(tcelula)); // cria um novo nó e aloca espaço pra ele
    novo->item = x;
    novo->pprox = NULL;
    novo->pant = NULL;

    if(listavazia(plista))
    {
        plista->pprimeiro = novo;
    }
    else
    {
        plista->pultimo->pprox = novo;
        novo->pant = plista->pultimo;
    }

    plista->pultimo = novo;

    return 1;
}


// INSERE EM QUALQUER POSIÇÃO
int insereMEIO (tlista *plista, int p, titem x)
{
   if(p > tamanho(plista) + 1) // se a posição for maior que o tamanho da lista no momento + 1 (oq significa que não é pra inserir na ultima posição)
    {
        printf("Impossivel inserir valor: %d pois o Tamanho da lista e: %d e posicao dada foi: %d\n", x.chave,tamanho(plista), p);
        return 0;
    }

    tcelula *novo = (tcelula*) malloc(sizeof(tcelula)); // cria um novo nó e aloca espaço pra ele
    novo->item = x;
    novo->pprox = NULL;
    novo->pant = NULL;

    tcelula *paux = plista->pprimeiro;

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
            plista->pprimeiro->pant = novo;
            plista->pprimeiro = novo;

            break;
        }
        else if (cont == p) // se quiser inserir no meio
        {
            novo->pprox = paux->pant->pprox;
            novo->pant = paux->pant;

            paux->pant->pprox = novo;
            paux->pant = novo;

            break;
        }
        else if ( paux == plista->pultimo ) // caso deseje inserir no final e a lista nao esteja vazia
        {
            plista->pultimo->pprox = novo;
            novo->pant = plista->pultimo;
            plista->pultimo = novo;

            break;
        }
        else // se nenhuma das anteriores, vá para a próxima posição
        {
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
    plista->pprimeiro->pant = NULL;

    free(paux);

    return 1;
}


// REMOVER NO FIM
int removerFIM (tlista *plista, titem *px)
{
    if(listavazia(plista))
    {
        printf("LISTA VAZIA!!!");
        return 0;
    }

    tcelula *paux = plista->pprimeiro;

    if(tamanho(plista) == 1)
    {
         plista->pprimeiro = NULL;
         plista->pultimo = NULL;
    }
    else
    {
        while(paux != plista->pultimo)
            paux = paux->pprox;


        paux->pant->pprox = NULL;
        plista->pultimo = paux->pant;
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
        printf("Impossivel remover pois o a lista vai de 0 a %d e a posicao dada foi: %d\n",tamanho(plista) - 1, p);

        return 0;
    }

    if(listavazia(plista))
    {
        printf("LISTA VAZIA!!!");
        return 0;
    }

    tcelula *paux = plista->pprimeiro;

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
            paux->pprox->pant = NULL;

            break;
        }

        else if(paux == plista->pultimo) // se a posição dada foi a do ultimo nó
        {
            paux->pant->pprox = NULL;
            plista->pultimo = paux->pant;

            break;
        }
        else if(cont == p) // se quiser remover no meio
        {
            paux->pant->pprox = paux->pprox;
            paux->pprox->pant = paux->pant;

            break;
        }

        cont++;
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

    insereMEIO(&lista,0, item1);
    imprimir(&lista,0);

    insereMEIO(&lista,1, item2);
    imprimir(&lista,0);

    insereMEIO(&lista, 1, item3);
    imprimir(&lista,0);

    titem itemRemovido;
    if(removerMEIO (&lista,1, &itemRemovido))
        printf("Item removido: %d\n", itemRemovido.chave);

    item3.chave = 7777;

    insereMEIO(&lista,3, item3);
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
        printf("\nEsta presente!");

}
