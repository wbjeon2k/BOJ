#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool visited[2020];
int glist[2020];
vector<vector<int>> adjList(2020);

int T, N, M;

bool dfs(int here, int gender) {
	glist[here] = gender;

	bool ret = true;
	for (int i = 0; i < adjList[here].size(); ++i) {
		int there = adjList[here][i];
		if (glist[there] == -1) {
			ret = dfs(there, (gender + 1) % 2);
			if (!ret) return ret;
		}
		else {
			if (glist[here] == glist[there]) return false;
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;

	int cnt = 1;
	while (T--) {
		cin >> N >> M;
		adjList = vector<vector<int>>(2020);
			
		for (int i = 0; i < M; ++i) {
			int a, b;
			cin >> a >> b;
			adjList[a].push_back(b);
			adjList[b].push_back(a);
		}

		memset(glist, -1, sizeof(glist));
		bool chk = true;
		for (int i = 1; i <= N; ++i) {
			if (glist[i] == -1) chk = dfs(i, 1);
			if (!chk) break;
		}
		printf("Scenario #%d:\n", cnt);
		if (chk) {
			printf("No suspicious bugs found!\n");
			printf("\n");
		}
		else {
			printf("Suspicious bugs found!\n");
			printf("\n");
		}
		++cnt;
	}

	return 0;
}

/*
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool visited[2020];
int glist[2020];
vector<vector<int>> adjList(2020);

int T, N, M;

bool dfs(int here, int gender) {
	//printf("h%d g%d\n", here, gender);
	visited[here] = true;
	glist[here] = gender;

	bool ret = true;
	for (int i = 0; i < adjList[here].size(); ++i) {
		int there = adjList[here][i];
		if (!visited[there]) {
			ret = dfs(there, (gender + 1) % 2);
			if (!ret) return ret;
		}
		else {
			if (glist[here] == glist[there]) return false;
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;

	int cnt = 1;
	while (T--) {
		cin >> N >> M;
		adjList.clear();
		adjList.resize(2020);

		for (int i = 0; i < M; ++i) {
			int a, b;
			cin >> a >> b;
			adjList[a].push_back(b);
			adjList[b].push_back(a);
		}

		memset(visited, 0, sizeof(visited));
		memset(glist, -1, sizeof(glist));
		bool chk = true;
		for (int i = 1; i <= N; ++i) {
			if (!visited[i]) chk = dfs(i, 1);
			if (!chk) break;
		}
		printf("Scenario #%d:\n", cnt);
		if (chk) {
			printf("No suspicious bugs found!\n");
			printf("\n");
		}
		else {
			printf("Suspicious bugs found!\n");
			printf("\n");
		}
		++cnt;
	}

	return 0;
}

*/