#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

int N, M;

#define Msize 40400
#define pii pair<int,int>
#define ll long long

int traverse[2 * Msize];
vector<int> traverseDepth(2 * Msize, INT_MAX);
int traverseLoc[Msize];
int parentNode[Msize];

vector<vector<pii>> adjList;
vector<vector<int>> tree;

bool visited[40400];

void bfstree() {
    queue<int> q;
    memset(visited, 0, sizeof(visited));
    q.push(0);

    while (!q.empty()) {
        int here = q.front();
        q.pop();
        visited[here] = true;

        for (int i = 0; i < adjList[here].size(); ++i) {
            int child = adjList[here][i].first;
            if (!visited[child]) {
                q.push(child);
                tree[here].push_back(child);
                parentNode[child] = here;
            }
        }
    }

    return;
}

int idx = 0;
void dfs(int here, int depth) {
    traverseLoc[here] = idx;
    traverse[idx] = here;
    traverseDepth[idx] = depth;
    ++idx;

    for (int i = 0; i < tree[here].size(); ++i) {
        int child = tree[here][i];
        dfs(child, depth + 1);
        traverse[idx] = here;
        traverseDepth[idx] = depth;
        ++idx;
    }
}

struct segtree {
    int n;
    vector<pii> stree;

    segtree(const vector<int>& a) {
        n = a.size();
        stree.resize(4 * n);
        init(a, 0, n - 1, 1);
    }

    pii init(const vector<int>& a, int left, int right, int node) {
        if (left == right) {
            stree[node] = { a[left], left };
            return stree[node];
        }

        int mid = (left + right) / 2;

        pii linit = init(a, left, mid, node * 2);
        pii rinit = init(a, mid + 1, right, node * 2 + 1);
        stree[node] = min(linit, rinit);
        return stree[node];
    }

    pii query(int left, int right, int node, int nodeLeft, int nodeRight) {
        if (left > nodeRight || right < nodeLeft) {
            return make_pair(INT_MAX, 0);
        }

        if (left <= nodeLeft && right >= nodeRight) {
            return stree[node];
        }

        int nodeMid = (nodeLeft + nodeRight) / 2;
        pii lquery = query(left, right, node * 2, nodeLeft, nodeMid);
        pii rquery = query(left, right, node * 2 + 1, nodeMid + 1, nodeRight);
        return min(lquery, rquery);
    }

    pii querycall(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }
};

ll distance(int s, int lca, ll dist) {
    if (s == lca) {
        return dist;
    }

    int parent = parentNode[s];

    for (int i = 0; i < adjList[s].size(); ++i) {
        if (adjList[s][i].first == parent) {
            return distance(parent, lca, dist + adjList[s][i].second);
        }
    }
}

int main()
{
    memset(traverse, 0, sizeof(traverse));
    memset(traverseLoc, 0, sizeof(traverseLoc));
    memset(parentNode, 0, sizeof(parentNode));

    adjList.resize(Msize);
    tree.resize(Msize);

    scanf("%d", &N);
    for (int i = 0; i < N-1; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adjList[a - 1].push_back({ b - 1,c });
        adjList[b - 1].push_back({ a - 1,c });
    }

    bfstree();
    dfs(0, 0);

    segtree S(traverseDepth);

    scanf("%d", &M);

    for (int i = 0; i < M; ++i) {
        int s, e;
        scanf("%d %d", &s, &e);

        int lu = traverseLoc[s - 1];
        int lv = traverseLoc[e - 1];

        if (lu > lv) swap(lu, lv);

        pii qlca = S.querycall(lu, lv);
        int lca = traverse[qlca.second];

        ll ldist = 0, rdist=0;
        ldist = distance(s-1, lca, 0);
        rdist = distance(e-1, lca, 0);

        printf("%lld\n", ldist + rdist);
    }

    return 0;
}

/*
//koosaga's solution.
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

int n;
vector<pi> graph[100005];
int depth[100005];
int pa[100005][17], sum[100005][17];

void dfs(int x, int p, int e, int d){
    if(x != 1){
        pa[x][0] = p;
        depth[x] = d;
        sum[x][0] = e;
        for (int i=1; (1<<i) <= d; i++) {
            pa[x][i] = pa[pa[x][i-1]][i-1];
            sum[x][i] = sum[pa[x][i-1]][i-1] + sum[x][i-1];
        }
    }
    for (int i=0; i<graph[x].size(); i++) {
        if(graph[x][i].second == p) continue;
        dfs(graph[x][i].second,x,graph[x][i].first,d+1);
    }
}

inline void query(int a, int b){
    int diff = depth[b] - depth[a];
    int sm = 0;
    for (int i=0; diff; i++) {
        if(diff&1){
            sm += sum[b][i];
            b = pa[b][i];
        }
        diff >>= 1;
    }
    for (int i=16; i>=0; i--) {
        if(pa[a][i] != pa[b][i]){
            sm += sum[a][i] + sum[b][i];
            a = pa[a][i];
            b = pa[b][i];
        }
    }
    if(a != b){
        sm += sum[a][0] + sum[b][0];
    }
    printf("%d\n",sm);
}

int main(){
    scanf("%d",&n);
    for (int i=0; i<n-1; i++) {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        graph[a].push_back(pi(c,b));
        graph[b].push_back(pi(c,a));
    }
    dfs(1,0,0,0);
    int q;
    scanf("%d",&q);
    while (q--) {
        int a,b;
        scanf("%d %d",&a,&b);
        if(depth[a] > depth[b]) swap(a,b);
        query(a,b);
    }
}
*/

/*
//topology's solution

#include <bits/stdc++.h>
#ifdef TOPOLOGY
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
using namespace std;

int n, par[40003][20], depth[40003], cost[40003];
vector<pair<int, int> > graph[40003];

void dfs(int node, int p) {
    par[node][0] = p;
    for (int i = 1; i < 20; i++) {
        par[node][i] = par[par[node][i - 1]][i - 1];
    }
    for (auto &nxt : graph[node]) {
        if (nxt.second == p) continue;
        depth[nxt.second] = depth[node] + 1;
        cost[nxt.second] = cost[node] + nxt.first;
        dfs(nxt.second, node);
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    int dif = depth[v] - depth[u];
    for (int i = 0; (1 << i) <= dif; i++) {
        if (dif & (1 << i)) v = par[v][i];
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if (par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        graph[u].push_back({c, v});
        graph[v].push_back({c, u});
    }
    dfs(1, 0);
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        int p = lca(u, v);
        printf("%d\n", cost[u] + cost[v] - 2 * cost[p]);
    }
    return 0;
}

*/

/* 
//cgiosy's solution.
#include <bits/stdc++.h>
#define N 40001
constexpr int LG=ceil(log2(N));
using namespace std;

int a[N][LG], b[N], d[N], n, m;
vector<pair<int, int>> g[N];
void dfs(int i) {
    for(auto[j, w] : g[i])
        if(!d[j]) {
            d[j]=d[i]+1; b[j]=b[i]+w;
            a[j][0]=i;
            for(int k=1; (1<<k)<d[j]; k++)
                a[j][k]=a[a[j][k-1]][k-1];
            dfs(j);
        }
}
int lca(int l, int r) {
    if(d[l]<d[r])
        swap(l, r);
    while(d[l]!=d[r])
        l=a[l][__builtin_ctz(d[l]-d[r])];
    if(l==r)
        return l;
    for(int i=LG; i--;)
        if(a[l][i]!=a[r][i])
            l=a[l][i], r=a[r][i];
    return a[l][0];
}
int dist(int l, int r) {
    return b[l]+b[r]-2*b[lca(l, r)];
}
int main() {
    scanf("%d", &n);
    for(int i=1; i<n; i++) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        g[x].push_back({y, w});
        g[y].push_back({x, w});
    }
    d[1]=1;
    dfs(1);

    scanf("%d", &m);
    for(int i=0; i<m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", dist(l, r));
    }
}
*/