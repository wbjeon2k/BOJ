//BOJ6196

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Mod 100000000

int N, M;
int board[20][20];

int cache[15][1 << 15];

int dp(int row, int state) {
	int& ret = cache[row][state];

	if (ret != -1) return ret;

	ret = 0;

	if (row == N - 1) {
		ret = 1;
		return ret;
	}

	int statebit[20], tstate = state;

	for (int i = 0; i < 15; ++i) {
		statebit[i] = tstate % 2;
		tstate /= 2;
	}


	for (int i = 0; i < (1 << M); ++i) {
		int nextstate[20], tmp = i;
		for (int j = 0; j < 15; ++j) {
			nextstate[j] = tmp % 2;
			tmp /= 2;
		}

		bool chk = true;
		for (int j = 0; j < M; ++j) {
			if (nextstate[j] && nextstate[j + 1]) chk = false;
			if (nextstate[j] && statebit[j]) chk = false;
			if (nextstate[j] && board[row+1][j] == 0) chk = false;

			if (!chk) break;
		}

		if (!chk) continue;

		ret += dp(row + 1, i);
		ret %= Mod;
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> board[i][j];
		}
	}

	memset(cache, -1, sizeof(cache));

	int ans = 0;

	for (int i = 0; i < (1 << M); ++i) {
		//memset(cache, -1, sizeof(cache));
		int nextstate[20];
		int tmp = i;
		for (int j = 0; j < 15; ++j) {
			nextstate[j] = tmp % 2;
			tmp /= 2;
		}

		bool chk = true;
		for (int j = 0; j < 15; ++j) {
			if (nextstate[j] && nextstate[j + 1]) chk = false;
			if (nextstate[j] && board[0][j] == 0) chk = false;

			if (!chk) break;
		}

		if (!chk) continue;

		ans += dp(0, i);
		ans %= Mod;
	}

	printf("%d\n", ans);

	return 0;
}