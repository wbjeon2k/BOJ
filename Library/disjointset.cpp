#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>

/*debug
	ifstream cin;
	cin.open("input.txt");
*/

#define pll pair<ll, ll>
#define INF LLONG_MAX/4

struct disjointset {
	int parent[1010];
	int rank[1010];
	long long setsize[1010];

	disjointset() {
		for (int i = 0; i < 1010; ++i) parent[i] = i;
		memset(setsize, 1, sizeof(setsize));
		memset(rank, 0, sizeof(rank));
	}

	int find(int u) {
		if (parent[u] == u) return u;

		return parent[u] = find(parent[u]);
	}

	bool merge(int u, int v) {
		u = find(u);
		v = find(v);

		if (u == v) return false;

		if (rank[u] > rank[v]) swap(u, v);

		setsize[v] += setsize[u];
		setsize[u] = 1;
		parent[u] = v;
		if (rank[u] == rank[v]) ++rank[v];

		return true;
	}

	int size(int u) {
		return setsize[find(u)];
	}
};