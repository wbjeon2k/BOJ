// BOJ 6195

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

priority_queue<ll, vector<ll>, greater<ll>> pq;
int N;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		ll t;
		cin >> t;
		pq.emplace(t);
	}

	ll ans = 0;

	while (pq.size() > 1) {
		ll s, e;

		s = pq.top();
		pq.pop();
		e = pq.top();
		pq.pop();

		ans += (s + e);

		pq.push(s + e);
	}

	printf("%lld\n", ans);

	return 0;
}

/*
//first attempt. WA

int N;
ll planks[20200];
ll psum[20200];
ll ans = 0;
int dnccall = 0;
int bisearch(int s, int e, ll target) {
	if (e - s == 1) return s;

	int lo, hi;

	lo = s, hi = e;

	while (lo < hi) {

		int mid = (lo + hi) / 2;

		ll midpsum = psum[mid] - psum[s - 1];

		if (midpsum >= target) {
			hi = mid;
		}
		else {
			lo = mid + 1;
		}
	}

	assert(lo == hi);

	ll lopsum, hipsum;
	lopsum = psum[lo - 1] - psum[s - 1];
	hipsum = psum[hi] - psum[s - 1];

	if (abs(target - lopsum) < abs(target - hipsum)) return lo - 1;
	else return hi;
}

int bisearch2(int s, int e) {
	ll sumtot = psum[e] - psum[s - 1], diff = INT_MAX, didx = 0;

	for (int i = s; i <= e; ++i) {
		ll tmpsum = psum[i] - psum[s - 1];
		if (diff > abs(tmpsum - (sumtot / 2))) {
			diff = abs(tmpsum - (sumtot / 2));
			didx = i;
		}
	}

	return didx;
}

void dnc(int s, int e) {
	if (e == s) return;
	
	++dnccall;

	ll tmp = psum[e] - psum[s - 1];
	ans += tmp;

	if (s + 1 == e) return;

	int mid = bisearch2(s, e);

	dnc(s, mid);
	dnc(mid + 1, e);

	return;
}


int main() {

	//ifstream cin;
	//cin.open("input.txt");

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	planks[0] = 0;
	for (int i = 1; i <= N; ++i) {
		cin >> planks[i];
	}

	sort(planks, planks + N + 1);

	psum[0] = 0;
	for (int i = 1; i <= N; ++i) {
		psum[i] = psum[i - 1] + planks[i];
	}

	printf("%d\n", bisearch2(1, N));
	dnc(1, N);

	//printf("%d\n", bisearch(1, 4, 9));

	printf("%lld\n", ans);
	printf("%d\n", dnccall);
	return 0;
}

*/