//BOJ2668

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N;
int adj[101];
bool visited[101];
vector<vector<int>> ans;

vector<int> dfs(int n, int start, vector<int> path) {
	// 현재 정점 n, 시작 정점 start, 시작 부터 경로 담은 path
	visited[n] = true;
	path.push_back(n);
	if (visited[adj[n]]) {
		if (adj[n] == start) return path;
		else {
			visited[n] = false;
			//#1
			//cycle 에 포함되지 않는 정점은 visited 상태를 false로 유지하여
			//cycle 에 포함 된 정점만 visited 상태를 true로 설정.
			return vector<int>();
		}
	}
	else {
		vector<int> ret = dfs(adj[n], start, path);
		if (ret.size() == 0) { 
			// 만약 다음 정점이 cycle 에 포함되지 않는다면
			// 현재 정점도 포함되지 않는다.
			visited[n] = false;
			//#1 과 동일
			return ret;
		}
		else {
			return ret;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> adj[i];
	}

	for (int i = 1; i <= N; ++i) {
		vector<int> tmp;
		if (!visited[i]) {
			// cycle 에 포함된 정점은 중복 탐색 하지 않는다.
			tmp = dfs(i, i, vector<int>());
		}
		if(tmp.size() > 0) ans.push_back(tmp);
	}

	int cnt = 0;
	for (int i = 1; i <= N; ++i) {
		if (visited[i]) ++cnt;
	}

	printf("%d\n", cnt);
	for (int i = 1; i <= N; ++i) {
		if (visited[i]) printf("%d\n", i);
	}

	return 0;
}