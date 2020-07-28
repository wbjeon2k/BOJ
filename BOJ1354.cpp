// BOJ 1354

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
map<ll,ll> cache;

ll N, P, Q, X, Y;

ll dp(ll i) {
	if (i <= 0) {
		return 1;
	}

	if (cache[i] == 0) {
		cache[i] = dp((i / P) - X) + dp((i / Q) - Y);
		return cache[i];
	}
	else {
		return cache[i];
	}
}

int main() {
	cin >> N >> P >> Q >> X >> Y;

	printf("%lld", dp(N));

	return 0;
}

/*
//goooora's solution. 아니 1<22 해도 메모리가 안터지면 ;;
#include <cstdio>
typedef long long LL;
#define MAX 1<<22

LL n, p, q, x, y;
int dp[MAX];
LL recur(LL a) {
	if (a <= 0) return 1;
	if (a < MAX) {
		if (dp[a]) return dp[a];
		return dp[a] = recur(a / p - x) + recur(a / q - y);
	}
	else return recur(a / p - x) + recur(a / q - y);
}

int main() {
	scanf("%lld%lld%lld%lld%lld", &n, &p, &q, &x, &y);
	printf("%lld", recur(n));
}
*/