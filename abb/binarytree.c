/* 

    Binary Search Tree

*/

#include <stdio.h>
#include <stdlib.h>


#define TRUE  1;
#define FALSE 0;


// ============== BST DEF =================


typedef int DATA_TYPE;

typedef struct N {
	DATA_TYPE   data;
	struct N   *left, *right;		
} NODE;

typedef NODE* BINARY_TREE;


// ============ AUX LIST DEF ==============

typedef BINARY_TREE ELEM_TYPE;

typedef struct LN {
	ELEM_TYPE   elem;
	struct LN   *next;		
} LNODE;

typedef LNODE* LINKED_LIST;


// ============ AUX LIST FUNC =============


void listInit(LINKED_LIST *list) {
	*list = NULL;
}

void listInsertLast(LINKED_LIST *list, ELEM_TYPE elem) {
	LNODE *n;
	LNODE *aux;

	n = malloc(sizeof(LNODE));
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

int listRemoveFirst(LINKED_LIST *list, ELEM_TYPE *elem) {
	LNODE *aux;
	
	if (!listIsEmpty(list)) {
		aux = *list;
		*list = aux->next;
		*elem = aux->elem;
		free(aux);
		return TRUE;
	}
		
	return FALSE;
}

int listIsEmpty(LINKED_LIST *list) {
	return *list == NULL;
}

void listFree(LINKED_LIST *list) {
	LNODE *aux;
	
	while (*list != NULL) {
		aux = *list;
		*list = (*list)->next;
		free(aux);
	} 
}

// ============ BST FUNCTIONS =============

void treeInit(BINARY_TREE *tree) {
	*tree = NULL;
}


void treeInOrder(BINARY_TREE tree) {
    if (tree != NULL) {
        treeInOrder(tree->left);
        printf("%d ", tree->data);
        treeInOrder(tree->right);
    }
}

void treePreOrder(BINARY_TREE tree) {
    if (tree != NULL) {
        printf("%d ", tree->data);
        treeInOrder(tree->left);
        treeInOrder(tree->right);
    }
}

void treePostOrder(BINARY_TREE tree) {
    if (tree != NULL) {
        treeInOrder(tree->left);
        treeInOrder(tree->right);
        printf("%d ", tree->data);
    }
}


int treeInsert(BINARY_TREE *tree, DATA_TYPE data) {
    
    NODE *node;
    
    if(*tree == NULL) {
        node = malloc(sizeof(NODE));
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        
        *tree = node;
        
        return TRUE;
    } 
    
    if (data < (*tree)->data) {
        return treeInsert(&(*tree)->left, data);
    }
    
    if (data > (*tree)->data) {
        return treeInsert(&(*tree)->right, data);
    }
    
    return FALSE;
}

int treeRemove(BINARY_TREE *tree, DATA_TYPE data) {
    
    NODE *aux;
    
    if ((*tree) == NULL) {
        return FALSE;
    }
    
    if (data < (*tree)->data) {
        return treeRemove(&(*tree)->left, data);
    }  
    
    if (data > (*tree)->data) {
        return treeRemove(&(*tree)->right, data);
    } 
    
    // if the program arrives here, than 'data' was found
    if ((*tree)->left != NULL && (*tree)->right != NULL) {
        
        // gets the node with minimum value from right
        aux = (*tree)->right;
        while (aux->left != NULL) {
            aux = aux->left;
        }
        
        // put the node found in place of removed node
        (*tree)->data = aux->data;
        return treeRemove(&(*tree)->right, aux->data);
        
    } else {
        // if there is one or zero children
        // removes node and points the father node to the subtree
        
        aux = *tree; 
        if ((*tree)->left == NULL) {
            *tree = (*tree)->right;
        } else if ((*tree)->right == NULL) {
            *tree = (*tree)->left;
        } 
            
        free(aux);
        
        return TRUE;
    }
    
}

int treeSearch(BINARY_TREE tree, DATA_TYPE data) {
    
    if (tree == NULL) {
        return FALSE;
    }
    
    if (data == tree->data) {
        return TRUE;
    }
    
    if (data < tree->data) {
        return treeSearch(tree->left, data);
    }
    
    if (data > tree->data) {
        return treeSearch(tree->right, data);
    }
    
}

void treeFree(BINARY_TREE *tree) {
    if ((*tree) != NULL) {
        treeFree(&(*tree)->left);
        treeFree(&(*tree)->right);
        free((*tree));
    }
}

void treeBreadthFirstSearch(BINARY_TREE *tree) {
    
    LINKED_LIST queue;
    BINARY_TREE aux;
    
    listInit(&queue);
    
    listInsertLast(&queue, *tree);
    
    while(!listIsEmpty(&queue)) {
        listRemoveFirst(&queue, &aux);
        printf("%d ", aux->data);
        
        if (aux->left != NULL)
            listInsertLast(&queue, aux->left);
        
        if (aux->right != NULL)
            listInsertLast(&queue, aux->right);
    }
    
    listFree(&queue);
}


// ========================================



int main(){
    BINARY_TREE tree;
    
    treeInit(&tree);
    
    treeInsert(&tree, 10);
    treeInsert(&tree, 5);
    treeInsert(&tree, 15);
    treeInsert(&tree, 4);
    treeInsert(&tree, 7);
    treeInsert(&tree, 11);
    treeInsert(&tree, 17);
    
    
    treeRemove(&tree, 5);

    treeBreadthFirstSearch(&tree);
    
    printf("\n--------\n");
    
    treeInOrder(tree);
    
    printf("\n--------\n");
    
    treePreOrder(tree);
    
    printf("\n--------\n");
    
    treePostOrder(tree);
    
    printf("\n--------\n");
    
    printf("search 5: %d\n", treeSearch(tree, 5));
    printf("search 15: %d\n", treeSearch(tree, 15));
    printf("search 10: %d\n", treeSearch(tree, 10));
    printf("search 2: %d\n", treeSearch(tree, 2));
    printf("search 20: %d\n", treeSearch(tree, 20));
    
    printf("\n--------\n");
    
    
    treeFree(&tree);    
    
    return 0;
}