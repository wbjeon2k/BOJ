//BOJ7579

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, W, Val;
int cache[2][10010], weight[101], value[101];

int knapsack() {
	int ret = 0;
	for (int i = 1; i <= N; ++i) {
		int now, prev;
		if (i % 2) {
			now = 1, prev = 0;
		}
		else {
			now = 0, prev = 1;
		}

		for (int j = 0; j <= W; ++j) {
			if (weight[i] <= j) {
				cache[now][j] = max(cache[prev][j], cache[prev][j - weight[i]] + value[i]);
			}
			else {
				cache[now][j] = cache[prev][j];
			}
		}
		ret = now;
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> Val;

	W = 0;
	for (int i = 1; i <= N; ++i) {
		cin >> value[i];
	}
	for (int i = 1; i <= N; ++i) {
		cin >> weight[i];
		W += weight[i];
	}

	memset(cache, 0, sizeof(cache));
	int idx = knapsack();

	for (int i = 0; i < 10000; ++i) {
		if (cache[idx][i] >= Val) {
			printf("%d\n", i);
			break;
		}
	}

	return 0;
}