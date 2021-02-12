//BOJ13261

//https://koosaga.com/242
//https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXI 100100
#define cplx complex<double>
const double PI = acos(-1);
const ll INF = LLONG_MAX/2;

int l, g;
ll input[8080], psum[8080];
vector<ll> pre(8080), now(8080);

inline ll cost(int s, int e) {
	return (psum[e] - psum[s - 1]) * ((ll)e - s + 1);
}

void dp(int s, int e, int opts, int opte) {
	if (s > e) return;

	int optm, mid = (s + e) / 2;
	ll ans = INF;

	optm = opts;
	for (int i = opts; i <= min(mid,opte); ++i) {
		ll tmp = pre[i] + cost(i + 1, mid);
		if (ans > tmp) {
			ans = tmp;
			optm = i;
		}
	}

	now[mid] = ans;

	dp(s, mid - 1, opts, optm);
	dp(mid + 1, e, optm, opte);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin; cin.open("input.txt");

	cin >> l >> g;
	for (int i = 1; i <= l; ++i) cin >> input[i];
	psum[0] = 0;
	for (int i = 1; i <= l; ++i) psum[i] = psum[i - 1] + input[i];

	for (int i = 1; i <= l; ++i) now[i] = cost(1, i);
	//dp(1,i);
	//get dp

	for (int i = 2; i <= g; ++i) {
		pre = now;
		now.clear();
		now.resize(8080);
		dp(1, l, 1, l);
	}

	printf("%lld\n", now[l]);

	return 0;

}