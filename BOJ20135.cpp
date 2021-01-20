//BOJ20135

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 202
#define INF INT_MAX/2
int N, M, source, sink;

ll input[MAXI], start[MAXI], capacity[MAXI][MAXI], flow[MAXI][MAXI], lbound[MAXI][MAXI], ubound[MAXI][MAXI];
ll mflow;
vector<int> adjlist[202];
vector<int> level, visited, see;

bool bfs() {
	level = vector<int>(MAXI, -1);
	queue<int> q;
	q.push(source);
	level[source] = 0;

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		for (int i = 0; i < adjlist[here].size(); ++i) {
			int there = adjlist[here][i];
			if (level[there] == -1 && capacity[here][there] - flow[here][there] > 0) {
				level[there] = level[here] + 1;
				q.push(there);
			}
		}
	}

	if (level[sink] == -1) return false;
	else return true;
}

int dfs(int here, ll bf) {
	if (here == sink) return bf;

	for (; see[here] < adjlist[here].size(); see[here]++) {
		int there = adjlist[here][see[here]];
		if (level[there] == level[here] + 1 && capacity[here][there] - flow[here][there] > 0) {
			int nflow = dfs(there, min(bf, capacity[here][there] - flow[here][there]));
			if (nflow > 0) {
				flow[here][there] += nflow;
				flow[there][here] -= nflow;
				return nflow;
			}
		}
	}

	return 0;
}

void dinic() {

	mflow = 0;

	while (bfs()) {
		
		see = vector<int>(MAXI, 0);

		while (1) {
			ll f = dfs(source, INF);
			if (f == 0) break;
			mflow += f;
		}
		
	}
}

bool findcirculation() {
	ll neg, pos;
	neg = pos = 0;
	for (int i = 1; i <= N; ++i) {
		if (start[i] > 0) pos += start[i];
		else if (start[i] < 0) neg -= start[i];
		else continue;
	}

	if (neg != pos) return false;

	for (int i = 1; i <= N; ++i) {
		if (start[i] < 0) {
			adjlist[source].push_back(i);
			adjlist[i].push_back(source);
			capacity[source][i] = -start[i];
		}
		else if (start[i] > 0) {
			adjlist[i].push_back(sink);
			adjlist[sink].push_back(i);
			capacity[i][sink] = start[i];
		}
	}

	dinic();

	if (mflow == pos) return true;
	else return false;
}

struct edgedata {
	ll u, v, s, e;
};

edgedata edgelist[1010];

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);
	cin >> N >> M;
	for (int i = 0; i < N; ++i) cin >> input[i + 1], input[i+1] *= -1;
	//Pi 가 양수면 받는것 -> demand 는 음수!!!!!!!
	for (int i = 0; i < N; ++i) start[i + 1] = input[i + 1];

	source = 0, sink = N+1;

	memset(lbound, 0, sizeof(lbound));
	memset(capacity, 0, sizeof(capacity));
	memset(flow, 0, sizeof(flow));

	for (int i = 0; i < M; ++i) {
		ll u, v, s, e;
		cin >> u >> v >> s >> e;
		edgelist[i] = { u,v,s,e };
		adjlist[u].push_back(v);
		adjlist[v].push_back(u);
		lbound[u][v] = s;
		ubound[u][v] = e;
		capacity[u][v] = e - s;
		start[u] += s;
		start[v] -= s;
	}

	if (findcirculation()) {
		

		printf("1\n");

		for (int i = 0; i < M; ++i) {
			int u, v;
			u = edgelist[i].u;
			v = edgelist[i].v;
			printf("%lld\n", flow[u][v] + lbound[u][v]);
		}

	}
	else printf("-1\n");



	return 0;

}
