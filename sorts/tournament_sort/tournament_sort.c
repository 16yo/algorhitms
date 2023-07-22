#ifndef TOURNAMENT_SORT_H
#define TOURNAMENT_SORT_H

#include <inttypes.h>
#include <stdlib.h>

#ifndef templ_type
#define templ_type int64_t
#endif

#ifndef max_value
#define max_value INT64_MAX
#endif

#define at(begin, i) (*(begin + i))

templ_type min(templ_type a, templ_type b) {
    return (a < b ? a : b);
}

typedef uint64_t size_t;

// begin - pointer to the first element of the memory line
// end - pointer to next from the last element of the memory line
// <-------line-------->
// [0x1 0x2 0x3 0x3 0x4, ...]
//  ^                     ^
// begin                 end
typedef struct line {
    templ_type* begin;
    templ_type* end;
} line;

// Play tournament with given participants
void build_tournament_brackets(line tb, size_t n) {
    if (n < 2) {
        return;
    }
    templ_type* begin = tb.begin;

    // 'm' is beginning of playing tournament level, 'sz' - number of participants on the level
    size_t m = (2 * n - 1) - (n) - (n / 2), sz = n / 2;
    while (0 < m) {
        for (size_t i = m; i < m + sz; ++i) {
            at(begin, i) = min(at(begin, 2 * i + 1), at(begin, 2 * i + 2));
        }
        sz /= 2;
        m -= sz;
    }
    at(begin, 0) = min(at(begin, 1), at(begin, 2));
}

// Rebuild tournament brackets without winner element (root)
void rebuild_tournament_brackets(line tb, size_t n, size_t i) {
    templ_type* begin = tb.begin;
    templ_type t = at(begin, i);
    at(begin, i) = max_value;

    // If there is lower layer then go
    if (i < n - 1) {
        if (at(begin, 2 * i + 1) == t) {
            rebuild_tournament_brackets(tb, n, 2 * i + 1);
        } else if (at(begin, 2 * i + 2) == t) {
            rebuild_tournament_brackets(tb, n, 2 * i + 2);            
        }
        at(begin, i) = min(at(begin, 2 * i + 1), at(begin, 2 * i + 2));
    }
}

// Sorts array with length that is a degree of 2 (2^k)
void trivial_tournament_sort(line l) {
    templ_type* begin = l.begin;
    templ_type* end = l.end;
    size_t n = end - begin, k = 2 * n - 1;

    // 1. Build tournament bracket
    templ_type* tb = (templ_type*)malloc(k * sizeof(templ_type));
    for (size_t i = 0; i < n; ++i) {
        tb[i + k - n] = at(begin, i);
    }

    build_tournament_brackets((line){ .begin = tb, .end = tb + k }, n);

    // 2. Sort winners

    for (size_t i = 0; i < n; ++i) {
        // Choose winner
        at(begin, i) = tb[0];
        // Rebuild tournament brackets without chosen element
        rebuild_tournament_brackets((line){ .begin = tb, .end = tb + k }, n, 0);
    }
    free(tb);
}

// Copys line's content
line copy_line(line l) {
    line r;
    size_t n = l.end - l.begin;
    r.begin = (templ_type*)malloc(n * sizeof(templ_type));
    for (size_t i = 0; i < n; ++i) {
        at(r.begin, i) = at(l.begin, i);
    }
    r.end = r.begin + n;
    return r;
}

// Sorts arrays in general case
void tournament_sort(line l) {
    size_t n = l.end - l.begin, k = 1;
    // k least numer that not less than n and is some degree of 2
    while (k < n) {
        k <<= 1;
    }

    templ_type* arr = (templ_type*)malloc(k * sizeof(templ_type));
    for (size_t i = 0; i < n; ++i) {
        arr[i] = at(l.begin, i);
    }
    for (size_t i = n; i < k; ++i) {
        arr[i] = max_value;
    }

    trivial_tournament_sort((line){ .begin = arr, .end = arr + k});

    for (size_t i = 0; i < n; ++i) {
        at(l.begin, i) = arr[i];
    }

    free(arr);

}

#endif