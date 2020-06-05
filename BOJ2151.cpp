#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct tup {
	int x, y, dir;
};

pair<int, int> sloc, eloc;
int N, M;
int cache[111][111][10];
int input[111][111];
#define Mnum 12346789

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int dircode[4] = { 1,2,3,4 };

bool isInside(int a, int b) {
	if (a<1 || a>N || b<1 || b>N) return false;
	return true;
}

bool dirchk(int a, int b) {
	if (a < 1) return true;

	if (a%2) {
		//1,3
		if (b % 2 == 0) return true;
		else return false;
	}
	else {
		//2,4
		if (b % 2) return true;
		else return false;
	}
}

void bfs() {
	queue<tup> q;
	q.push({ sloc.first, sloc.second, 1 });
	q.push({ sloc.first, sloc.second, 2 });
	q.push({ sloc.first, sloc.second, 3 });
	q.push({ sloc.first, sloc.second, 4 });
	cache[sloc.first][sloc.second][1] = 0;
	cache[sloc.first][sloc.second][2] = 0;
	cache[sloc.first][sloc.second][3] = 0;
	cache[sloc.first][sloc.second][4] = 0;

	while (!q.empty()) {
		tup here = q.front();
		int x = here.x, y = here.y, dir = here.dir;
		q.pop();

		if (input[x][y] == '.') {
			int nx = x + dx[dir - 1], ny = y + dy[dir - 1];
			if (isInside(nx, ny) && input[nx][ny] != '*' && cache[nx][ny][dir] > cache[x][y][dir]) {
				q.push({ nx,ny,dir });
				cache[nx][ny][dir] = cache[x][y][dir];
			}
		}
		if (input[x][y] == '!') {
			for (int i = 0; i < 4; ++i) {
				int nx = x + dx[i], ny = y + dy[i], ndir = dircode[i];
				if (isInside(nx, ny) && input[nx][ny] != '*' && dirchk(dir, ndir)) {
					if (cache[nx][ny][ndir] > cache[x][y][dir] + 1) {
						q.push({ nx,ny,ndir });
						cache[nx][ny][ndir] = cache[x][y][dir] + 1;
					}
				}
				if (isInside(nx, ny) && input[nx][ny] != '*' && dir == ndir) {
					if (cache[nx][ny][ndir] > cache[x][y][dir]) {
						q.push({ nx,ny,ndir });
						cache[nx][ny][ndir] = cache[x][y][dir];
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

	cin >> N;
	int locnt = 0;
	for (int i = 1; i <= N; ++i) {
		string s;
		cin >> s;
		for (int j = 1; j <= N; ++j) {
			input[i][j] = s[j - 1];
			if (s[j - 1] == '#' && locnt == 0) {
				sloc.first = i; sloc.second = j;
				locnt++;
				input[i][j] = '.';
			}
			if (s[j - 1] == '#' && locnt > 0) {
				eloc.first = i; eloc.second = j;
				input[i][j] = '.';
			}
		}
	}

	fill(&cache[0][0][0], &cache[0][0][0] + 111 * 111 * 10, Mnum);

	bfs();

	int ans = Mnum;
	for (int i = 1; i < 10; ++i) {
		ans = min(ans, cache[eloc.first][eloc.second][i]);
	}

	printf("%d", ans);

	return 0;

}