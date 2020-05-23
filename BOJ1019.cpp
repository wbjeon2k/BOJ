#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N;
int num[10] = {0,0,0,0,0,0,0,0,0,0};

int main()
{
    scanf("%lld", &N);
    int idx = 1;
    int prev = 0;
    int next = N;
    while (N != 0) {
        int t = N % 10;
        next = N/ 10;

        for (int i = 0; i < t; ++i) {
            num[i] += (next + 1) * idx;
        }
        num[t] += next * idx + prev + 1;

        for (int i = t + 1; i < 10; ++i) {
            num[i] += next*idx;
        }

        num[0] -= idx;

        prev += t * idx;
        idx *= 10;
        N = next;
    }
    for (int i = 0; i < 10; ++i) {
        printf("%d ", num[i]);
    }
    return 0;
}

/*
//ntopia's solution
#include <cstdio>
using namespace std;

void proc() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < 10; ++i) {
        long long res = 0;
        for (int j = 1; j <= n; j *= 10) {
            long long v = n / 10 / j - !i;
            if (v >= 0) {
                res += v * j + (n / j % 10 > i ? j : n / j % 10 == i ? n % j + 1 : 0);
            }
        }
        printf("%lld ", res);
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    proc();
    return 0;
}
*/