//BOJ6216

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;


#define ll long long
#define pii pair<ll,ll>
vector<pii> cowlist;
int N;
ll psum[100100];
ll eatsum;

bool comp(pii& a, pii& b) {
	//1초당 먹는 비율 큰 순으로 정렬.
	double x, y;
	x = ((double)a.second / (double)a.first) * 100;
	y = ((double)b.second / (double)b.first) * 100;

	if (x > y) return true;

	return false;
}

ll solve() {
	ll ret = 0;

	psum[0] = cowlist[0].first;

	for (int i = 1; i < N; ++i) {
		psum[i] = psum[i-1] + cowlist[i].first;
	}

	for (int i = 0; i < N; ++i) {
		eatsum -= cowlist[i].second;
		ret += eatsum * 2 * cowlist[i].first;
		//printf("%lld\n", ret);
	}

	return ret;
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	eatsum = 0;

	for (int i = 0; i < N; ++i) {
		pii tmp;
		cin >> tmp.first >> tmp.second;
		cowlist.push_back(tmp);
		eatsum += tmp.second;
	}

	sort(cowlist.begin(), cowlist.end(), comp);

	ll ans = solve();

	printf("%lld\n", ans);

	return 0;
}