#include <ctime>
#include <cstdio>
#include <algorithm>

const int m = 2e6;
const int l1 = 24000; // l1
const int l2 = 442368; // l2
const int l3 = 3588096; // l3

int *a, *q, *t;

void build(int k, int n) {
    static int i = 0;
    if (k <= n) {
        build(2 * k, n);
        t[k] = a[i++];
        build(2 * k + 1, n);
    }
}

int baseline(int x, int n) {
    return *std::lower_bound(a, a + n, x);
}

int branchless(int x, int n) {
    int *base = a, len = n;
    while (len > 1) {
        int half = len / 2;
        base = (base[half] < x ? &base[half] : base);
        len -= half;
    }
    return *(base + (*base < x));
}

int eytzinger(int x, int n) {
    int k = 1;
    while (k <= n) {
        __builtin_prefetch(t + k * 16);
        k = 2 * k + (t[k] < x);
    }
    k >>= __builtin_ffs(~k);
    return t[k];
}

float timeit(int (*lower_bound)(int, int), int n) {
    clock_t start = clock();

    int checksum = 0;

    for (int i = 0; i < m; i++)
        checksum += lower_bound(q[i], n);
    
    float duration = float(clock() - start) / CLOCKS_PER_SEC;

    printf("  checksum: %d\n", checksum);
    printf("  latency: %.2fns\n", 1e9 * duration / m);

    return duration;
}

void run_test(int n) {
    a = new int[n];
    q = new int[m];
    t = new int[n + 1];

    for (int i = 0; i < n; i++)
        a[i] = rand();
    for (int i = 0; i < m; i++)
        q[i] = rand();
    
    a[0] = RAND_MAX; // to avoid dealing with end-of-array iterators 

    std::sort(a, a + n);
    build(1, n);

    printf("std::lower_bound:\n");
    float x = timeit(baseline, n);
    
    printf("branchless:\n");
    printf("  speedup: %.2fx\n", x / timeit(branchless, n));
 
    printf("eytzinger:\n");
    printf("  speedup: %.2fx\n", x / timeit(eytzinger, n));

    delete[] a;
    delete[] q;
    delete[] t;
}

int main() {
    printf("L1 cache:\n");
    run_test(l1);
    printf("\nL2 cache:\n");
    run_test(l2);
    printf("\nL3 cache:\n");
    run_test(l3);

    return 0;
}