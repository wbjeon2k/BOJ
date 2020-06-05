#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct tup {
	int x, y, dir;
};

pair<int, int> sloc, eloc;
int N, M;
int cache[111][111][222];
int input[111][111];
#define Mnum 12346789

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int dircode[4] = { 1,2,3,4 };

bool isInside(int a, int b) {
	if (a<1 || a>N || b<1 || b>M) return false;
	return true;
}

void bfs() {
	queue<tup> q;
	q.push({ sloc.first, sloc.second, 0});
	cache[sloc.first][sloc.second][0] = 0;

	while (!q.empty()) {
		tup here = q.front();
		int x = here.x, y = here.y, dir = here.dir;
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i], ndir = dircode[i];

			if (isInside(nx, ny) && input[nx][ny] != 1) {
				if (dir!= ndir && cache[nx][ny][ndir] > cache[x][y][dir] + 1) {
					q.push({ nx,ny,ndir });
					cache[nx][ny][ndir] = cache[x][y][dir] + 1;
				}
				if (dir == ndir && cache[nx][ny][ndir] > cache[x][y][dir]) {
					q.push({ nx,ny,ndir });
					cache[nx][ny][ndir] = cache[x][y][dir];
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream cin;
	cin.open("input.txt");

	cin >> M >> N;
	int locnt = 0;
	for (int i = 1; i <= N; ++i) {
		string s;
		cin >> s;
		for (int j = 1; j <= M; ++j) {
			if (s[j - 1] == '.') {
				input[i][j] = 0;
			}
			if (s[j - 1] == '*') {
				input[i][j] = 1;
			}
			if (s[j - 1] == 'C' && locnt == 0) {
				sloc.first = i;
				sloc.second = j;
				++locnt;
				input[i][j] = 0;
			}
			if (s[j - 1] == 'C' && locnt > 0) {
				eloc.first = i;
				eloc.second = j;
				input[i][j] = 0;
			}
		}
	}

	fill(&cache[0][0][0], &cache[0][0][0] + 111 * 111 * 222, Mnum);

	bfs();

	//if (isInside(3, 4)) printf("true\n");

	int ans = Mnum;
	for (int i = 1; i < 222; ++i) {
		ans = min(ans, cache[eloc.first][eloc.second][i]);
	}

	printf("%d", ans-1);

	return 0;

}