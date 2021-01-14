//BOJ3640

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 2020

int N, M;
ll mcost, mflow;
int source, sink;

struct edge {
	int from, to, dist, flow, capacity;
	edge* backward;

	edge(const int& u, const int& v, const int& ecap, const int& d) {
		from = u;
		to = v;
		dist = d;
		capacity = ecap;
		flow = 0;
		backward = NULL;
	}

	int residual() {
		return capacity - flow;
	}

	void addflow(const int& x) {
		flow += x;
		backward->flow -= x;
	}
};

vector<vector<edge*>> adjlist(MAXI);

inline int inbound(const int& x) {
	return 2 * x;
}

inline int outbound(const int& x) {
	return (2 * x) + 1;
}

void addedge(const int& x, const int& y, const int& z) {
	edge* fedge = new edge(x, y, 1, z);
	edge* bedge = new edge(y, x, 0, -z);
	fedge->backward = bedge;
	bedge->backward = fedge;


	adjlist[x].push_back(fedge);
	adjlist[y].push_back(bedge);
}

int minshell() {

	bool isinq[MAXI] = { 0, };
	ll parent[MAXI], upper[MAXI];
	edge* prev[MAXI] = { 0, };
	memset(parent, -1, sizeof(parent));
	fill(upper, upper + MAXI, INT_MAX / 2);

	queue<int> q;
	q.push(source);
	isinq[source] = true;
	upper[source] = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		isinq[here] = false;


		for (int i = 0; i < adjlist[here].size(); ++i) {
			edge* nedge = adjlist[here][i];
			int there = nedge->to;
			if (nedge->residual() > 0 && upper[there] > upper[here] + nedge->dist) {
				upper[there] = upper[here] + nedge->dist;
				parent[there] = here;
				prev[there] = nedge;
				if (!isinq[there]) {
					q.push(there);
					isinq[there] = true;
				}
			}

		}
	}

	int b = INT_MAX / 2;
	for (int i = sink; i != source; i = prev[i]->from) {
		b = min(b, prev[i]->residual());
	}

	for (int i = sink; i != source; i = prev[i]->from) {
		prev[i]->addflow(b);
	}

	mflow += b;
	mcost += upper[sink] * b;

	memset(parent, -1, sizeof(parent));
	fill(upper, upper + MAXI, INT_MAX / 2);
	q.push(source);
	isinq[source] = true;
	upper[source] = 0;

	while (!q.empty()) {
		int here = q.front();
		q.pop();
		isinq[here] = false;


		for (int i = 0; i < adjlist[here].size(); ++i) {
			edge* nedge = adjlist[here][i];
			int there = nedge->to;
			if (nedge->residual() > 0 && upper[there] > upper[here] + nedge->dist) {
				upper[there] = upper[here] + nedge->dist;
				parent[there] = here;
				prev[there] = nedge;
				if (!isinq[there]) {
					q.push(there);
					isinq[there] = true;
				}
			}

		}
	}

	b = INT_MAX / 2;
	for (int i = sink; i != source; i = prev[i]->from) {
		b = min(b, prev[i]->residual());
	}

	for (int i = sink; i != source; i = prev[i]->from) {
		prev[i]->addflow(b);
	}

	mflow += b;
	mcost += upper[sink] * b;
	
	return mcost;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	//ifstream cin;
	//cin.open("input.txt");

	while (1) {
		cin >> N;
		if (cin.eof()) break;
		cin >> M;

		source = 1;
		sink = inbound(N);

		adjlist.clear();
		adjlist.resize(MAXI);

		for (int i = 2; i < N; ++i) {
			addedge(inbound(i), outbound(i), 0);
		}

		for (int i = 0; i < M; ++i) {
			int a, b, c;
			cin >> a >> b >> c;

			if (a == source) {
				addedge(source, inbound(b), c);
			}
			else if (inbound(b) == sink) {
				addedge(outbound(a), sink, c);
			}
			else {
				addedge(outbound(a), inbound(b), c);
			}
		}

		mflow = mcost = 0;
		int ans = minshell();
		printf("%d\n", ans);

	}

	
	return 0;

}