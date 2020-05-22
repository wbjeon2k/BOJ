#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct disjointSet {
	vector<int> parent;
	vector<int> rank;
	vector<int> size;

	disjointSet() {
		parent.resize(1010);
		rank.resize(1010, 1);
		size.resize(1010, 1);
		for (int i = 0; i < 1010; ++i) {
			parent[i] = i;
		}
	}

	bool merge(int u, int v) {
		u = find(u);
		v = find(v);

		if (u == v) return false;

		if (rank[u] > rank[v]) swap(u, v);
		size[u] += size[v];
		size[v] = 1;
		parent[v] = u;
		if (rank[u] == rank[v]) ++rank[v];
		return true;
	}

	int setsize(int u) {
		int t = find(u);
		return size[t];
	}

	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}
};

int T, N, M;

#define pii pair<int,int>

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	cin >> T;

	while (T--) {
		cin >> N >> M;
		set<pii> edgeSet;
		disjointSet DJS;

		bool istree = true;

		for (int i = 0; i < M; ++i) {
			int a, b;
			cin >> a >> b;
			if (a > b) swap(a, b);
			edgeSet.insert({ a,b });
		}

		if (M != N-1) {
			istree = false;
			printf("graph\n");
		}
		else if (!istree || edgeSet.size() != N - 1) {
			istree = false;
			printf("graph\n");
		}
		else {
			int a = 0;
			for (auto k : edgeSet) {
				int u = k.first;
				int v = k.second;
				if (DJS.find(u) == DJS.find(v)) {
					istree = false;
					printf("graph\n");
					break;
				}
				else if (!DJS.merge(u, v)) {
					istree = false;
					printf("graph\n");
					break;
				}
				a = u;
			}
			if (istree) {
				if (DJS.setsize(a) != N) {
					printf("graph\n");
				}
				else {
					printf("tree\n");
				}
			}
		}
	}

	return 0;
}


/*
//kks227's solution.
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 1000;

struct UnionFind{
	int p[MAX];
	UnionFind(){ fill(p, p+MAX, -1); }
	int f(int a){
		if(p[a] < 0) return a;
		return p[a] = f(p[a]);
	}
	bool u(int a, int b){
		a = f(a); b = f(b);
		if(a == b) return false;
		if(p[a] > p[b]) swap(a, b);
		p[a] += p[b];
		p[b] = a;
		return true;
	}
	int getSize(int a){ return -p[f(a)]; }
};

int main(){
	int T;
	scanf("%d", &T);
	for(int t = 0; t < T; ++t){
		int N, M;
		scanf("%d %d", &N, &M);
		UnionFind UF;
		for(int i = 0; i < M; ++i){
			int u, v;
			scanf("%d %d", &u, &v);
			UF.u(u-1, v-1);
		}
		puts(M == N-1 && UF.getSize(0) == N ? "tree" : "graph");
	}
}
*/