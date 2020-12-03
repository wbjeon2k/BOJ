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

int N, M;

pll vertex[1010];
priority_queue < pair < ll, pii >> pq;

ll dist(int x, int y) {
	ll distsq = (vertex[x].first - vertex[y].first) * (vertex[x].first - vertex[y].first) + (vertex[x].second - vertex[y].second) * (vertex[x].second - vertex[y].second);
	return distsq;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < N; ++i) {
		pii tmp;
		cin >> tmp.first >> tmp.second;
		vertex[i + 1] = tmp;
	}

	disjointset DJS;

	for (int i = 0; i < M; ++i) {
		int s, e;
		cin >> s >> e;
		DJS.merge(s, e);
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			if (DJS.find(i) == DJS.find(j)) continue;

			ll ijdist = dist(i, j);

			pq.push({ -ijdist, {i,j} });
		}
	}

	double ans = 0;

	while (!pq.empty()) {
		ll topdist = -pq.top().first;
		int s, e;
		s = pq.top().second.first, e = pq.top().second.second;
		pq.pop();

		if (!DJS.merge(s, e)) continue;

		ans += sqrt(topdist);
	}
	
	printf("%.2lf", ans);


	return 0;

}