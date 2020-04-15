#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

using namespace std;

long long dp[35];

long long tile(int n) {
	long long& ret = dp[n];

	if (ret != -1) {
		return ret;
	}

	long long t=0;
	for (int i = 1; i < n; ++i) {
		
		if (i == 1) {
			t = 3 * tile(n - 2);
		}
		else if (n - (2 * i) > 0) {
			t += 2 * tile(n - 2 * i);
		}
		else {
			t += 0;
		}
	}

	ret = t;
	ret += 2;

	return ret;
}

int main() {
	int n;
	scanf("%d", &n);

	fill(dp, dp + 35, -1);
	for (int i = 0; i < 17; ++i) {
		dp[2 * i + 1] = 0;
	}
	dp[2] = 3;

	long long t = tile(n);

	printf("%lld", t);

	return 0;

}