//BOJ13161

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 505
#define INF INT_MAX/2

ll sad[MAXI][MAXI], capacity[MAXI][MAXI], flow[MAXI][MAXI];
ll group[MAXI];

vector<int> adjlist[MAXI], level, see;

int N, M;
ll mcost, mflow;
int source, sink;

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


//bf: block flow
int dfs(int here, int bf) {
	if (here == sink) return bf;

	for (; see[here] < adjlist[here].size(); see[here]++) {
		int there = adjlist[here][see[here]];
		if (level[there] == level[here] + 1 && capacity[here][there] - flow[here][there] > 0) {
			int nflow = dfs(there, min((ll)bf, capacity[here][there] - flow[here][there]));
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
			int blockflow = dfs(source, INF);
			if (blockflow == 0) break;
			if (blockflow == INF) continue;
			mflow += blockflow;
		}
	}

}

set<int> cut;

void findcut() {
	queue<int> q;
	q.push(source);
	vector<bool>visited(MAXI, 0);
	visited[source] = 1;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		cut.insert(here);
		visited[here] = true;

		for (int i = 0; i < adjlist[here].size(); ++i) {
			int there = adjlist[here][i];
			if (visited[there]) continue;
			if (capacity[here][there] - flow[here][there] <= 0) continue;
			q.push(there);
			visited[there] = true;
		}
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	source = 0, sink = MAXI - 1;

	for (int i = 1; i <= N; ++i) {
		cin >> group[i];
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			cin >> capacity[i][j];
		}
	}

	for (int i = 1; i <= N; ++i) {
		if (group[i] == 1) {
			adjlist[source].push_back(i);
			adjlist[i].push_back(source);
			capacity[source][i] = INF;
		}
		if (group[i] == 2) {
			adjlist[i].push_back(sink);
			adjlist[sink].push_back(i);
			capacity[i][sink] = INF;
		}

		for (int j = 1; j <= N; ++j) {
			if (i == j) continue;
			adjlist[i].push_back(j);
			adjlist[j].push_back(i);
		}
	}

	dinic();

	printf("%lld\n", mflow);

	findcut();
	cut.erase(source);

	for (auto i = cut.begin(); i != cut.end(); ++i) {
		printf("%d ", (*i));
	}

	printf("\n");
	for (int i = 1; i <= N; ++i) {
		if (cut.find(i) == cut.end()) printf("%d ", i);
	}
	printf("\n");

	return 0;

}

