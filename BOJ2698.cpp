//BOJ2698

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll cache[111][111][2];

int T, N, K;

ll dp(int n, int k, int last) {
	ll& ret = cache[n][k][last];

	if (ret != -1) return ret;

	if (k >= n) {
		ret = 0;
		return ret;
	}

	ret = 0;

	if (last == 1) {
		ret = (k > 0 ? dp(n - 1, k - 1, 1) : 0) + dp(n - 1, k, 0);
	}
	else {
		ret = dp(n - 1, k, 1) + dp(n - 1, k, 0);
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;

	memset(cache, -1, sizeof(cache));

	cache[1][0][0] = 1;
	cache[1][0][1] = 1;

	dp(100, 98, 1);
	dp(100, 98, 0);

	while (T--) {
		cin >> N >> K;
		printf("%lld\n", dp(N, K, 0) + dp(N, K, 1));
	}

	return 0;
}