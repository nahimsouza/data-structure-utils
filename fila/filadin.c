/**

==========================================================================
					  		CAIXA PREFERENCIAL
==========================================================================

Uma loja possui uma fila unica para o atendimento dos seus caixas. 
Entretanto, sempre que uma pessoa com idade >= 60 anos chega
na fila ela tem prioridade sobre as outras pessoas, entrando no começo da fila. 
Caso duas pessoas com 60 anos ou mais entrem na fila, a pessoa mais velha tem 
prioridade sobre a mais nova.

Você deve implementar uma estrutura de dados fila adaptada para tratar
a entrada das pessoas na fila de acordo com as prioridades citadas acima.

Entrada:
A entrada consiste de um número inteiro (1 <= N <= 10000) que representa a 
quantidade de pessoas que entraram na fila (0 para sair do programa). 
As entradas seguintes representam a idade das pessoas na ordem em que
elas chegaram na fila. Em seguida é informado um numero inteiro <= N de pessoas 
que já foram atendidas até o momento.

Saída:
A saída deve ser uma lista de números representando as pessoas que ainda 
restaram na fila, isto é, as suas respectivas idades.

==========================================================================
						 	  Exemplo
==========================================================================

Entrada:
	8
	15 18 14 22 60 39 67 62 
	5
	3
	28 22 30
	2
	0

Saída:
	67 62 60 15 18 
	28 22

==========================================================================
*/


#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

typedef int elem_t;

typedef struct no{
  elem_t info;
  struct no *prox;
} No_lista;

typedef No_lista* Lista;



/* Inicializa uma lista */
void inicLista(Lista *p_l){
	*p_l = NULL;
}

/* Verifica se a lista está vazia ou nao */
int listaVazia(Lista *p_l){
	if (*p_l == NULL)
		return 1;
	return 0;
}

/* Insere um elemento no inicio da lista */
void insereInicio(Lista *p_l, elem_t e){
	No_lista *no;
	no = malloc (sizeof(No_lista));
	no->info = e;
	no->prox = *p_l;
	*p_l = no;
}

/* Insere um elemento no final da lista */
void insereFim(Lista *p_l, elem_t e){
	No_lista *no, *aux;
	if(listaVazia(p_l)){
		insereInicio(p_l,e);
	}else{
		no = malloc(sizeof(No_lista));
		no->info = e;
		aux = *p_l;
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = no;
		no->prox = NULL;
	}
}

/* Insere um elemento na lista de maneira ordenada (decrescente) */
void inserePrioridade(Lista *p_l, elem_t e){
	No_lista *no,*aux;
	int inseriu = 0; //flag

	aux = *p_l;
	no = malloc(sizeof(No_lista));
	no->info = e;

	if(listaVazia(p_l)){
		no->prox = NULL;
		aux = no; // POR QUE, SE EU TIRAR ESTA LINHA ACONTECE 'FALHA DE SEGMENTACAO' E...
		*p_l = no; // ... SE EU TIRAR ESTA, NAO FUNCIONA AO INSERIR ???
		inseriu = 1;

	}
	
	if(no->info > aux->info && !inseriu){ //qdo for inserir o primeiro elemento
		no->prox = aux;
		*p_l = no;
		inseriu = 1;	

	}

	while(aux->prox!=NULL && !inseriu){
		if(no->info > aux->prox->info){
			no->prox = aux->prox;
			aux->prox = no;
			inseriu = 1;

		}	
		if(!inseriu)
			aux = aux->prox;
	}

	if(!inseriu){ // se for inserir no ultimo elemento
		no->prox = NULL;
		aux->prox = no;
	}
}

void insereLista(Lista *p_l, elem_t e) {
	if (e >= 60) 
		return inserePrioridade(p_l, e);
	else
		return insereFim(p_l, e);
}

/* Remove o elemento que esta no inicio da lista.
   Retorna 0 caso a lista esteja vazia */
int removeInicio(Lista *p_l, elem_t *p_e){
	No_lista *no;
	
	if(!listaVazia(p_l)){
		
		no = *p_l;
		*p_l = no->prox;
		*p_e = no->info;
		free(no);
		return 1; 
	}
	return 0;
}


/* Remove todos os numeros da lista */
void libera(Lista *p_l){
	No_lista *aux;
	
	while(*p_l != NULL){
		aux = *p_l;
		*p_l = (*p_l)->prox;
		free(aux);
	}

}

/* Exibe o conteudo da lista */
void exibe(Lista *p_l){
	No_lista *aux;
	aux = *p_l;
	while (aux != NULL){
		printf("%d ", aux->info);
		aux = aux->prox;
	}

}


int main() {

	int N;				// numero de pessoas na fila
	Lista l;			// lista - usada para a fila dinamica
	int i;				// contador
	int pessoa;			// idade da pessoa que entrou na fila
	int a;				// quantidade de pessoas que foi atendida
	int tam;			// tamanho da fila

	scanf("%d", &N);
	while (N > 0) {
		inicLista(&l);
		
		// insere as pessoas na fila		
		for (i = 0; i < N; i++) {
			scanf("%d", &pessoa);
			insereLista(&l, pessoa);
		}

		// remove da fila as pessoas que ja foram atendidas
		scanf("%d", &a);
		for (i = 0; i < a; i++) {
			int e;
			removeInicio(&l, &e);
			printf("%d ", e);
		}
		printf("\n");

		scanf("%d", &N);
		
		libera(&l);
	}

	return 0;
}