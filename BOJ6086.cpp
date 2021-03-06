//BOJ6086


#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 1001

int N, M;

struct edge {
	int u, v, cap, flow;
	edge* backward;

	edge() {
		u = v = cap = flow = 0;
		backward = NULL;
	}

	edge(const int& from, const int& to, const int& ecap) {
		u = from;
		v = to;
		cap = ecap;
		flow = 0;
		backward = NULL;
	}

	void addflow(int f) {
		flow += f;
		backward->flow -= f;
	}

	int residual() {
		return cap - flow;
	}

};

vector<edge*> adjlist[MAXI];
edge* path[MAXI];
bool visited[MAXI];
int parent[MAXI];
//source 0, sink: MAXI - 1;

const int source = 0, sink = 'Z' - 'A';

void addedge(const int& u, const int& v, const int& ecap) {
	
	edge* fedge = new edge(u, v, ecap);
	edge* bedge = new edge(v, u, ecap);

	fedge->backward = bedge;
	bedge->backward = fedge;

	adjlist[u].push_back(fedge);
	adjlist[v].push_back(bedge);
}


int maxflow() {

	int ret = 0;
	
	while (1) {
		memset(parent, -1, sizeof(parent));
		memset(path, NULL, sizeof(path));
		memset(visited, 0, sizeof(visited));
		queue<int> q;
		q.push(0);
		visited[0] = true;
		//find simple path
		while (!q.empty()) {
			int here = q.front();
			visited[here] = true;
			q.pop();

			if (here == sink) break;

			for (int i = 0; i < adjlist[here].size(); ++i) {
				edge* cur = adjlist[here][i];
				int there = adjlist[here][i]->v;
				if (!visited[there] && cur->residual() > 0) {
					q.push(there);
					parent[there] = here;
					path[there] = cur;
					if (there == sink) break;
				}
			}
		}

		if (parent[sink] == -1) break;
		//no residual path

		//find bottleneck
		int b = MAXI;
		for (int i = sink; i != source; i = parent[i]) {
			b = min(b, path[i]->residual());
		}

		//addflow
		for (int i = sink; i != source; i = parent[i]) {
			path[i]->addflow(b);
		}

		ret += b;
	}

	return ret;

}

inline int CtoI(char c) {
	if (c <= 'Z') return c - 'A';
	return c - 'a' + 26;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N;

	for (int i = 0; i < N; ++i) {
		char s, e;
		int c;
		cin >> s >> e >> c;
		addedge(CtoI(s), CtoI(e), c);
	}

	int ans = maxflow();

	printf("%d\n", ans);

	return 0;

}
