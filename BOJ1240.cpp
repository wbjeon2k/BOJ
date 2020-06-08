//1240
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool visited[1010];
int cost[1010][1010];
vector<vector<int>> adjList(1010);
int N, M;

#define pii pair<int,int>

void bfs(int s, int e) {
	memset(visited, 0, sizeof(visited));
	queue<pii> q;
	q.push({ s,0 });

	while (!q.empty()) {
		pii here = q.front();
		q.pop();
		int h = here.first, dist = here.second;
		visited[h] = true;

		if (h == e) {
			printf("%d\n", dist);
			return;
		}

		for (int i = 0; i < adjList[h].size(); ++i) {
			int there = adjList[h][i];
			if (!visited[there]) {
				visited[there] = true;
				q.push({ there, dist + cost[h][there] });
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	memset(cost, 0, sizeof(cost));

	for (int i = 0; i < N-1; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
		cost[a][b] = c;
		cost[b][a] = c;
	}

	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;
		bfs(a, b);
	}

	return 0;

}


/*
//ntopia's solution. using LCA
//LCA 는 과하다 싶었는데 이렇게 간단하게도 구현할 수 있다.
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int MAXLN = 10;
int n;
vector<pair<int, int>> tree[MAXN];
int depth[MAXN];
long long distFromRoot[MAXN];
int parent[MAXLN][MAXN];

void dfs(int u, int par) {
	for (const auto& e : tree[u]) {
		if (e.first == par) {
			continue;
		}
		distFromRoot[e.first] = distFromRoot[u] + e.second;
		depth[e.first] = depth[u] + 1;
		parent[0][e.first] = u;
		dfs(e.first, u);
	}
}

int lca(int u, int v) {
	if (depth[u] < depth[v]) {
		swap(u, v);
	}

	int logu = 1;
	for (; (1 << logu) <= depth[u]; ++logu);
	--logu;

	if (depth[u] > depth[v]) {
		for (int i = logu; i >= 0; --i) {
			if (depth[u] - (1 << i) >= depth[v]) {
				u = parent[i][u];
			}
		}
	}
	if (u == v) {
		return u;
	}
	for (int i = logu; i >= 0; --i) {
		if (parent[i][u] != parent[i][v]) {
			u = parent[i][u];
			v = parent[i][v];
		}
	}
	return parent[0][u];
}

void proc() {
  int q;
	scanf("%d %d", &n, &q);
	for (int i = 0; i < n - 1; ++i) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		tree[a].push_back({ b, c });
		tree[b].push_back({ a, c });
	}

	parent[0][1] = 1;
	dfs(1, -1);
	for (int i = 1; i < MAXLN; ++i) {
		for (int j = 1; j <= n; ++j) {
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
		}
	}

	for (int i = 0; i < q; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%lld\n", distFromRoot[a] + distFromRoot[b] - 2 * distFromRoot[lca(a, b)]);
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	proc();
	return 0;
}
*/