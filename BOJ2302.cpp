#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

int N, M;

int cache[50];
int cuts[50];

void calc() {
    cache[0] = 1;
    cache[1] = 1;
    cache[2] = 2;
    for (int i = 3; i < 41; ++i) {
        cache[i] = cache[i - 1] + cache[i - 2];
    }
}

int main()
{
    scanf("%d %d", &N, &M);

    cuts[0] = 0;
    cuts[M+1] = N + 1;

    for (int i = 1; i <= M; ++i) {
        scanf("%d", &cuts[i]);
    }

    calc();

    int ans = 1;

    for (int i = 1; i <= M + 1; ++i) {
        ans *= cache[cuts[i] - cuts[i - 1] - 1];
    }

    printf("%d", ans);

    return 0;
}
