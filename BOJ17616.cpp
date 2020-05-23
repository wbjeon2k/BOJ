#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>>alist, blist;
int front[100100], back[100100];
bool visited[100100];

int N, M, X;

int dfs(int here, const vector<vector<int>>& adjlist) {
	visited[here] = true;

	if (adjlist[here].size() == 0) return 0;

	int ret = 0;
	for (int i = 0; i < adjlist[here].size(); ++i) {
		int there = adjlist[here][i];
		if(!visited[there]) ret += dfs(there, adjlist) + 1;
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> N >> M >> X;

	memset(front, 0, sizeof(front));
	memset(back, 0, sizeof(back));

	alist.resize(100100); blist.resize(100100);

	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;
		alist[a].push_back(b);
		blist[b].push_back(a);
	}

	memset(visited, 0, sizeof(visited));
	int maxi = dfs(X, alist);
	memset(visited, 0, sizeof(visited));
	int mini = dfs(X, blist);

	printf("%d %d", mini + 1, N - maxi);

	return 0;
}