#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int inherit[100100];
vector<vector<int>>adjlist(100100);
int N, M;

void dfs(int here) {

	for (int i = 0; i < adjlist[here].size(); ++i) {
		int there = adjlist[here][i];
		inherit[there] += inherit[here];
		dfs(there);
	}

	return;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> N >> M;
	memset(inherit, 0, sizeof(inherit));

	int t;
	cin >> t;
	for (int i = 2; i <= N; ++i) {
		cin >> t;
		adjlist[t].push_back(i);
	}

	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;
		inherit[a] += b;
	}

	dfs(1);

	for (int i = 1; i <= N; ++i) {
		printf("%d ", inherit[i]);
	}

	return 0;

}