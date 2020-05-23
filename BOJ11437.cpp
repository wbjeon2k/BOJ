#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#define Msize 100100

int traverseLoc[Msize];
int traverse[2*Msize];
vector<int> traverseDepth(Msize*2-2, INT_MAX - 100);
int idx = 0;

vector<vector<int>> tree;
vector<vector<int>> adjList;
int N, M;

void dfs(int here, int depth) {
    traverseLoc[here] = idx;
    traverse[idx] = here;
    traverseDepth[idx] = depth;
    ++idx;

    for (int i = 0; i < tree[here].size(); ++i) {
        int there = tree[here][i];
        dfs(there, depth + 1);
        traverse[idx] = here;
        traverseDepth[idx] = depth;
        ++idx;
    }

    return;
}

bool visited[Msize];

void makeTreebfs(int start) {
    queue<int> q;
    q.push(start);
    memset(visited, 0, sizeof(visited));

    while(!q.empty()) {
        int parent = q.front();
        q.pop();
        visited[parent] = true;
        for (int i = 0; i < adjList[parent].size(); ++i) {
            int child = adjList[parent][i];
            if (!visited[child]) {
                tree[parent].push_back(child);
                q.push(child);
            }
        }
    }
}

#define pii pair<int,int>

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
            stree[node] = make_pair( a[left], left );
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
            return { INT_MAX - 100, 0};
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

segtree* buildTree() {
    idx = 0;
    dfs(0, 0);
    return new segtree(traverseDepth);
}

void testTree() {
    for (int i = 0; i < tree.size(); ++i) {
        printf("%d ", i);
        for (int j = 0; j < tree[i].size(); ++j) {
            printf("%d ", tree[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    scanf("%d", &N);

    tree.resize(N + 1);
    adjList.resize(N + 1);

    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        adjList[a - 1].push_back(b - 1);
        adjList[b - 1].push_back(a - 1);
    }

    makeTreebfs(0);

    segtree* S = buildTree();

    scanf("%d", &M);
    
    /*
    testTree();
    */
    /*
    printf("\n");
    printf("\n");


    for (int i = 0; i < N; ++i) {
        printf("%d ", traverseLoc[i]);
    }
    printf("\n");

    for (int i = 0; i < 2 * N -2; ++i) {
        printf("%d %d %d\n",i, traverseDepth[i], traverse[i]);
    }
    
    printf("\n");

    */
    
    
    for (int i = 0; i < M; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        int lu = traverseLoc[a-1];
        int lv = traverseLoc[b-1];
        if (lu > lv) {
            int t = lu;
            lu = lv;
            lv = t;
        }
        pii lca = S->querycall(lu, lv);
        //printf("lca %d %d\n", lca.first, lca.second);
        //printf("lu lv %d %d\n", lu, lv);
        printf("%d\n", traverse[lca.second] + 1);
    }
    
    return 0;
    
}


/*
//djm03178's solution. usage of heavy light decomposition(HLD)
#include <bits/stdc++.h>
using namespace std;

vector<int> adj[100005];
int sz[100005], par[100005];

int dfs(int i, int p)
{
    par[i] = p;
    sz[i] = 1;
    for (int x : adj[i])
        if (x != p)
            sz[i] += dfs(x, i);
    return sz[i];
}

vector<int> chain[100005];
int depth[100005];
int chain_number[100005], chain_index[100005];

void HLD(int i, int p, int cur_chain, int d)
{
    depth[i] = d;
    chain_number[i] = cur_chain;
    chain_index[i] = chain[cur_chain].size();
    chain[cur_chain].push_back(i);

    int heavy = -1;
    for (int x : adj[i])
        if (x != p && (heavy == -1 || sz[x] > sz[heavy]))
            heavy = x;
    if (heavy != -1)
        HLD(heavy, i, cur_chain, d);
    for (int x : adj[i])
        if (x != p && x != heavy)
            HLD(x, i, x, d + 1);
}

int LCA(int a, int b)
{
    while (chain_number[a] != chain_number[b])
    {
        if (depth[a] > depth[b])
            a = par[chain_number[a]];
        else
            b = par[chain_number[b]];
    }
    return chain_index[a] > chain_index[b] ? b : a;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, i;
    cin >> n;
    for (i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);
    HLD(1, 0, 1, 0);
    cin >> m;
    while (m--)
    {
        int a, b;
        cin >> a >> b;
        cout << LCA(a, b) << '\n';
    }
}

*/