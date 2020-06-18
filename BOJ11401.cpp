//BOJ11401
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define M 1000000007
#define ll long long

ll N, K;

ll Npow(ll n, ll p) {
	ll base = n, ans = 1;
	while (p) {
		if (p & 1) {
			ans *= base;
			ans %= M;
		}
		base = base * base;
		base %= M;
		p >>= 1;
	}

	return ans;
}

ll factorial(ll n) {
	ll ret = 1;
	for (ll i = 1; i <= n; ++i) {
		ret *= i;
		ret %= M;
	}
	ret %= M;
	return ret;
}

int main() {
	cin >> N >> K;
	ll A, B, ans;
	A = factorial(N);
	B = (factorial(K) * factorial(N - K)) % M;
	B = Npow(B, M - 2);
	ans = (A * B) % M;
	printf("%lld", ans);

	return 0;
}