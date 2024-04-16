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
        int half = len / 2;
        base += (base[half - (~len & 1)] < x) * half;
        len -= half;
    }
    return *base;
}
*/

/*
int lower_bound(int x) {
    int *base = t, len = n;
    while (len > 1) {
        int half = len / 2;
        if (base[half - 1] < x)
            base += half;
        len -= half;
    }
    return *base;
}
*/

int interpolation_search(int x) {
    int lo = 0, hi = n - 1;

    while (lo <= hi && x >= t[lo] && x <= t[hi]) {
        if (lo == hi) {
            return t[lo] == x ? lo : -1;
        }

        int pos = lo + (((double)(hi - lo) / (t[hi] - t[lo])) * (x - t[lo]));

        int is_equal = (t[pos] == x);
        int is_less = (t[pos] < x);

        lo = lo * (!is_equal && !is_less) + (pos + 1) * is_less;
        hi = hi * (!is_equal && is_less) + (pos - 1) * (!is_less);

        if (is_equal) return pos;
    }
    return -1;
}

/*
// final
int lower_bound(int x) {
    int *base = t, len = n;
    while (len > 1) {
        base += (base[(len - 1) / 2] < x) * (len / 2);
        len = (len + 1) / 2;
    }
    return *base;
}
*/

/*
int lower_bound(int x) {
    int *base = t, len = n - 1;
    while (len != 0) {
        bool odd = len & 1;
        len /= 2;
        base += (base[len] < x) * (len + odd);
    }
    return *base;
}
*/

/*
int lower_bound(int x) {
    int *base = t, len = n;
    while (len > 1) {
        //int half = len / 2;
        //int half1 = (len - 1) / 2;
        //base += (base[half1] < x ? half : 0);
        //len -= half;
        
        int half = (len - 1) >> 1;
        int new_len = (len + 1) >> 1;
        base += (base[half] < x) * (len - new_len); //new_base + new_len = len
        len = new_len;

        //std::cout << len << std::endl;
    }
    return *base;
}
*/
