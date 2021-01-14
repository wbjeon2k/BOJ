//BOJ11408

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 808

int N, M;

vector<int> adjlist[MAXI];
ll dist[MAXI][MAXI], flow[MAXI][MAXI], capacity[MAXI][MAXI];

ll mcost, mflow;

int source, sink;

void mcmf() {
	mcost = mflow = 0;

	while (1) {
		ll upper[MAXI], parent[MAXI];
		bool isinq[MAXI] = { 0, };
		fill(upper, upper + MAXI, INT_MAX);
		fill(parent, parent + MAXI, -1);

		queue<int> q;
		q.push(source);
		isinq[source] = true;
		upper[source] = 0;

		while (!q.empty()) {
			int here = q.front();
			q.pop();
			isinq[here] = false;

			for (int i = 0; i < adjlist[here].size(); ++i) {
				int there = adjlist[here][i];

				if (capacity[here][there] - flow[here][there] > 0 && upper[there] > upper[here] + dist[here][there]) {
					upper[there] = upper[here] + dist[here][there];
					parent[there] = here;
					if (!isinq[there]) {
						q.push(there);
						isinq[there] = true;
					}
				}
			}
		}

		if (parent[sink] == -1) break;

		ll b = INT_MAX;
		for (int i = sink; i != source; i = parent[i]) {
			b = min(b, capacity[parent[i]][i] - flow[parent[i]][i]);
		}

		for (int i = sink; i != source; i = parent[i]) {
			flow[parent[i]][i] += b;
			flow[i][parent[i]] -= b;
		}

		mflow += b;
		mcost += upper[sink] * b;
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N >> M;

	memset(dist, 0, sizeof(dist));
	memset(capacity, 0, sizeof(capacity));
	memset(flow, 0, sizeof(flow));

	source = 0, sink = MAXI - 1;

	for (int i = 1; i <= N; ++i) {
		adjlist[source].push_back(i);
		adjlist[i].push_back(source);

		capacity[source][i] = 1;
	}

	for (int i = 1; i <= M; ++i) {
		adjlist[i + N].push_back(sink);
		adjlist[sink].push_back(i + N);

		capacity[i+N][sink] = 1;
	}

	for (int i = 1; i <= N; ++i) {
		int t;
		cin >> t;
		while (t--) {
			int s, e;
			cin >> s >> e;
			adjlist[i].push_back(s+N);
			capacity[i][s + N] = 1;
			dist[i][s + N] = e;

			adjlist[s + N].push_back(i);
			dist[s + N][i] = -e;
		}
	}

	mcmf();

	printf("%lld\n%lld\n", mflow, mcost);

	return 0;

}


/*
//1st trial. TLE
//BOJ11408


#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>

#define MAXI 808

int N, M;

ll adjmat[MAXI][MAXI], capacity[MAXI][MAXI], flow[MAXI][MAXI], dist[MAXI][MAXI], upper[MAXI];
ll parent[MAXI];
bool visited[MAXI], isinq[MAXI];

int source, sink;
//source, sink 는 main 에서 지정.

ll mcost = 0, mflow = 0;

void mcmf() {
	while (1) {
		//initialze spfa utilities
		fill(upper, upper + MAXI, INT_MAX);
		memset(parent, -1, sizeof(parent));
		memset(isinq, 0, sizeof(isinq));

		queue<int> q;
		q.push(source);
		isinq[source] = true;
		upper[source] = 0;

		//spfa
		while (!q.empty()) {
			int here = q.front();
			q.pop();
			isinq[here] = false;

			for (int i = 0; i < MAXI; ++i) {
				if (!adjmat[here][i]) continue;

				//residual > 0 && upper[i] > upper[here] + dist[here][i]
				if (capacity[here][i] - flow[here][i] > 0 && upper[i] > upper[here] + dist[here][i]) {
					upper[i] = upper[here] + dist[here][i];
					parent[i] = here;
					if (!isinq[i]) {
						q.push(i);
						isinq[i] = true;
					}
				}
			}
		}

		//if there is no residual shortest path
		if (parent[sink] == -1) break;


		//find bottleneck
		ll b = INT_MAX;
		for (int i = sink; i != source; i = parent[i]) {
			b = min(b, capacity[parent[i]][i] - flow[parent[i]][i]);
		}

		//add flow
		for (int i = sink; i != source; i = parent[i]) {
			flow[parent[i]][i] += b;
			flow[i][parent[i]] -= b;
		}

		mflow += b;
		mcost += upper[sink] * b;
	}
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	//source: 0 sink:MAXI - 1
	//worker: 1 ~ N
	//work: N + 1 ~ N + M

	source = 0;
	sink = MAXI - 1;

	//link worker with source
	//dist=0, capacity = 1;
	for (int i = 1; i <= N; ++i) {
		adjmat[0][i] = 1;
		dist[0][i] = 0;
		capacity[0][i] = 1;

		adjmat[i][0] = 1;
		dist[i][0] = 0;
		capacity[i][0] = 0;
	}

	//link work with sink
	//dist = 0, capacity = 1;
	for (int i = 1; i <= M; ++i) {
		adjmat[i + N][sink] = 1;
		dist[i + N][sink] = 0;
		capacity[i + N][sink] = 1;

		adjmat[sink][i + N] = 1;
		dist[sink][i + N] = 0;
		capacity[sink][i + N] = 0;
	}


	//get input
	for (int i = 1; i <= N; ++i) {
		int t;
		cin >> t;

		int s, e;
		while (t--) {
			//dist = 월급, capacity =1;
			cin >> s >> e;
			adjmat[i][s + N] = 1;
			dist[i][s + N] = e;
			capacity[i][s + N] = 1;

			adjmat[s + N][i] = 1;
			dist[s + N][i] = -e;
			capacity[s + N][i] = 0;
		}
	}

	mcmf();

	printf("%lld\n%lld\n", mflow, mcost);

	return 0;

}

/*
5 5
2 1 3 2 2
1 1 5
2 2 1 3 7
3 3 9 4 9 5 9
1 1 0

예제 결과: 3, 10
정답: 4, 18


/*
5 5
2 1 3 2 2
1 1 5
2 2 1 3 7
3 3 9 4 9 5 9
1 1 0

예제 결과: 3, 10
정답: 4, 18

*/