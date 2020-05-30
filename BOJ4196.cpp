#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 100100

vector<vector<int>>adjList(Msize), compressed(Msize);
vector<int> discovered(Msize), sccId(Msize);
stack<int> vstack;
int vertexCount, sccCount;
int sccIndegree[Msize];
int N, M, T;


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
			if (top == here) break;
		}
		++sccCount;
	}

	return ret;
}

void tarjan() {
	vertexCount = 0;
	sccCount = 0;
	for (int i = 1; i <= N; ++i) {
		if (discovered[i] == -1) scc(i);
	}
}

void compress() {
	for (int i = 1; i <= N; ++i) {
		int scchere = sccId[i];
		for (int j = 0; j < adjList[i].size(); ++j) {
			int there = adjList[i][j];
			if (scchere != sccId[there]) {
				sccIndegree[sccId[there]]++;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> T;

	while (T--) {
		cin >> N >> M;

		adjList.clear(); adjList.resize(Msize);
		for (int i = 0; i < Msize; ++i) {
			discovered[i] = sccId[i] = -1;
		}
		vstack = stack<int>();
		memset(sccIndegree, 0, sizeof(sccIndegree));

		for (int i = 1; i <= M; ++i) {
			int a, b;
			cin >> a >> b;
			adjList[a].push_back(b);
		}

		tarjan();
		compress();

		int ans = 0;
		for (int i = 0; i < sccCount ; ++i) {
			if (sccIndegree[i] == 0) ++ans;
		}
		printf("%d\n", ans);
	}
}