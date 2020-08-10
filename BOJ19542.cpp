//BOJ 19542

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 100100

vector<vector<int>> adjList(Msize);
int N, root, D;

struct node {
	int label;
	vector<node*> child;
};

node tree[Msize];
bool visited[Msize];
int depth[Msize];

int buildTree(int here) {
	
	visited[here] = true;

	int d = -1;
	for (int i = 0; i < adjList[here].size(); ++i) {
		int there = adjList[here][i];
		if (!visited[there]) {
			tree[here].child.push_back(&tree[there]);
			d = max(d, buildTree(there) + 1);
		}
	}

	if (d == -1) d = 0;

	depth[here] = d;
	return d;
}

int dfs(int here) {
	visited[here] = true;

	int ret = 1;

	for (int i = 0; i < tree[here].child.size(); ++i) {
		int there = tree[here].child[i]->label;
		if (!visited[there] && depth[there] >= D) {
			ret += dfs(there);
		}
	}

	return ret;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> root >> D;

	for (int i = 0; i < N - 1; ++i) {
		int a, b;
		cin >> a >> b;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}

	for (int i = 0; i < Msize; ++i) {
		tree[i].label = i;
	}

	memset(visited, 0, sizeof(visited));

	buildTree(root);

	memset(visited, 0, sizeof(visited));

	int ans = dfs(root);

	if (ans <= 1) printf("0\n");
	else printf("%d", 2 * ans - 2);

	return 0;

}