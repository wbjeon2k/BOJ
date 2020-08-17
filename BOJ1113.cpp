//BOJ1113


//https://hellogaon.tistory.com/60
//https://github.com/kks227/BOJ/blob/master/15700/15730.cpp
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pvi pair<vector<int>, int>

int board[105][105];
bool visited[105][105];
int N, M;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

#define pii pair<int,int>

int fillwater() {

	bool threshold[105][105];
	int ret = 0;
	for (int i = 1; i <= 9; ++i) {
		
		memset(threshold, 0, sizeof(threshold));

		for (int x = 1; x <= N; ++x) {
			for (int y = 1; y <= M; ++y) {
				if (board[x][y] < i) threshold[x][y] = 0;
				else threshold[x][y] = 1;
			}
		}

		queue<pii> q;
		q.push({ 0,0 });
		threshold[0][0] = true;

		while (!q.empty()) {
			pii here = q.front();
			q.pop();

			int x = here.first, y = here.second;

			threshold[x][y] = true;

			for (int d = 0; d < 4; ++d) {
				int nx = x + dx[d], ny = y + dy[d];

				if (nx < 0 || nx > N+2 || ny < 0 || ny > M+2) continue;

				if (threshold[nx][ny] == false) {
					threshold[nx][ny] = true;
					q.push({ nx,ny });
				}

			}
		}

		for (int x = 1; x <= N; ++x) {
			for (int y = 1; y <= M; ++y) {
				if (threshold[x][y] == false) ++ret;
			}
		}

	}

	return ret;

}

int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);

	cin >> N >> M;

	memset(board, 0, sizeof(board));

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%1d", &board[i][j]);
		}
	}

	int ans = fillwater();

	printf("%d\n", ans);

	return 0;
	
}

/*
//kks227's solution.
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <algorithm>
using namespace std;
const int INF = 1e9;
const int roff[4] = {-1, 1, 0, 0};
const int coff[4] = {0, 0, -1, 1};
typedef pair<int, int> P;

int main(){
	int N, M, H[102][102] = {0};
	scanf("%d %d", &N, &M);
	for(int i=1; i<=N; i++)
		for(int j=1; j<=M; j++)
			scanf("%d", &H[i][j]);
	N += 2; M += 2;

	int dist[102][102];
	for(int i=0; i<N; i++)
		fill(dist[i], dist[i]+M, INF);
	dist[0][0] = 0;
	bool visited[102][102] = {0};
	priority_queue<P, vector<P>, greater<P>> PQ;
	PQ.push(P(0, 0));
	while(!PQ.empty()){
		int r, c;
		do{
			r = PQ.top().second/1000;
			c = PQ.top().second%1000;
			PQ.pop();
		}while(!PQ.empty() && visited[r][c]);
		if(visited[r][c]) break;
		visited[r][c] = true;

		for(int d=0; d<4; d++){
			int nr = r+roff[d], nc = c+coff[d];
			if(nr<0 || nr>=N || nc<0 || nc>=M) continue;
			int nd = max(dist[r][c], H[nr][nc]);
			if(dist[nr][nc] > nd){
				dist[nr][nc] = nd;
				PQ.push(P(nd, nr*1000+nc));
			}
		}
	}

	int result = 0;
	for(int i=0; i<N; i++)
		for(int j=0; j<M; j++)
			result += dist[i][j] - H[i][j];
	printf("%d\n", result);
}

*/

/*
//1st trial. WA
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pvi pair<vector<int>, int>

int board[105][105];
bool visited[105][105];
int N, M;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

int flatten() {
	int ret = 0;
	for (int i = 2; i <= N; ++i) {
		for (int j = 2; j <= M; ++j) {
			int minH = 123456;
			bool chk = false;
			for (int k = 0; k < 4; ++k) {
				int nx, ny;
				nx = i + dx[k];
				ny = j + dy[k];
				if (board[nx][ny] <= board[i][j]) {
					chk = false;
					break;
				}
				else {
					chk = true;
					minH = min(minH, board[nx][ny]);
				}
			}

			if (chk) {
				ret += minH - board[i][j];
				board[i][j] = minH;
			}
		}
	}

	return ret;
}

#define pii pair<int,int>

vector<pii> listfill;

bool dfs(int x, int y) {
	//printf("x%d y%d\n", x, y);
	visited[x][y] = true;

	if (x == 1 || x == N || y == 1 || y == M) {
		visited[x][y] = false;
		return false;
	}

	for (int i = 0; i < 4; ++i) {
		int nx, ny;
		nx = x + dx[i];
		ny = y + dy[i];

		if (board[nx][ny] < board[x][y]) {
			visited[x][y] = false;
			return false;
		}



		if (board[nx][ny] == board[x][y] && !visited[nx][ny]) {
			if (dfs(nx, ny) == false) {
				visited[x][y] = false;
				return false;
			}
		}

	}

	listfill.push_back({ x,y });

	return true;
}

int fillwater() {
	for (int i = 0; i < listfill.size(); ++i) {
		int x = listfill[i].first, y = listfill[i].second;
		++board[x][y];
	}
	return listfill.size();
}

int dfsall() {
	memset(visited, 0, sizeof(visited));
	listfill.clear();

	int ret = 0;
	for (int i = 2; i <= N; ++i) {
		for (int j = 2; j <= M; ++j) {
			memset(visited, 0, sizeof(visited));
			listfill.clear();
			if (dfs(i, j)) {
				//printf("i%d j%d\n", i, j);
				ret += fillwater();
			}
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%1d", &board[i][j]);
		}
	}

	int ans = 0;

	ans += flatten();

	while (1) {
		int tmp = dfsall();
		if (tmp == 0) break;
		ans += tmp;
	}

	printf("%d\n", ans);

	return 0;
}



*/