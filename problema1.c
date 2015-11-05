#include <stdio.h>
#include <stdlib.h>

/*
    Aluna: Victória Silva Roiz				Nº USP 8955431
	Aluna: Ana Luiza Queiroz Oliveira 		Nº USP 8955598
    Problema 1
*/

#include<stdlib.h>
#include<stdio.h>

typedef struct arvore{
    int chave;
    int dado;
    struct arvore *esq;
    struct arvore *dir;
}arvore;

arvore* busca(arvore *raiz, int chave){
    if(raiz==NULL){return NULL;}
    if(raiz->chave==chave){
        return raiz;
    }
    if(chave>=raiz->chave){
        return busca(raiz->dir, chave);}
    if(chave < raiz->chave){
        return busca(raiz->esq, chave);
    }
}

void insercao(arvore* no, int chave){
    arvore *p = no;
    arvore *pai = NULL;

    while(p != NULL) {
        pai = p;
        if (p->chave >= chave) {
            p = p->esq;
        } else {
            p= p->dir;
        }
    }

    arvore *novo= (arvore*)malloc(sizeof(struct arvore));
    novo->chave = chave;
    novo->dado = 10;
    novo->esq = NULL;
    novo->dir = NULL;

    if(pai->chave >= novo->chave){
        pai->esq=novo;
    }
    else{
        pai->dir=novo;
        }
}

void remocao(arvore *no, int chave){
    arvore *p = no;
    arvore *pai = NULL;

    while(p != NULL && p->chave != chave) {
        pai = p;
        if (p->chave >= chave) {
            p = p->esq;
        } else {
            p = p->dir;
        }
    }
        if(p == NULL){
                 return;
    }
    arvore *m = p->dir;
    while(m != NULL && m->esq != NULL){
            m = m->esq;
    }
    arvore *n;
        if(m != NULL){
        m -> esq = p -> esq;
        n = p->dir;
    } else {
        n = p->esq;
    }
        if(pai->chave < chave) {
        pai->dir = n;
    } else {
        pai->esq = n;
    }
    free(p);
}

arvore* freearvore(arvore* a){
	if (a!=NULL){
		freearvore(a->esq); /* libera sae */
		freearvore(a->dir); /* libera sad */
		free(a); /* libera raiz */
	}
	return NULL;
}

void visita(arvore *no){
	printf("%d ",no->chave);
}

void preordem(arvore *no){
	if(no!=NULL)
	{
		visita(no);
		preordem(no->esq);
		preordem(no->dir);
	}
}

void emordem(arvore*no) //vai passar por todas as chaves, em ordem crescente.
{
	if(no!=NULL)
	{
		emordem(no->esq);
		visita(no);
		emordem(no->dir);
	}
}

void posordem(arvore*no)
{
	if(no!=NULL)
	{
		posordem(no->esq);
		posordem(no->dir);
		visita(no);
	}
}

void labelledbracket(arvore *no){
    if(no == NULL){
            printf("[]");
        return;
    }
    printf("[%d ",no->chave);
    labelledbracket(no->esq);
    printf(" ");
    labelledbracket(no->dir);
    printf("]");

}


// API PRINCIPAL

void main(){
    arvore *raiz = NULL;
    int op=0;
	int loop=1; // Encerrar programa na opção sair
	int opmenu=0;
	int valor,n,i;
	arvore *aux;

	while(loop == 1){
		printf("\nMenu de opcoes:\n(1) Inserir\n(2) Remover\n(3) Impressao Pre-Ordem\n(4) Impressao Pos-Ordem\n(5) Impressao Em Ordem\n(6) Impressao em labelled bracketing\n(7) Busca\n(8) Sair\n                Opcao Escolhida: ");
		scanf("%d",&opmenu);
		printf("%d\n",opmenu);
		switch(opmenu){
			case 1:
			    printf("Digite o numero de elementos para inserir: ");
			    scanf("%d",&n);
			    for(i=0;i<n;i++){
                    printf("\nInsira o %d valor para ser inserido na arvore: ",i);
                    scanf("%d",&valor);
                    if(raiz == NULL){
                        raiz = (arvore*) malloc(sizeof(arvore));
                        raiz->chave = valor;
                        raiz->dir = NULL;
                        raiz->esq = NULL;
                    }
                    else{
                        insercao(raiz,valor);
                    }
                    printf("%d Inserido com Sucesso!",valor);
			    }
				break;
			case 2:
				printf("Insira um valor para ser removido da arvore: ");
				scanf("%d",&valor);
				remocao(raiz,valor);
				printf("%d Removido com Sucesso!",valor);
				break;
			case 3:
				preordem(raiz);
				break;
			case 4:
				posordem(raiz);
				break;
			case 5:
				emordem(raiz);
				break;
			case 6:
                labelledbracket(raiz);
				break;
            case 7:
                printf("Insira um valor para ser buscado na arvore: ");
				scanf("%d",&valor);
				aux = busca(raiz,valor);
				if(aux == NULL){
                    printf("%d Nao Encontrado!",valor);
				}else{
                    printf("%d Encontrado!",valor);
				}
				break;
			case 8:
				loop =0;
				break;
			default:
				printf("Opcao Invalida\n");
				break;
		}
	}
}

