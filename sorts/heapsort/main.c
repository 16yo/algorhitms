#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define templ_type int
#include "heapsort.c"


int main() {
    srand(time(NULL) + 1000);

    int size = (rand() + 10) % 20;

    int* arr = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; ++i) {
        arr[i] = (rand() + 1) % 20;
        for (int j = 0; j < 10000; ++j) {}
    }

    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    heap_sort(arr, arr + size);

    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }

    return 0;
}