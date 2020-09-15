//BOJ 11657

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define ll long long
#define INF LLONG_MAX/2
int N, M;
vector<vector<pii>> adjList(555);
vector<ll> ans;

vector<ll> bellmanford(int start) {
	vector<ll> upper(N + 1, INF);

	upper[start] = 0;

	bool updated = false;
	for (int i = 0; i < N; ++i) {
		updated = false;
		for (int j = 1; j <= N; ++j) {
			for (int k = 0; k < adjList[j].size(); ++k) {
				ll here, there, cost;
				here = j;
				there = adjList[j][k].first;
				cost = adjList[j][k].second;

				if (upper[here] != INF && upper[there] > upper[here] + cost) {
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		}

		if (!updated) break;
	}

	if (updated) return vector<ll>();
	else return upper;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < M; ++i) {
		int a, b, c;
		cin >> a >> b >> c;

		adjList[a].push_back({ b,c });
	}

	ans = bellmanford(1);

	if (ans.size() == 0) printf("-1\n");
	else {
		for (int i = 2; i <= N; ++i) {
			if (ans[i] == INF) printf("-1\n");
			else printf("%lld\n", ans[i]);
		}
	}

	return 0;
}