#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, K;

bool visited[100100];
int dist[100100];
int parent[100100];

bool isInside(int n) {
	if (n < 0 || n>100000) return false;
	return true;
}

void bfs() {
	queue<int> q;
	q.push(N);
	visited[N] = true;
	dist[N] = 0;

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		int there;
		there = here - 1;
		if (isInside(there) && dist[there] > dist[here] + 1) {
			dist[there] = dist[here] + 1;
			parent[there] = here;
			q.push(there);
		}

		there = here + 1;
		if (isInside(there) && dist[there] > dist[here] + 1) {
			dist[there] = dist[here] + 1;
			parent[there] = here;
			q.push(there);
		}

		there = here*2;
		if (isInside(there) && dist[there] > dist[here] + 1) {
			dist[there] = dist[here] + 1;
			parent[there] = here;
			q.push(there);
		}
	}
}

int main() {
	memset(visited, 0, sizeof(visited));
	fill(dist, dist+100100, 1000000);
	memset(parent, 0, sizeof(parent));

	cin >> N >> K;
	bfs();
	int backtrack = K;
	vector<int> ans;
	while(1) {
		ans.push_back(backtrack);
		if (backtrack == N) break;
		backtrack = parent[backtrack];
	}

	int t = ans.size();
	if (t > 0) printf("%d\n", t - 1);
	for (int i = t - 1; i >= 0; --i) {
		printf("%d ", ans[i]);
	}

	return 0;
}