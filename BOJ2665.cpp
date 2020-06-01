#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int visited[55][55];
int input[100][100];

int N;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

struct tup {
	int x, y, col;
};

bool isInside(int a, int b) {
	if (a<1 || a>N || b<1 || b>N) return false;
	return true;
}

void bfs() {
	queue<tup> q;
	q.push({ 1,1,0 });

	while (!q.empty()) {
		tup here = q.front();
		q.pop();

		int x = here.x, y = here.y, col = here.col;

		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			if (isInside(nx, ny)) {
				if (input[nx][ny]==0 && visited[nx][ny] > col + 1) {
					visited[nx][ny] = col+1;
					q.push({ nx,ny,col + 1 });
				}
				if (input[nx][ny]==1 && visited[nx][ny] > col) {
					visited[nx][ny] = col;
					q.push({ nx,ny,col });
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

	memset(input, 0, sizeof(input));
	
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		string s;
		cin >> s;
		for (int j = 1; j <= N; ++j) {
			input[i][j] = s[j - 1] - '0';
			visited[i][j] = INT_MAX;
		}
	}

	bfs();

	printf("%d", visited[N][N]);

	return 0;
}