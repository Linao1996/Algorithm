#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 10
#define FUNCNUM 7

void printArray(int A[], char *name, int length);

void getArray(int A[], int length, int seed);

void insertSort(int A[], int n);

void shellSort(int A[], int n);

void bubbleSort(int A[], int n);

void quickSort(int A[], int n);

void mergeSort(int A[], int n);

void selectionSort(int A[], int n);

void heapSort(int A[], int n);

void swap(int *i, int *j);

int main(void) {
    int A[LENGTH];

    char *functionName[FUNCNUM] = {
            "insertSort",
            "shellSort",
            "bubbleSort",
            "quickSort",
            "mergeSort",
            "selectionSort",
            "heapSort",
    }; // note the semicolon in the end of array initialization;

    void (*func[FUNCNUM])(int *, int) = {//must the be the same type as function return type;
            insertSort,
            shellSort,
            bubbleSort,
            quickSort,
            mergeSort,
            selectionSort,
            heapSort,
    };

    for (int i = 0; i < FUNCNUM; i++) {
        getArray(A, LENGTH,
                 (i + 1) * (i + 2));//when passing an array to a function, you should eliminate the square bracket;
        (*func[i])(A, LENGTH);
        printArray(A, functionName[i], LENGTH);
    }
}

void getArray(int A[], int n, int seed) {
    srand((unsigned) seed * seed);
    for (int i = 0; i < n; i++) {
        A[i] = rand() % (n + 1);
    }
}

void printArray(int A[], char *name, int length) {
    printf("%s:\t", name);
    for (int i = 0; i < length; i++) {
        printf("%3d", A[i]);
    }
    printf("\n\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertSort(int A[], int n) {
    int i, j, temp;
    for (i = 1; i < n; i++) {
        temp = A[i];
        for (j = i; j > 0 && A[j - 1] > temp; j--) {
            A[j] = A[j - 1];
        }
        A[j] = temp;
    }
}
//shellSort

void shellSort(int A[], int n) {
    int i, step, j, temp;
    for (step = n / 2; step >= 1; step = step / 2) {
        j = 0;
        for (i = step; i < n; i++) { //change all the "-1" to "-step"
            temp = A[i];
            for (j = i; j >= step && A[j - step] > temp;j-=step) {
                A[j] = A[j - step];
            }
            A[j] = temp;
        }
    }
}

//bubbleSort

void bubbleSort(int A[], int n) {
    int flag;
    for (int i = 0; i < n; i++) {
        flag = 1;
        //use itoa() to convert int to char*
        //how ever, in linux you can't use this function, use sprintf instead
        for (int j = n - 1; j > i; j--) {// note the start is always the same!
            if (A[j] < A[j - 1]) {
                swap(&A[j], &A[j - 1]);
                flag = 0;
            }
        }
        if (flag) {
            break;
        }
    }
}
// quickSort  1, 3, 5, 3, 4, 6, 3, 8

void qSort(int A[], int left, int right) {
    if (left <= right) {
        int median = A[left];
        int i = left + 1, j = right;
        while (1) {
            while (A[i] <= median && i <= right) i++;// you can't write as A[j] < median;
            //image this scenario: A[i] and A[j] are both  median, and that i < j, so the program
            //without "=" will result in i and j exchanging forever.
            while (A[j] > median) j--;// j would meet median anyway.``
            if (i > j) break;
            swap(&A[j], &A[i]);
        }
        swap(&A[j], &A[left]);//in the end, j point to the rightest element smaller than median;
        qSort(A, left, j - 1);
        qSort(A, j + 1, right);
    }
}

void quickSort(int A[], int n) {
    qSort(A, 0, n - 1);
}

// mergeSort


int B[LENGTH];

void merge(int A[], int lb, int le, int rb, int re) {
    int i = lb, j = rb;
    int q = 0;
    while (i <= le && j <= re) {
        if (A[i] < A[j]) {
            B[q++] = A[i++];
        } else {
            B[q++] = A[j++];
        }
    }

    while (i <= le) {
        B[q++] = A[i++];
    }

    while (j <= re) {
        B[q++] = A[j++];
    }
    //copy back;
    q = 0;
    while (lb <= re) {
        A[lb++] = B[q++];
    }
}

void mSort(int A[], int left, int right) {
    if (left < right) {
        int half = (left + right) / 2;
        mSort(A, left, half);
        mSort(A, half + 1, right);
        merge(A, left, half, half + 1, right);
    }
}

void mergeSort(int A[], int n) {
    mSort(A, 0, n - 1);
}


//selectionSort

int findMin(int A[], int left, int right) {
    int min = A[left];
    int loc = left;
    for (int i = left + 1; i <= right; i++) {
        if (A[i] < min) {
            min = A[i];
            loc = i;
        }
    }
    return loc;

}

void selectionSort(int A[], int n) {
    int j;
    for (int i = 0; i < n; i++) {
        j = findMin(A, i, n - 1);
        swap(&A[i], &A[j]);
    }
}

// heapSort

void rotateDown(int A[], int start, int last) {
    int child = start * 2 + 1;
    while (child <= last) {
        if (child != last) {
            child = A[child] > A[child + 1] ? child : child + 1;
        }
        if (A[start] > A[child]) {
            break;
        }
        swap(&A[start], &A[child]);
        start = child;
        child = start * 2 + 1;
    }
}

void heapSort(int A[], int n) {
    for (int i = (n - 1) / 2; i >= 0; i--) {
        rotateDown(A, i, n - 1);
    }
    for (int i = 0; i < n; i++) {
        swap(&A[0], &A[n - i - 1]);
        rotateDown(A, 0, n - i - 2);
    }
}


/*

void builtHeap(int A[], int last) { // the last element

//    priontf("%s", "I am here!");
    int child;
    for (int i = (last -1) /2; i >= 0; i--) {
        int j = i;
//        printArray(A, "building", last);
        while (i <= (last - 1) / 2) {
            child = i * 2 + 1;// start from 0, making all things different
            if (child < last ) {
                child = A[child] > A[child + 1] ? child : child + 1;
            }
            if (A[child] > A[i]) {
                swap(&A[i], &A[child]);
            }
            i = child;
        }
        i = j;
    }
}

void deleteTop(int A[], int n) {// n = 3
    int last = n - 1;
    swap(&A[0], &A[last]);
//    builtHeap(A, n - 1);
//    printArray(A, "after deleteTop",LENGTH);
}

void heapSort(int A[], int n) {
//    printf("\t%s", "heapsort");
    //can't be printed somehow, what amazed me most is after insert a print statement in buildheap, this line is printed. How could that be?
    builtHeap(A, n - 1);// big heap
    printf("\n");
    printArray(A, "after build", n);
    for (int i = 0; i < n; i++) {
        deleteTop(A, n - i);
//        printf("i:%d\n",i);
    }
//    printArray(A, "after delete", n);
}

 */
