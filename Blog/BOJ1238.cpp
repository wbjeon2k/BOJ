//BOJ1238

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define vii vector<int> 
#define pii pair<int,int>
#define INF 123456789
#define Msize 1010

int adjMat[Msize][Msize];
int N, M, X;
vector<vii> mindist(Msize);

vii dijkstra(int start) {
	vii dist(Msize, INF);
	dist[start] = 0;
	priority_queue<pii, vector<pii>> pq;
	pq.push({ 0,start });

	while (!pq.empty()) {
		pii tmp = pq.top();
		pq.pop();

		int cost, here;
		cost = -(tmp.first);
		here = tmp.second;

		if (dist[here] < cost) continue;

		for (int i = 1; i <= N; ++i) {
			if (adjMat[here][i] == -1) continue;

			int there = i;
			int tdist = dist[here] + adjMat[here][there];
			if (tdist < dist[there]) {
				dist[there] = tdist;
				pq.push({ -tdist, there });
			}
		}
	}


	return dist;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M >> X;

	memset(adjMat, -1, sizeof(adjMat));

	for (int i = 0; i < M; ++i) {
		int a, b, d;
		cin >> a >> b >> d;
		adjMat[a][b] = d;
	}

	for (int i = 1; i <= N; ++i) {
		mindist[i] = dijkstra(i);
	}

	int ans = -1;

	for (int i = 1; i <= N; ++i) {
		ans = max(ans, mindist[i][X] + mindist[X][i]);
	}

	printf("%d\n", ans);


	return 0;
}