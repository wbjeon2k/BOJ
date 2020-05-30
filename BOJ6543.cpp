#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adjList(5050);
vector<int> discovered(5050, -1), sccId(5050, -1), visited(5050, 0), sccSize(5050, 0);
stack<int> vstack;
int sccCount, vertexCount;

int scc(int here) {
	discovered[here] = vertexCount;
	vertexCount++;
	vstack.push(here);

	int ret = discovered[here];
	for (int i = 0; i < adjList[here].size(); ++i) {
		int there = adjList[here][i];
		if (discovered[there] == -1) {
			ret = min(ret, scc(there));
		}
		else if (sccId[there] == -1) {
			ret = min(ret, discovered[there]);
		}
	}

	if (discovered[here] == ret) {
		while (1) {
			int top = vstack.top();
			vstack.pop();
			sccId[top] = sccCount;
			sccSize[sccCount]++;
			if (top == here) break;
		}
		++sccCount;
	}

	return ret;
}

void tarjan(int n) {
	sccCount = 0;
	vertexCount = 0;

	for (int i = 1; i <= n; ++i) {
		if (discovered[i] == -1) scc(i);
	}
}

bool dfs(int here, int id) {
	//printf("here %d id %d\n", here, id);
	visited[here] = true;
	if (sccId[here] != id) return false;
	int ret = true;
	for (int i = 0; i < adjList[here].size(); ++i) {
		int there = adjList[here][i];
		if (!visited[there]) {
			ret = dfs(there, id);
			if (!ret) break;
		}
	}
	return ret;
}

int main() {
	//ifstream cin;
	//cin.open("input.txt");

	while (1) {
		int N, M;
		cin >> N;
		if (N == 0) break;
		cin >> M;

		adjList = vector<vector<int>>(5050);
		discovered = vector<int>(5050, -1);
		sccId = vector<int>(5050, -1);

		sccSize = vector<int>(5050, 0);
		vstack = stack<int>();

		for (int i = 0; i < M; ++i) {
			int a, b;
			cin >> a >> b;
			adjList[a].push_back(b);
		}

		tarjan(N);

		vector<int> bottom;

		vector<int> sccchk(5050, 0);
		for (int i = 1; i <= N; ++i) {
			int scchere = sccId[i];
			for (int j = 0; j < adjList[i].size(); ++j) {
				if (scchere != sccId[adjList[i][j]]) {
					sccchk[scchere] = true;
				}
			}
		}

		for (int i = 1; i <= N; ++i) {
			if (!sccchk[sccId[i]]) printf("%d ", i);
		}
		printf("\n");
	}

	return 0;
}
/*
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adjList(5050);
vector<int> discovered(5050, -1), sccId(5050, -1), visited(5050,0), sccSize(5050,0);
stack<int> vstack;
int sccCount, vertexCount;

int scc(int here) {
	discovered[here] = vertexCount;
	vertexCount++;
	vstack.push(here);

	int ret = discovered[here];
	for (int i = 0; i < adjList[here].size(); ++i) {
		int there = adjList[here][i];
		if (discovered[there] == -1) {
			ret = min(ret, scc(there));
		}
		else if (sccId[there] == -1) {
			ret = min(ret, discovered[there]);
		}
	}

	if (discovered[here] == ret) {
		while (1) {
			int top = vstack.top();
			vstack.pop();
			sccId[top] = sccCount;
			sccSize[sccCount]++;
			if (top == here) break;
		}
		++sccCount;
	}

	return ret;
}

void tarjan(int n) {
	sccCount = 0;
	vertexCount = 0;

	for (int i = 1; i <= n; ++i) {
		if (discovered[i] == -1) scc(i);
	}
}

bool dfs(int here, int id) {
	//printf("here %d id %d\n", here, id);
	visited[here] = true;
	if (sccId[here] != id) return false;
	int ret = true;
	for (int i = 0; i < adjList[here].size(); ++i) {
		int there = adjList[here][i];
		if (!visited[there]) {
			ret = dfs(there, id);
			if (!ret) break;
		}
	}
	return ret;
}

int main() {
	//ifstream cin;
	//cin.open("input.txt");

	while (1) {
		int N, M;
		cin >> N;
		if (N == 0) break;
		cin >> M;

		adjList = vector<vector<int>>(5050);
		discovered = vector<int>(5050, -1);
		sccId = vector<int>(5050, -1);
		
		sccSize = vector<int>(5050, 0);
		vstack = stack<int>();

		for (int i = 0; i < M; ++i) {
			int a, b;
			cin >> a >> b;
			adjList[a].push_back(b);
		}

		tarjan(N);

		vector<int> bottom;

		for (int i = 1; i <= N; ++i) {
			int scchere = sccId[i];
			visited = vector<int>(5050, 0);
			if (dfs(i, scchere)) bottom.push_back(i);
		}

		if (bottom.size() > 0) {
			for (int i = 0; i < bottom.size(); ++i) {
				printf("%d ", bottom[i]);
			}
			printf("\n");
		}
	}

	return 0;
}
*/

/*
//kks227's solution.
#include <cstdio>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

int V, E, SN, sn[5000], cnt, dfsn[5000];
bool finished[5000], sOut[5000];
vector<int> adj[5000];
stack<int> S;

int dfs(int curr){
	int result = dfsn[curr] = ++cnt;
	S.push(curr);
	for(int next: adj[curr]){
		if(finished[next]);
		else if(dfsn[next]) result = min(result, dfsn[next]);
		else result = min(result, dfs(next));
	}

	if(result == dfsn[curr]){
		while(1){
			int v = S.top();
			S.pop();
			sn[v] = SN;
			finished[v] = true;
			if(v == curr) break;
		}
		SN++;
	}
	return result;
}

int main(){
	while(1){
		scanf("%d", &V);
		if(V == 0) break;

		scanf("%d", &E);
		SN = cnt = 0;
		for(int i=0; i<V; i++){
			adj[i].clear();
			dfsn[i] = finished[i] = sOut[i] = 0;
		}
		for(int i=0; i<E; i++){
			int u, v;
			scanf("%d %d", &u, &v);
			adj[u-1].push_back(v-1);
		}

		for(int i=0; i<V; i++)
			if(dfsn[i] == 0) dfs(i);
		for(int i=0; i<V; i++)
			for(int j: adj[i])
				if(sn[i] != sn[j]) sOut[sn[i]] = true;
		for(int i=0; i<V; i++)
			if(!sOut[sn[i]]) printf("%d ", i+1);
		puts("");
	}
}
*/