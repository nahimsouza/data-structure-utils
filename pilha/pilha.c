/*

================================================================================
                 LEXSIM - Sintatic and Lexical Avaliator
================================================================================

Description: https://www.urionlinejudge.com.br/judge/en/problems/view/1083
Cheat Sheet: http://csis.pace.edu/~wolf/CS122/infix-postfix.htm


syntax errors:

- nao fechar N parentesis 
    >> acho q é só verificar na expressao posfixa se tem algum parentesis aberto
- usar simbolos com mais de uma letra (AA+BB, por exemplo)
    >> ao encontrar um simbolo, verificar se o proximo eh um sinal, ou '\0'
- expressao infixa termina com um sinal (a+b+)
    >> só fazer um if
- usar dois sinais juntos (a++b, por exemplo)
    >> um if para verificar o proximo token
- fechar parentesis sem abrir
    >> um if depois para ver se chegou no fim da pilha e nao achou o parentesis
    
================================================================================

*/

#include <stdio.h>
#include <string.h>

#define MAX 10000

typedef struct {
	char pilha[MAX];
	int tam;
} Pilha;

// retorna 1 se inseriu, 0 se nao inseriu
int inserePilha(Pilha *p, char elem){
	if (pilhaCheia(p))
		return 0;

	p->pilha[p->tam] = elem;
	p->tam++;
	return 1;

}

// retorna o elemento, ou '' se nao tiver elemento
char removePilha(Pilha *p){
	if (pilhaVazia(p))
		return '\0';
			
	p->tam--;
	return p->pilha[p->tam];
}

char topo(Pilha *p) {
    return p->pilha[p->tam - 1];
}

int pilhaVazia(Pilha *p) {
	return p->tam == 0;
}

int pilhaCheia(Pilha *p) {
	return p->tam == MAX;
}

int inicializaPilha(Pilha *p) {
	p->tam = 0;
	return 1;
}

int operadorValido(char c) {
    return ((c>='a') && (c<='z')) || ((c>='A') && (c<='Z')) 
        || ((c>='0') && (c<='9'))
        || c == '(' || c == ')' 
        || c == '+' || c  == '-' || c  == '*' || c  == '/'
        || c  == '>' || c  == '<' || c  == '=' || c  == '#'
        || c  == '.' || c  == '|' || c  == '^';
        
}

int simbolo(char c) {
    return ((c>='a') && (c<='z')) || ((c>='A') && (c<='Z')) 
        || ((c>='0') && (c<='9'));
}

// retorna 1 caso op1 tenha precedencia sobre op2
int temPrecedencia(char op1, char op2) {
    int pre1, pre2;
    
    switch (op1) {
        case '^':
            pre1 = 6;
            break;
        case '*':
        case '/':
            pre1 = 5;
            break;
        case '+':
        case '-':
            pre1 = 4;
            break;
        case '<':
        case '>':
        case '=':
        case '#':
            pre1 = 3;
            break;
        case '.':
            pre1 = 2;
            break;
        case '|':
            pre1 = 1;
            break;
        default:
            pre1 = 0;
            break;
    }
    
    switch (op2) {
        case '^':
            pre2 = 6;
            break;
        case '*':
        case '/':
            pre2 = 5;
            break;
        case '+':
        case '-':
            pre2 = 4;
            break;
        case '<':
        case '>':
        case '=':
        case '#':
            pre2 = 3;
            break;
        case '.':
            pre2 = 2;
            break;
        case '|':
            pre2 = 1;
            break;
        default:
            pre2 = 0;
            break;
    }
    
    // retorna 1 quando precedencia eh igual
    return (pre1 - pre2) >= 0;
}

void infixToPostfix(char expr[], Pilha *p, char post[]) {
    int i = 0;
    int count = 0;
    int abriuParentesis = 0; // flag para indicar se abriu parentesis
    
    // limpar o post
    post[0] = '\0';
    
    // para evitar: a+b+
    char ultimo = expr[strlen(expr) - 1];
    
    
    // Garante que a string possui somente caracteres validos
    i = 0;
    while (i < MAX && expr[i] != '\0' && expr[i] != '\n') {
        if (!operadorValido(expr[i])) {
            strcpy(post,"Lexical Error!");
            return;
        }
        i++;
    }
    
    i = 0;
    while (i < MAX && expr[i] != '\0' && expr[i] != '\n') {
        // do infix to postfix
        if (simbolo(expr[i])) {
            
            // para evitar: aa+bb, a(b+c)
            if (i+1 != MAX && (simbolo(expr[i + 1]) || expr[i + 1] == '(')) {
                strcpy(post,"Syntax Error!");
                return;
            }
            
            // concatena o na string posfixa
            post[count] = expr[i];
            post[count + 1] = '\0';
            count++;
        } else {
            
            // para evitar: a++b
            if (expr[i]=='(' && !simbolo(expr[i+1]) || (expr[i]!='(' && expr[i]!=')') && (expr[i+1]!='(' && expr[i+1]!=')') && !simbolo(expr[i+1]) ) {
                strcpy(post,"Syntax Error!");
                return;
            }
            
            if (pilhaVazia(p) || expr[i]=='(' || abriuParentesis) {
                inserePilha(p, expr[i]);
                abriuParentesis = expr[i] == '(' ? 1 : 0;
            } else if (expr[i] == ')') {
                while (!pilhaVazia(p) && topo(p) != '(') {
                    // remove da pilha e insere na string
                    post[count] = removePilha(p);
                    post[count + 1] = '\0';
                    count++;
                }
                
                // caso encontre o '(' remove da pilha
                if (pilhaVazia(p)) {
                    strcpy(post,"Syntax Error!");
                    return;
                } else {
                    removePilha(p);
                    abriuParentesis = 0;
                }
            
            } else {
                if (temPrecedencia(topo(p), expr[i])) {
                    do {
                        post[count] = removePilha(p);
                        post[count + 1] = '\0';
                        count++;
                    } while (!pilhaVazia(p) && temPrecedencia(topo(p), expr[i]));
                  
                    inserePilha(p, expr[i]);
                } else {
                    inserePilha(p, expr[i]);
                }
            } 
        }
        i++;
    } 
    
    if (operadorValido(ultimo) && !simbolo(ultimo) && ultimo != ')') {
        strcpy(post,"Syntax Error!");
        return;
    }
    
    while(!(pilhaVazia(p))) {
        post[count] = removePilha(p);
        post[count + 1] = '\0';
        count++;
	}
	
	// verifica se faltou fechar algum parentesis
	for (i = 0; i < count; i++) {
	    if (post[i] == '(') {
	        strcpy(post,"Syntax Error!");
            return;
	    }
	}
}

int main() {
	char expr[MAX];
	char post[MAX];
	Pilha p;
	int i;

	while (scanf("%s", expr) != EOF) {
    	inicializaPilha(&p);
    	//scanf("%s", expr);
        infixToPostfix(expr, &p, post);
        printf("%s\n", post);
        
        i++;
    } // fim while
	
	return 0;
}
