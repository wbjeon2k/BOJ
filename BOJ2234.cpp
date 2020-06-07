#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, M;
bool visited[55][55];
int input[55][55];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

#define pii pair<int,int>

struct tup {
	int x, y, wall;
};

struct disjointSet {

	pii parent[55][55];
	int size[55][55], rank[55][55];

	disjointSet() {
		for (int i = 0; i < 55; ++i) {
			for (int j = 0; j < 55; ++j) {
				parent[i][j] = { i,j };
				size[i][j] = 1;
				rank[i][j] = 1;
			}
		}
	}

	void unite(pii u, pii v) {
		pii a = find(u);
		pii b = find(v);

		if (a == b) return;

		int ax = a.first, ay = a.second, bx = b.first, by = b.second;
		if (rank[ax][ay] > rank[bx][by]) {
			swap(ax, bx); swap(ay, by);
		}

		size[ax][ay] += size[bx][by];
		size[bx][by] = 1;
		parent[bx][by] = { ax,ay };
		if (rank[ax][ay] == rank[bx][by]) ++rank[bx][by];

		return;
	}

	pii find(pii u) {
		int x = u.first, y = u.second;
		if (parent[x][y] == u) return {x,y};
		return parent[x][y] = find(parent[x][y]);
	}

	int setsize(pii a) {
		pii p = find(a);
		return size[p.first][p.second];
	}

};

disjointSet DJS;

void bfs(int w, int a, int b) {
	queue<tup> q;
	q.push({ a,b,w });
	visited[a][b] = true;

	while (!q.empty()) {
		tup here = q.front();
		q.pop();
		int x = here.x, y = here.y, wall = here.wall;

		//printf("x%d y%d\n", x, y);

		if (wall % 2 == 0) {
			int nx = x, ny = y-1;
			if (!visited[nx][ny]) {
				q.push({ nx,ny,input[nx][ny] });
				DJS.unite({ x,y }, { nx,ny });
				visited[nx][ny] = true;
			}
		}
		wall = wall >> 1;
		if (wall % 2 == 0) {
			int nx = x-1, ny = y;
			if (!visited[nx][ny]) {
				q.push({ nx,ny,input[nx][ny] });
				DJS.unite({ x,y }, { nx,ny });
				visited[nx][ny] = true;
			}
		}
		wall = wall >> 1;
		if (wall % 2 == 0) {
			int nx = x, ny = y + 1;
			if (!visited[nx][ny]) {
				q.push({ nx,ny,input[nx][ny] });
				DJS.unite({ x,y }, { nx,ny });
				visited[nx][ny] = true;
			}
		}
		wall = wall >> 1;
		if (wall % 2 == 0) {
			int nx = x +1, ny = y;
			if (!visited[nx][ny]) {
				q.push({ nx,ny,input[nx][ny] });
				DJS.unite({ x,y }, { nx,ny });
				visited[nx][ny] = true;
			}
		}
	}
}

bool isInside(int a, int b) {
	if (a<1 || a>N || b<1 || b>M) return false;
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> M >> N;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			cin >> input[i][j];
		}
	}

	int bfscnt = 0;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (!visited[i][j]) {
				bfs(input[i][j], i, j);
				++bfscnt;
			}
		}
	}

	int maxsize = -1;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			maxsize = max(maxsize, DJS.setsize({ i,j }));
		}
	}

	int maxunite = -1;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			int x = i, y = j;
			int mchk = -1;
			for (int k = 0; k < 4; ++k) {
				int nx = x + dx[k], ny = y + dy[k];
				if (isInside(nx,ny) && DJS.find({ nx,ny }) != DJS.find({ x,y })) {
					mchk = max(mchk, DJS.setsize({ nx,ny }));
				}
			}
			if (mchk != -1) {
				maxunite = max(maxunite, DJS.setsize({ x,y }) + mchk);
			}
		}
	}

	printf("%d\n%d\n%d\n", bfscnt, maxsize, maxunite);

	return 0;

}