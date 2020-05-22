#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

int cache[1010][10];
int M = 10007;

void calc() {
    for (int n = 2; n <= 1000; ++n) {
        cache[n][0] = 1;
        for (int i = 1; i < 10; ++i) {
            cache[n][i] = 0;
            for (int j = 0; j <= i; ++j) {
                cache[n][i] += (cache[n - 1][j]%M);
            }
            cache[n][i] = cache[n][i] % M;
        }
    }
}

void ans(int n) {
    int t = 0;
    for (int i = 0; i < 10; ++i) {
        t += cache[n][i];
    }

    t = t % M;

    printf("%d", t);
}

int main()
{
    int N;
    scanf("%d", &N);

    memset(cache, 0, sizeof(cache));
    for (int i = 0; i < 10; ++i) {
        cache[1][i] = 1;
    }

    calc();
    ans(N);

    return 0;
}
