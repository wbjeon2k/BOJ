#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool visited[1010][1010];
int dist[1010][1010][2], input[1010][1010];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

int N, M;

#define pii pair<int,int>
pii sloc, eloc;

struct tup {
	int x, y, col;
};

bool isInside(int a, int b) {
	if (a<1 || a>N || b<1 || b>M) return false;
	return true;
}

void bfs() {
	queue<tup> q;
	q.push({ sloc.first, sloc.second, 0 });

	dist[sloc.first][sloc.second][0] = 0;

	while (!q.empty()) {
		int x = q.front().x, y = q.front().y, col = q.front().col;
		//printf("%d %d %d\n", x, y, col);
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			if (isInside(nx, ny) && col==1) {
				if (input[nx][ny] == 0) {
					if (dist[x][y][1] + 1 < dist[nx][ny][1]) q.push({ nx,ny,1 });
					dist[nx][ny][1] = min(dist[nx][ny][1], dist[x][y][1] + 1);
				}
			}
			if (isInside(nx, ny) && col == 0) {
				if (input[nx][ny] == 1) {
					if (dist[x][y][0] + 1 < dist[nx][ny][1]) q.push({ nx,ny,1 });
					dist[nx][ny][1] = min(dist[nx][ny][1], dist[x][y][0] + 1);
				}
				if (input[nx][ny] == 0) {
					if (dist[x][y][0] + 1 < dist[nx][ny][0]) q.push({ nx,ny,0 });
					dist[nx][ny][0] = min(dist[nx][ny][0], dist[x][y][0] + 1);
				}
			}
		}
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> N >> M;

	int a, b;
	cin >> a >> b;
	sloc = { a,b };
	cin >> a >> b;
	eloc = { a,b };

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			cin >> input[i][j];
			if (input[i][j]) visited[i][j] = true;
		}
	}

	fill(&dist[0][0][0], &dist[0][0][0] + 1010 * 1010 * 2, 123456789);

	bfs();

	int endx = eloc.first, endy = eloc.second;
	int ans = min(dist[endx][endy][0], dist[endx][endy][1]);
	if (ans == 123456789) {
		printf("-1");
	}
	else printf("%d", ans);

	return 0;
}