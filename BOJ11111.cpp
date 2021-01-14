//BOJ11111

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 3300

int N, M;

vector<int> adjlist[MAXI];
ll dist[MAXI][MAXI], flow[MAXI][MAXI], capacity[MAXI][MAXI];

ll mcost, mflow;

int source, sink;
int board[55][55];
int value[6][6] = { {0,0,0,0,0,0},{0,10,8,7,5,1},{0,8,6,4,3,1},{0,7,4,3,2,1},{0,5,3,2,2,1},{0,1,1,1,1,0} };
//{i,j} = 55*i + j;


int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

//x,y: x행 y열
bool isinside(const int& x, const int& y) {
	if (x<1 || x>M || y<1 || y>N) return false;
	return true;
}

inline int getnode(const int& x, const int& y) {
	return (55 * x) + y;
}

void mcmf() {
	mcost = mflow = 0;

	while (1) {
		int parent[MAXI], upper[MAXI];
		bool isinq[MAXI] = { 0, };

		memset(parent, -1, sizeof(parent));
		fill(upper, upper + MAXI, INT_MAX / 2);

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
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);

	scanf("%d %d", &M, &N);

	memset(dist, 0, sizeof(dist));
	memset(capacity, 0, sizeof(capacity));
	memset(flow, 0, sizeof(flow));


	//get input
	for (int i = 1; i <= M; ++i) {
		char buf[55];
		scanf("%s", &buf);
		for (int j = 0; j < N; ++j) {
			buf[j] -= 'A';
			if (buf[j] > 4) buf[j] = 4;
			board[i][j + 1] = buf[j] + 1;
		}
	}

	source = 0, sink = MAXI - 1;

	for (int i = 1; i <= M; ++i) {
		for (int j = 1; j <= N; ++j) {
			int node = getnode(i, j);

			adjlist[node].push_back(sink);
			adjlist[sink].push_back(node);
			capacity[node][sink] = 1;

			int here = board[i][j];

			if ((i + j) % 2 == 0) {
				adjlist[source].push_back(node);
				adjlist[node].push_back(source);
				capacity[source][node] = 1;
				//dist=0,backward=0;

				int nx, ny;
				for (int k = 0; k < 4; ++k) {
					nx = i + dx[k];
					ny = j + dy[k];
					if (!isinside(nx, ny)) continue;

					int next = getnode(nx, ny);
					int there = board[nx][ny];

					adjlist[node].push_back(next);
					capacity[node][next] = 1;
					dist[node][next] = -value[here][there];

					adjlist[next].push_back(node);
					dist[next][node] = -dist[node][next];
				}
			}
		}
	}

	mcmf();

	printf("%lld\n", -mcost);

	return 0;

}
