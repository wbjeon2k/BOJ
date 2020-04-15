
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

int N;

long long inputmap[105][105];
long long cache[105][105];

int main()
{
    for (int i = 0; i < 105; ++i) {
        for (int j = 0; j < 105; ++j) {
            inputmap[i][j] = 0;
            cache[i][j] = 0;
        }
    }

    scanf("%d", &N);

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            scanf("%lld", &inputmap[i][j]);
        }
    }

    cache[1][1] = 1;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            long long t = inputmap[i][j];
            long long c = cache[i][j];
            if (cache[i][j] != 0 && inputmap[i][j] !=0) {
                if (i + t <= N) {
                    cache[i + t][j] += c;
                }
                if (j + t <= N) {
                    cache[i][j + t] += c;
                }
            }
        }
    }

    printf("%lld", cache[N][N]);

    return 0;
}
