#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

long long cache[105][10005];

int N, K;

struct Coin {
    int value;
    int cnt;  
};

struct{
    bool operator()(Coin a, Coin b) {
        return a.value < b.value;
    }
}comp;

Coin input[105];

int main()
{
    scanf("%d %d", &N, &K);

    for (int i = 0; i < K; ++i) {
        scanf("%d %d", &input[i+1].value, &input[i+1].cnt);
    }

    sort(input + 1, input + K + 1, comp);
    cache[0][0] = 1;

    for (int i = 1; i <= K; ++i) {
        for (int k = 0; k <= input[i].cnt; ++k) {
            for (int j = 0; j <= N; ++j) {
                if (j + k * input[i].value <= N) {
                    cache[i][j + k * input[i].value] += cache[i - 1][j];
                }
            }
        }
    }

    printf("%lld", cache[K][N]);

    return 0;

}

/*

//csehydrogen's solution. sliding window again

#include <cstdio>
int d[10001];
int main() {
    int t, k;
    scanf("%d%d", &t, &k);
    d[0] = 1;
    for (int i = 0; i < k; ++i) {
        int p, n;
        scanf("%d%d", &p, &n);
        for (int j = t; j >= 0; --j) {
            for (int k = 1; k <= n && j - p * k >= 0; ++k) {
                d[j] += d[j - p * k];
            }
        }
    }
    printf("%d", d[t]);
    return 0;
}
*/
