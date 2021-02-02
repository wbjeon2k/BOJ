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
 */

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