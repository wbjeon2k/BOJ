#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 2020
#define pii pair<int,int>

int years[Msize][Msize];
int ancestor[Msize][Msize];
int input[Msize][Msize];
bool visited[Msize][Msize];
queue<pii> q;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

int N, K;

struct disjointSet {
	vector<int> parent;
	vector<int> rank;
	vector<int> size;

	disjointSet() {
		parent.resize(Msize * Msize);
		rank.resize(Msize * Msize, 1);
		size.resize(Msize * Msize, 1);
		for (int i = 0; i < Msize * Msize; ++i) {
			parent[i] = i;
		}
	}

	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}

	bool merge(int u, int v) {
		u = find(u);
		v = find(v);

		if (u == v) return false;

		if (rank[u] > rank[v]) swap(u, v);

		size[u] += size[v];
		size[v] = 1;
		parent[v] = u;
		if (rank[v] == rank[u]) ++rank[v];
		return true;
	}

	int setsize(int u) {
		return size[find(u)];
	}
};

disjointSet DJS;

bool isinside(int a, int b) {
	if (a<1 || a>N || b<1 || b>N) return false;
	return true;
}

void bfs() {

	int cnt = 0;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		visited[x][y] = true;
		q.pop();

		int ans = 0;
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (isinside(nx, ny) && visited[nx][ny] && years[nx][ny] <= years[x][y]) {
				DJS.merge(ancestor[x][y], ancestor[nx][ny]);
			}
			else if (isinside(nx, ny) && !visited[nx][ny]) {
				years[nx][ny] = years[x][y] + 1;
				ancestor[nx][ny] = ancestor[x][y];
				q.push({ nx, ny });
				visited[nx][ny] = true;
			}
			
		}
		if (DJS.setsize(ancestor[x][y]) == K) {
			//printf("%d %d\n", x, y);
			printf("%d\n", years[x][y]);
			return;
		}
	}
}




int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	memset(visited, 0, sizeof(visited));
	memset(ancestor, 0, sizeof(ancestor));
	memset(input, 0, sizeof(input));
	memset(years, 0, sizeof(years));

	//ifstream cin;
	//cin.open("input.txt");

	cin >> N >> K;

	for (int i = 1; i <= K; ++i) {
		int a, b;
		cin >> a >> b;
		input[a][b] = 1;
		q.push({ a,b });
		visited[a][b] = true;
		ancestor[a][b] = i;
	}

	bfs();
	
	/*for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			printf("%d ", years[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	*/

	return 0;
}

/*

//kajebii's solution.
// dx dy 사방을 이렇게 돌 수도 있다. 클라스...
//for(int k=0; k<4; k++) {
	int nx = x + "1012"[k] - '1', ny = y + "0121"[k] - '1';
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

#define SZ(v) ((int)(v).size())
#define ALL(v) (v).begin(),(v).end()
#define one first
#define two second
typedef long long ll;
typedef pair<int, int> pi; typedef pair<ll, int> pli; typedef pair<ll, pi> plp;
typedef tuple<int, int, int> ti; typedef tuple<ll, int, int> tli;
const int INF = 0x3f2f1f0f;
const ll LINF = 1ll * INF * INF;

const int MAX_N = 2e3 + 100, MAX_K = 1e5 + 100;

int N, K, UNF[MAX_K], Vis[MAX_N * MAX_N], Mp[MAX_N * MAX_N];
int F(int v) { return UNF[v] == v ? v : UNF[v] = F(UNF[v]); }
int U(int a, int b) {
	a = F(a); b = F(b);
	UNF[a] = b;
	return a != b;
}
int main() {
	cin >> N >> K;
	for(int i=1; i<=K; i++) UNF[i] = i;
	for(int i=0; i<N*N; i++) Vis[i] = INF;
	vector<pi> nr;
	for(int i=1; i<=K; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--; y--;
		nr.push_back(pi(x, y));
	}
	sort(ALL(nr));
	queue<pi> Q;
	for(int i=0; i<K; i++) {
		int x, y; tie(x, y) = nr[i];
		Q.push(pi(x, y));
		Vis[x*N+y] = 1;
		Mp[x*N+y] = i+1;
	}
	int cnt = K;
	for(int q=1; ; q++) {
		while(!Q.empty()) {
			int x, y; tie(x, y) = Q.front();
			int p = x*N+y;
//			printf("%d %d\n", x, y);
			if(Vis[p] != q) break; Q.pop();
			for(int k=0; k<4; k++) {
				int nx = x + "1012"[k] - '1', ny = y + "0121"[k] - '1';
				int pp = nx * N + ny;
				if(nx<0 || ny<0 || nx>=N || ny>=N) continue;
				if(Vis[pp] <= q) {
					cnt -= U(Mp[p], Mp[pp]);
				} else if(Vis[pp] == INF) {
					Vis[pp] = q+1;
					Mp[pp] = Mp[p];
					Q.push(pi(nx, ny));
				}
			}
		}
		if(cnt == 1) {
			printf("%d\n", q-1);
			return 0;
		}
	}
	return 0;
}
*/