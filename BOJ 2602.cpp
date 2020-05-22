#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

string s1, s2, s3;
char input[105][2];
int cache[30][105][2];

int M = 100;

int calc(int x, int y, int z) {
    //printf("%d %d %d\n", x, y, z);
    int& ret = cache[x][y][z];
    if (ret != -1) {
        return ret;
    }
    if (x > y) {
        return 0;
    }
    if (x == 0) {
        return 1;
    }

    ret = 0;
    int zprime = (z == 1) ? 0 : 1;
    for (int i = y; i >= x;--i) {
        if (s1[x] == input[i][z]) {
            ret += calc(x - 1, i - 1, zprime);
        }
    }

    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> s1 >> s2 >> s3;

    s1 = "0" + s1;
    for (int i = 0; i < s2.size(); ++i) {
        input[i + 1][0] = s2[i];
        input[i + 1][1] = s3[i];
    }

    memset(cache, -1, sizeof(cache));

    int x, y;
    x = s1.size() - 1;
    y = s2.size();

    int ans = calc(x, y, 1) + calc(x, y, 0);

    printf("%d", ans);

    return 0;
}

/*
//cubelover's solution.
#include <cstdio>

char a[101], b[101], c[101];
int d[101][2];

int main()
{
    int i, j, n;
    scanf("%s%s%s", a, b, c);
    for (n = 0; a[n]; n++);
    d[0][0] = d[0][1] = 1;
    for (i = 0; b[i]; i++) for (j = n - 1; j >= 0;j--)
    {
        if (b[i] == a[j]) d[j + 1][1] += d[j][0];
        if (c[i] == a[j]) d[j + 1][0] += d[j][1];
    }
    printf("%d", d[n][0] + d[n][1]);
}

*/