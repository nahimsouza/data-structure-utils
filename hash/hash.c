
/*

    hash + lista encadeada
    
    http://www.algolist.net/Data_structures/Hash_table/Chaining
    http://inst.eecs.berkeley.edu/~selfpace/studyguide/47B.sg/Output/real.world.hash.functs.pdf
    
    sample source code:
    http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html
    
	
	HASH TABLE with exterior chaining

	URI - 1256

*/


#include <stdio.h>
#include <stdlib.h>

// ============ LINKED LIST DEF ==============

typedef int ELEM_TYPE;

typedef struct N {
	ELEM_TYPE   elem;
	struct N   *next;		
} NODE;

typedef NODE* LINKED_LIST;

#define TRUE  1;
#define FALSE 0;

// ========== LINKED LIST FUNCTIONS ==========

void listInsertLast(LINKED_LIST *list, ELEM_TYPE elem) {
	NODE *n;
	NODE *aux;

	n = malloc(sizeof(NODE));
	n->elem = elem;
	n->next = NULL;

	if(*list == NULL) {
		*list = n;
	} else {
		aux = *list;	
		while (aux->next != NULL) aux = aux->next;

		// when it arrived in a null pointer
		// points to the new node
		aux->next = n;
	}
}

int listRemoveFirst(LINKED_LIST *list, ELEM_TYPE *elem) {
	NODE *aux;
	
	if (!(*list == NULL)) {
		aux = *list;
		*list = aux->next;
		*elem = aux->elem;
		free(aux);
		return TRUE;
	}
		
	return FALSE;
}

void listFree(LINKED_LIST *list) {
	NODE *aux;
	
	while (*list != NULL) {
		aux = *list;
		*list = (*list)->next;
		free(aux);
	} 
}

// ============ HASH FUNCTIONS ===============

#define MAX_M 100
#define MAX_C 200

// clean init all lists in the vector
void initHash(LINKED_LIST hash[MAX_M]) {
    int i;

    for (i = 0; i < MAX_M; i++) {
    	hash[i] = NULL;
    }
}

// insert elements on hash
void putElement(int elem, LINKED_LIST hash[MAX_M], int M) {
	int index = elem % M; // h(x) = x mod M

	listInsertLast(&hash[index], elem);

}

// prints all elements in hash table
void printHashElements(LINKED_LIST hash[MAX_M], int M) {
    int i;
    int elem;

    for (i = 0; i < M; i++) {
    	if (i!=0) printf("\n");

    	if (hash[i] == NULL) {
    		printf("%d -> \\", i);
    	} else {
    		printf("%d -> ", i);
    		while(listRemoveFirst(&hash[i], &elem)) {
    			printf("%d -> ", elem);
    		}
    		printf("\\");
    	}
    }

}

void freeHash(LINKED_LIST hash[MAX_M]) {
	int i;

    for (i = 0; i < MAX_M; i++) {
 		listFree(&hash[i]);   
    }

}

// ===========================================

int main(){
    
    int N; // number of test cases 
    int M; // number of base addresses
    int C; // amount of keys to be stored
    
    // this hash is a vector of lists
    LINKED_LIST hash[MAX_M];
    
    int i, j;
    int aux;
    
    
    scanf("%d", &N);
    
    for (i = 0; i < N; i++) {
        initHash(hash);    
        scanf("%d %d", &M, &C);
        
        for (j = 0; j < C; j++) {
            // reads the number to insert on hash
            scanf("%d", &aux);
            putElement(aux, hash, M);
        }
        
        printHashElements(hash, M);

        printf("\n");
        if (i!=N-1) printf("\n");
        
        freeHash(hash);
    }
    

    return 0;
}