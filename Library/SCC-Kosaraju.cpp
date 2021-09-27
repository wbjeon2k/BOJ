//https://www.acmicpc.net/problem/1648

#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define pii pair<int, int>
#define pll pair<ll, ll>
#define MAXI 1000000000
#define cplx complex<double>
#define MOD 9901
const double PI = acos(-1);
const ll INF = INT_MAX / 4;

#define MSIZE 10010
int visited[MSIZE + 1];
int x, y, r, v, e;
vector<vector<int>> scc;
vector<vector<int>> adjlist;
vector<vector<int>> rev_adjlist;
stack<int> st;
bool cmp(vector<int> x, vector<int> y) {
    return x[0] < y[0];
}
void dfs(int v) {
    visited[v] = true;
    for (int next : adjlist[v]) {
        if (visited[next])
            continue;
        dfs(next);
    }
    st.push(v);
}
void func(int v, int c) {
    visited[v] = true;
    scc[c].push_back(v);
    for (int next : rev_adjlist[v]) {
        if (visited[next])
            continue;
        func(next, c);
    }
}

void kosaraju(){
    for (int i = 1; i <= v; i++) {
        if (visited[i])
            continue;
        dfs(i);
    }
    memset(visited, 0, sizeof(visited));
    while (st.size()) {
        int here = st.top();
        st.pop();
        if (visited[here])
            continue;
        scc.push_back(vector<int>());
        ++r;
        func(here, r - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    //ifstream cin; cin.open("input.txt");

    scanf("%d%d", &v, &e);
    adjlist.resize(v + 1);
    rev_adjlist.resize(v + 1);
    for (int i = 0; i < e; i++) {
        scanf("%d%d", &x, &y);
        adjlist[x].push_back(y);
        rev_adjlist[y].push_back(x);
    }

    kosaraju();

    for (int i = 0; i < r; i++){
        sort(scc[i].begin(), scc[i].end());
    }
        
    sort(scc.begin(), scc.end(), cmp);
    printf("%d\n", r);
    for (int i = 0; i < r; i++) {
        for (int x : scc[i])
            printf("%d ", x);
        printf("-1\n");
    }

    return 0;
}
