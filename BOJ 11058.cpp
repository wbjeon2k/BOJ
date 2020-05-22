#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

#define ll long long

using namespace std;

ll cache[110];

ll dp(ll n) {
    ll& ret = cache[n];
    if (ret != -1) {
        return ret;
    }

    if (n < 7) {
        ret = n;
        return ret;
    }

    ll c1 = dp(n - 1) + 1;
    ll c2 = -1;
    for (ll i = 1; i < n - 3; ++i) {
        c2 = max(c2, dp(i) * (n - i - 1));
    }

    ret = max(c1, c2);

    return ret;
}

int main()
{
    memset(cache, -1, sizeof(cache));
    ll N;
    scanf("%lld", &N);

    printf("%lld", dp(N));

    return 0;
}
