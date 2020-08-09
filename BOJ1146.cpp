//BOJ 1146

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD 1000000

ll cache[101][101];
int N;

int dp(int left, int right) {
	if (left == 0 && right == 0) return 1;

	ll& ret = cache[left][right];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 1; i <= right; ++i) {
		ret += dp(right - i, left + i - 1);
		ret %= MOD;
	}

	return ret;
}

int main() {
	cin >> N;

	if (N == 1) {
		printf("1\n");
		return 0;
	}

	memset(cache, -1, sizeof(cache));

	ll ans = 0;
	for (int i = 1; i <= N; ++i) {
		ans += dp(i - 1, N - i);
		ans %= MOD;
		ans += dp(N - i, i - 1);
		ans %= MOD;
	}

	printf("%lld\n", ans);

	return 0;
}