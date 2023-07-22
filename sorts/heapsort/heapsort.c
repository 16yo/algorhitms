#ifndef HEAPSORT_H

#include <inttypes.h>
#include <stdlib.h>

#ifndef templ_type
#define templ_type int64_t
#endif

typedef size_t uint64_t;

#define at(i) *(begin + i)

void swap(templ_type* a, templ_type* b) {
    templ_type t = *a;
    *a = *b;
    *b = t;
}

void heapify(templ_type* begin, templ_type* end, templ_type* root) {
    templ_type* left = begin + (root - begin) * 2  + 1;
    templ_type* right = left + 1;

    templ_type* largest = root;

    if (end - left > 0 && *left > *largest) {
        largest = left;
    }
    if (end - right > 0 && *right > *largest) {
        largest = right;
    }

    if (largest != root) {
        swap(root, largest);
        heapify(begin, end, largest);
    }
}

void heap_sort(templ_type* begin, templ_type* end) {
    size_t n = end - begin;
    for (size_t i = 0; i < n/2; ++i) {
        heapify(begin, end, begin + (n/2 - 1 - i));
    }
    for (size_t i = 0; i < n; ++i) {
        swap(begin, end - i - 1);
        heapify(begin, end - i - 1, begin);
    }
}

#endif