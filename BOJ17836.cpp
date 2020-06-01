#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

bool visited[111][111];
int input[111][111];
int timechk[111][111];
int N, M, T;

bool isInside(int a, int b) {
	if (a < 1 || a > N || b < 1 || b > M) return false;
	return true;
}

int bfs() {

	visited[1][1] = true;
	queue<pii> q;
	q.push({ 1,1 });

	pii swordloc = { -1,-1 };
	timechk[1][1] = 0;
	timechk[N][M] = INT_MAX;

	while (!q.empty()) {
		pii here = q.front();
		q.pop();
		
		for (int i = 0; i < 4; ++i) {
			int nx = here.first + dx[i];
			int ny = here.second + dy[i];
			if (isInside(nx, ny) && !visited[nx][ny]) {
				q.push({ nx,ny });
				visited[nx][ny] = true;
				timechk[nx][ny] = timechk[here.first][here.second] + 1;
				if (input[nx][ny] == 2) swordloc = { nx,ny };
			}
		}
	}

	int ans = INT_MAX;
	if (swordloc != make_pair(-1,-1)) {
		int sx = swordloc.first, sy = swordloc.second;
		ans = timechk[sx][sy] + (N - sx) + (M - sy);
	}
	ans = min(ans, timechk[N][M]);
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	//ifstream cin;
	//cin.open("input.txt");

	memset(visited, 0, sizeof(visited));
	memset(input, 0, sizeof(input));
	memset(timechk, -1, sizeof(timechk));

	cin >> N >> M >> T;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			cin >> input[i][j];
			if (input[i][j] == 1) visited[i][j] = true;
		}
	}

	int ans = bfs();

	if (ans > T) {
		printf("Fail");
	}
	else {
		printf("%d", ans);
	}

	return 0;
}