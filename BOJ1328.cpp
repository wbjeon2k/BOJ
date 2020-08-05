//BOJ1328

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 1000000007

ll binomial[101][101];
ll dp[101][101];

int N, L, R;

void binomialproc() {
    memset(binomial, 0, sizeof(binomial));

    binomial[0][0] = 1;
    binomial[1][0] = 1;
    binomial[1][1] = 1;

    for (int i = 0; i <= 100; ++i) {
        binomial[i][0] = 1;
        binomial[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            binomial[i][j] = (binomial[i - 1][j - 1] + binomial[i - 1][j]) % MOD;
        }
    }
}

void calc() {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    dp[1][1] = 1;

    for (int i = 2; i <= N; ++i) {
        for (int j = 1; j <= i; ++j) {
            dp[i][j] = dp[i - 1][j - 1] + ((ll)i - 1) * dp[i - 1][j];
            dp[i][j] %= MOD;
        }
    }

}

int main() {
    cin >> N >> L >> R;
    binomialproc();
    calc();

    ll ans = 0;
    for (int i = L - 1; i < N - R + 1; ++i) {
        ans += (((dp[i][L - 1] * dp[N - i - 1][R - 1]) % MOD) * binomial[N - 1][i]);
        ans %= MOD;
    }

    printf("%lld\n", ans);

    return 0;
}

/*
1st trial. memory complexity O(N^3)
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define ll long long

ll cache[101][101][101];
int N, L, R;

ll dp(ll N, ll L, ll R) {
    //printf("n%d i%d l%d r%d\n", N, L, R);

    if (N <= 0 || L <= 0 || R <= 0) return 0;

    ll& ret = cache[N][L][R];

    if (L + R > N + 1) return 0;

    if (ret != -1) return ret;

    ret = 0;

    ret += dp(N - 1, L - 1, R);
    ret += dp(N - 1, L, R - 1);
    ret += ((N - 2) * dp(N - 1, L, R) % MOD);
    ret %= MOD;

    return ret;
}

int main() {
    cin >> N >> L >> R;

    memset(cache, -1, sizeof(cache));

    cache[1][1][1] = 1;
    cache[2][2][1] = 1;
    cache[2][1][2] = 1;

    printf("%lld\n", dp(N, L, R));

    return 0;
}

*/




/*
//kcm1700's solution.
#include <cstdio>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

const int mod = 1000000007;
long long binom[102][102];
long long dp[102][102]; // total, increasing count

int main()
{
  int n, l, r;
  scanf("%d%d%d", &n, &l, &r);
  for (int i = 0; i <= n; i++) {
    binom[i][0] = binom[i][i] = 1;
    for (int j = 1; j < i; j++) {
      binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod;
    }
  }
  dp[0][0] = 1;
  dp[1][1] = 1;
  //for (int i = 2; i <= n; i++) {
  //  dp[i][1] = dp[i-1][1] * (i - 1);
  //  for (int j = 2; j <= i; j++) {
  //    long long val = 0;
  //    for (int k = 0; k < i; k++) {
  //      val += dp[k][j - 1] * binom[i - 1][k] % mod * dp[i - k][1];
  //      val %= mod;
  //    }
  //    dp[i][j] = val;
  //  }
  //}
  for (int i = 2; i <= n; i++) {
    for (int j = 1; j <= i; j++) {
      dp[i][j] = (dp[i - 1][j - 1] + (i - 1) * dp[i - 1][j]) % mod;
    }
  }
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += dp[i][l - 1] * dp[n - i - 1][r - 1] % mod * binom[n-1][i];
    ans %= mod;
  }
  printf("%lld\n", ans);
  return 0;
}
*/