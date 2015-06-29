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

#define MAX 10000


// insere no fim
int insereFim(int fila[], int elem){
	int tam = 0;
	while (fila[tam] != -1) tam++;
	fila[tam] = elem;

	// retorna posicao inserida
	return tam;
}

int inserePrioridade(int fila[], int elem) {
	int pos = 0;
	int aux;
	int i = 0;

	// encontra a posicao onde sera inserido
	while (elem < fila[pos] && pos < MAX) pos++;

	// se for na ultima posicao
	if (pos == MAX-1 || fila[pos] == -1) {
		fila[pos] = elem;
		return pos;
	} else {
		// para i apontar para o fim da fila
		while (fila[i] != -1 && i < MAX) i++;

		while (i >= pos) {
			fila[i] = fila[i-1];
			i--;
		}

		fila[pos] = elem;
		
		return pos;
	}	

}

int insereFila(int fila[], int elem) {
	if (filaCheia(fila)) 
		return -1;

	if (elem >= 60) 
		return inserePrioridade(fila, elem);
	else
		return insereFim(fila, elem);
}

int removeFila(int fila[]){
	if (filaVazia(fila))
		return -1;


	// remove o primeiro elemento da fila
	int elem = fila[0];
	fila[0] = -1;
	int i = 0;

	// deslocamento
	while (fila[i+1] != -1 && i < MAX) {
		fila[i] = fila[i+1];
		i++;
	}

	fila[i] = -1;

	return elem;

}


int filaCheia(int fila[]) {
	return fila[MAX-1] != -1;
}

int filaVazia(int fila[]) {
	return fila[0] == -1;
}

void inicializaFila(int fila[]) {
	int i;
	for (i = 0; i < MAX; i++) {
		fila[i] = -1;
	}
}


int main() {

	int N;				// numero de pessoas na fila
	int fila[MAX];		// fila estática
	int i;				// contador
	int pessoa;			// idade da pessoa que entrou na fila
	int a;				// quantidade de pessoas que foi atendida
	int tam;			// tamanho da fila

	scanf("%d", &N);
	while (N > 0) {
		inicializaFila(fila);
		
		// insere as pessoas na fila		
		for (i = 0; i < N; i++) {
			scanf("%d", &pessoa);
			insereFila(fila, pessoa);
		}

		// remove da fila as pessoas que ja foram atendidas
		scanf("%d", &a);
		for (i = 0; i < a; i++) {
			printf("%d ", removeFila(fila));
		}
		printf("\n");

		scanf("%d", &N);
	}

	return 0;
}