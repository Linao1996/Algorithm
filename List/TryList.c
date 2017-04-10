#include <stdio.h>
#include <stdlib.h>
#include "List.c"
int main(void){
List l = malloc(sizeof(struct Node));
          for(int i = 0;i<SIZE;i++){// initalization list
                   insert(i,l,l);
           }
           Position p = l->next;
           Position inserted= find(5,l);
      printf("to be deleted: %d\n",inserted->element);
           insert(500,l,inserted);
             for(int i = 0;i<SIZE &&p!=NULL;i++ ){
	                printf("%d\n",p->element);
	                p = p->next;
	  
	 
      }

 }
