//BOJ12849

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll dp[2][11];

#define M 1000000007

int main() {
	memset(dp, 0, sizeof(dp));

	dp[1][1] = 1;
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 1; j <= 8; ++j) dp[0][j] = dp[1][j];
		dp[1][1] = dp[0][2] + dp[0][3];
		dp[1][2] = dp[0][1] + dp[0][4] + dp[0][3];
		dp[1][3] = dp[0][2] + dp[0][4] + dp[0][1] + dp[0][5];
		dp[1][4] = dp[0][2] + dp[0][3] + dp[0][6] + dp[0][5];
		dp[1][5] = dp[0][3] + dp[0][4] + dp[0][6] + dp[0][7];
		dp[1][6] = dp[0][4] + dp[0][5] + dp[0][8];
		dp[1][7] = dp[0][5] + dp[0][8];
		dp[1][8] = dp[0][6] + dp[0][7];

		for (int j = 1; j <= 8; ++j) dp[1][j] %= M;
	}

	printf("%lld\n", dp[1][1]);

	return 0;
}