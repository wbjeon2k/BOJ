//BOJ1949

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 10010
#define ll long long

vector<vector<int>>adjList(Msize);
vector<vector<int>>tree(Msize);
int N;
int weight[Msize];
ll cache[Msize][2];
bool visited[Msize];

void dfsTree(int here) {
	visited[here] = true;

	for (int i = 0; i < adjList[here].size(); ++i) {
		int there = adjList[here][i];
		if (!visited[there]) {
			tree[here].push_back(there);
			dfsTree(there);
		}
	}
}


ll dp(int here, bool chk) {
	ll& ret = cache[here][chk];
	if (ret != -1) return ret;

	ret = 0;
	if (chk) {
		ret += weight[here];
		for (int i = 0; i < tree[here].size(); ++i) {
			int there = tree[here][i];
			ret += dp(there, 0);
		}
	}
	else {
		for (int i = 0; i < tree[here].size(); ++i) {
			int there = tree[here][i];
			ret += max(dp(there, 1), dp(there,0));
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		cin >> weight[i + 1];
	}

	for (int i = 0; i < N - 1; ++i) {
		int a, b;
		cin >> a >> b;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}

	dfsTree(1);

	memset(cache, -1, sizeof(cache));

	printf("%lld", max(dp(1, 0), dp(1, 1)));

	return 0;
}