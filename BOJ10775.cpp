//BOJ10775

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct disjointset {
	int parent[100100];
	bool chk[100100];

	disjointset() {
		for (int i = 0; i < 100100; ++i) parent[i] = i;
		memset(chk, 0, sizeof(chk));
	}

	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	bool merge(int u) {
		u = find(u);

		if (u == 0) return false;

		parent[u] = u - 1;
		return true;
	}

	
};

disjointset DJS;
int G, P;

int main() {
	cin >> G >> P;

	int cnt = 0;
	for (int i = 0; i < P; ++i) {
		int t;
		cin >> t;
		if (DJS.merge(t)) ++cnt;
		else break;
	}

	printf("%d\n", cnt);

	return 0;
}