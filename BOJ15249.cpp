//BOJ15249


#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXI 100100
#define cplx complex<double>
const double PI = acos(-1);
const ll INF = INT_MAX / 2;

//https://github.com/kth-competitive-programming/kactl/blob/master/content/data-structures/LineContainer.h
//https://stonejjun.tistory.com/53

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b);
	}
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({ k, m, 0 }), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

ll n;
ll dp[MAXI], psum[MAXI], h[MAXI], w[MAXI];

// y = mx + b

inline ll m(ll x) {
	return (-2) * h[x];
}

inline ll b(ll x) {
	return dp[x] + h[x]*h[x] - psum[x];
}

inline ll c(ll x) {
	return (h[x] * h[x]) + psum[x - 1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> h[i];
	for (int i = 1; i <= n; ++i) cin >> w[i];

	psum[0] = 0;
	for (int i = 1; i <= n; ++i) psum[i] = psum[i - 1] + w[i];

	LineContainer LC;

	memset(dp, 0, sizeof(dp));

	for (int i = 2; i <= n; ++i) {
		LC.add(-m(i - 1), -b(i - 1));
		dp[i] = c(i) - LC.query(h[i]);
	}

	printf("%lld\n", dp[n]);


	return 0;

}