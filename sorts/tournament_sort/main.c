#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "tournament_sort.c"

int main() {

    srand(time(NULL));

    const uint64_t size = 7;

    int64_t* arr = (int64_t*)malloc(size * sizeof(int64_t));

    for (int i = 0; i < size; ++i) {
        arr[i] = 1 + (rand() % 9); 
    }

    for (int i = 0; i < size; ++i) {
        printf("%ld ", arr[i]);
    }
    printf("\n");


    tournament_sort((line){.begin = arr, .end = arr + size});

    for (int i = 0; i < size; ++i) {
        printf("%ld ", arr[i]);
    }
    printf("\n");


    return 0;
}