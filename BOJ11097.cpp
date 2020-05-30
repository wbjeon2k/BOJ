#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 333

int N, M, vertexCount, sccCount;
vector<int> discovered(Msize), sccId(Msize);
stack<int> vstack;
vector<vector<int>>sccGroup(Msize), adjList(Msize);
int compressedgraph[303][303];

int scc(int here) {
	discovered[here] = vertexCount;
	++vertexCount;
	vstack.push(here);

	int ret = discovered[here];
	for (int i = 0; i < adjList[here].size(); ++i) {
		int there = adjList[here][i];
		if (discovered[there] == -1) ret = min(ret, scc(there));
		else if (sccId[there] == -1) ret = min(ret, discovered[there]);
	}

	if (discovered[here] == ret) {
		while (1) {
			int top = vstack.top();
			vstack.pop();
			sccId[top] = sccCount;
			sccGroup[sccCount].push_back(top);
			if (top == here) break;
		}
		++sccCount;
	}

	return ret;
}

void tarjan() {
	vertexCount = 0;
	sccCount = 0;
	for (int i = 1; i <= M; ++i) {
		if (discovered[i] == -1) scc(i);
	}
}

void compress(int s) {
	for (int i = 1; i <= s; ++i) {
		for (int j = 0; j < adjList[i].size(); ++j) {
			int t = adjList[i][j];
			int idx = sccId[i], idy = sccId[t];
			if(idx!=idy) compressedgraph[idx][idy] = 1;
			
		}
	}

	for (int k = 0; k < sccCount; ++k) {
		for (int i = 0; i < sccCount; ++i) {
			for (int j = 0; j < sccCount; ++j) {
				if (compressedgraph[i][k] && compressedgraph[k][j] && compressedgraph[i][j]) compressedgraph[i][j] = 0;
			}
		}
	}
}

vector<pair<int,int>> getRoute() {
	vector<pair<int,int>> ret;
	for (int i = 0; i < sccCount; ++i) {
		vector<int> tmp = sccGroup[i];
		if (tmp.size() > 1) {
			for (int j = 0; j < tmp.size() - 1; ++j) {
				ret.push_back({ tmp[j], tmp[j + 1] });
			}
			ret.push_back({ tmp[tmp.size() - 1], tmp[0] });
		}
	}

	for (int i = 0; i < sccCount; ++i) {
		for (int j = 0; j < sccCount; ++j) {
			if (compressedgraph[i][j]) {
				ret.push_back({ sccGroup[i][0], sccGroup[j][0] });
			}
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> N;

	while (N--) {
		cin >> M;

		
		memset(compressedgraph, 0, sizeof(compressedgraph));
		discovered = vector<int>(Msize, -1);
		sccId = vector<int>(Msize, -1);
		adjList.clear(); adjList.resize(Msize);
		sccGroup.clear(); sccGroup.resize(Msize);

		for (int i = 1; i <= M; ++i) {
			string s;
			cin >> s;
			for (int j = 1; j <= M; ++j) {
				int t = s[j - 1] - '0';
				if (t && i!=j) adjList[i].push_back(j);
			}
		}

		tarjan();

		compress(M);

		vector<pair<int,int>>ans = getRoute();
		printf("%d\n", ans.size());
		for (int i = 0; i < ans.size(); ++i) {
			printf("%d %d\n", ans[i].first, ans[i].second);
		}
		printf("\n");

	}

	return 0;
}

/*
//YunGoon's solution. Union-find
#include <bits/stdc++.h>
#define X first
#define Y second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define ini(x, y) memset(x, y, sizeof(x))
#define endl '\n'
#define fastio cin.sync_with_stdio(false); cin.tie(nullptr)
using namespace std;

using ll = long long;
const ll ee = 1e9;
const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

int pa[300];

int fnd(int n) {
	if (pa[n] < 0) return n;
	return pa[n] = fnd(pa[n]);
}
void uni(int a, int b) {
	a = fnd(a), b = fnd(b);
	if (a != b) pa[b] = a;
}
int main() {
	fastio;
	int t;
	cin >> t;

	char str[300][301];
	while (t--) {
		ini(pa, -1);

		int n;
		cin >> n;

		for (int i = 0; i < n; ++i) cin >> str[i];
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (str[i][j] == '1' && str[j][i] == '1') uni(i, j);

		vector<int> scc[300];
		bool adj[300][300]{};
		for (int i = 0; i < n; ++i) {
			scc[fnd(i)].push_back(i);
			for (int j = 0; j < n; ++j) if (fnd(i) != fnd(j))
				if (str[fnd(i)][fnd(j)] == '1') adj[fnd(i)][fnd(j)] = 1;
		}

		vector<pair<int, int>> edge;
		for (int r = 0; r < n; ++r) {
			if (sz(scc[r]) <= 1) continue;
			for (int i = 1; i < sz(scc[r]); ++i)
				edge.push_back({ scc[r][i - 1], scc[r][i] });
			edge.push_back({ scc[r].back(), scc[r].front() });
		}

		for (int k = 0; k < n; ++k)
			for (int i = 0; i < n; ++i) if (adj[i][k])
				for (int j = 0; j < n; ++j)
					adj[i][j] &= !(adj[i][k] && adj[k][j]);

		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (adj[i][j]) edge.push_back({ scc[i][0], scc[j][0] });

		cout << sz(edge) << endl;
		for (auto &it : edge) cout << it.X + 1 << ' ' << it.Y + 1 << endl;
		cout << endl;
	}

	return 0;
}
*/