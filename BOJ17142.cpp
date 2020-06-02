#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define  pii pair<int,int>

int N, M;
bool visited[55][55];
int input[55][55], dist[55][55];
vector<bool> permute;
vector <pii> list2;
int numberoflab = 0;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

bool isInside(int a, int b) {
	if (a<1 || a>N || b<1 || b>N) return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	memset(input, 0, sizeof(input));

	int cnt1 = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			cin >> input[i][j];
			if (input[i][j] == 2) list2.push_back({ i,j });
			if (input[i][j] == 1) ++cnt1;
		}
	}
	numberoflab = N*N - cnt1;
	//printf("numberoflab %d\n", numberoflab);

	int psize = list2.size();
	permute.resize(psize,0);
	for (int i = psize-1; i > psize-M-1; --i) permute[i] = true;

	
	int mintime = INT_MAX;
	do {
		memset(visited, 0, sizeof(visited));
		memset(dist, 0, sizeof(dist));

		queue<pii> q;
		for (int i = 0; i < psize; ++i) {
			if (permute[i]) {
				q.push(list2[i]);
				pii tmp = list2[i];
				visited[tmp.first][tmp.second] = true;
			}
		}

		int maxdist = 0;

		while (!q.empty()) {
			int x = q.front().first, y = q.front().second;
			q.pop();
			visited[x][y] = true;

			for (int i = 0; i < 4; ++i) {
				int nx = x + dx[i], ny = y + dy[i];
				if (isInside(nx,ny) && !visited[nx][ny] && input[nx][ny] != 1) {
					dist[nx][ny] = dist[x][y] + 1;
					if (input[nx][ny] == 0) maxdist = max(maxdist, dist[nx][ny]);
					visited[nx][ny] = true;
					q.push({ nx,ny });
				}
			}
		}

		int lcnt = 0;
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (input[i][j] != 1 && visited[i][j]) ++lcnt;
			}
		}

		if (lcnt == numberoflab) {
			mintime = min(mintime, maxdist);
			//printf("mintime %d\n", mintime);
		}

	} while (next_permutation(permute.begin(), permute.end()));

	if (mintime == INT_MAX) {
		printf("-1");
	}
	else {
		printf("%d", mintime);
	}

	return 0;

}