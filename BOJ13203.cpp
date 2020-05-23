#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

bool visited[2020];
int N, M;
vector<vector<int>> adjList(2020);

bool dfs(int here, int cnt) {
    visited[here] = true;

    if (cnt >= 4) {
        return true;
    }

    bool ret = false;
    for (int i = 0; i < adjList[here].size(); ++i) {
        int there = adjList[here][i];

        if (!visited[there]) {
            ret = dfs(there, cnt + 1);
            if (ret) return ret;
        }
    }
    visited[here] = false;// 실수하기 쉽다
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin;
    //cin.open("input.txt");

    cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    bool chk = false;
    for (int i = 0; i < N; ++i) {
        memset(visited, 0, sizeof(visited));
        if (dfs(i, 0)) {
            printf("1");
            chk = true;
            break;
        }
    }
    if (!chk) {
        printf("0");
    }

    return 0;
}
