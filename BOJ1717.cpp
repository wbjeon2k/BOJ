#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct disjointSet {
    vector<int> rank;
    vector<int> parent;

    disjointSet() {
        rank.resize(1000001, 1);
        parent.resize(1000001);
        for (int i = 0; i < 1000001; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u == parent[u]) return u;

        return parent[u] = find(parent[u]);
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v) return;

        if (rank[u] > rank[v]) swap(u, v);
        parent[u] = v;
        if (rank[u] == rank[v]) ++rank[v];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin;
    //cin.open("input.txt");

    int N, M;
    cin >> N >> M;

    disjointSet DJS;

    for (int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;

        if (a) {
            if (DJS.find(b) == DJS.find(c)) {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }
        }
        else {
            DJS.merge(b, c);
        }
    }

    return 0;
}
