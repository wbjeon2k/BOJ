//BOJ4008


#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXI 1001000
#define cplx complex<double>
const double PI = acos(-1);
const ll INF = INT_MAX / 2;

//https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/LineContainer.h
//https://stonejjun.tistory.com/53

struct Line {
	ll m, b;
	//mx + b;
};

ll cx(Line x, Line y) { // floored division
	ll a, b;
	a = x.b - y.b;
	b = y.m - x.m;
	return a / b - ((a ^ b) < 0 && a % b);
}

Line stk[MAXI];
ll sz = 0;

void lineinsert(Line v) {
	stk[sz] = v;
	while (1 < sz) {
		ll p, q;
		p = cx(stk[sz], stk[sz - 1]);
		q = cx(stk[sz - 1], stk[sz - 2]);

		if (p > q) break;
		stk[sz - 1] = stk[sz];
		sz--;
	}
	sz++;
}

ll sol(ll x) {
	ll lo = 0, hi = sz - 1;
	while (lo < hi) {
		ll mid = (lo + hi) / 2;
		if (cx(stk[mid], stk[mid + 1]) < x) lo = mid + 1;
		else hi = mid;
	}
	return stk[lo].m * x + stk[lo].b;
}

ll n, a, b, c;
ll dp[MAXI], psum[MAXI];

inline ll f(ll x) {
	return (a * x * x) + (b * x) + c;
}

// y = mx + B

inline ll m(ll x) {
	return (-2) * a * psum[x];
}

inline ll B(ll x) {
	return dp[x] + (a * psum[x] * psum[x]) - (b * psum[x]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> n;
	cin >> a >> b >> c;
	psum[0] = 0;

	ll tmp;
	for (int i = 1; i <= n; ++i) {
		cin >> tmp;
		psum[i] = psum[i - 1] + tmp;
	}

	lineinsert(Line({ 0, 0 }));
	for (int i = 1; i <= n; ++i) {
		dp[i] = f(psum[i]) + sol(psum[i]);
		//dp[i] 값이 결정 되어야 B 계산 가능.
		lineinsert(Line({ m(i), B(i) }));
	}

	printf("%lld\n", dp[n]);


	return 0;

}