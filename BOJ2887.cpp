#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define ll long long

struct tup {
	ll x,y,z, idx;
};

struct disjointSet {
	vector<int> parent, rank;
	disjointSet() {
		parent.resize(100100);
		rank.resize(100100, 1);
		for (int i = 0; i < 100100; ++i) parent[i] = i;
	}

	int find(int u) {
		if (u == parent[u]) return u;

		return parent[u] = find(parent[u]);
	}

	bool merge(int s, int e) {
		int u = find(s), v = find(e);
		if (u == v) return false;

		if (rank[u] > rank[v]) swap(u, v);

		parent[v] = u;
		if (rank[v] == rank[u]) ++rank[v];
		return true;
	}
};

int N;

vector<tup> vertexList;
vector<pair<ll, pii>> costList;

ll dist(tup a, tup b) {
	ll ret = LLONG_MAX;
	ret = min(ret, abs(a.x - b.x));
	ret = min(ret, abs(a.y - b.y));
	ret = min(ret, abs(a.z - b.z));
	return ret;
}


bool compx(const tup& a, const tup& b) {
	if (a.x < b.x) return true;
	else return false;
}

bool compy(const tup& a, const tup& b) {
	if (a.y < b.y) return true;
	else return false;
}

bool compz(const tup& a, const tup& b) {
	if (a.z < b.z) return true;
	else return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> N;
	for (int i = 0; i < N; ++i) {
		ll a, b, c;
		cin >> a >> b >> c;
		vertexList.push_back({ a,b,c,i });
	}

	sort(vertexList.begin(), vertexList.end(), compx);
	for (int i = 0; i < N - 1; ++i) {
		tup s = vertexList[i], e = vertexList[i + 1];
		ll d = dist(s,e);
		costList.push_back({ d,{s.idx,e.idx} });
	}

	sort(vertexList.begin(), vertexList.end(), compy);
	for (int i = 0; i < N - 1; ++i) {
		tup s = vertexList[i], e = vertexList[i + 1];
		ll d = dist(s, e);
		costList.push_back({ d,{s.idx,e.idx} });
	}

	sort(vertexList.begin(), vertexList.end(), compz);
	for (int i = 0; i < N - 1; ++i) {
		tup s = vertexList[i], e = vertexList[i + 1];
		ll d = dist(s, e);
		costList.push_back({ d,{s.idx,e.idx} });
	}
	
	sort(costList.begin(), costList.end());

	disjointSet DJS;

	ll ret = 0;
	for (int i = 0; i < costList.size(); ++i) {
		ll cost = costList[i].first;
		int s = costList[i].second.first, e = costList[i].second.second;
		if (DJS.merge(s, e)) {
			ret += cost;
		}
	}

	printf("%lld", ret);

	return 0;
}