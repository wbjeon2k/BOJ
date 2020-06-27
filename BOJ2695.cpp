//BOJ2695

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int cache[55][1010];

int T, B, M;

int dp(int b, int m) {
	int& ret = cache[b][m];

	if (ret != -1) return ret;

	if (b == 1) {
		ret = m;
		return ret;
	}
	else if (b == 0 || m==0) {
		ret = 0;
		return ret;
	}
	else if (m == 1) {
		ret = 1;
		return ret;
	}

	int tmp=m;
	for (int i = 1; i <= m; ++i) {
		int broke, notbroke;
		broke = dp(b - 1, i-1) + 1;
		notbroke = dp(b, m - i) + 1;
		tmp = min(tmp, max(broke, notbroke));
	}

	ret = tmp;
	return ret;
}

int main() {
	cin >> T;

	memset(cache, -1, sizeof(cache));

	dp(50, 1000);

	while (T--) {
		cin >> B >> M;
		printf("%d\n", dp(B, M));
	}

	return 0;
}

/*
//ntopia's solution.
#include <cstdio>
#include <algorithm>
using namespace std;

int d[51][1001];

void preproc() {
	for (int k = 1; k <= 1000; ++k) {
		d[1][k] = k;
	}
	for (int i = 2; i <= 50; ++i) {
		for (int k = 1; k <= 1000; ++k) {
			d[i][k] = 100000000;
			for (int j = 1; j <= k; ++j) {
				int v = max(d[i - 1][j - 1] + 1, d[i][k - j] + 1);
				d[i][k] = min(d[i][k], v);
			}
		}
	}
}

void proc() {
	int n, m;
	scanf("%d %d", &n, &m);
	printf("%d\n", d[n][m]);
}

int main() {
	//freopen("input.txt", "r", stdin);
	preproc();
	int t;
	scanf("%d", &t);
	while (t-- > 0) {
		proc();
	}
	return 0;
}
*/