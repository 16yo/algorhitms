#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <stdlib.h>
#include <inttypes.h>

#ifndef templ_type
#define templ_type int64_t
#endif

#define zero (templ_type)(0)

typedef struct {
    templ_type* arr;
    size_t size;
} array;

templ_type min(templ_type a, templ_type b) {
    return (a < b ? a : b);
}

templ_type max(templ_type a, templ_type b) {
    return (a > b ? a : b);
}

templ_type* merge_sort(array a, array b) {
    array c = (array){ .arr = (templ_type*)malloc((a.size + b.size) * sizeof(templ_type)), .size = (a.size + b.size) };

    c.arr[0] = min(a.arr[0], b.arr[0]);

    templ_type buff[2] = { max(a.arr[0], b.arr[0]), zero };

    size_t i = 1, j = 1;

    for (size_t k = 1; k < c.size; ++k) {
        
    }
    


#endif