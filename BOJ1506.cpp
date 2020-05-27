#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

vector<int> sccid(111, -1), discovered(111, -1);
stack<int> st;
vector<vector<int>> sccList(111);

int sccCount, vertexCount;
int adjMat[111][111], cost[111];
int N;


int scc(int here) {
	discovered[here] = vertexCount;
	++vertexCount;
	int ret = discovered[here];
	st.push(here);

	for (int i = 1; i <= N; ++i) {
		bool chk = adjMat[here][i];
		int there = i;
		if (chk && discovered[there] == -1) {
			ret = min(ret, scc(there));
		}
		else if (chk && sccid[there] == -1 && here != there) {
			ret = min(ret, discovered[there]);
		}
	}

	if (ret == discovered[here]) {
		while (1) {
			int top = st.top();
			st.pop();
			sccid[top] = sccCount;
			sccList[sccCount].push_back(top);
			if (top == here) break;
		}

		++sccCount;
	}

	return ret;
}

void tarjan() {
	sccCount = 0;
	vertexCount = 0;

	for (int i = 1; i <= N; ++i) {
		if (discovered[i] == -1) scc(i);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	memset(adjMat, 0, sizeof(adjMat));
	memset(cost, 0, sizeof(cost));

	cin >> N;
	for (int i = 1; i <= N; ++i) {
		cin >> cost[i];
	}

	for (int i = 1; i <= N; ++i) {
		string s;
		cin >> s;
		for (int j = 1; j <= N; ++j) {
			adjMat[i][j] = s[j-1] - '0';
		}
	}

	tarjan();

	long long ans = 0;
	for (int i = 0; i < sccCount; ++i) {
		int tmp = INT_MAX;
		for (int j = 0; j < sccList[i].size(); ++j) {
			tmp = min(tmp, cost[sccList[i][j]]);
		}
		ans += tmp;
	}

	printf("%lld", ans);

	return 0;
}