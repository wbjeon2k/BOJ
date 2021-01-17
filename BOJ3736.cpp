//BOJ3736

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 20020
#define INF INT_MAX/2

//ll sad[MAXI][MAXI], capacity[MAXI][MAXI], flow[MAXI][MAXI];
//ll group[MAXI];

vector<vector<int>> adjlist(MAXI);

int N, M;
ll mcost, mflow;
int source, sink;

vector<int> lmatch, rmatch, dist;

bool dfs(int here) {
	for (int i = 0; i < adjlist[here].size(); ++i) {
		int there = adjlist[here][i];
		if (!rmatch[there] || (dist[there] == dist[here] + 1 && dfs(rmatch[there]))) {
			lmatch[here] = there;
			rmatch[there] = here;
			return true;
		}
	}

	return false;
}

void hopcroftkarp() {
	mflow = 0;
	lmatch = vector<int>(MAXI, 0);
	rmatch = vector<int>(MAXI, 0);
	dist = vector<int>(MAXI, 0);

	while (1) {
		queue<int> q;

		for (int i = 1; i <= N; ++i) {
			if (lmatch[i] == 0) {
				dist[i] = 0;
				q.push(i);
			}
			else dist[i] = INF;
		}

		while (!q.empty()) {
			int here = q.front();
			q.pop();

			for (int i = 0; i < adjlist[here].size(); ++i) {
				int there = adjlist[here][i];
				if (rmatch[there] && dist[rmatch[there]] == INF) {
					dist[there] = dist[here] + 1;
					q.push(there);
				}
			}
		}

		int f = 0;
		for (int i = 1; i <= N; ++i) {
			if (lmatch[i] == 0 && dfs(i)) ++f;
		}
		if (f == 0) break;
		mflow += f;
	}
}


int main() {
	//ios::sync_with_stdio(false);
	//cin.tie(NULL);

	//FILE* pFile = NULL;
	//pFile = fopen("d:\\Text.txt", "r");

	while (1) {
		adjlist.resize(MAXI);
		if (scanf("%d", &N) < 0) break;

		for (int i = 1; i <= N; ++i) {
			int s, e, t;
			scanf("%d : (%d)", &s, &t);
			++s;
			for (int j = 0; j < t; ++j) {
				scanf("%d", &e);
				++e;
				adjlist[s].push_back(e);
			}
		}

		hopcroftkarp();

		printf("%lld\n", mflow);

		adjlist.clear();
	}


	return 0;

}

