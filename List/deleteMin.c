#include<stdio.h>
#include <stdlib.h>
#define ElemType int
#define MAXSIZE 10

typedef struct SqList{
	ElemType data[MAXSIZE];
	int length;
}SqList; 

ElemType deleteMin(SqList *l){//in c you can't use reference as &l like c++;
	ElemType result;
	int position;
	if(l->length == 0){ // in c, as l is a pointer, you must use -> rather than .
		printf("%s","No data");
		exit(1);
	}else{
		result = l->data[0];
		position = 0;
		for(int i = 1; i<l->length;i++){
	 		if(l->data[i] < result){
				result = l->data[i];
				position = i;
			}

		}
		l->data[position] = l->data[l->length - 1];
		l->length--;
		return result;
	}

}
int main(void){
    SqList *l;
    l = malloc(sizeof(SqList)) ; //so,malloc return a point of void type, which in c can be assigned to any type of pointer;while in c++ this is not allowed! 
    // Also, unlick primitive type, you must explicitly  malloc memory for l, or you will get segmentation fault at run time(compiler is fine with that, though)
    l->length = 10;
    for(int i = 0; i<10;i++){
	l->data[i] = i+7;
    }
    ElemType result = deleteMin(l);
     printf("%d\n",result);

}
