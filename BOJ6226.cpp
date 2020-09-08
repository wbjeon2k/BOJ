//BOJ 6226 

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 33
#define pii pair<int,int>
#define ll long long

int board[Msize][Msize];
bool chk[Msize][Msize];
pii pred[Msize][Msize];
int dist[Msize][Msize];
int N, M;
pii spoint, epoint;

int dx[8] = { -2,-2,-1,1,2,2,1,-1 };
int dy[8] = { -1,1,2,2,1,-1,-2,-2 };

bool isInside(int x, int y) {
	if (x<1 || x>N || y<1 || y>M) return false;
	else return true;
}


struct node {
	int putpad, distpad;
	ll numbers;

	node() {
		putpad = -1;
		distpad = -1;
		numbers = 0;
	}
};

node cache[Msize][Msize];
queue<pii> q;

void updatecache(int nputpad, int nx, int ny, int x, int y) {

	if (cache[nx][ny].putpad == -1 || nputpad < cache[nx][ny].putpad) {
		cache[nx][ny].putpad = nputpad;
		cache[nx][ny].distpad = cache[x][y].distpad + 1;
		cache[nx][ny].numbers = cache[x][y].numbers;

		if(!chk[nx][ny]){
			chk[nx][ny] = true;
			q.push({ nx,ny });
		}
		return;
	}

	if (cache[nx][ny].putpad != -1 && nputpad == cache[nx][ny].putpad && cache[nx][ny].distpad > cache[x][y].distpad + 1) {
		cache[nx][ny].distpad = cache[x][y].distpad + 1;
		cache[nx][ny].numbers = cache[x][y].numbers;

		if (!chk[nx][ny]) {
			chk[nx][ny] = true;
			q.push({ nx,ny });
		}
		return;
	}

	if (cache[nx][ny].putpad != -1 && nputpad == cache[nx][ny].putpad && cache[nx][ny].distpad == (cache[x][y].distpad + 1)) {
		cache[nx][ny].numbers += cache[x][y].numbers;
		return;
	}
}

void bfs() {
	int x, y;
	x = spoint.first, y = spoint.second;

	cache[x][y].distpad = 0;
	cache[x][y].putpad = 0;
	cache[x][y].numbers = 1;
	
	
	q.push(spoint);

	while (!q.empty()) {
		int x, y;
		x = q.front().first, y = q.front().second;
		q.pop();

		chk[x][y] = true;

		for (int i = 0; i < 8; ++i) {
			int nx, ny;
			nx = x + dx[i], ny = y + dy[i];

			if (!isInside(nx, ny)) continue;
			if (board[nx][ny] == 2) continue;
			//if (chk[nx][ny]) continue;

			int nputpad = cache[x][y].putpad + (board[nx][ny] == 1 ? 0 : 1);
			updatecache(nputpad, nx, ny, x, y);
		}

		chk[x][y] = false;
	}

}



void debug() {

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			printf("%3d ", cache[i][j].distpad);
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			printf("%3d ", cache[i][j].putpad);
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			printf("%3lld ", cache[i][j].numbers);
		}
		printf("\n");
	}
}

int main() {
	cin >> N >> M;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			cin >> board[i][j];
			if (board[i][j] == 3) {
				spoint = { i,j };
				board[i][j] = 1;
			}
			if (board[i][j] == 4) {
				board[i][j] = 1;
				epoint = { i,j };
			}
		}
	}

	memset(chk, 0, sizeof(chk));

	bfs();

	//debug();
	
	if (cache[epoint.first][epoint.second].distpad == -1) printf("-1\n");
	else {
		printf("%d\n", cache[epoint.first][epoint.second].putpad);
		printf("%d\n", cache[epoint.first][epoint.second].distpad);
		printf("%lld\n", cache[epoint.first][epoint.second].numbers);
	}
	return 0;
}

/*

//	xiaowuc1's solution. using dp
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

using namespace std;

// BEGIN NO SAD
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef vector<int> vi;
// END NO SAD

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<vector<ll>> matrix;
typedef pair<ll, ll> pll;

int g[30][30];
int dp[30][30][900]; // [row][col][num lilypads] -> min dist needed
ll numw[30][30][900];
int dx[8]{-2,-2,-1,-1,1,1,2,2};
int dy[8]{-1,1,-2,2,-2,2,-1,1};

typedef pair<pii, int> state; // <row, col> pad

void solve() {
  int r, c;
  cin >> r >> c;
  memset(dp, 1, sizeof(dp));
  queue<state> q;
  int ex, ey;
  for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) {
	cin >> g[i][j];
	if(g[i][j] == 3) {
	  dp[i][j][0] = 0;
	  numw[i][j][0] = 1;
	  q.push(state({i, j}, 0));
	}
	if(g[i][j] == 4) {
	  ex = i;
	  ey = j;
	}
  }
  while(sz(q)) {
	state curr = q.front(); q.pop();
	int x, y, pads;
	x = curr.first.first;
	y = curr.first.second;
	pads = curr.second;
	if(dp[x][y][pads] >= 900) break;
	if(g[x][y] == 4) {
	  continue;
	}
	for(int k = 0; k < 8; k++) {
	  int nx = x + dx[k];
	  int ny = y + dy[k];
	  if(nx < 0 || nx >= r || ny < 0 || ny >= c || g[nx][ny] == 2) continue;
	  int npads = pads;
	  if(g[nx][ny] == 0) npads++;
	  if(dp[nx][ny][npads] > 1 + dp[x][y][pads]) {
		dp[nx][ny][npads] = 1 + dp[x][y][pads];
		numw[nx][ny][npads] = 0;
		q.push(state({nx, ny}, npads));
	  }
	  if(dp[nx][ny][npads] == 1 + dp[x][y][pads]) {
		numw[nx][ny][npads] += numw[x][y][pads];
	  }
	}
  }
  for(int i = 0; i <= 899; i++) {
	if(dp[ex][ey][i] < 900) {
	  cout << i << "\n";
	  cout << dp[ex][ey][i] << "\n";
	  cout << numw[ex][ey][i] << "\n";
	  return;
	}
  }
  cout << "-1\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  solve();
}
*/