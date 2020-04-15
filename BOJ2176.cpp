#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>


int cache[305][305];
int input[305][305];

int partialdp(int sx, int sy, int ex, int ey) {
    return cache[ex][ey] + cache[sx - 1][ sy - 1] - cache[ex][ sy - 1] - cache[sx - 1][ey];
}

int dp(int x, int y) {
    int& ret = cache[x][y];

    if (ret != -1) {
        return ret;
    }

    ret = dp(x - 1, y) + dp(x, y - 1) - dp(x - 1, y - 1) + input[x][y];

    return ret;
}


int N, M, K;

int main()
{
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            scanf("%d", &input[i][j]);
        }
    }

    for (int i = 0; i < 305; ++i) {
        for (int j = 0; j < 305; ++j) {
            cache[i][j] = -1;
        }
    }

    for (int i = 0; i < 305; ++i) {
        cache[i][0] = 0;
    }

    for (int i = 0; i < 305; ++i) {
        cache[0][i] = 0;
    }

    for (int i = 0; i < 305; ++i) {
        cache[N+1][i] = 0;
    }

    for (int i = 0; i < 305; ++i) {
        cache[i][M+1] = 0;
    }
    
    cache[1][1] = input[1][1];

    dp(N, M);

    scanf("%d", &K);

    for (int i = 0; i < K; ++i) {
        int a, b, x, y, t;
        scanf("%d %d %d %d", &a, &b, &x, &y);
        t = partialdp(a, b, x, y);
        printf("%d\n", t);
    }

    return 0;
}
