#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

int x, y, z;

int cache[25][25][25];

int w(int a,int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 1;
    }

    if (a > 20 || b > 20 || c > 20) {
        return w(20, 20, 20);
    }

    int& ret = cache[a][b][c];
    if (ret != -1) {
        return ret;
    }

    if (a < b && b < c) {
        ret = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
        return ret;
    }
    else {
        ret = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
        return ret;
    }
}

int main()
{
    while (1) {
        scanf("%d %d %d", &x, &y, &z);
        if (x == -1 && y == -1 && z == -1) {
            break;
        }

        memset(cache, -1, sizeof(cache));

        int ans = w(x, y, z);
        printf("w(%d, %d, %d) = %d\n", x, y, z, ans);
    }

    return 0;
}
