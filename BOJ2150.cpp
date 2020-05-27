#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

vector<int> sccid(10010, -1), discovered(10010, -1);
stack<int> st;
int sccCount, vertexCount;
vector<vector<int>> adjList(10010);
vector<vector<int>> sccList(10010);
int V, E;

int scc(int here) {
	discovered[here] = vertexCount;
	++vertexCount;
	int ret = discovered[here];

	st.push(here);

	for (int i = 0; i < adjList[here].size(); ++i) {
		int there = adjList[here][i];

		if (discovered[there] == -1) {
			ret = min(ret, scc(there));
		}
		else if (sccid[there] == -1) {
			ret = min(ret, discovered[there]);
		}
	}

	if (ret == discovered[here]) {
		while (1) {
			int top = st.top();
			st.pop();
			sccid[top] = sccCount;
			sccList[sccCount].push_back(top);
			if (top == here) break;
		}
		++sccCount;
	}

	return ret;
}

void tarjan() {
	sccCount = 0;
	vertexCount = 0;
	for (int i = 1; i <= V; ++i) {
		if (discovered[i] == -1) scc(i);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> V >> E;
	for (int i = 0; i < E; ++i) {
		int a, b;
		cin >> a >> b;
		adjList[a].push_back(b);
	}

	tarjan();

	printf("%d\n", sccCount);

	for (int i = 0; i <= sccCount; ++i) {
		sort(sccList[i].begin(), sccList[i].end());
	}

	bool printed[10010];
	memset(printed, 0, sizeof(printed));
	for (int i = 1; i <= V; ++i) {
		if (!printed[sccid[i]]) {
			int t = sccid[i];
			for (int j = 0; j < sccList[t].size(); ++j) {
				printf("%d ", sccList[t][j]);
			}

			if (sccList[t].size() > 0) printf("-1\n");
			printed[t] = true;
		}
	}

	return 0;
}