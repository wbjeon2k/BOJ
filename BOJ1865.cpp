//BOJ 1865

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define ll long long
#define INF INT_MAX

vector<vector<pii>> adjList(555);
int TC, N, M, W, V;

bool bellmanford(int start) {
	vector<ll> upper(N+1, INF);

	upper[start] = 0;
	
	bool updated = false;
	for (int it = 0; it < N; ++it) {
		updated = false;

		for (int i = 1; i <= N; ++i) {
			for (int j = 0; j < adjList[i].size(); ++j) {
				int here, there, cost;
				here = i;
				there = adjList[i][j].first;
				cost = adjList[i][j].second;

				if (upper[there] > upper[here] + cost) {
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		}

		if (!updated) break;
		
	}

	if (updated) return true;

	//if (upper[start] < 0) return true;
	else return false;
}

void solve() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M >> W;

	for (int i = 0; i < M; ++i) {
		int s, e, t;
		cin >> s >> e >> t;
		adjList[s].push_back({ e,t });
		adjList[e].push_back({ s,t });
	}

	for (int i = 0; i < W; ++i) {
		int s, e, t;
		cin >> s >> e >> t;
		adjList[s].push_back({ e, -t });
	}

	bool chk = false;
	if (bellmanford(1)) {
		printf("YES\n");
		chk = true;
	}

	if(!chk) printf("NO\n");

	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> TC;

	while (TC--) {
		adjList.clear();
		adjList.resize(555);
		solve();
	}

	return 0;
}