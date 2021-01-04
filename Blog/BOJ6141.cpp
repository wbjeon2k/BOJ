//BOJ6141

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pid pair<int,double>

#define MAXI 1010

int V, E;
double INF = 2000000.0;
double eps = 1e-6;

double fun[MAXI];
vector<vector<pid>> adjList(MAXI);

bool isinQ[MAXI];
double upper[MAXI];
int cnt[MAXI];

bool SPFA(double X) {
	fill(upper, upper + MAXI, INF);
	upper[1] = 0.0;

	memset(isinQ, 0, sizeof(isinQ));
	memset(cnt, 0, sizeof(cnt));

	queue<int> Q;
	Q.push(1);
	isinQ[1] = true;

	while (!Q.empty()) {
		int here = Q.front();
		Q.pop();
		isinQ[here] = false;

		for (int i = 0; i < adjList[here].size(); ++i) {
			int there = adjList[here][i].first;
			double cost = adjList[here][i].second * X - fun[there];
			
			if (upper[there] > upper[here] + cost) {
				upper[there] = upper[here] + cost;
				++cnt[there];
				if (!isinQ[there]) Q.push(there);
				if (cnt[there] >= V) return true;
			}

		}
	}

	return false;
}

double binsearch(double lo, double hi) {
	while (hi - lo > eps) {
		double mid = (lo + hi) / 2;
		if (SPFA(mid)) lo = mid;
		else hi = mid;
	}

	return lo;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> V >> E;

	for (int i = 0; i < V; ++i) {
		cin >> fun[i + 1];
	}

	for (int i = 0; i < E; ++i) {
		int s, e;
		double t;
		cin >> s >> e >> t;
		adjList[s].push_back({ e,t });
	}

	double ans = binsearch(0, 100000.0);

	printf("%.2f", ans);
	
	return 0;

}
