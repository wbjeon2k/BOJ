
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

int seq[1010];
int LIS[1010];
int LDS[1010];
int N;

int calclis(int i) {
    int& ret = LIS[i];
    if (ret != -1) {
        return ret;
    }

    ret = 1;
    for (int t = i - 1; t >= 1; --t) {
        if (seq[i] > seq[t]) {
            ret = max(ret, 1 + calclis(t));
        }
    }

    return ret;
}
int calclds(int i) {
    int& ret = LDS[i];
    if (ret != -1) {
        return ret;
    }

    ret = 1;
    for (int t = i + 1; t <= N; ++t) {
        if (seq[i] > seq[t]) {
            ret = max(ret, 1 + calclds(t));
        }
    }

    return ret;
}

int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &seq[i]);
    }

    fill(LIS, LIS + 1001, -1);
    fill(LDS, LDS + 1001, -1);

    for (int i = 1; i <= N; ++i) {
        calclis(i);
        calclds(N - i + 1);
    }

    int maxi = -1;
    for (int i = 1; i <= N; ++i) {
        maxi = max(maxi, LIS[i] + LDS[i] - 1);
    }


    printf("%d", maxi);

    return 0;
}

