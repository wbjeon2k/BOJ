#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 3030

struct disjointSet {
    vector<int> parent;
    vector<int> rank;

    disjointSet() {
        parent.resize(Msize);
        rank.resize(Msize, 1);
        for (int i = 0; i < Msize; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }

    int merge(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v) return 0;

        if (rank[u] > rank[v]) swap(u, v);

        parent[v] = u;
        if (rank[v] == rank[u]) ++rank[v];
        return 1;
    }
};

struct node {
    int x, y, r;
};

int T, N;
vector<node> input;

bool inRange(node a, node b) {
    int x = a.x - b.x;
    int y = a.y - b.y;
    return (x * x + y * y) <= (a.r + b.r)*(a.r + b.r);
}

#define pii pair<int,int>

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin;
    //cin.open("input.txt");

    cin >> T;

    while (T--) {
        input.clear();
        cin >> N;
        input.resize(N);

        map<pii, int> mp;

        for (int i = 0; i < N; ++i) {
            int x, y, r;
            cin >> x >> y >> r;
            input[i].x = x;
            input[i].y = y;
            input[i].r = r;
        }

        disjointSet DJS;
        int cnt = N;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j < N; ++j) {
                if (inRange(input[i], input[j])) {
                    cnt -= DJS.merge(i, j);
                }
            }
        }

        /*
        set<int> s;
        for (int i = 0; i < N; ++i) {
            int u = mp[{input[i].x, input[i].y}];
            s.insert(DJS.find(u));
        }
        */

        printf("%d\n", cnt);
    }

    return 0;
}
