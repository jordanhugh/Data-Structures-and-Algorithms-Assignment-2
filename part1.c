#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void swap(int a[], int b, int c);
void randomise(int a[], int size);
int partition(int *a, int beg, int end);
void quicksort(int *a, int beg, int end);
void printArray(int a[], int size);
bool checkIfSorted(int a[], int size);
void resetData();
void printData(int a[], int size);

int swaps = 0;
int comparisons = 0;

int main(){

    /*
    printf("\nRunning profile tests with 10 elements\n\n");
    int SIZE = 10;

    int a[] = {9, 3, 0, 2, 4, 7, 5, 6, 8, 1}; //Unique Random Values
    int b[] = {9, 3, 3, 2, 4, 7, 7, 6, 8, 2}; //Random Values
    int c[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; //Ascending Sorted List
    int d[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; //Descending Sorted List
    int e[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}; //Uniform List
    */

    printf("\nRunning profile tests with 10000 elements\n\n");
    int SIZE = 10000;

    //Unique Random Values
    int a[SIZE];
    for (int i  = 0; i < SIZE; i++){
        a[i] = i;
    }
    randomise(a, SIZE);

    //Random Values
    int b[SIZE];
    for (int i  = 0; i < SIZE; i++){
        b[i] = rand() % 10000;
    }

    //Ascending Sorted List
    int c[SIZE];
    for (int i  = 0; i < SIZE; i++){
        c[i] = i;
    }

    //Descending Sorted List
    int d[SIZE];
    for (int i  = 0; i < SIZE; i++){
        d[i] = SIZE-1 - i;
    }

    //Uniform List
    int e[10000];
    for (int i  = 0; i < 10000; i++){
        e[i] = 3;
    }

    quicksort(a, 0, SIZE - 1);
    printf("TEST: Unique Random Values\n");
    printData(a, SIZE);

    quicksort(b, 0, SIZE - 1);
    printf("TEST: Random Values\n");
    printData(b, SIZE);

    quicksort(c, 0, SIZE - 1);
    printf("TEST: Ascending Sorted List\n");
    printData(c, SIZE);

    quicksort(d, 0, SIZE - 1);
    printf("TEST: Descending Sorted List\n");
    printData(d, SIZE);
    
    quicksort(e, 0, SIZE - 1);
    printf("TEST: Uniform List\n");
    printData(e, SIZE);

    return 0;
}

void swap(int a[], int b, int c){
    int temp = a[b];
    a[b] = a[c];
    a[c] = temp;
}

void randomise(int a[], int size){
    for (int i = size - 1; i > 0; i--) {
		int j = rand() % (i + 1); //Randomly chooses a number between 0 - i

		swap(a, i , j);
	}
}

int partition(int *a, int beg, int end){

    comparisons++;
    if (beg == end){ //If the array only has one element return that element
        return beg;
    }

    int pivot = a[end];
    int low = beg - 1;
    int high = end;

    for(;;){
        do{ //Searches for value less than the pivot
            low++; 
            comparisons++;
        }while(a[low] < pivot && low < high);

        do{ //Searches for value greater than the pivot
            high--;
            comparisons++;
        }while(a[high] > pivot && low < high);

        comparisons++;

        if(low >= high){ //If all elements have been checked swap pivot
            comparisons++;
            if (a[low] != pivot){ //Doesn't swap with pivot if values are equal
                swap(a, low, end);
                swaps++;
            }
            return low;
        }

        
        comparisons++;
        if (a[low] != a[high]){ //Swaps if the value left of the pivot is greater
            swap(a, low, high);
            swaps++;
        }
    }
}

void quicksort(int *a, int beg, int end){

    if(beg < end){
        int partitionIndex = partition(a, beg, end);
        quicksort(a, beg, partitionIndex - 1); //Sorts everything left of the pivot
        quicksort(a, partitionIndex + 1, end); //Sorts everything right of the pivot
    }

}

void printArray(int a[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

bool checkIfSorted(int a[], int size){
    for(int i = 0; i < size - 1; i++){
        if (a[i] > a[i + 1]) 
            return false; //returns false if the current is greater than the next element
    }
    return true;
}

void resetData(){
    swaps = 0;
    comparisons = 0;
}

void printData(int a[], int size){
    printf("SORTED: ");
    if (checkIfSorted(a, size)){
        printf("Y\n");
    }
    else{
        printf("N\n");
    }
    printf("SWAPS: %d\n", swaps);
    printf("COMPS: %d\n\n", comparisons);
    resetData();
}