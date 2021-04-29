#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER 100

int swaps = 0;
int comparisons = 0;

typedef struct Game{
    char title[MAX_BUFFER];
    char platform[MAX_BUFFER];
    int score;
    int release_year;
}Game;

void swap(Game **a, int b, int c);
int partitionByScore(Game **a, int beg, int end); //Functions to sort by Score...
void quicksortByScore(Game **a, int beg, int end);
void insertionByScore(Game **a, int beg, int end);
int partitionByTitle(Game **a, int beg, int end); //Function to sub-sort by Title...
void quicksortByTitle(Game **a, int beg, int end);
void insertionByTitle(Game **a, int beg, int end);
bool checkIfSorted(Game **a, int size);
void resetData();
void printData(Game **a, int size);
int nextField(FILE *csv, char *buffer, int max_len);
void fillUpArray(FILE *csv, Game **a, int *capacity);
void printArray(Game **a, int capacity);
void printTop10(Game **a, int capacity);

int main(){
    int capacity = 0; int MAX_CAPACITY = 20000;
    Game *a[MAX_CAPACITY];
    for (int i = 0; i < MAX_CAPACITY; i++) {
    	a[i] = (Game*)malloc(sizeof(Game)); //Allocate space for each game
    }

    //Try to open input file. If there is a problem, report failure and quit 
    FILE *pFile;
    pFile = fopen("ign.csv", "r");
    if (pFile == NULL){
        perror ("Error opening file");
    }
    else{
        printf("File opened successfully!\n");
    }
    fillUpArray(pFile, a, &capacity);


    //Sort by Score
    quicksortByScore(a, 0, capacity - 1);
    
    //Sub-sort by Title
    int beg, end = 0;
    for(int i = 1; i <= 10; i++){
        
        beg = end;
        while (a[end]->score < i + 1 && end < capacity){ //Finds parameters of sort
            end++;
        }

        quicksortByTitle(a, beg, end - 1);
    }
    
    printTop10(a, capacity);
    return 0;
}

void swap(Game **a, int b, int c){
    Game *temp = a[b];
    a[b] = a[c];
    a[c] = temp;
}

int partitionByScore(Game **a, int beg, int end){

    comparisons++;
    if (beg == end){ //If the array only has one element return that element
        return beg;
    }

    int pivot = a[end]->score;
    int low = beg - 1;
    int high = end;

    for(;;){
        do{ //Searches for value less than the pivot
            low++;
            comparisons++;
        }while(a[low]->score < pivot && low < high);

        do{ //Searches for value greater than the pivot
            high--;
            comparisons++;
        }while(a[high]->score > pivot && low < high);

        comparisons++;
        if(low >= high){ //If all elements have been checked swap pivot
            comparisons++;
            if (a[low]->score != pivot){ //Doesn't swap with pivot if values are equal
                swap(a, low, end);
                swaps++;
            }
            return low;
        }

        comparisons++;
        if (a[low]->score != a[high]->score){ //Swaps if the value left of the pivot is greater
            swap(a, low, high);
            swaps++;
        }
    }
}

int partitionByTitle(Game **a, int beg, int end){

    comparisons++;
    if (beg == end){
        return beg;
    }

    char pivot[MAX_BUFFER];
    strcpy(pivot, a[end]->title);

    int low = beg - 1;
    int high = end;

    for(;;){
        do{
            low++;
            comparisons++;
        }while(strcmp(a[low]->title, pivot) < 0 && low < high);

        do{
            high--;
            comparisons++;
        }while(strcmp(a[high]->title, pivot) > 0 && low < high);

        comparisons++;
        if(low >= high){
            comparisons++;
            if (strcmp(a[low]->title, pivot) != 0){
                swap(a, low, end);
                swaps++;
            }
            return low;
        }

        comparisons++;
        if (strcmp(a[low]->title, a[high]->title) != 0){
            swap(a, low, high);
            swaps++;
        }
    }
}

void quicksortByScore(Game **a, int beg, int end){
    int partitionIndex;

    if(end - beg > 9){ //Sort by quicksort if array has more than 9 elements
        partitionIndex = partitionByScore(a, beg, end);
        quicksortByScore(a, beg, partitionIndex - 1); //Sorts everything left of the pivot
        quicksortByScore(a, partitionIndex + 1, end); //Sorts everything right of the pivot
    }

    else{ //Otherwise sort by insertion
        insertionByScore(a, beg, end);
    }
}

void quicksortByTitle(Game **a, int beg, int end){
    int partitionIndex;

    if(end - beg > 9){
        partitionIndex = partitionByTitle(a, beg, end);
        quicksortByTitle(a, beg, partitionIndex - 1);
        quicksortByTitle(a, partitionIndex + 1, end);
    }

    else{
        insertionByTitle(a, beg, end);
    }
}

void insertionByScore(Game **a, int beg, int end){

    for (int pass = beg; pass < end; pass++){
        for (int i = pass + 1; i > 0; i--){

            comparisons++;
            if (a[i-1]->score > a[i]->score){
                swap(a, i, i-1);
                swaps++;
            }
            else{
                break;
            }
            
            comparisons++;
        }

        comparisons++;
    }
}

void insertionByTitle(Game **a, int beg, int end){

    for (int pass = beg; pass < end; pass++){
        for (int i = pass + 1; i > 0; i--){

            comparisons++;
            if (strcmp(a[i-1]->title, a[i]->title) > 0){
                swap(a, i, i-1);
                swaps++;
            }
            else{
                break;
            }
            
            comparisons++;
        }

        comparisons++;
    }
}

bool checkIfSorted(Game **a, int size){
    for(int i = 0; i < size - 1; i++){
        if (a[i]->score > a[i + 1]->score){
            return false; //returns false if the current is greater than the next element
        }
    }
    return true;
}

void resetData(){
    swaps = 0;
    comparisons = 0;
}

void printData(Game **a, int size){
    printf("\nSORTED: ");
    if (checkIfSorted(a, size)){
        printf("Y\n");
    }
    else{
        printf("N\n");
    }
    printf("SWAPS: %d\n", swaps);
    printf("COMPS: %d\n", comparisons);
    resetData();
}

int nextField(FILE *csv, char *buffer, int max_len){
    char c;
    bool quoted = false;

    for(int i = 0; i < max_len; i++){
        //Read in next character from line
        c = getc(csv);

        if (c == '"'){ //If we encounter quotation makrs then flip our state and read in the next character
            quoted = !quoted;
            i--;
        }

        else if (c == ',' && !quoted){ //End Record if we reach comma
            buffer[i] = '\0';
            return 0;
        }

        else if (c == '\n' || c == EOF){ //End Record if we reach new line or truncates fields that would overflow the buffer
            buffer[i] = '\0';
            return 1;
        }

        else{
            buffer[i] = c;
        }
    }
}

void fillUpArray(FILE *csv, Game **a, int *capacity){
    char buf[MAX_BUFFER];

    //Remove Row 1
    char c;
    do{
        c = getc(csv);
    }while(c != '\n');

    //Reads in Records 
    int i = 0;
    while(!feof(csv)){

        //Initalise Index
        nextField(csv, buf, MAX_BUFFER); //Load title into buf as string
        strcpy(a[i]->title, buf); //Copy String
        nextField(csv, buf, MAX_BUFFER); //Repeat...
        strcpy(a[i]->platform, buf);
	    nextField(csv, buf, MAX_BUFFER);
        a[i]->score = atoi(buf); //Parse to Integer
        nextField(csv, buf, MAX_BUFFER);
        a[i]->release_year = atoi(buf);

        i++;
    }

    *capacity = i;
}

void printArray(Game **a, int capacity){
    printf("%50s", "Title");
    printf("%25s", "Platform");
    printf("%10s", "Score");
    printf("%16s", "Release Year\n");

    for (int i = 0; i < capacity; i++){
        printf("%50s", a[i]->title);
        printf("%25s", a[i]->platform);
        printf("%10d", a[i]->score);
        printf("%15d\n", a[i]->release_year);
    }
}

void printTop10(Game **a, int capacity){
    printf("%50s", "Title");
    printf("%25s", "Platform");
    printf("%10s", "Score");
    printf("%16s", "Release Year\n");

    int i = capacity; int count = 0; 
    while(count != 10){
        i--;

        if(strcmp(a[i]->title, a[i + 1]->title) == 0){
            continue;
        }
        printf("%50s", a[i]->title);
        printf("%25s", a[i]->platform);
        printf("%10d", a[i]->score);
        printf("%15d\n", a[i]->release_year);

        count++;
    }
}