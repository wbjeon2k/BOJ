//BOJ8895

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll binomial[22][22];
ll dp[22][22];

int N, L, R, T;

void binomialproc() {
    memset(binomial, 0, sizeof(binomial));

    binomial[0][0] = 1;
    binomial[1][0] = 1;
    binomial[1][1] = 1;

    for (int i = 0; i <= 20; ++i) {
        binomial[i][0] = 1;
        binomial[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            binomial[i][j] = (binomial[i - 1][j - 1] + binomial[i - 1][j]);
        }
    }
}

void calc() {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    dp[1][1] = 1;

    for (int i = 2; i <= 20; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = dp[i - 1][j - 1] + ((ll)i - 1) * dp[i - 1][j];
        }
    }

}

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(NULL);

    cin >> T;
    binomialproc();
    calc();

    while (T--) {
        cin >> N >> L >> R;
        ll ans = 0;
        for (int i = L - 1; i < N - R + 1; ++i) {
            ans += (((dp[i][L - 1] * dp[N - i - 1][R - 1])) * binomial[N - 1][i]);
        }

        printf("%lld\n", ans);
    }

    return 0;
}