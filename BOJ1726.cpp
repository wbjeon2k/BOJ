#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, M;
int input[111][111];
int cache[111][111][10];
#define INF 123456789

struct tup {
	int x, y, dir;
};

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
int dircode[4] = { 1,2,3,4 };
//east, west, south, north

bool isInside(int a, int b) {
	if (a<1 || a>N || b<1 || b>M) return false;
	return true;
}


int diffarr[5][5];

int dirdiff(int a, int b) {

	if (a == 1) {
		if (b == 1) return 0;
		if (b == 2) return 2;
		if (b == 3) return 1;
		if (b == 4) return 1;
	}
	if (a == 2) {
		if (b == 1) return 2;
		if (b == 2) return 0;
		if (b == 3) return 1;
		if (b == 4) return 1;
	}
	if (a == 3) {
		if (b == 1) return 1;
		if (b == 2) return 1;
		if (b == 3) return 0;
		if (b == 4) return 2;
	}
	if (a == 4) {
		if (b == 1) return 1;
		if (b == 2) return 1;
		if (b == 3) return 2;
		if (b == 4) return 0;
	}
}

void bfs(tup start) {
	queue<tup> q;

	int sdir = start.dir;
	q.push(start);
	cache[start.x][start.y][start.dir] = 0;
	for (int i = 1; i <= 4; ++i) {
		if (sdir != i) {
			cache[start.x][start.y][i] = diffarr[sdir][i];
			q.push({ start.x, start.y, i });
		}
	}
	

	while (!q.empty()) {
		tup here = q.front();
		q.pop();
		
		int x = here.x, y = here.y, dir = here.dir;

		for (int i = 0; i < 4; ++i) {
			for (int j = 1; j <= 3; ++j) {
				int nx = x + dx[i] * j, ny = y + dy[i] * j;
				if (isInside(nx, ny)) {
					if (input[nx][ny]==1) break;
					for (int k = 0; k < 4; ++k) {
						int ndir = dircode[k];
						int tmp = cache[x][y][dir] + 1 + diffarr[dir][i+1] + diffarr[i+1][ndir];
						if (tmp < cache[nx][ny][ndir]) {
							cache[nx][ny][ndir] = tmp;
							q.push({ nx,ny,ndir });
						}
					}
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

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			cin >> input[i][j];
		}
	}

	for (int i = 1; i <= 4; ++i) {
		for (int j = 1; j <= 4; ++j) {
			diffarr[i][j] = dirdiff(i, j);
		}
	}

	tup sloc, eloc;
	int a, b, c;
	cin >> a >> b >> c;
	sloc = { a,b,c };
	cin >> a >> b >> c;
	eloc = { a,b,c };

	fill(&cache[0][0][0], &cache[0][0][0] + 111 * 111 * 10, INF);

	bfs(sloc);

	int ex, ey, edir;
	ex = eloc.x; ey = eloc.y; edir = eloc.dir;
	printf("%d\n", cache[ex][ey][edir]);

	return 0;
}

/*
//rebas's solution.
#include <cstdio>
#include <queue>
using namespace std;

struct robot {
	int x, y, d;
};

int n, m;
int sx, sy, sd, ex, ey, ed;
int a[100][100];
int dist[100][100][4];
const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

void bfs() {
	queue<robot> q;
	q.push({sx-1, sy-1, sd-1});
	while (!q.empty()) {
		int x = q.front().x, y = q.front().y, d = q.front().d; q.pop();
		if (x == ex-1 && y == ey-1 && d == ed-1) {
			printf("%d\n", dist[x][y][d]);
			return;
		}
		for (int i=1; i<=3; i++) {
			int nx = x+dx[d]*i, ny = y+dy[d]*i;
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) break;
			if (a[nx][ny]) break;           // Cannot pass the wall.
			if (dist[nx][ny][d]) continue;  // Already visited.
			q.push({nx, ny, d});
			dist[nx][ny][d] = dist[x][y][d]+1;
		}
		for (int i=0; i<4; i++) {
			 if (i == d) continue;  // Same direction.
			 int k = (i+d)%4 == 1 ? 2 : 1;  // Check rotation. 180 degree (+2), 90 degree (+1)
			 if (dist[x][y][i]) continue;   // Already visited.
			 q.push({x, y, i});
			 dist[x][y][i] = dist[x][y][d]+k;
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	scanf("%d %d %d", &sx, &sy, &sd);
	scanf("%d %d %d", &ex, &ey, &ed);
	bfs();
	return 0;
}


출처: https://rebas.kr/742 [PROJECT REBAS]
*/