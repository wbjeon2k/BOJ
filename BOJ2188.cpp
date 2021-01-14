//BOJ2188

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 202

int N, M;
ll mcost, mflow;
int source, sink;

bool adjmat[MAXI][MAXI];
vector<int> amatch, bmatch;
vector<bool> visited;

bool dfs(int here) {
	if (visited[here]) return false;

	visited[here] = true;

	for (int i = 1; i <= M; ++i) {
		if (!adjmat[here][i]) continue;

		if (bmatch[i] == -1 || dfs(bmatch[i])) {
			amatch[here] = i;
			bmatch[i] = here;
			return true;
		}
	}

	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < N; ++i) {
		int s,e;
		cin >> s;
		while (s--) {
			cin >> e;
			adjmat[i + 1][e] = 1;
		}
	}

	amatch = vector<int>(N + 1, -1);
	bmatch = vector<int>(M + 1, -1);

	int ans = 0;
	for (int i = 1; i <= N; ++i) {
		visited = vector<bool>(N + 1, false);

		if (dfs(i)) ++ans;
	}

	printf("%d\n", ans);
	
	return 0;

}

