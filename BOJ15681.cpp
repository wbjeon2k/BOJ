#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool visited[100100];
int cache[100100];

vector<vector<int>> adjList;
int N, R, Q;

int dfs(int here) {

	visited[here] = true;

	int& ret = cache[here];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < adjList[here].size(); ++i) {
		int there = adjList[here][i];
		if(!visited[there]) ret += dfs(there);
	}

	ret += 1;
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	memset(visited, 0, sizeof(visited));
	adjList.resize(100100);
	memset(cache, -1, sizeof(cache));

	cin >> N >> R >> Q;
	for (int i = 0; i < N-1; ++i) {
		int a, b;
		cin >> a >> b;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}

	dfs(R);

	for (int i = 0; i < Q; ++i) {
		int t;
		cin >> t;
		printf("%d\n", dfs(t));
	}

	return 0;
}