#include <bits/stdc++.h>
#include <chrono>

#ifndef N
#define N (1<<20)
#endif

void prepare(int *a, int n);

int main(int argc, char* argv[]) {
    int n = (argc > 1 ? atoi(argv[1]) : N);
    int m = (argc > 2 ? atoi(argv[2]) : 1<<20);

    int *a = new int[n];
    int *q = new int[m];

    for (int i = 0; i < n; i++)
        a[i] = rand();
    for (int i = 0; i < m; i++)
        q[i] = rand();

    a[0] = RAND_MAX;

    clock_t start = clock();
    prepare(a, n);
    float seconds = float(clock() - start) / CLOCKS_PER_SEC;
    printf("%.2f ns per sort\n", 1e9 * seconds/ m);

    return 0;
}

