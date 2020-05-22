#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>

int input[1010][1010];
int cluster[1010][1010];
bool visited[1010][1010];
vector<int> clist;

int N, M;

bool isinside(int a, int b) {
	if (a<1 || a>N) return false;
	if (b<1 || b>M) return false;
	return true;
}

int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

int dfs(int a, int b, int c) {
	cluster[a][b] = c;
	visited[a][b] = true;
	int ret = 1;

	for (int i = 0; i < 4; ++i) {
		int nx = a + dx[i];
		int ny = b + dy[i];
		if (isinside(nx, ny) && !visited[nx][ny]) {
			ret += dfs(nx, ny, c);
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	memset(input, 0, sizeof(input));
	memset(cluster, 0, sizeof(cluster));
	memset(visited, 0, sizeof(visited));

	//ifstream cin;
	//cin.open("input.txt");

	cin >> N >> M;

	for (int i = 1; i <= N; ++i){
		string s;
		cin >> s;
		for (int j = 1; j <= M; ++j) {
			input[i][j] = s[j - 1] - '0';
			if (input[i][j]) visited[i][j] = true;
		}
	}

	clist.push_back(0);
	int cnt = 1;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (input[i][j] == 0 && !visited[i][j]) {
				clist.push_back(dfs(i, j, cnt));
				++cnt;
			}
		}
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (input[i][j] == 1 ) {
				set<int> cset;
				int ans = 1;
				for (int k = 0; k < 4; ++k) {
					int nx = i + dx[k];
					int ny = j + dy[k];
					if (isinside(nx, ny) && input[nx][ny]==0) cset.insert(cluster[nx][ny]);
				}
				for (auto k : cset) ans += clist[k];
				printf("%d", ans % 10);
			}
			else {
				printf("0");
			}
		}
		printf("\n");
	}

	return 0;

}

/*
//YunGoon's solution. using disjoint set. 내껀 왜 TLE 였을까ㅠ
#include <bits/stdc++.h>
#define X first
#define Y second
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pdd = pair<double, double>;

const int MOD = 1e9 + 7;
const int INF32 = 0x3f3f3f3f;
const ll  INF64 = 0x3f3f3f3f3f3f3f3fLL;
const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
const double PI = acos(-1);

int N, M;
char bo[1000][1001];
int pa[1000000];
char ans[1000][1001];

int c(int x, int y) {
	return x * 1000 + y;
}
int fnd(int n) {
	if (pa[n] < 0) return n;
	return pa[n] = fnd(pa[n]);
}
void uni(int a, int b) {
	a = fnd(a), b = fnd(b);
	if (a != b) {
		pa[a] += pa[b];
		pa[b] = a;
	}
}
int main() {
	memset(pa, -1, sizeof(pa));
	fastio;

	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		cin >> bo[i];
		memset(ans[i], '0', M);
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) if (bo[i][j] == '0') {
			for (int k = 0; k < 4; ++k) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (nx < 0 || nx >= N || ny < 0 || ny >= M ||
					bo[nx][ny] == '1' || fnd(c(i, j)) == fnd(c(nx, ny))) continue;

				uni(c(i, j), c(nx, ny));
			}
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) if (bo[i][j] == '1') {
			int res = 1;
			set<int> s;
			for (int k = 0; k < 4; ++k) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (nx < 0 || nx >= N || ny < 0 || ny >= M ||
					bo[nx][ny] == '1' || s.find(fnd(c(nx, ny))) != s.end()) continue;

				res += -pa[fnd(c(nx, ny))];
				s.insert(fnd(c(nx, ny)));
			}

			ans[i][j] = res % 10 + 48;
		}
	}

	for (int i = 0; i < N; ++i) cout << ans[i] << '\n';

	return 0;
}
*/

/*
//first trial. TLE
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, M;

#define Msize 1000100

struct disjointSet {
	vector<int> parent;
	vector<int> rank;
	vector<int> dsize;

	disjointSet() {
		parent.resize(Msize);
		rank.resize(Msize, 1);
		dsize.resize(Msize, 1);
		for (int i = 0; i < Msize; ++i) {
			parent[i] = i;
		}
	}

	int find(int u) {
		if (u == parent[u]) return u;

		return parent[u] = find(parent[u]);
	}

	int merge(int u, int v) {
		u = find(u);
		v = find(v);

		if (u == v) return dsize[u];

		if (rank[u] > rank[v]) swap(u, v);

		parent[v] = u;
		dsize[u] += dsize[v];
		dsize[v] = 1;
		if (rank[u] == rank[v]) rank[v]++;
		return dsize[u];
	}

	int setsize(int u) {
		return dsize[find(u)];
	}
};

int input[1010][1010];
#define pii pair<int,int>
map<pii, int> idx;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

bool isinside(int a, int b) {
	if (a < 1 || a > N) return false;
	if (b < 1 || b > M) return false;
	return true;
}

bool visited[1010][1010];
disjointSet DJS;

void bfs(int a, int b) {
	queue<pii> q;
	q.push({ a,b });

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		visited[x][y] = true;
		q.pop();

		int now = idx[{x, y}];
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (isinside(nx, ny) && !visited[nx][ny]) {
				q.push({ nx,ny });
				DJS.merge(now, idx[{nx, ny}]);
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	memset(input, 0, sizeof(input));
	memset(visited, 0, sizeof(visited));
	cin >> N >> M;


	int cnt = 1;
	for (int i = 1; i <= N; ++i) {
		string s;
		cin >> s;
		for (int j = 1; j <= M; ++j) {
			input[i][j] = s[j-1] - '0';
			if (input[i][j]) visited[i][j] = true;
			idx[{i, j}] = cnt;
			++cnt;
		}
	}



	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (input[i][j]==0 && !visited[i][j]) {
				bfs(i, j);
			}
		}
	}


	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			disjointSet copyDJS = DJS;
			if (input[i][j] == 1) {
				int now = idx[{i, j}];
				for (int k = 0; k < 4; ++k) {
					int nx = i + dx[k];
					int ny = j + dy[k];
					if (isinside(nx, ny) && input[nx][ny] == 0) copyDJS.merge(now, idx[{nx, ny}]);
				}
				printf("%d", copyDJS.setsize(now) % 10);
			}
			else {
				printf("0");
			}
		}
		printf("\n");
	}

	return 0;
}

*/