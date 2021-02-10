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

/*
//Green55's solution.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define xx first
#define yy second

/*
 * dp[i] = max(j<i){dp[j] + (j+1 ~ i의 전투력)}
 * = dp[j] + a*(sum[i]-sum[j])^2 + b*(sum[i]-sum[j]) + c
 * = dp[j] + a*sum[i]*sum[i] -2*a*sum[i]*sum[j] + a*sum[j]*sum[j] + b*sum[i] - b*sum[j] + c
 * = (-2*a*sum[j])*(sum[i])+ (dp[j] + a*sum[j]*sum[j] - b*sum[j]) + (a*sum[i]*sum[i] + b*sum[i] + c)
 * b[j] 순증가, a[i] 순증가
 *

 //dp[i] = min{b[j]*a[i] + c[j]}+d[i]; j<i, b[j]는 비증가/비감소
const int MAX = 1000100;
struct ConvexHullTrick {
	int s = 0, e = 0, idx[MAX];
	pll deq[MAX]; //first * x + second
	double cross(int a, int b) {
		return 1.0 * (deq[a].yy - deq[b].yy) / (deq[b].xx - deq[a].xx);
	}
	void insert(pll v, int line_idx) {//current line , i
		deq[e] = v;
		idx[e] = line_idx;
		//기울기가 증가하는 순서대로 저장한다
		while (s + 1 < e && cross(e - 2, e - 1) > cross(e - 1, e)) {
			deq[e - 1] = deq[e];
			idx[e - 1] = idx[e];
			e--;
		}
		e++;
	}
	ll query(long long x) {  // query가 증가수열일 경우
		//그래프 = └ 꼴 (>=), ┌ 꼴 (<=)
		while (s + 1 < e && deq[s + 1].yy - deq[s].yy >= x * (deq[s].xx - deq[s + 1].xx))
			s++;
		return deq[s].xx * x + deq[s].yy; //idx[s]
	}
}CHT;

ll n, a, b, c, x[MAX], sum[MAX], dp[MAX];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> a >> b >> c;
	for (int i = 1; i <= n; ++i) {
		cin >> x[i];
		sum[i] = sum[i - 1] + x[i];
	}
	CHT.insert({ 0,0 }, 0);
	//max{(-2*a*sum[j])*(sum[i])+ (dp[j] + a*sum[j]*sum[j] - b*sum[j])} + (a*sum[i]*sum[i] + b*sum[i] + c)
	for (int i = 1; i <= n; ++i) {
		dp[i] = CHT.query(sum[i]) + (a * sum[i] * sum[i] + b * sum[i] + c);
		CHT.insert({ -2 * a * sum[i], dp[i] + a * sum[i] * sum[i] - b * sum[i] }, i);
	}
	cout << dp[n];
}
*/