#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define pdd pair<double, double>
#define pdpdd pair<double, pair<double, double>>

vector<pdd> vertexList;
vector<pdpdd> costList;
int N;

struct disjointSet {
	vector<int> parent, rank;

	disjointSet() {
		parent.resize(111);
		rank.resize(111, 1);
		for (int i = 0; i < 111; ++i) parent[i] = i;
	}

	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}

	bool merge(int a, int b) {
		int u = find(a), v = find(b);

		if (u == v) return false;

		if (rank[u] > rank[v])swap(u, v);
		parent[v] = u;
		if (rank[v] == rank[u]) ++rank[v];
		return true;
	}
};

double dist(pdd a, pdd b) {
	double x, y;
	x = a.first - b.first;
	x = x*x;
	y = a.second - b.second;
	y = y*y;
	return sqrt(x + y);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i) {
		double a, b;
		cin >> a >> b;
		vertexList.push_back({ a,b });
	}

	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			pdd s = vertexList[i], e = vertexList[j];
			double d = dist(s, e);
			costList.push_back({ d, {i,j} });
			costList.push_back({ d, {j,i} });
		}
	}

	sort(costList.begin(), costList.end());

	disjointSet DJS;

	double ret = 0;
	for (int i = 0; i < costList.size(); ++i) {
		double d = costList[i].first, s = costList[i].second.first, e = costList[i].second.second;
		if (DJS.merge(s, e)) {
			ret += d;
		}
	}

	printf("%.2lf", ret);

	return 0;

}