#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool visited[100][100];
int input[100][100], chk[100][100];
int N, M, maxi;
#define pii pair<int,int>

queue<pii> q;

int dx[8] = { -1,0,1,0, 1, 1,-1,-1};
int dy[8] = { 0,1,0,-1,1 ,-1,-1,1};


bool isInside(int a, int b) {
	if (a<1 || a > N || b<1 || b>M) return false;
	return true;
}


void bfs() {
	maxi = -1;
	while (!q.empty()) {
		pii here = q.front();
		q.pop();

		for (int i = 0; i < 8; ++i) {
			int nx = here.first + dx[i];
			int ny = here.second + dy[i];
			if (isInside(nx, ny) && !visited[nx][ny]) {
				q.push({ nx,ny });
				visited[nx][ny] = true;
				if(!chk[nx][ny]) chk[nx][ny] = chk[here.first][here.second] + 1;
				maxi = max(maxi, chk[nx][ny]);
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	memset(visited, 0, sizeof(visited));
	memset(chk, 0, sizeof(chk));
	memset(input, 0, sizeof(input));

	cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			cin >> input[i][j];
			if (input[i][j]) {
				q.push({ i,j });
				visited[i][j] = true;
				chk[i][j] = 0;
			}
		}
	}

	bfs();

	printf("%d", maxi);

	return 0;
}