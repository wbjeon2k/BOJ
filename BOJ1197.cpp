#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define ll long long
vector<vector<pii>> adjList(10010);

vector<pair<int, pii>> vertexList;

int V, E;

struct disjointSet {
	vector<int> parent, rank;

	disjointSet() {
		parent.resize(10010);
		rank.resize(10010);
		for (int i = 0; i < 10010; ++i) {
			parent[i] = i;
			rank[i] = 1;
		}
	}

	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}

	bool merge(int s, int e) {
		int u = find(s), v = find(e);

		if (u == v) return false;

		if (rank[u] > rank[v]) swap(u, v);

		parent[v] = u;
		if (rank[u] == rank[v]) ++rank[v];
		return true;
	}
};

ll kruskal(){

	ll ret = 0;
	disjointSet DJS;
	for (int i = 0; i < vertexList.size(); ++i) {
		pair<int, pii> vhere = vertexList[i];
		int cost = vhere.first, s = vhere.second.first, e = vhere.second.second;
		if (DJS.find(s) != DJS.find(e)) {
			DJS.merge(s, e);
			ret += (ll)cost;
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> V >> E;

	for (int i = 0; i < E; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		adjList[a].push_back({ b,c });
		adjList[b].push_back({ a,c });
		vertexList.push_back({ c, {a,b} });
		vertexList.push_back({ c, {b,a} });
	}

	sort(vertexList.begin(), vertexList.end());

	ll ans = kruskal();
	printf("%lld", ans);

	return 0;
}