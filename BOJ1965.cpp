#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

int cache[1010];
int input[1010];

int N;

int LIS(int n) {
    int& ret = cache[n];
    if (ret != -1) {
        return ret;
    }

    ret = 1;
    for (int i = n + 1; i <= N; ++i) {
        if (input[i] > input[n]) {
            ret = max(ret, 1 + LIS(i));
        }
    }

    return ret;
}

int main()
{
    scanf("%d", &N);

    memset(cache, -1, sizeof(cache));
    memset(input, 0, sizeof(input));

    for (int i = 1; i <= N; ++i) {
        scanf("%d", &input[i]);
    }

    int ans=-1;
    for (int i = 1; i <= N; ++i) {
        ans = max(ans, LIS(i));
    }

    printf("%d", ans);

    return 0;
}
