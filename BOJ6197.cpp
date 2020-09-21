//BOJ6197

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>
#define Msize 5050
#define ll long long
#define pll pair<ll,ll>
#define INF LLONG_MAX/2
vector<vector<pll>> adjList(Msize);
//vector<vector<ll>> distmat(Msize);
vector<ll> distmat2;

int R, N;

void dijkstra(int src) {
	vector<ll> dist(N + 1, INF);
	vector<ll> dist2(N + 1, INF);
	dist[src] = 0;
	//dist2[src] = 0;

	priority_queue<pll> pq;

	pq.push({ 0,src });

	while (!pq.empty()) {
		ll cost, here;

		cost = -pq.top().first;
		here = pq.top().second;

		pq.pop();

		if (dist2[here] < cost) continue;

		for (int i = 0; i < adjList[here].size(); ++i) {
			int there = adjList[here][i].first;
			ll ndist = cost + adjList[here][i].second;

			if (ndist < dist[there]) {
				swap(ndist, dist[there]);
				pq.push({ -dist[there], there });
			}

			if (ndist < dist2[there] && ndist > dist[there]) {
				dist2[there] = ndist;
				pq.push({ -ndist, there });
			}
		}
	}

	distmat2 = dist2;
	//distmat[src] = dist;

	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> N >> R;

	for (int i = 0; i < R; ++i) {
		ll s, e, w;

		cin >> s >> e >> w;
		adjList[s].push_back({ e,w });
		adjList[e].push_back({ s,w });
	}

	dijkstra(1);

	ll secdist = distmat2[N];

	printf("%lld\n", secdist);

	return 0;
}