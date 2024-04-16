#include "intsearch.hh"

int n;
int *t;

void prepare(int *a, int _n) {
    t = new int[n = _n];
    memcpy(t, a, 4 * n);
}

int interpolation_search(int x) {
    int lo = 0, hi = n - 1;

    while (lo <= hi && x >= t[lo] && x <= t[hi]) {
        if (lo == hi) {
            if (t[lo] == x) return lo;
            return -1;
        }

        int pos = lo + (((double)(hi - lo) / (t[hi] - t[lo])) * (x - t[lo]));

        if (t[pos] == x)
            return pos;

        if (t[pos] < x)
            lo = pos + 1;
        else
            hi = pos - 1;
    }
    return -1;
}
