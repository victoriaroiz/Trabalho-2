
/*
    Problema 2
    Aluna: Victória Silva Roiz				Nº USP 8955431
	Aluna: Ana Luiza Queiroz Oliveira 		Nº USP 8955598
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <locale.h>


typedef struct arvore{
    int chave;
    int grau;
    char label[20];
    struct arvore *esq;
    struct arvore *dir;
}arvore;

// Constantes para comparação

int h;

arvore* busca(arvore *raiz, char *chave){
    arvore *aux1;
    if(strcmp(chave,raiz->label) == 0){return raiz;}

    if(raiz->esq!=NULL){
        aux1 = busca(raiz->esq,chave);
        if(aux1!=NULL){
            return aux1;
        }
    }
    if(raiz->dir!=NULL){
        aux1 = busca(raiz->dir,chave);
        if(aux1!=NULL){
            return aux1;
        }
    }
    return NULL;
}

arvore* grau(arvore *raiz, char *chave){
    arvore *aux1;
    if(strcmp(chave,raiz->label) == 0){
            raiz->grau=0;
            return raiz;}

    if(raiz->esq!=NULL){
        aux1 = grau(raiz->esq,chave);
        if(aux1!=NULL){
            aux1->grau++;
            return aux1;
        }
    }
    if(raiz->dir!=NULL){
        aux1 = grau(raiz->dir,chave);
        if(aux1!=NULL){
            aux1->grau++;
            return aux1;
        }
    }
    return NULL;
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
	printf("%s ",no->label);
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
    printf("[%s ",no->label);
    labelledbracket(no->esq);
    printf(" ");
    labelledbracket(no->dir);
    printf("]");

}

//calcula o grau de todos em relação a raiz
void calculagraus(arvore *raiz,arvore*no)
{
	if(no!=NULL)
	{
		calculagraus(raiz,no->esq);
		grau(raiz,no->label);
		if(h <= no->grau){h=no->grau;}
		calculagraus(raiz,no->dir);
	}
}

void imprimegraux(arvore*no, int x)
{
	if(no!=NULL)
	{
		imprimegraux(no->esq,x);
		if(no->grau == x){
                printf("%s ",no->label);
        }
		imprimegraux(no->dir,x);
	}
}

void printantepassado(arvore *raiz, int flag){ //flag indica se e print da familia toda ou de um individuo apenas (imprimir ou nao a raiz)
    int i,n;
    h=0;
    calculagraus(raiz,raiz);
    for(i=flag;i<=h;i++){
        imprimegraux(raiz,i);
        if(flag == 0)printf("\n");
    }
}


// API PRINCIPAL

void main(){


    arvore *raiz = NULL;
    int op=0;
	int loop=1; // Encerrar programa na opção sair
	int opmenu=0;
	int valor,n,i;
	char in1[20],in2[20],in3[20];
	arvore *aux,*aux1;

	while(loop == 1){
		printf("\nMenu de opcoes:\n(1) Inserir\n(2) Impressao por Geracao\n(3) Antepassados de Alguem\n(4) Impressao Labelled Bracketing\n(5) Grau de Parentesco\n(6) Sair\n               Opcao Escolhida: ");
		scanf("%d",&opmenu);
		fflush(stdin);
		printf("%d\n",opmenu);
		switch(opmenu){
			case 1:
			    printf("Digite o numero de elementos para inserir: ");
			    scanf("%d",&n);
			    fflush(stdin);
			    for(i=0;i<n;i++){
                    scanf("%s %s %s",in1,in2,in3);
                    fflush(stdin);
                    // Se ainda nao inseriu nada
                    if(raiz == NULL){
                        raiz = (arvore*) malloc(sizeof(arvore));
                        strcpy(raiz->label,in1);
                        raiz->dir = NULL;
                        raiz->esq = NULL;
                    }
                    // seleciona o no que recebera parentes
                    aux = busca(raiz,in1);
                    //cria parente da esqeurda
                    aux->esq = (arvore*) malloc(sizeof(arvore));
                    strcpy(aux->esq->label,in2);
                    aux->esq->esq=NULL;
                    aux->esq->dir=NULL;
                    //cria parente da direita
                    aux->dir = (arvore*) malloc(sizeof(arvore));
                    strcpy(aux->dir->label,in3);
                    aux->dir->esq=NULL;
                    aux->dir->dir=NULL;
                    printf("%s %s %s Inserido com Sucesso!",in1,in2,in3);
			    }

				break;
			case 2:
			    printantepassado(raiz,0);
				break;
			case 3:
			    printf("Digite o nome do antepassado para imprimir: ");
			    scanf("%s",in1);
			    fflush(stdin);
			    printf("Busca por antepassados de: %s\n",in1);
			    aux = busca(raiz,in1);
			    printantepassado(aux,1);
				break;
			case 4:
				labelledbracket(raiz);
				break;
			case 5:
			    printf("Digite os parentes para calcular o grau: (Ex: pai filho)");
				scanf("%s %s",in1,in2);
				fflush(stdin);
				//Seleciona
				aux = grau(raiz,in1);
				aux1 = grau(raiz,in2);
				printf("Grau de Parentesco de %s %s eh: %d ",in1,in2, abs(aux->grau - aux1->grau));
				break;
			case 6:
                loop =0;
				break;
			default:
				printf("Opcao Invalida\n");
				break;
		}
	}
	freearvore(raiz);
}
