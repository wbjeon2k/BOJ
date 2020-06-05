#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool visited[1010][1010];
char input[1010][1010];
int touch[1010][1010];

int N, M, changecnt;

#define pii pair<int,int>

int dx[8] = { 0,0,1,1,1,-1,-1,-1 };
int dy[8] = { 1,-1,1,0,-1,1,0,-1 };

bool isInside(int a, int b) {
	if (a<1 || a>N || b<1 || b>M) return false;
	return true;
}

int chk(int a, int b) {
	if (!isInside(a, b)) return 0;

	int ret = 0;
	for (int i = 0; i < 8; ++i) {
		int nx = a + dx[i], ny = b + dy[i];
		if (isInside(nx, ny) && input[nx][ny] == '.') ++ret;
	}

	return ret;
}

vector<pii> q;

int bfs() {

	int ret = 0;
	vector<pii> newq;


	while (!q.empty()) {
		++ret;
		for (int i = 0; i < q.size(); ++i) {
			int x = q[i].first, y = q[i].second;
			input[x][y] = '.';
			visited[x][y] = true;
		}

		for (int i = 0; i < q.size(); ++i) {
			int x = q[i].first, y = q[i].second;
			for (int i = 0; i < 8; ++i) {
				int nx = x + dx[i], ny = y + dy[i];
				if (isInside(nx, ny) && !visited[nx][ny] && input[nx][ny] != '.') {
					if (chk(nx, ny) >= input[nx][ny] - '0') {
						visited[nx][ny] = true;
						newq.push_back({ nx,ny });
					}
				}
			}

		}

		q = newq;
		newq.clear();
	}

	return ret;
}

int main() {
	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; ++i) {
		scanf("%s", &input[i][0] + 1);
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (input[i][j] == '.') visited[i][j] = true;
			else {
				touch[i][j] = chk(i, j);
				if (touch[i][j] >= input[i][j] - '0') q.push_back({ i,j });
			}
		}
	}

	printf("%d", bfs());

	return 0;
}
/*
//first attempt. TLE
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool visited[1010][1010];
char input[1010][1010];
int touch[1010][1010];

int N, M, changecnt;

#define pii pair<int,int>

int dx[8] = { 0,0,1,1,1,-1,-1,-1 };
int dy[8] = { 1,-1,1,0,-1,1,0,-1 };

bool isInside(int a, int b) {
	if (a<1 || a>N || b<1 || b>M) return false;
	return true;
}

int bfs(int a, int b) {

	memset(touch, 0, sizeof(touch));
	changecnt = 0;

	queue<pii> q;

	q.push({ a,b });
	visited[a][b] = true;

	while (!q.empty()) {
		int x = q.front().first, y = q.front().second;

		q.pop();

		for (int i = 0; i < 8; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			if (isInside(nx, ny) && input[nx][ny] == '.' && !visited[nx][ny]) {
				visited[nx][ny] = true;
				q.push({ nx,ny });
			}
			if (isInside(nx, ny) && input[nx][ny] != '.') {
				touch[nx][ny]++;
				if (touch[nx][ny] >= input[nx][ny] - '0') {
					visited[nx][ny] = true;
					++changecnt;
					input[nx][ny] = '.';
				}
			}
		}
	}

	return changecnt;
}

int main() {

	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; ++i) {
		scanf("%s", &input[i][0] + 1);
	}

	int cnt = 0;
	int loopcnt = 0;
	while (1) {
		int tcnt = 0;

		memset(visited, 0, sizeof(visited));
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= M; ++j) {
				if (input[i][j] == '.' && !visited[i][j]) {
					tcnt += bfs(i, j);
					++loopcnt;
				}
			}
		}

		printf("loop %d\n", loopcnt);

		if (tcnt == 0) break;
		++cnt;
	}

	printf("%d", cnt);

	return 0;
}
*/