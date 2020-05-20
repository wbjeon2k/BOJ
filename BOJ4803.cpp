#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct disjointSet {
    vector<int> parent;
    vector<int> rank;
    vector<int> istree;

    disjointSet() {
        parent.resize(505);
        rank.resize(505, 1);
        istree.resize(505, 1);
        for (int i = 0; i < 505; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] == u) return u;

        return parent[u] = find(parent[u]);
    }

    bool merge(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v || !istree[u] || !istree[v]) {
            istree[u] = false;
            istree[v] = false;
        }

        if (rank[u] > rank[v]) swap(u, v);
        parent[v] = u;
        if (rank[u] == rank[v]) ++rank[v];
        return true;
    }

    int treecnt(int n) {
        int ret = 0;
        for (int i = 1; i <= n; ++i) {
            if (istree[find(i)]) {
                istree[find(i)] = false;
                ++ret;
            }
        }
        return ret;
    }
};

int N, M;
#define pii pair<int,int>

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin;
    //cin.open("input.txt");

    int cnt = 1;
    while (1) {
        cin >> N >> M;
        if (N == 0 && M == 0) break;

        disjointSet DJS;
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            if (a > b) swap(a, b);
            DJS.merge(a, b);
        }

        int ans = DJS.treecnt(N);

        if (ans == 0) {
            printf("Case %d: No trees.\n", cnt);
        }
        if (ans == 1) {
            printf("Case %d: There is one tree.\n", cnt);
        }
        if (ans > 1) {
            printf("Case %d: A forest of %d trees.\n", cnt, ans);
        }
        ++cnt;
    }

    return 0;
}
