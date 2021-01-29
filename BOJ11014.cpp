//BOJ11014

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define pii pair<int,int>
#define pll pair<ll,ll>
#define MAXI 82
#define cplx complex<double>
const double PI = acos(-1);
const ll INF = INT_MAX / 2;

int N, M;
int board[MAXI][MAXI];

int lmatch[MAXI * MAXI], rmatch[MAXI * MAXI], see[MAXI * MAXI], dist[MAXI * MAXI];
int mflow, source, sink;

vector<vector<int>> adjlist(MAXI* MAXI);

int dx[6] = { -1,0,1,0,1,-1 };
int dy[6] = { -1,-1,-1,1,1,1 };

inline bool isinside(int x, int y) {
	if (x<1 || x>N || y<1 || y>M) return false;
	return true;
}

inline int coordinate(int x, int y) {
	return (M * x) + y;
}

int freeseats;

bool dfs(int here) {
	for (; see[here] < adjlist[here].size(); ++see[here]) {
		int there = adjlist[here][see[here]];
		if (rmatch[there] == 0 || (dist[rmatch[there]] == dist[here] + 1 && dfs(rmatch[there]))) {
			lmatch[here] = there;
			rmatch[there] = here;
			return true;
		}
	}

	return false;
}

void hopcroftkarp() {
	mflow = 0;
	memset(lmatch, 0, sizeof(lmatch));
	memset(rmatch, 0, sizeof(rmatch));

	while (1) {
		queue<int> q;

		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				int here = coordinate(i, j);
				if (board[i][j] == 0) continue;
				if (j % 2 == 0) continue;

				if (lmatch[here] != 0) dist[here] = INF;
				else {
					dist[here] = 0;
					q.push(here);
				}
			}
		}

		memset(see, 0, sizeof(see));

		while (!q.empty()) {
			int here = q.front();
			q.pop();

			for (int i = 0; i < adjlist[here].size(); ++i) {
				int there = adjlist[here][i];
				if (rmatch[there] != 0 && dist[rmatch[there]] == INF) {
					dist[rmatch[there]] = dist[here] + 1;
					q.push(rmatch[there]);
				}
			}
		}

		int tflow = 0;
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				int here = coordinate(i, j);
				if (board[i][j] == 0) continue;
				if (j % 2 == 0) continue;

				if (lmatch[here] == 0 && dfs(here)) {
					++tflow;
				}
			}
		}
		if (tflow == 0) break;
		mflow += tflow;

	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	int t;
	cin >> t;

	while (t--) {
		cin >> N >> M;

		adjlist.clear();
		adjlist.resize(MAXI * MAXI);
		freeseats = 0;

		source = 0;
		sink = MAXI * MAXI - 1;

		string tmp;
		for (int i = 1; i <= N; ++i) {
			cin >> tmp;
			for (int j = 1; j <= M; ++j) {
				if (tmp[j - 1] == '.') {
					board[i][j] = 1;
					++freeseats;
				}
				else board[i][j] = 0;
			}
		}

		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				int here = coordinate(i, j);
				if (board[i][j] == 0) continue;

				for (int k = 0; k < 6; ++k) {
					int nx, ny, there;
					nx = i + dx[k];
					ny = j + dy[k];
					there = coordinate(nx, ny);
					if (!isinside(nx, ny)) continue;
					if (board[nx][ny] == 0) continue;

					adjlist[here].push_back(there);
				}
			}
		}

		hopcroftkarp();

		printf("%d\n", freeseats - mflow);
	}


	return 0;

}
