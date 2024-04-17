
#include "intsearch.hh"

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
    int lo = 0, hi = n - 1;

    while (lo <= hi && x >= t[lo] && x <= t[hi]) {
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
// int interpolation_search(int x) {
//     int lo = 0, hi = n - 1;
//     int padding_value = 0; // Change this to the value you're using for padding

//     while (lo <= hi && t[hi] != padding_value) {
//         // Calculate the position based on the indices, not the values
//         int pos = lo + ((hi - lo) / 2);

//         if (t[pos] == x)
//             return pos;

//         if (t[pos] < x)
//             lo = pos + 1;
//         else
//             hi = pos - 1;
//     }
//     return -1;
// }