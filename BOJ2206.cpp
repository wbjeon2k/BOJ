#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct tup {
	int x, y, col;
};

int dist[1010][1010][2];
int input[1010][1010];
int N, M;


bool isInside(int a, int b) {
	if (a<1 || a>N || b<1 || b>M) return false;
	return true;
}

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

void bfs() {
	queue<tup> q;
	q.push({ 1,1,0 });
	dist[1][1][0] = 1;

	while (!q.empty()) {
		tup here = q.front();
		q.pop();
		int x = here.x, y = here.y, col = here.col;

		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			if (isInside(nx, ny)) {
				if (col == 0 && input[nx][ny] == 0) {
					if(dist[nx][ny][0]> dist[x][y][0] + 1) q.push({ nx,ny,0 });
					dist[nx][ny][0] = min(dist[nx][ny][0], dist[x][y][0] + 1);
				}
				if (col == 0 && input[nx][ny] == 1) {
					if (dist[nx][ny][1] > dist[x][y][0] + 1) q.push({ nx,ny,1 });
					dist[nx][ny][1] = min(dist[nx][ny][1], dist[x][y][0] + 1);
				}
				if (col == 1 && input[nx][ny] == 0) {
					if (dist[nx][ny][1] > dist[x][y][1] + 1) q.push({ nx,ny,1 });
					dist[nx][ny][1] = min(dist[nx][ny][1], dist[x][y][1] + 1);
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	fill(&dist[0][0][0], &dist[0][0][0] + 1010 * 1010 * 2, 123456789);
	memset(input, 0, sizeof(input));

	for (int i = 1; i <= N; ++i) {
		string s;
		cin >> s;
		for (int j = 1; j <= M; ++j) {
			input[i][j] = s[j - 1] - '0';
		}
	}

	bfs();

	int ans = min(dist[N][M][0], dist[N][M][1]);
	if (ans == 123456789) printf("-1");
	else printf("%d", ans);

	return 0;
}