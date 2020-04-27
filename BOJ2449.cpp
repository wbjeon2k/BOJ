#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

int cache[202][202];
int input[202];

int N, K;

int dp(int a, int b) {
    int& ret = cache[a][b];
    if (ret != -1) {
        return ret;
    }

    if (a == b) {
        ret = 0;
        return ret;
    }

    ret = 1000000;
    for (int i = a; i < b; ++i) {
        if (input[i+1] == input[a]) {
            ret = min(ret, dp(a, i) + dp(i + 1, b));
        }
        else {
            ret = min(ret, dp(a, i) + dp(i + 1, b)+1);
        }
    }

    return ret;
}

int main() {

    memset(cache, -1, sizeof(cache));

    scanf("%d %d", &N, &K);

    for (int i = 1; i <= N; ++i) {
        scanf("%d", &input[i]);
    }

    printf("%d", dp(1, N));

    return 0;
}


/*

//first trial. time out

int cache[50400][22];
int input[202];
int N, K;
int M = 1000000;

void chk(int p, int q, int color) {
    printf("%d %d %d %d\n", p, q, color, cache[p * 202 + q][color]);
}

int dp(int p, int q, int color) {
    int& ret = cache[p * 202 + q][color];
    if (ret != -1) {
        return ret;
    }

    if (p == q) {
        if (color == input[p]) {
            ret = 0;
        }
        else {
            ret = M;
        }
        return ret;
    }

    ret = M;
    for (int i = p; i < q; ++i) {
        for (int j = 1; j < 21; ++j) {
            ret = min(ret, dp(p, i, color) + dp(i + 1, q, j) + (color == j ? 0 : 1));
        }
    }

    return ret;
}



int main()
{
    memset(cache, -1, sizeof(cache));
    memset(input, 0, sizeof(input));
    scanf("%d %d", &N, &K);

    for (int i = 1; i <= N; ++i) {
        scanf("%d", &input[i]);
    }

    int ans = M;
    for (int i = 1; i < 21; ++i) {
        ans = min(ans, dp(1, N, i));
    }

    printf("%d", ans);

    return 0;
}


*/