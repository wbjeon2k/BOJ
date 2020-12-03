//BOJ 6242
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll,ll>
map<int, vector<pll>> mp;
multiset<ll, greater<ll>> st;
int N;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		ll s, e, height;
		cin >> s >> e >> height;
		mp[s].push_back({ height, 1 });
		mp[e].push_back({ height, 0 });
	}
	
	ll spoint, epoint, ans;
	spoint = 1;
	epoint = 1;
	ans = 0;
	for (auto it = mp.begin(); it != mp.end(); ++it) {
		
		epoint = it->first;
		if (!st.empty()) ans += (epoint - spoint) * (*st.begin());
		spoint = epoint;

		for (int i = 0; i < (it->second).size(); ++i) {
			ll height, open;
			height = it->second[i].first;
			open = it->second[i].second;

			if (open) {
				st.emplace(height);
			}
			else {
				if(!st.empty()) st.erase(st.find(height));
			}
		}
	}

	printf("%lld\n", ans);
}

/*
//1st trial. WA
struct tup {
	ll s, e, height;
};


multiset<ll> st;

vector<tup> input;
vector<ll> coordinates;
ll shadow[40040];
int N;

int bisearch(ll target) {
	int sz = coordinates.size() - 1;

	int lo = 0, hi = sz;

	while (lo < hi) {
		int mid = (lo + hi) / 2;
		if (coordinates[mid] > target) {
			hi = mid;
		}
		else if (coordinates[mid] < target) {
			lo = mid + 1;
		}
		else {
			return mid;
		}
	}

	return lo;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		tup tmp;
		cin >> tmp.s >> tmp.e >> tmp.height;
		if (!st.count(tmp.s)) {
			coordinates.push_back(tmp.s);
			st.emplace(tmp.s);
		}

		if (!st.count(tmp.e)) {
			coordinates.push_back(tmp.e);
			st.emplace(tmp.e);
		}

		input.push_back(tmp);
	}

	sort(coordinates.begin(), coordinates.end());

	for (int i = 0; i < N; ++i) {
		ll s, e;
		s = input[i].s, e = input[i].e;

		int sidx, eidx;
		sidx = bisearch(s);
		eidx = bisearch(e);

		for (int j = sidx; j <= eidx; ++j) {
			if (shadow[j] < input[i].height) shadow[j] = input[i].height;
		}
	}

	ll ans = 0;

	for (int i = 0; i < coordinates.size() - 1; ++i) {
		ans += shadow[i]*(coordinates[i+1] - coordinates[i]);
	}

	printf("%lld\n", ans);

	return 0;
}
*/