//BOJ6142
//https://ace.delosent.com/TESTDATA/DEC07.gourmet.htm

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pid pair<int,double>
#define pll pair<ll,ll>

#define MAXI 100100

vector<pll> cow, grass;

int N, M;

set<pll> pickgrass;
int lastinsert;

bool cmp(const pll& a, const pll& b) {
	if (a.second == b.second) return (a.first <= b.first);
	return a.second <= b.second;
}

void insertset(int x) {
	for (int i = lastinsert - 1; i >= 0; --i) {
		if (grass[i].second >= cow[x].second) {
			pickgrass.insert({ grass[i].first, i });
			lastinsert = i;
		}
		else break;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N >> M;

	cow.resize(N);
	for (int i = 0; i < N; ++i) {
		cin >> cow[i].first >> cow[i].second;
	}

	grass.resize(M);
	for (int i = 0; i < M; ++i){
		cin >> grass[i].first >> grass[i].second;
	}

	sort(cow.begin(), cow.end(), cmp);
	sort(grass.begin(), grass.end(), cmp);

	lastinsert = M;

	ll ans = 0;
	for (int i = N - 1; i >= 0; --i) {
		insertset(i);

		set<pll>::iterator iter = pickgrass.lower_bound({ cow[i].first, -1 });
		if (iter == pickgrass.end()) {
			ans = -1;
			break;
		}

		ans += (*iter).first;
		pickgrass.erase(iter);
	}

	printf("%lld\n", ans);
	return 0;

}
