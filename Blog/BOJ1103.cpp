//BOJ1103

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 55
#define INF 123456789

int board[Msize][Msize], cache[Msize][Msize][4];
int N, M;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

bool isInside(int x, int y) {
	if (x<1 || x>N || y<1 || y>M) return false;
	else return true;
}

bool visited[Msize][Msize];

int dp(int x, int y, int dir) {
	if (!isInside(x, y)) return 0;
	if (board[x][y] == -1) return 0;
	if (visited[x][y]) return INF;

	int& ret = cache[x][y][dir];
	if (ret != -1) return ret;

	visited[x][y] = true;

	int dist = board[x][y];
	
	for (int i = 0; i < 4; ++i) {
		int tmp = 1 + dp(x + dist * dx[dir], y + dist * dy[dir], i);
		ret = max(ret, tmp);
		if (ret > INF) ret = INF;
	}

	visited[x][y] = false;
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 1; i <= N; ++i) {
		string s;
		cin >> s;
		for (int j = 1; j <= M; ++j) {
			board[i][j] = s[j - 1];
			if (board[i][j] == 'H') board[i][j] = -1;
			else board[i][j] -= '0';
		}
	}
	
	int ans = -1;

	memset(cache, -1, sizeof(cache));
	memset(visited, 0, sizeof(visited));

	for (int i = 0; i < 4; ++i) {
		ans = max(ans, dp(1, 1, i));
	}

	if (ans == INF) printf("-1\n");
	else printf("%d\n", ans);

	
	return 0;
}

/*
//1st trial. WA
//BOJ1103

#define _CRT_SECURE_NO_WARNINGS
//#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define Msize 55
#define INF 123456789

int board[Msize][Msize], cache[Msize][Msize][4];
int N, M;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

bool isInside(int x, int y) {
	if (x<1 || x>N || y<1 || y>M) return false;
	else return true;
}

int dp(int x, int y, int dir) {
	if (!isInside(x, y)) return 0;

	if (board[x][y] == -1) return 0;

	int& ret = cache[x][y][dir];
	if (ret != -1) return ret;

	int dist = board[x][y];

	for (int i = 0; i < 4; ++i) {
		int tmp = 1 + dp(x + dist * dx[dir], y + dist * dy[dir], i);
		ret = max(ret, tmp);
	}

	return ret;
}


bool visited[Msize][Msize];

bool findCycle(int x, int y, int dir, int cnt) {

	if (isInside(x, y) == false) return false;
	if (board[x][y] == -1) return false;
	if (cnt > N*M) return true;

	//printf("cnt%d\n", cnt);

	visited[x][y] = true;
	int nx, ny;
	nx = x + board[x][y] * dx[dir];
	ny = y + board[x][y] * dy[dir];

	bool ret = false;
	if (!isInside(nx, ny)) return false;

	if (!visited[nx][ny]) {
		for (int i = 0; i < 4; ++i) {
			ret |= findCycle(nx, ny, i, cnt + 1);
		}
		visited[x][y] = false;
		return ret;
	}
	else {
		visited[x][y] = false;
		return true;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 1; i <= N; ++i) {
		string s;
		cin >> s;
		for (int j = 1; j <= M; ++j) {
			board[i][j] = s[j - 1];
			if (board[i][j] == 'H') board[i][j] = -1;
			else board[i][j] -= '0';
		}
	}


	bool chk = false;
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < 4; ++i) {
		chk |= findCycle(1, 1, i, 1);
	}


	if (chk) {
		printf("-1\n");
	}
	else {
		int ans = -1;
		memset(cache, -1, sizeof(cache));
		for (int k = 0; k < 4; ++k) {
			ans = max(ans, dp(1, 1, k));
		}

		printf("%d\n", ans);
	}


	return 0;
}
*/