//BOJ1298

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 5050

int N, M;
ll mcost, mflow;
int source, sink;

vector<vector<int>>adjlist(MAXI);
vector<int> amatch, bmatch;
vector<bool> visited;

bool dfs(int here) {
	if (visited[here]) return false;

	visited[here] = true;

	for (int i = 0; i < adjlist[here].size(); ++i) {

		int there = adjlist[here][i];

		if (bmatch[there] == -1 || (!visited[bmatch[there]] && dfs(bmatch[there]))) {
			amatch[here] = there;
			bmatch[there] = here;
			return true;
		}
	}

	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < M; ++i) {
		int s, e;
		cin >> s >> e;
		adjlist[s].push_back(e);
	}

	amatch = vector<int>(MAXI, -1);
	bmatch = vector<int>(MAXI, -1);

	int ans = 0;
	for (int i = 1; i <= N; ++i) {
		if (amatch[i] != -1) continue;

		visited = vector<bool>(MAXI, false);
		if (dfs(i)) {
			++ans;
		}
	}

	printf("%d\n", ans);
	
	return 0;

}

