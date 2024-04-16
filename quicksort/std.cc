#include "quicksort.hh"

int n;
int *t;

void prepare(int *a, int _n) {
    t = new int[n = _n];
    memcpy(t, a, 4 * n);
    std::sort(t, t + n);  // Sort the array using std::sort
}

int lower_bound(int x) {
    return *std::lower_bound(t, t + n, x);
}
