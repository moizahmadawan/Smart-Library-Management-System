#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include "Book.h"
#include "Utils.h"

// ------------------------------------------------------------
// Merge Sort on a vector of Book pointers.
// Time: O(n log n) in all cases. Stable sort.
// mode: 1 = year, 2 = author, 3 = id
// ------------------------------------------------------------
inline bool bookLess(const Book *a, const Book *b, int mode) {
    if (mode == 1) return a->year < b->year;
    if (mode == 2) return toLower(a->author) < toLower(b->author);
    return a->id < b->id;
}

inline void mergeSort(std::vector<Book *> &v, int lo, int hi, int mode) {
    if (lo >= hi) return;
    int mid = (lo + hi) / 2;
    mergeSort(v, lo, mid, mode);
    mergeSort(v, mid + 1, hi, mode);

    std::vector<Book *> tmp;
    int i = lo, j = mid + 1;
    while (i <= mid && j <= hi)
        tmp.push_back(bookLess(v[j], v[i], mode) ? v[j++] : v[i++]);
    while (i <= mid) tmp.push_back(v[i++]);
    while (j <= hi) tmp.push_back(v[j++]);
    for (int k = 0; k < (int)tmp.size(); k++) v[lo + k] = tmp[k];
}

#endif
