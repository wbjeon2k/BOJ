#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

struct disjointSet {
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

    disjointSet() {
        parent.resize(1000001);
        size.resize(1000001, 1);
        for (int i = 0; i < 1000001; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u == parent[u]) return u;

        return parent[u] = find(parent[u]);
    }

    int merge(int s, int e) {
        int u, v;
        u = find(s);
        v = find(e);

        if (u == v) return size[u];

        parent[u] = v;
        size[v] += size[u];
        size[u] = 1;
        return size[v];
        //if (rank[u] == rank[v]) ++rank[v];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin;
    cin.open("input.txt");

    int T, F;
    cin >> T;

    while (T--) {
        disjointSet DJS;
        int F;
        cin >> F;
        map<string, int> names;
        int cnt = 1;
        while(F--) {
            string s1, s2;
            cin >> s1 >> s2;

            if (names.count(s1)== 0) {
                names[s1] = cnt;
                ++cnt;
            }
            if (names.count(s2) == 0) {
                names[s2] = cnt;
                ++cnt;
            }
            
            printf("%d\n", DJS.merge(names[s1], names[s2]));
        }
    }

    return 0;
}
