#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>

vector<pair<int, pii>> vertexList;
int maxCost;

int N, M;


struct disjointSet {
	vector<int> parent, rank;

	disjointSet() {
		parent.resize(100100);
		rank.resize(100100);
		for (int i = 0; i < 100100; ++i) {
			parent[i] = i;
			rank[i] = 1;
		}
	}

	int find(int u) {
		if (parent[u] == u) return u;

		return parent[u] = find(parent[u]);
	}

	bool merge(int a, int b) {
		int u = find(a), v = find(b);

		if (u == v) return false;

		if (rank[u] > rank[v]) swap(a, b);

		parent[v] = u;
		if (rank[v] == rank[u]) ++rank[v];
		return true;
	}

};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		vertexList.push_back({ c, {a,b} });
		vertexList.push_back({ c, {b,a} });
	}

	sort(vertexList.begin(), vertexList.end());

	disjointSet DJS;

	int ret = 0;
	maxCost = -1;
	for (int i = 0; i < vertexList.size(); ++i) {
		int cost = vertexList[i].first, s = vertexList[i].second.first, e = vertexList[i].second.second;
		if (DJS.merge(s, e)) {
			ret += cost;
			maxCost = max(maxCost, cost);
		}
	}

	ret -= maxCost;

	printf("%d", ret);

	return 0;
}

/*
//version 2 using priority queue.
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pii pair<int,int>

vector<pair<int, pii>> vertexList;

#define pipii pair<int,pii>

struct comp {
	bool operator()(const pipii& a, const pipii& b) {
		if (a.first > b.first) return true;
		else return false;
	}
};

priority_queue<pipii, vector<pipii>, comp> vertexpq;

int maxCost;

int N, M;


struct disjointSet {
	vector<int> parent, rank;

	disjointSet() {
		parent.resize(100100);
		rank.resize(100100);
		for (int i = 0; i < 100100; ++i) {
			parent[i] = i;
			rank[i] = 1;
		}
	}

	int find(int u) {
		if (parent[u] == u) return u;

		return parent[u] = find(parent[u]);
	}

	bool merge(int a, int b) {
		int u = find(a), v = find(b);

		if (u == v) return false;

		if (rank[u] > rank[v]) swap(a, b);

		parent[v] = u;
		if (rank[v] == rank[u]) ++rank[v];
		return true;
	}

};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		//vertexList.push_back({ c, {a,b} });
		//vertexList.push_back({ c, {b,a} });
		vertexpq.push({ c, {a,b} });
		vertexpq.push({ c, {b,a} });
	}

	disjointSet DJS;

	int ret = 0;
	maxCost = -1;
	while (!vertexpq.empty()) {
		pipii here = vertexpq.top();
		vertexpq.pop();

		int cost = here.first, s = here.second.first, e = here.second.second;
		
		if (DJS.merge(s, e)) {
			ret += cost;
			maxCost = max(cost, maxCost);
		}
	}

	ret -= maxCost;

	printf("%d", ret);

	return 0;
}
*/