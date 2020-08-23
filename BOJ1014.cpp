//BOJ 1014

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int cache[11][1 << 10];
char board[11][11];
int T, N, M;

int bitcnt(int state) {
	if (state == 0) return 0;
	return state % 2 + bitcnt(state / 2);
}

int dp(int idx, int state) {
	int& ret = cache[idx][state];
	if (ret != -1) return ret;

	if (idx == 0) {
		for (int i = 0; i < M - 1; ++i) {
			int biton, nbiton;
			biton = state & (1 << i);
			nbiton = state & (1 << (i+1));

			if (biton && nbiton) {
				ret = 0;
				return ret;
			}
		}

		for (int i = M - 1; i > 0; --i) {
			int biton, pbiton;
			biton = state & (1 << i);
			pbiton = state & (1 << (i - 1));

			if (biton && pbiton) {
				ret = 0;
				return ret;
			}
		}

		for (int i = 0; i < M; ++i) {
			int biton;
			biton = state & (1 << i);
			
			if (biton && board[0][i] == 'x') {
				ret = 0;
				return ret;
			}
		}

		ret = bitcnt(state);
		return ret;

	}

	for (int i = 0; i < M - 1; ++i) {
		int biton, nbiton;
		biton = state & (1 << i);
		nbiton = state & (1 << (i + 1));

		if (biton && nbiton) {
			ret = 0;
			return ret;
		}
	}

	for (int i = M - 1; i > 0; --i) {
		int biton, pbiton;
		biton = state & (1 << i);
		pbiton = state & (1 << (i - 1));

		if (biton && pbiton) {
			ret = 0;
			return ret;
		}
	}

	for (int i = 0; i < M; ++i) {
		int biton;
		biton = state & (1 << i);

		if (biton && board[idx][i] == 'x') {
			ret = 0;
			return ret;
		}
	}

	bool chk = true;
	for (int prevs = 0; prevs < (1<<M) - 1 ; ++prevs) {
		chk = true;

		for (int i = 0; i < M - 1; ++i) {
			int biton, nbiton, prevon;
			biton = state & (1 << i);
			prevon = prevs & (1 << (i + 1));

			if (biton && prevon) {
				chk = false;
			}
		}

		for (int i = M - 1; i > 0; --i) {
			int biton, prevon;
			biton = state & (1 << i);
			prevon = prevs & (1 << (i - 1));

			if (biton && prevon) {
				chk = false;
			}
		}

		if (chk) {
			ret = max(ret, dp(idx - 1, prevs) + bitcnt(state));
		}
	}

	return ret;
}

int main() {
	
	scanf("%d", &T);

	while (T--) {
		scanf("%d %d\n", &N, &M);
		for (int i = 0; i < N; ++i) {
			scanf("%s", &board[i]);
		}

		memset(cache, -1, sizeof(cache));

		int ans = -1;
		for (int i = 0; i <= (1 << M) - 1; ++i) {
			int cnt = i;
			ans = max(ans, dp(N - 1, i));
		}

		printf("%d\n", ans);
	}

	return 0;
}

/*
//djm03178's solution.
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char m[15][15];
int dp[10][1 << 10];
int r, c;

int f(int, int);

int g(int i, int b, int j, int x, int p)
{
	if (j >= c)
		return p + f(i + 1, x);
	int ret = 0;
	if (m[i][j] == '.' && !(b & (1 << (j - 1))) && !(b & (1 << (j + 1))))
		ret = g(i, b, j + 2, x | (1 << j), p + 1);
	return ret = max(ret, g(i, b, j + 1, x, p));
}

int f(int i, int b)
{
	if (i >= r)
		return 0;
	int &ret = dp[i][b];
	if (ret != -1)
		return ret;
	ret = g(i, b, 0, 0, 0);
	return ret;
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		memset(dp, -1, sizeof(dp));
		scanf("%d%d", &r, &c);
		for (int i = 0; i < r; i++)
			scanf("%s", m[i]);
		printf("%d\n", f(0, 0));
	}
}
*/