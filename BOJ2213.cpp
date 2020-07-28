//BOJ2213

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 10010

struct Node {
	int label;
	vector<Node*> children;
};

Node nodelist[Msize];
bool visited[Msize];
int cache[Msize], weight[Msize];
vector<vector<int>>adjList(Msize);
vector<vector<int>>backtrack(Msize);
int N;

void bfs() {
	queue<int> q;
	q.push(1);
	visited[1] = true;

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		for (int i = 0; i < adjList[here].size(); ++i) {
			int there = adjList[here][i];
			if (!visited[there]) {
				nodelist[here].children.push_back(&nodelist[there]);
				visited[there] = true;
				q.push(there);
			}
		}
	}
}

template <typename T>
vector<T> vmerge(vector<T> a, vector<T> b) {
	vector<T> ret;
	ret = a;
	for (int i = 0; i < b.size(); ++i) {
		ret.push_back(b[i]);
	}

	return ret;
}

int dp(int n) {
	//printf("n%d\n", n);
	int& ret = cache[n];
	if (ret != -1) return ret;

	Node here = nodelist[n];
	if (here.children.size() == 0) {
		ret = weight[n];
		return ret;
	}

	vector<Node*> childchild;
	int tmp1 = 0, tmp2 = weight[n];

	for (int i = 0; i < here.children.size(); ++i) {
		Node* c = here.children[i];
		childchild = vmerge(childchild, c->children);
	}

	vector<int> track1, track2;
	track2.push_back(n);

	for (int i = 0; i < here.children.size(); ++i) {
		tmp1 += dp(here.children[i]->label);
		track1.push_back(here.children[i]->label);
	}

	for (int i = 0; i < childchild.size(); ++i) {
		tmp2 += dp(childchild[i]->label);
		track2.push_back(childchild[i]->label);
	}
	
	if (tmp1 > tmp2) {
		backtrack[n] = track1;
		ret = tmp1;
	}
	else {
		backtrack[n] = track2;
		ret = tmp2;
	}

	return ret;
}

vector<int> vertexlist;
void track(int n) {
	int chk = 0;

	if (backtrack[n].size() == 0) {
		vertexlist.push_back(n);
		return;
	}

	if (backtrack[n][0] == n) {
		vertexlist.push_back(n);
		chk = 1;
	}
	for (int i = chk; i < backtrack[n].size(); ++i) {
		track(backtrack[n][i]);
	}
}

int main(){

	for (int i = 0; i < Msize; ++i) {
		nodelist[i].label = i;
	}

	memset(visited, 0, sizeof(visited));
	memset(cache, -1, sizeof(cache));

	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> weight[i];
	}

	for (int i = 1; i < N; ++i) {
		int a, b;
		cin >> a >> b;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}

	bfs();

	int ans = dp(1);
	printf("%d\n", ans);

	track(1);
	sort(vertexlist.begin(), vertexlist.end());
	for (int i = 0; i < vertexlist.size(); ++i) {
		printf("%d ", vertexlist[i]);
	}

	return 0;
}

/*
//koosaga's solution.

#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

vector<int> graph[10005];
int n, a[10005];
int dp[10005][2];

vector<int> ans;

int f(int x, int pa, int u){
	if(~dp[x][u]) return dp[x][u];
	int ret = 0;
	if(u) ret += a[x];
	for (auto &i : graph[x]) {
		if(i == pa) continue;
		int p = f(i,x,0);
		if(u == 0) p = max(p,f(i,x,1));
		ret += p;
	}
	return dp[x][u] = ret;
}

void track(int x, int pa, int u){
	if(u) ans.push_back(x);
	for (auto &i : graph[x]){
		if(i == pa) continue;
		if(u == 0 && dp[i][0] < dp[i][1]){
			track(i,x,1);
		}
		else track(i,x,0);
	}
}

int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%d",&n);
	for (int i=1; i<=n; i++) {
		scanf("%d",&a[i]);
	}
	for (int i=0; i<n-1; i++) {
		int x,y;
		scanf("%d %d",&x,&y);
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	f(1,0,0);
	f(1,0,1);
	if(dp[1][0] > dp[1][1]){
		track(1,0,0);
		printf("%d\n",dp[1][0]);
		sort(ans.begin(),ans.end());
		for (int i=0; i<ans.size(); i++) {
			printf("%d ",ans[i]);
		}
	}
	else{
		track(1,0,1);
		printf("%d\n",dp[1][1]);
		sort(ans.begin(),ans.end());
		for (int i=0; i<ans.size(); i++) {
			printf("%d ",ans[i]);
		}
	}
}
*/