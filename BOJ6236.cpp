#define _CRT_SECURE_NO_WARNINGS

#include <bits/stdc++.h>

int cap, N, K, M;
int consume[100100];

bool withdraw(int x) {
	int cnt = 1;
	int cash = x;

	for (int i = 0; i < N; ++i) {
		if (x < consume[i]) {
			return false;
		}

		if (cash - consume[i] < 0) {
			cash = x;
			++cnt;
		}

		cash -= consume[i];	
	}

	if (cnt <= M) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; ++i) {
		scanf("%d", &consume[i]);
	}
	int lo, hi,ret;
	lo = 1;
	hi = 100100;
	ret = 0;

	while (lo <= hi) {
		int mid = (lo + hi) / 2;

		if (withdraw(mid)) {
			ret = mid;
			hi = mid-1;
		}
		else {
			lo = mid+1;
		}
	}

	

	printf("%d", ret);

	return 0;
}