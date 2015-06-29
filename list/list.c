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

// =============== FUNCTIONS =================

void listInit(LINKED_LIST *list) {
	*list = NULL;
}

void listInsertFirst(LINKED_LIST *list, ELEM_TYPE elem) {
	NODE *n;
	
	n = malloc(sizeof(NODE));
	n->elem = elem;	
	n->next = *list;
	*list = n;
}

void listInsertLast(LINKED_LIST *list, ELEM_TYPE elem) {
	NODE *n;
	NODE *aux;

	n = malloc(sizeof(NODE));
	n->elem = elem;
	n->next = NULL;

	if(listIsEmpty(list)) {
		*list = n;
	} else {
		aux = *list;	
		while (aux->next != NULL) aux = aux->next;

		// when it arrived in a null pointer
		// points to the new node
		aux->next = n;
	}
}

void listInsertSorted(LINKED_LIST *list, ELEM_TYPE elem) {
	NODE *n;
	NODE *aux;

	n = malloc(sizeof(NODE));
	n->elem = elem;

	if(listIsEmpty(list)) {
		n->next = NULL;
		*list = n;
	} else if (elem < (*list)->elem) {
		n->next = *list;
		*list = n;
	} else {
		aux = *list;
		while (aux->next != NULL && elem > aux->elem && elem > aux->next->elem) 
			aux = aux->next;
		
		// if arrived in the end of list
		if (aux->next == NULL) {
			// insert in last position
			n->next = NULL;
			aux->next = n;
		} else {
			n->next = aux->next;
			aux->next = n;
		}

	}
}

int listRemoveFirst(LINKED_LIST *list, ELEM_TYPE *elem) {
	NODE *aux;
	
	if (!listIsEmpty(list)) {
		aux = *list;
		*list = aux->next;
		*elem = aux->elem;
		free(aux);
		return TRUE;
	}
		
	return FALSE;
}

int listRemoveLast(LINKED_LIST *list, ELEM_TYPE *elem) {
	NODE *aux, *aux2;

	if (!listIsEmpty(list)) {
		aux = *list;

		// if there is only one element
		if (aux->next == NULL) {
			*elem = aux->elem;
			*list = NULL;
			free(aux);
		} else {
			while (aux->next != NULL) {
				aux2 = aux;
				aux = aux->next;				
			}

			// aux arrived in last element
			*elem = aux->elem;
			free(aux);

			// aux2 is the pointer to previous element
			aux2->next = NULL;
		}

		return TRUE;
	}

	return FALSE;
}

int listRemoveElem(LINKED_LIST *list, ELEM_TYPE elem) {
	NODE *aux, *aux2;

	// removes the first element that is equals elem

	if (!listIsEmpty(list)) {
		aux = *list;

		// if is the first element
		if (aux->elem == elem) {
			*list = aux->next;
			free(aux);
			return TRUE;
		} else {
			while (aux->next != NULL && aux->elem != elem) {
				aux2 = aux;
				aux = aux->next;		
			}

			if (aux->elem == elem) {
				// aux2 is the pointer to previous element
				aux2->next = aux->next;
				free(aux);
				return TRUE;
			}
		}
	}

	return FALSE;
}

int listSearchElem(LINKED_LIST *list, ELEM_TYPE elem) {
	NODE *aux;

	aux = *list;
	while (aux != NULL) {
		if (aux->elem == elem) return TRUE;
		aux = aux->next;
	}

	return FALSE;
}

void listSort(LINKED_LIST *list) {
	LINKED_LIST newlist;
	ELEM_TYPE e;
	
	listInit(&newlist);
	while (listRemoveFirst(list, &e)) {
		listInsertSorted(&newlist, e);
	}
	
	*list = newlist;
}

void listShow(LINKED_LIST *list) {
	NODE *aux;

	aux = *list;
	while (aux != NULL) {
		printf("%d ", aux->elem);
		aux = aux->next;
	}
}

void listShowReverse(LINKED_LIST *list) {
	if (*list == NULL) 
		return;
	
	if ((*list)->next == NULL) {
		printf("%d ", (*list)->elem);
		return;
	}

	listShowReverse(&(*list)->next);
	printf("%d ", (*list)->elem);
}

void listReverse(LINKED_LIST *list) {
	NODE *current, *next, *prev;
	
	if(!listIsEmpty(list) && (*list)->next != NULL) {
		current = *list;
		prev = NULL;
		while (current != NULL) {
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		
		*list = prev;
	}
}

void listReverseRecursive(LINKED_LIST *list) {
	NODE *aux;
	NODE *aux2;
	
	aux = *list;
	
	if (aux == NULL || aux->next == NULL)
		return;
	
	aux2 = aux->next;
	listReverseRecursive(&aux2);
	
	aux->next->next = aux;
	aux->next = NULL;
	
	*list = aux2;
	
}

int listLength(LINKED_LIST *list) {
	NODE *aux;
	int counter = 0;

	aux = *list;
	while (aux != NULL) {
		aux = aux->next;
		counter++;
	}

	return counter;
}

int listIsEmpty(LINKED_LIST *list) {
	return *list == NULL;
}

void listFree(LINKED_LIST *list) {
	NODE *aux;
	
	while (*list != NULL) {
		aux = *list;
		*list = (*list)->next;
		free(aux);
	} 
}

// ================= MAIN ===================

int main() {
	LINKED_LIST list;	
	ELEM_TYPE elem;

	listInit(&list);

	listInsertSorted(&list, 3);
	listInsertSorted(&list, 1);
	listInsertSorted(&list, 2);
	listInsertSorted(&list, 2);
	listInsertSorted(&list, 2);
	listInsertSorted(&list, 7);
	listInsertSorted(&list, 5);

	printf("lenght: %d\n", listLength(&list));
	
	listReverseRecursive(&list);
	
	
	listSort(&list);

	listRemoveElem(&list, 2);

//	listShow(&list);

	EXIBE_L(&list);

	

	printf("\n");

	//listShowReverse(&list);

	printf("\nsearch 1: %d\n", listSearchElem(&list, 1));
	printf("search 2: %d\n", listSearchElem(&list, 2));
	printf("search 3: %d\n", listSearchElem(&list, 3));
	printf("search 4: %d\n", listSearchElem(&list, 4));


	listRemoveLast(&list, &elem);
	printf("removed %d ", elem);

	listRemoveLast(&list, &elem);
	printf("removed %d ", elem);

	listRemoveLast(&list, &elem);
	printf("removed %d ", elem);

	listRemoveLast(&list, &elem);
	printf("removed %d ", elem);	

	printf("\nlength %d\n", listLength(&list));

	return 0;
}