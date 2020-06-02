#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool visited[111][111];
int input[111][111];
int chk[111][111];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int N, M;
#define pii pair<int,int>

bool isInside(int a, int b) {
	if (a<1 || a>N || b<1 || b>M) return false;
	return true;
}

int bfs() {
	memset(visited, 0, sizeof(visited));
	memset(chk, 0, sizeof(chk));

	int count0 = 1;
	queue<pii> q;
	q.push({ 1,1 });
	visited[1][1] = true;

	while (!q.empty()) {
		int x = q.front().first, y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			//printf("nx%d ny%d\n", nx, ny);
			if (isInside(nx, ny)){

				if (input[nx][ny] == 0 && !visited[nx][ny]) {
					visited[nx][ny] = true;
					++count0;
					q.push({ nx,ny });
				}
				if (input[nx][ny] == 1) {
					++chk[nx][ny];
				}
				if (chk[nx][ny] >= 2) {
					visited[nx][ny] = true;
					input[nx][ny] = 0;
				}
			}
		}
	}

	return count0;
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

	int cnt = 0;
	while (1) {
		int t = bfs();
		
		//printf("%d\n", t);
		if (t == N * M)  break;
		++cnt;
	}

	printf("%d", cnt);

	return 0;
}