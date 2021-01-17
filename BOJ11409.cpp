//BOJ11409

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 808

int N, M;
ll mcost, mflow;
int source, sink;

vector<int> adjlist[MAXI];

ll dist[MAXI][MAXI], capacity[MAXI][MAXI], flow[MAXI][MAXI];

void mcmf() {
	
	mflow = mcost = 0;

	while (1) {
		vector<ll> upper(MAXI, INT_MAX);
		vector<ll> parent(MAXI, -1);
		vector<bool> isinq(MAXI, 0);

		queue<int> q;
		q.push(source);
		isinq[source] = true;
		upper[source] = 0;


		while (!q.empty()) {
			int here = q.front();
			q.pop();
			isinq[here] = false;

			for (int i = 0; i < adjlist[here].size(); ++i) {
				int there = adjlist[here][i];
				if (capacity[here][there] - flow[here][there] > 0 && upper[there] > upper[here] + dist[here][there]) {
					upper[there] = upper[here] + dist[here][there];
					parent[there] = here;
					if (!isinq[there]) {
						q.push(there);
						isinq[there] = true;
					}
				}
			}
		}

		if (parent[sink] == -1) break;

		ll b = INT_MAX;
		for (int i = sink; i != source; i = parent[i]) {
			b = min(b, capacity[parent[i]][i] - flow[parent[i]][i]);
		}

		for (int i = sink; i != source; i = parent[i]) {
			flow[parent[i]][i] += b;
			flow[i][parent[i]] -= b;
		}

		mflow += b;
		mcost += upper[sink] * b;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 1; i <= N; ++i) {
		int t;
		cin >> t;
		while (t--) {
			int s, e;
			cin >> s >> e;
			adjlist[i].push_back(s + N + 1);
			dist[i][s + N + 1] = -e;
			capacity[i][s + N + 1] = 1;

			adjlist[s + N + 1].push_back(i);
			dist[s + N + 1][i] = e;
		}
	}

	source = 0, sink = MAXI - 1;

	for (int i = 1; i <= N; ++i) {
		adjlist[source].push_back(i);
		capacity[source][i] = 1;
		adjlist[i].push_back(source);
	}

	for (int i = 1; i <= M; ++i) {
		adjlist[i + N + 1].push_back(sink);
		capacity[i + N + 1][sink] = 1;
		adjlist[sink].push_back(i + N + 1);
	}

	mcmf();

	printf("%lld\n", mflow);
	printf("%lld\n", -mcost);

	return 0;

}

