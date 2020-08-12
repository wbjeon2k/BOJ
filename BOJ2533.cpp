//BOJ2533

//2nd trial. 시간 차이 없음

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 1001000

struct node
{
	int label;
	vector<node*> child;
};

int N;

vector<vector<int>> adjList(Msize), Tree(Msize);
node tree[Msize];
int cache[Msize][2];
bool visited[Msize];

void makeTree(int root) {
	visited[root] = true;

	for (int i = 0; i < adjList[root].size(); ++i) {
		int there = adjList[root][i];
		if (!visited[there]) {
			Tree[root].push_back(there);
			makeTree(there);
		}
	}
}

int dp(int node, int chk) {
	int& ret = cache[node][chk];
	if (ret != -1) return ret;

	if (Tree[node].size() == 0) {
		ret = chk;
		return ret;
	}

	if (chk) {
		ret = 1;
		for (int i = 0; i < Tree[node].size(); ++i) {
			ret += min(dp(Tree[node][i], 0), dp(Tree[node][i], 1));
		}
		return ret;
	}
	else {
		ret = 0;
		for (int i = 0; i < Tree[node].size(); ++i) {
			ret += dp(Tree[node][i], 1);
		}
		return ret;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i <= N; ++i) {
		tree[i].label = i;
	}
	memset(cache, -1, sizeof(cache));
	memset(visited, 0, sizeof(visited));

	for (int i = 0; i < N - 1; ++i) {
		int a, b;
		cin >> a >> b;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}

	makeTree(1);

	printf("%d", min(dp(1, 0), dp(1, 1)));

	return 0;

}

/*
//BOJ2533

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 1001000

struct node
{
	int label;
	vector<node*> child;
};

int N;

vector<vector<int>> adjList(Msize);
node tree[Msize];
int cache[Msize][2];
bool visited[Msize];

void makeTree(int root) {
	visited[root] = true;

	for (int i = 0; i < adjList[root].size(); ++i) {
		int there = adjList[root][i];
		if (!visited[there]) {
			tree[root].child.push_back(&tree[there]);
			makeTree(there);
		}
	}
}

int dp(int node, int chk) {
	int& ret = cache[node][chk];
	if (ret != -1) return ret;

	if (tree[node].child.size() == 0) {
		ret = chk;
		return ret;
	}

	if (chk) {
		ret = 1;
		for (int i = 0; i < tree[node].child.size(); ++i) {
			ret += min(dp(tree[node].child[i]->label, 0), dp(tree[node].child[i]->label, 1));
		}
		return ret;
	}
	else {
		ret = 0;
		for (int i = 0; i < tree[node].child.size(); ++i) {
			ret += dp(tree[node].child[i]->label, 1);
		}
		return ret;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	for (int i = 0; i <= N; ++i) {
		tree[i].label = i;
	}
	memset(cache, -1, sizeof(cache));
	memset(visited, 0, sizeof(visited));

	for (int i = 0; i < N - 1; ++i) {
		int a, b;
		cin >> a >> b;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}

	makeTree(1);

	printf("%d", min(dp(1, 0), dp(1, 1)));

	return 0;

}

*/