// BOJ 6232

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 1010
#define pii pair<int,int>

set<pii> st;
vector<vector<int>> adjList(Msize);
bool contact[Msize][Msize];
bool visited[Msize];

int N, M;

void dfs(int here, int spoint) {
	visited[here] = true;
	contact[spoint][here] = true;

	for (int i = 0; i < adjList[here].size(); ++i) {
		int there = adjList[here][i];
		if (!visited[there]) dfs(there, spoint);
	}

	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	memset(contact, 0, sizeof(contact));
	memset(visited, 1, sizeof(visited));

	for (int i = 0; i < M; ++i) {
		int s, e;
		cin >> s >> e;

		adjList[s].push_back(e);
	}

	for (int i = 1; i <= N; ++i) {
		memset(visited, 0, sizeof(visited));
		dfs(i, i);
	}

	int cnt = 0;
	for (int i = 1; i <= N; ++i) {
		
		for (int j = i; j <= N; ++j) {
			if (!contact[i][j] && !contact[j][i]) ++cnt;
		}
	}

	printf("%d\n", cnt);

	return 0;
}