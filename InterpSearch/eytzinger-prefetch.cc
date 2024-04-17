#include "insearch.hh"

int n;
int *_a;
int *t;

const int B = 16; // = 64 / 4 = cache_line_size / sizeof(int)

void eytzinger(int k = 1) {
    static int i = 0;
    if (k <= n) {
        eytzinger(2 * k);
        t[k] = _a[i++];
        eytzinger(2 * k + 1);
    }
}

void prepare(int *a, int _n) {
    n = _n;
    _a = a;
    t = (int*) std::aligned_alloc(64, 4 * (n + 1));
    eytzinger();
}

int interpolation_search(int x) {
    int lo = 1, hi = n;

    while (lo <= hi && x >= t[lo] && x <= t[hi]) {
        __builtin_prefetch(t + lo * B);
        __builtin_prefetch(t + hi * B);

        if (lo == hi) {
            return t[lo] == x ? lo : -1;
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
