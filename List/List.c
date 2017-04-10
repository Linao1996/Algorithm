#include <stdio.h>
#include <stdlib.h>
#define  SIZE 20 
typedef struct Node *List;
typedef struct Node *Position;
typedef int elementType; // you can change the type, so the element type in your list changes, a simulation of generic.
struct Node{
	elementType element;
	Position next;
};


List makeEmpty(List l){
	l->next = NULL;	
}

int isEmpty(List l){
	if(l->next==NULL){
		return 1; // note that in c, there is no boolean type.
	}else{
		return 0; }
}

int isLast(Position p, List l){
	if(p->next == NULL){
		return 1;
	}else{
		return 0;
	}

}

Position find(elementType i,List l ){
	Position p = l->next;
	while(p != NULL && p->element != i){
		p = p->next;
	}
	return p;
}

Position findPrevious(elementType i, List l){
/*	Position  p = l->next;
	if(p->element){
		return l;

} */
	//too tricky? instead, you can just do this
	Position p = l; 
	while(p->next !=NULL && p->next->element != i){
		p = p->next;
	}
	return p;//if there is no such element, p returns the last element.
}

void delete(elementType i, List l){
	Position p = findPrevious(i,l);
	if(p->next == NULL){// istread of p == NULL!! Note that p won't be NULL whatsoever.
		printf("element not found/n");
		exit(1);
	}
	Position toBeDeleted = p->next;
	p->next = toBeDeleted->next;
	free(toBeDeleted);

}

void insert(elementType i, List l, Position p){
	Position newNode = malloc(sizeof(struct Node));
	if(newNode ==NULL){
		printf("Not enough space");
		exit(1);
	}
	newNode->element = i;
	newNode->next = p->next;
	p->next = newNode; 

}

void deleteList(List l){
	Position p = l ->next;
	Position tem ;
	free(l);
	while(p != NULL){
		tem = p->next;
		free(p);
		p = tem;
	}
}


 // int main(void){
	// List l = malloc(sizeof(struct Node));
	// for(int i = 0;i<SIZE;i++){// initalization list
		// insert(i,l,l);
	// }
	// Position p = l->next;
	// Position inserted= find(5,l);
	// printf("to be deleted: %d\n",inserted->element);
	// insert(500,l,inserted);
	// for(int i = 0;i<SIZE &&p!=NULL;i++ ){
		// printf("%d\n",p->element);
		// p = p->next;

// }

// }
