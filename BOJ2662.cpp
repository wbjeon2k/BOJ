//BOJ2662

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
int cache[333][22], price[333][22];

pii track[333][22];
int N, C;

int dp(int n, int c) {
	int& ret = cache[n][c];

	if (ret != -1) return ret;

	if (n == 0) {
		ret = 0;
		return ret;
	}

	if (c == 0) {
		ret = 0;
		return ret;
	}

	int maxi = 0;

	for (int i = 0; i <= n; ++i) {
		int t = dp(n-i, c-1) + price[i][c];
		if (t > maxi) {
			maxi = t;
			track[n][c] = { n - i,c - 1 };
		}
	}

	ret = maxi;
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> C;

	memset(price, 0, sizeof(price));
	memset(cache, -1, sizeof(cache));
	memset(track, 0, sizeof(track));


	for (int i = 0; i < N; ++i) {
		int a;
		cin >> a;

		for (int j = 1; j <= C; ++j) {
			int t;
			cin >> t;
			price[a][j] = t;
		}
	}

	printf("%d\n", dp(N, C));

	int a = N, b = C;
	vector<int> tracklist;
	while (1) {
		pii back = track[a][b];

		tracklist.push_back(a - back.first);
		a = back.first;
		b = back.second;

		if (back.second == 0) break;
	}

	for (int i = tracklist.size() - 1; i >= 0; --i) {
		printf("%d ", tracklist[i]);
	}

	return 0;
}