#include "intsearch.hh"

int n;
int *t;

void prepare(int *a, int _n) {
    t = new int[n = _n];
    memcpy(t, a, 4 * n);
}

/*
int lower_bound(int x) {
    int *base = t, len = n;
    while (len > 1) {
        int half = len / 2;
        __builtin_prefetch(&base[(len - half) / 2]);
        __builtin_prefetch(&base[half + (len - half) / 2]);
        base = (base[half] < x ? &base[half] : base);
        len -= half;
    }
    return *(base + (*base < x));
}
*/

/*
int lower_bound(int x) {
    int *base = t, len = n;
    while (len > 1) {
        __builtin_prefetch(&base[len / 4]);
        __builtin_prefetch(&base[3 * len / 4]);
        int half = len / 2;
        base += (base[half - 1] < x) * half;
        len -= half;
    }
    return *base;
}
*/

int interpolation_search(int x) {
    int lo = 0, hi = n - 1;

    while (lo <= hi && x >= t[lo] && x <= t[hi]) {
        __builtin_prefetch(t + lo * 64);
        __builtin_prefetch(t + hi * 64);
        if (lo == hi) {
            return t[lo] == x ? lo : -1;
        }

        int pos = lo + (((double)(hi - lo) / (t[hi] - t[lo])) * (x - t[lo]));

        // __builtin_prefetch(&t[pos / 2]);
        // __builtin_prefetch(&t[pos + (hi - pos) / 2]);

        int is_equal = (t[pos] == x);
        int is_less = (t[pos] < x);

        lo = lo * (!is_equal && !is_less) + (pos + 1) * is_less;
        hi = hi * (!is_equal && is_less) + (pos - 1) * (!is_less);

        if (is_equal) return pos;
    }
    return -1;
}
